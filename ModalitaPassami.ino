//Modalità multigiocatore Passami!!!!: ogni rand() di azioni bisogna passarlo al giocatore di colore ROSSO/VERDE/BLU

int azioniResidue = 0;
int vecchioGiocatore = -1;

//entro in questo loop quando viene scelta la modalita' passami
void loopModalitaPassami()
{

	if (giocatoriInPartita == 1){

		//controlloCondizioniVittoriaESpareggio();		//da usare se voglio guardare il punteggio, altrimenti:

		//annuncio il giocatore vincitore:
		if (coloreGiocatori[0] != 0){
			playTrack(AUDIO_VINCE);
			delay(3000);
			playTrack(AUDIO_VERDE);
			delay(2000);
			coloreGiocatori[0] = 0;
			giocatoriInPartita--;
		}
		else if (
			coloreGiocatori[1] != 0){
			playTrack(AUDIO_VINCE);
			delay(3000);
			playTrack(AUDIO_BLU);
			delay(2000);

			coloreGiocatori[1] = 0;
			giocatoriInPartita--;
		}
		else if (coloreGiocatori[2] != 0){
			playTrack(AUDIO_VINCE);
			delay(3000);
			playTrack(AUDIO_GIALLO);
			delay(2000);

			coloreGiocatori[2] = 0;
			giocatoriInPartita--;
		}
		else if (coloreGiocatori[3] != 0){
			playTrack(AUDIO_VINCE);
			delay(3000);
			playTrack(AUDIO_ROSSO);
			delay(2000);

			coloreGiocatori[3] = 0;
			giocatoriInPartita--;
		}

		inPartitaMultiplayer = false;
		resettaPartita();
		avviaSceltaGiocatori();
		return;


	}

	// se non è ancora stata fatta un'azione
	if (!azioneFatta)
	{
		//leggo tutti gli input
		leggiInput();

		//controllo gli input
		controlloAzioniPassami();
	}


	//se non è la prima mossa guardo se il tempo è scaduto

	if (primaMossa && inPartita)
	{

		primaMossa = false;
		timeOutAzione = 4000;
		giocatoreCorrente = -1;
		azioneFatta = true;
		azioniResidue = 0;
		//Serial.println("resett prima mossa");
	}

	if (azioneFatta && inPartita) {


		if (azioniResidue == 0 || giocatoreCorrente == -1)
		{
			cambiaGiocatoreModalitaPassami();
			//return;		//esco per controllare se è l'ultimo giocatore in partita
		}


		azioneFatta = false;
		scegliAzione();
		timeOutAzione -= (timeOutAzione * 0.1);

		if (timeOutAzione < 3000)
		{
			MP3player.setPlaySpeed(1);
			if (timeOutAzione < 2000)
			{
				MP3player.setPlaySpeed(2);
			}

			Serial.println("timeOutAzione= ");
			Serial.println(timeOutAzione);
		}

		azioniResidue--;

		switch (azioneDaEseguire) {
		case 0:
		{
				  pulsantiColorati();
				  break;
		}
		case 1:
		{
				  ventola();
				  break;
		}
		case 2:
		{
				  schiaccia();
				  break;
		}
		case 3:
		{
				  scuoti();
				  break;
		}

		case 4:
		{
				  gira();
				  break;
		}

		default:
		{
				   //non dovrei mai entrare, ma meglio metterlo per sicurezza.
				   break;
		}
		}

	}

	if (!primaMossa && inPartita)
	{
		tempoScaduto();//tempoScadutoPassami();

	}



}

