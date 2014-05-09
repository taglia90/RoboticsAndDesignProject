#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>
#include <AcceleroMMA7361.h>


AcceleroMMA7361 accelero;

// Below is not needed if interrupt driven. Safe to remove if not using.
#if defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_Timer1
#include <TimerOne.h>
#elif defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer
#include <SimpleTimer.h>
#endif

/**
 * \brief Object instancing the SdFat library.
 *
 * principal object for handling all SdCard functions.
 */
SdFat sd;

/**
 * \brief Object instancing the SFEMP3Shield library.
 *
 * principal object for handling all the attributes, members and functions for the library.
 */
uint16_t playspeed;
SFEMP3Shield MP3player;
//int playspeed=255;

int altoVentola;

//corrispondenze file audio
const int AUDIO_VERDE = 101;
const int AUDIO_ROSSO = 102;
const int AUDIO_BLU = 103;
const int AUDIO_GIALLO = 112;
const int AUDIO_SCUOTI = 104;
const int AUDIO_SBAAM = 105;
const int AUDIO_SCHIACCIA = 205;
const int AUDIO_GIRA = 106;
const int AUDIO_GIUSTO = 107;
const int AUDIO_SBAGLIATO = 108;
const int AUDIO_MUSICA = 109;
const int AUDIO_START = 110;
const int AUDIO_SOFFIA = 111;
const int AUDIO_SCEGLI_GIOCATORI = 113;
const int AUDIO_SCEGLI_MODALITA = 114;
const int AUDIO_MODALITA_SPEED = 115;
const int AUDIO_MODALITA_AUDIO = 116;          //manca
const int AUDIO_MODALITA_MEMORY = 117;
const int AUDIO_MODALITA_MEMORY_RANDOM = 118;
const int AUDIO_MODALITA_PASSAMI = 119;
const int AUDIO_PASSAMI_AL_BLU = 120;
const int AUDIO_PASSAMI_AL_GIALLO = 121;
const int AUDIO_PASSAMI_AL_ROSSO = 122;
const int AUDIO_PASSAMI_AL_VERDE = 123;
const int AUDIO_SPAREGGIO = 124;		//manca
const int AUDIO_VINCE = 125;			//manca

//led rgb 1
const int LED_ROSSO_1 = 24;
const int LED_VERDE_1 = 23;
const int LED_BLU_1 = 22;

//bottone rgb 1
const int BOTTONE_1 = 25;

//led rgb 2
const int LED_ROSSO_2 = 28;
const int LED_VERDE_2 = 27;
const int LED_BLU_2 = 26;

//bottone rgb 2
const int BOTTONE_2 = 33;

//led rgb 3
const int LED_ROSSO_3 = 32;
const int LED_VERDE_3 = 31;
const int LED_BLU_3 = 30;

//bottone rgb 3
const int BOTTONE_3 = 29;

//led rgb 4
const int LED_ROSSO_4 = 40;
const int LED_VERDE_4 = 39;
const int LED_BLU_4 = 38;

//bottone rgb 4
const int BOTTONE_4 = 37;

//led rgb pulsantone
const int LED_ROSSO_GRANDE_1 = 36;
const int LED_VERDE_GRANDE_1 = 35;
const int LED_BLU_GRANDE_1 = 34;

//bottone rgb pulsantone
const int BOTTONE_GRANDE = 41;

//led rgb maniglia
const int LED_ROSSO_MANIGLIA = 44;
const int LED_VERDE_MANIGLIA = 43;
const int LED_BLU_MANIGLIA = 42;

//bottone rgb maniglia
const int BOTTONE_MANIGLIA = 45;

//led punteggio
const int LED_PUNTEGGIO[6] = {
	21, 20, 19, 18, 17, 16 };

//ventola
const int PIN_VENTOLA_OUT = A13;
const int PIN_VENTOLA_IN = A12;
const int PIN_VIBRAZIONE = A11;
int intensitaVentola;
int limiteVelocitaVentola = 4;

//bottoni premuti
int bottonePremuto1;
int bottonePremuto2;
int bottonePremuto3;
int bottonePremuto4;
int bottonePremutoGrande;
int bottonePremutoManiglia;

//corrispondenza colori
const int VERDE = 1;
const int ROSSO = 2;
const int BLU = 3;
const int GIALLO = 4;

