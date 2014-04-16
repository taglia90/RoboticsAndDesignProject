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
const int audioVerde = 101;
const int audioRosso = 102;
const int audioBlu = 103;
const int audioGiallo = 112;
const int audioScuoti = 104;
const int audioSbaam = 105;
const int audioSchiaccia = 205;
const int audioGira = 106;
const int audioGiusto = 107;
const int audioSbagliato = 108;
const int audioMusica = 109;
const int audioStart = 110;
const int audioSoffia = 111;
const int audioScegliGiocatori = 113;
const int audioScegliModalita = 114;

const int audioModalitaSpeed = 115;
const int audioModalitaAudio = 116;          //manca
const int audioModalitaMemory = 117;
const int audioModalitaMemoryRandom = 118;
const int audioModalitaPassami = 119;

const int audioPassamiAlBlu = 120;
const int audioPassamiAlGiallo = 121;
const int audioPassamiAlRosso = 122;
const int audioPassamiAlVerde = 123;


//led rgb 1
const int ledRosso1 = 22;
const int ledBlu1 = 24;
const int ledVerde1 = 23;

//bottone rgb 1
const int bottone1 = 25;

//led rgb 2
const int ledRosso2 = 26;
const int ledBlu2 = 28;
const int ledVerde2 = 27;

//bottone rgb 2
const int bottone2 = 29;

//led rgb 3
const int ledRosso3 = 30;
const int ledBlu3 = 32;
const int ledVerde3 = 31;

//bottone rgb 3
const int bottone3 = 33;

//led rgb 4
const int ledRosso4 = 34;
const int ledBlu4 = 36;
const int ledVerde4 = 35;

//bottone rgb 4
const int bottone4 = 37;

//led rgb sbaaaaaaaaam
const int ledRossoGrande1 = 38;
const int ledBluGrande1 = 39;
const int ledVerdeGrande1 = 40;

//bottone rgb sbaaaaam
const int bottoneGrande = 41;

//led rgb maniglia
const int ledRossoManiglia = 42;
const int ledBluManiglia = 43;
const int ledVerdeManiglia = 44;

//bottone rgb maniglia
const int bottoneManiglia = 45;



const int ledPunteggio[6] = {
	16, 17, 18, 19, 20, 21 };





const int pinVentolaOut = A13;
const int pinVentolaIn = A12;
const int pinVibrazione = A11;
int intensitaVentola;
int limiteVelocitaVentola = 30;

int bottonePremuto1;
int bottonePremuto2;
int bottonePremuto3;
int bottonePremuto4;
int bottonePremutoGrande;
int bottonePremutoManiglia;


const int verde = 1;
const int rosso = 2;
const int blu = 3;
const int giallo = 4;

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
int limiteAccelerazione = 2500;
int timeOutAzione = 4000;

float inizioAzione;
boolean inPartita = false;
int mosseGiuste = 0;
boolean primaMossa = true;


//numero di giocatori in partita, inizialmente a 0
int giocatoriInPartita = 0;

//vettore in cui una volta scelti i giocatori associo in ordine i colori scelti, dove  verde=1, rosso=2, blu=3, giallo=4
//esempio con due giocatori di colore giallo e rosso il vettore e' del tipo [4 2 0 0]
int coloreGiocatori[4] = {
	0, 0, 0, 0 };

//variabile a 0 inizialmente oppure assume i valori 1 2 3 4 5 a seconda della modalita
int modalitaScelta = 0;

int i;
int j = 0;
int k;

int mosseModalitaMemory[100][3];
int contaMosse = 0;

boolean totaleAzioniFatto = false;
int posizioneAzione = 0;


void setup() {

	fermaVibrazione();
	Serial.begin(9600);

	inizializzaVentola();

	inizializzaLed();
	inizializzaBottoni();
	inizializzaMp3Shield();
	inizializzaAccelerometro();


	playTrack(audioStart);
	delay(2000);
	//mi metto in attesa che i giocatori schiaccino i tasti colorati
	avviaSceltaGiocatori();

}

void loop() {


	//se non sono piu' in partita resetto modalita scelta a 0 (se viene premuto push ho in memoria la precedente)
	if (!inPartita&&modalitaScelta != 0)
	{
		modalitaScelta = 0;

		//resetto il timeOutAzione nel  caso fosse stato modificato dalla modalita' Speed o dalla modalita' audio
		timeOutAzione = 3000;
	}


	//finche' non e' stato premuto il pulsante push continuo a controllare l'input dei pulsanti colorati
	if (giocatoriInPartita == 0)
	{
		aggiornaSceltaGiocatori();
	}

	//quando ho i giocatori in partita rilevo il cambiamento della modalita  
	if (giocatoriInPartita != 0 && modalitaScelta == 0)
	{
		scegliModalita();
	}


	//se non è la prima mossa guardo se il tempo è scaduto


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



void spegniLed() {


	digitalWrite(ledRossoManiglia, HIGH);
	digitalWrite(ledBluManiglia, HIGH);
	digitalWrite(ledVerdeManiglia, HIGH);
	digitalWrite(ledRossoGrande1, HIGH);
	digitalWrite(ledBluGrande1, HIGH);
	digitalWrite(ledVerdeGrande1, HIGH);

	digitalWrite(ledRosso4, HIGH);
	digitalWrite(ledBlu4, HIGH);
	digitalWrite(ledVerde4, HIGH);

	digitalWrite(ledRosso3, HIGH);
	digitalWrite(ledBlu3, HIGH);
	digitalWrite(ledVerde3, HIGH);
	digitalWrite(ledRosso2, HIGH);
	digitalWrite(ledBlu2, HIGH);
	digitalWrite(ledVerde2, HIGH);
	digitalWrite(ledRosso1, HIGH);
	digitalWrite(ledBlu1, HIGH);
	digitalWrite(ledVerde1, HIGH);
}


void resettaPartita() {


	Serial.println("resetto la partita.................");
	MP3player.setPlaySpeed(0);
	primaMossa = true;
	playTrack(audioMusica);
	accendiLedPunteggio();
	spegniLedPunteggio();
	playTrack(audioStart);
	delay(attesaNuovaPartita);

	mosseGiuste = 0;
	modalitaScelta = 0;
}

void accendiLedPunteggio()
{
	for (i = 0; i<6; i++)
	{
		if (mosseGiuste>((i + 1) * 3))
		{
			digitalWrite(ledPunteggio[i], HIGH);
			delay(1000);
		}
	}

}



void spegniLedPunteggio()
{
	for (i = 0; i < 6; i++)
	{
		digitalWrite(ledPunteggio[i], LOW);

	}
}





void playTrack(int track) {
	//if(!MP3player.isPlaying()) {
	MP3player.playTrack(track);
	union twobyte mp3_vol; // create key_command existing variable that can be both word and double byte of left and right.
	mp3_vol.word = MP3player.getVolume(); // returns a double uint8_t of Left and Right packed into int16_t
	mp3_vol.byte[1] = 2;
	//mp3_vol.byte[1] = 30;

	// push byte[1] into both left and right assuming equal balance.
	MP3player.setVolume(mp3_vol.byte[1], mp3_vol.byte[1]); // commit new volume
	//}

}

void scegliAzione()
{

	//scelgo un'azione da eseguire diversa dalla precedente inizializzo la funzione rand con un valore casuale
	while (azioneDaEseguire == vecchiaAzioneDaEseguire) {
		randomSeed(analogRead(A14));
		azioneDaEseguire = random(5);


	}
	vecchiaAzioneDaEseguire = azioneDaEseguire;
	Serial.println("sgelgo una azione");
	inizioAzione = millis();

}