//cambio giocatore e memorizzo quante azioni deve fare
void cambiaGiocatoreModalitaPassami(){
	//Serial.println("cambiaGiocatoreModalitaPassamiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii");
	timeOutAzione = 3000;
	MP3player.setPlaySpeed(1);
	azioniResidue = 3 + random(6);
	//Serial.print("Scelgo di fare N azioniResidue = ");
	//Serial.println(azioniResidue);

	vecchioGiocatore = giocatoreCorrente;


	giocatoreCorrente = random(4);

	//	Serial.print("Ho scelto il giocatore = ");
	//Serial.println(giocatoriInPartita);

	i = 0;		//variabile di controllo  per uscire dal ciclo while
	while ((coloreGiocatori[giocatoreCorrente] == 0 || vecchioGiocatore == giocatoreCorrente) && i < 10)
	{
		i++;
		giocatoreCorrente = random(4);
		Serial.print("riscelgo: ");
		Serial.println(giocatoreCorrente);

	}

	//punteggioGiocatori[giocatoreCorrente] = 0;


	/*	if (i == 10)	//vuol dire che è rimasto solo un giocatore che non ha fatto errori
	{
	//controlloCondizioniVittoriaESpareggio();		//da usare se voglio guardare il punteggio, altrimenti:

	//annuncio il giocatore vincitore:
	if (coloreGiocatori[0] != 0){
	playTrack(AUDIO_VINCE);
	delay(3000);
	playTrack(AUDIO_VERDE);
	delay(2000);
	coloreGiocatori[0] = 0;
	}
	else if (
	coloreGiocatori[1] != 0){
	playTrack(AUDIO_VINCE);
	delay(3000);
	playTrack(AUDIO_BLU);
	delay(2000);

	coloreGiocatori[1] = 0;
	}
	else if (coloreGiocatori[2] != 0){
	playTrack(AUDIO_VINCE);
	delay(3000);
	playTrack(AUDIO_GIALLO);
	delay(2000);

	coloreGiocatori[2] = 0;
	}
	else if (coloreGiocatori[3] != 0){
	playTrack(AUDIO_VINCE);
	delay(3000);
	playTrack(AUDIO_ROSSO);
	delay(2000);

	coloreGiocatori[3] = 0;
	}

	inPartitaMultiplayer = false;
	return;
	}*/

	switch (giocatoreCorrente){
	case 0:
	{
			  playTrack(AUDIO_PASSAMI_AL_VERDE);
			  delay(2000);
			  break;
	}
	case 1:
	{
			  playTrack(AUDIO_PASSAMI_AL_BLU);
			  delay(2000);
			  break;
	}
	case 2:
	{
			  playTrack(AUDIO_PASSAMI_AL_GIALLO);
			  delay(2000);
			  break;
	}
	case 3:
	{
			  playTrack(AUDIO_PASSAMI_AL_ROSSO);
			  delay(2000);
			  break;
	}
	default:
		break;
	}

	delay(timeOutAzione / 2);

}

//come controlloAzioni però con le variabili della modalita' passami
void controlloAzioniPassami() {
	switch (azioneDaEseguire) {

		//bottoni colorati
	case 0:
	{
			  if ((pulsanteDaScegliere == 0 && (bottonePremuto2 + bottonePremuto3 + bottonePremuto4 > 0))
				  || (pulsanteDaScegliere == 1 && (bottonePremuto1 + bottonePremuto3 + bottonePremuto4 > 0))
				  || (pulsanteDaScegliere == 2 && (bottonePremuto1 + bottonePremuto2 + bottonePremuto4 > 0))
				  || (pulsanteDaScegliere == 3 && (bottonePremuto1 + bottonePremuto2 + bottonePremuto3 > 0))
				  || bottoneManigliaPremuto()
				  || bottoneGrandePremuto()
				  || ventolaSoffiata()){
				  /* || scosso())*/
				  Serial.println("bottoni colorati sbagliati");
				  mossaSbagliataPassami();
			  }
			  if ((pulsanteDaScegliere == 0 && bottonePremuto1 == 1)
				  || (pulsanteDaScegliere == 1 && bottonePremuto2 == 1)
				  || (pulsanteDaScegliere == 2 && bottonePremuto3 == 1)
				  || (pulsanteDaScegliere == 3 && bottonePremuto4 == 1)) {

				  mossaGiustaColorati();
			  }
			  break;
	}
		//soffia
	case 1:
	{
			  if (bottoniColoratiPremuti() || bottoneGrandePremuto() || bottoneManigliaPremuto()) {
				  Serial.println("soffia sbagliati");

				  mossaSbagliataPassami();
			  }
			  if (ventolaSoffiata()) {
				  mossaGiustaSoffia();
			  }
			  break;
	}
		//BOTTONE_GRANDE
	case 2:
	{
			  if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneManigliaPremuto() /*|| scosso() */) {
				  Serial.println("bottone grande sbagliati");

				  mossaSbagliataPassami();
			  }
			  if (bottoneGrandePremuto()) {

				  mossaGiustaSchiaccia();
			  }
			  break;
	}
		//scuoti
	case 3:
	{
			  if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneManigliaPremuto() || bottoneGrandePremuto()) {
				  Serial.println("scuoti sbagliati");

				  mossaSbagliataPassami();
			  }
			  if (scosso()) {
				  mossaGiustaScuoti();

			  }
			  break;
	}
		//BOTTONE_MANIGLIA
	case 4:
	{
			  if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneGrandePremuto() /*|| scosso()*/) {
				  Serial.println("maniglia sbagliati");

				  mossaSbagliataPassami();
			  }

			  if (bottoneManigliaPremuto()) {
				  mossaGiustaManiglia();
			  }
			  break;
	}

	default:
	{
			   break;
	}

	}
}