int buttonState = 0;

boolean azioneFatta = true;
int azioneDaEseguire = 0;
int vecchiaAzioneDaEseguire = 0;
int attesaNuovaAzione = 2000;
int attesaNuovaPartita = 2000;

int coloreDaScegliere;
int pulsanteDaScegliere;

int sommaAccelerazione;
int accelerazioneParziale = 0;
float inizioAccelerazione;
int accelerazioneIstantanea;
int vecchiaAccelerazioneIstantanea;
int limiteAccelerazione = 13000;
int timeOutAzione = 4000;

float inizioAzione;
int mosseGiuste = 0;
boolean inPartita = false;
boolean inPartitaMultiplayer = false;
boolean primaMossa = true;

//numero di giocatori in partita, inizialmente a 0
int giocatoriInPartita = 0;

int giocatoreCorrente = -1;
int punteggioGiocatoreCorrente = 0;
int punteggioMassimo = 0;

//vettore in cui una volta scelti i giocatori associo in ordine i colori scelti
//esempio con due giocatori di colore GIALLO e ROSSO il vettore e' del tipo [4 2 0 0]
int coloreGiocatori[4] = {
	0, 0, 0, 0 };

int punteggioGiocatori[4] = { -1, -1, -1, -1 };

//variabile a 0 inizialmente oppure assume i valori 1 2 3 4 5 a seconda della modalita
int modalitaScelta = 0;

//iteratori
int i;
int j = 0;
int k;

int mosseModalitaMemory[100][3];
int contaMosse = 0;

boolean totaleAzioniFatto = false;
int posizioneAzione = 0;


void setup() {

	fermaVibrazione();
	//Serial.begin(9600);
	Serial.begin(115200);

	inizializzaVentola();

	inizializzaLed();
	inizializzaBottoni();
	inizializzaMp3Shield();
	inizializzaAccelerometro();

	delay(2000);
	//mi metto in attesa che i giocatori schiaccino i tasti colorati
	avviaSceltaGiocatori();

}

void loop() {

	//if I don't detect players in the game:
	//finche' non e' stato premuto il pulsantone continuo a controllare l'input dei pulsanti colorati
	if (giocatoriInPartita <= 0)
	{
		aggiornaSceltaGiocatori();		//Updates player list
	}



	//if multiplayer (more than 1 player in game) && game not started && choosen mode != "Passami"
	//Se sono nella modalità multiplayer entro in questo IF per capire quale giocatore sta giocando
	if (giocatoriInPartita > 1 && !inPartita && modalitaScelta != 5){

		if (coloreGiocatori[0] != 0 && punteggioGiocatori[0] == -1){
			inPartitaMultiplayer = true;
			giocatoreCorrente = 0;
		}
		else if (coloreGiocatori[1] != 0 && punteggioGiocatori[1] == -1){
			inPartitaMultiplayer = true;
			giocatoreCorrente = 1;
		}
		else if (coloreGiocatori[2] != 0 && punteggioGiocatori[2] == -1){
			inPartitaMultiplayer = true;
			giocatoreCorrente = 2;
		}
		else if (coloreGiocatori[3] != 0 && punteggioGiocatori[3] == -1){
			inPartitaMultiplayer = true;
			giocatoreCorrente = 3;
		}
		else{
			controlloCondizioniVittoriaESpareggio();
		}


	}


	//se è il primo avvio o se non sono piu' in partita resetto modalita scelta a 0 (se viene premuto push ho in memoria la precedente)
	if (!inPartita && modalitaScelta != 0)
	{
		//resetto il timeOutAzione nel  caso fosse stato modificato dalla modalita' Speed o dalla modalita' audio
		timeOutAzione = 3000;

		if (!inPartitaMultiplayer){
			modalitaScelta = 0;
		}
		else avviaPartita();

	}

	//quando ho i giocatori in partita rilevo il cambiamento della modalita  
	if (giocatoriInPartita != 0 && modalitaScelta == 0)
	{
		scegliModalita();
	}

	//faccio partire la relativa modalità
	if (modalitaScelta == 1)
		loopModalitaSpeed();
	else if (modalitaScelta == 2)
		loopModalitaAudio();
	else if (modalitaScelta == 3)
		loopModalitaMemory();
	else if (modalitaScelta == 4)
		loopModalitaMemoryRandom();
	else if (modalitaScelta == 5)
		loopModalitaPassami();
}

//funzione che spegne tutti i led
void spegniLed() {

	digitalWrite(LED_ROSSO_MANIGLIA, HIGH);
	digitalWrite(LED_BLU_MANIGLIA, HIGH);
	digitalWrite(LED_VERDE_MANIGLIA, HIGH);
	digitalWrite(LED_ROSSO_GRANDE_1, HIGH);
	digitalWrite(LED_BLU_GRANDE_1, HIGH);
	digitalWrite(LED_VERDE_GRANDE_1, HIGH);

	digitalWrite(LED_ROSSO_4, HIGH);
	digitalWrite(LED_BLU_4, HIGH);
	digitalWrite(LED_VERDE_4, HIGH);
	digitalWrite(LED_ROSSO_3, HIGH);
	digitalWrite(LED_BLU_3, HIGH);
	digitalWrite(LED_VERDE_3, HIGH);
	digitalWrite(LED_ROSSO_2, HIGH);
	digitalWrite(LED_BLU_2, HIGH);
	digitalWrite(LED_VERDE_2, HIGH);
	digitalWrite(LED_ROSSO_1, HIGH);
	digitalWrite(LED_BLU_1, HIGH);
	digitalWrite(LED_VERDE_1, HIGH);
}

//funzione che viene invocata quando finisce una partita
void resettaPartita() {

	//Serial.println("resetto la partita.................");
	MP3player.setPlaySpeed(0);
	primaMossa = true;
	playTrack(AUDIO_MUSICA);
	accendiLedPunteggio();
	spegniLedPunteggio();
	delay(attesaNuovaPartita);

	mosseGiuste = 0;
	modalitaScelta = 0;
}

//funzione che viene invocata quando un giocatore finisce il suo turno nella modalita' multiplayer
void resettaPartitaMultiplayer() {

	//Serial.println("resetto la partita multiplayer.................");
	MP3player.setPlaySpeed(0);
	primaMossa = true;
	//playTrack(AUDIO_MUSICA);
	if (modalitaScelta != 5){
		accendiLedPunteggio();
		spegniLedPunteggio();
	}
	delay(attesaNuovaPartita);

	mosseGiuste = 0;
}

//funzione che accende i 6 led del punteggio
void accendiLedPunteggio()
{
	if (modalitaScelta == 3)
	{
		mosseGiuste = contaMosse;
	}

	Serial.println("mosse giuste = ");
	Serial.println(mosseGiuste);

	for (i = 0; i<2; i++)
	{
		if (mosseGiuste>((i + 1) * 3))
		{
			digitalWrite(LED_PUNTEGGIO[i], LOW);
			delay(1000);
		}
	}

	for (i = 3; i<6; i++)
	{
		if (mosseGiuste>((i + 1) * 3))
		{
			digitalWrite(LED_PUNTEGGIO[i], HIGH);
			delay(1000);
		}
	}
}

//funzione che spegne i 6 led del punteggio
void spegniLedPunteggio()
{
	for (i = 0; i < 2; i++)
	{
		digitalWrite(LED_PUNTEGGIO[i], HIGH);

	}
	for (i = 3; i < 6; i++)
	{
		digitalWrite(LED_PUNTEGGIO[i], LOW);

	}
}

//funzione che fa partire una determinata traccia audio
void playTrack(int track) {
	//if(!MP3player.isPlaying()) {


	MP3player.stopTrack();

	MP3player.playTrack(track);
	union twobyte mp3_vol; // create key_command existing variable that can be both word and double byte of left and right.
	mp3_vol.word = MP3player.getVolume(); // returns a double uint8_t of Left and Right packed into int16_t
	mp3_vol.byte[1] = 2;
	//mp3_vol.byte[1] = 30;

	// push byte[1] into both left and right assuming equal balance.
	MP3player.setVolume(mp3_vol.byte[1], mp3_vol.byte[1]); // commit new volume
	//}

}

//funzione invocata per selezionare un'azione da fare
void scegliAzione()
{

	//scelgo un'azione da eseguire diversa dalla precedente inizializzo la funzione rand con un valore casuale
	while (azioneDaEseguire == vecchiaAzioneDaEseguire) {
		randomSeed(analogRead(A14));
		azioneDaEseguire = random(5);

	}
	vecchiaAzioneDaEseguire = azioneDaEseguire;
	Serial.println("scelgo un'azione");
	inizioAzione = millis();

}

//funzione  che quando scade il tempo in cui si deve fare un'azione invoca la funzione mossaSbagliata()
void tempoScaduto() {
	if (((millis() - inizioAzione) > timeOutAzione)) {

		Serial.println("tempo scaduto con   ");
		Serial.print((millis() - inizioAzione));
		mossaSbagliata();
	}
}


/*void tempoScadutoPassami() {
	if (((millis() - inizioAzione) > timeOutAzione)) {

		Serial.println("tempo scaduto con   ");
		Serial.print((millis() - inizioAzione));
		mossaSbagliataPassami();
	}
}*/

//fuonzione che controlla chi vince o in caso di pareggio seleziona i concorrenti che giocheranno lo spareggio
void controlloCondizioniVittoriaESpareggio(){
	giocatoreCorrente = -1;

/*	Serial.println("\nStampa punteggi");
	Serial.println(punteggioGiocatori[0]);
	Serial.println(punteggioGiocatori[1]);
	Serial.println(punteggioGiocatori[2]);
	Serial.println(punteggioGiocatori[3]);*/

	//annuncio il vincitore
	if (punteggioGiocatori[0] > punteggioGiocatori[1] && punteggioGiocatori[0] > punteggioGiocatori[2] && punteggioGiocatori[0] > punteggioGiocatori[3]){
		inPartitaMultiplayer = false;
		if (modalitaScelta == 5){
			giocatoriInPartita--;
		}
		playTrack(AUDIO_VINCE);
		delay(3000);
		playTrack(AUDIO_VERDE);
		delay(2000);
	}
	else if (punteggioGiocatori[1] > punteggioGiocatori[0] && punteggioGiocatori[1] > punteggioGiocatori[2] && punteggioGiocatori[1] > punteggioGiocatori[3]){
		inPartitaMultiplayer = false;
		if (modalitaScelta == 5){
			giocatoriInPartita--;
		}
		playTrack(AUDIO_VINCE);
		delay(3000);
		playTrack(AUDIO_BLU);
		delay(2000);
	}
	else if (punteggioGiocatori[2] > punteggioGiocatori[0] && punteggioGiocatori[2] > punteggioGiocatori[1] && punteggioGiocatori[2] > punteggioGiocatori[3]){
		inPartitaMultiplayer = false;
		if (modalitaScelta == 5){
			giocatoriInPartita--;
		}
		playTrack(AUDIO_VINCE);
		delay(3000);
		playTrack(AUDIO_GIALLO);
		delay(2000);
	}
	else if (punteggioGiocatori[3] > punteggioGiocatori[0] && punteggioGiocatori[3] > punteggioGiocatori[1] && punteggioGiocatori[3] > punteggioGiocatori[2]){
		inPartitaMultiplayer = false;
		if (modalitaScelta == 5){
			giocatoriInPartita--;
		}
		playTrack(AUDIO_VINCE);
		delay(3000);
		playTrack(AUDIO_ROSSO);
		delay(2000);
	}
	else{//altrimenti spareggio
		playTrack(AUDIO_SPAREGGIO);
		giocatoriInPartita = 0;
		for (i = 0; i < 4; i++){
			coloreGiocatori[i] = 0;
			if (punteggioGiocatori[i]>punteggioMassimo)
				punteggioMassimo = punteggioGiocatori[i];
		}



		if (punteggioGiocatori[0] == punteggioMassimo){
			coloreGiocatori[0] = VERDE;
			giocatoriInPartita++;
		}
		if (punteggioGiocatori[1] == punteggioMassimo){
			coloreGiocatori[1] = BLU;
			giocatoriInPartita++;
		}
		if (punteggioGiocatori[2] == punteggioMassimo){
			coloreGiocatori[2] = GIALLO;
			giocatoriInPartita++;
		}
		if (punteggioGiocatori[3] == punteggioMassimo){
			coloreGiocatori[3] = ROSSO;
			giocatoriInPartita++;
		}


		delay(2000);
	}
	punteggioMassimo = 0;

	//Serial.println("resetto punteggiooooooooooooooooooooooooooooo");

	for (i = 0; i < 4; i++){
		punteggioGiocatori[i] = -1;
	}
}