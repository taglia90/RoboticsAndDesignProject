

//decido un pulsante che si deve illuminare di un colore casuale tra i 4
void pulsantiColorati() {

	coloreDaScegliere = random(4); //scelgo un colore
	pulsanteDaScegliere = random(4); //scelgo un pulsante

	impostaColoreBottoni(VERDE, BLU, ROSSO, GIALLO);
	delay(timeOutAzione / 20);
	impostaColoreBottoni(GIALLO, VERDE, BLU, ROSSO);
	delay(timeOutAzione / 20);
	impostaColoreBottoni(ROSSO, GIALLO, VERDE, BLU);
	delay(timeOutAzione / 20);

	spegniLed();


	switch (coloreDaScegliere) {

	case 0:
	{

			  if (modalitaScelta != 2)
				  playTrack(AUDIO_VERDE);


			  switch (pulsanteDaScegliere) {


			  case 0:
			  {

						impostaColoreBottoni(VERDE, BLU, ROSSO, GIALLO);

						break;
			  }
			  case 1:
			  {
						impostaColoreBottoni(GIALLO, VERDE, ROSSO, BLU);

						break;
			  }
			  case 2:
			  {
						impostaColoreBottoni(ROSSO, GIALLO, VERDE, BLU);

						break;
			  }
			  case 3:
			  {
						impostaColoreBottoni(ROSSO, GIALLO, BLU, VERDE);

						break;
			  }

			  default:
				  break;
			  }
			  break;

	}
	case 1:
	{

			  if (modalitaScelta != 2)
				  playTrack(AUDIO_BLU);

			  switch (pulsanteDaScegliere) {
			  case 0:
			  {
						impostaColoreBottoni(BLU, GIALLO, ROSSO, VERDE);

						break;
			  }
			  case 1:
			  {
						impostaColoreBottoni(GIALLO, BLU, VERDE, ROSSO);

						break;
			  }
			  case 2:
			  {
						impostaColoreBottoni(GIALLO, ROSSO, BLU, VERDE);

						break;
			  }
			  case 3:
			  {
						impostaColoreBottoni(ROSSO, GIALLO, VERDE, BLU);

						break;
			  }


			  default:
				  break;
			  }
			  break;
	}
	case 2:
	{
			  if (modalitaScelta != 2)
				  playTrack(AUDIO_ROSSO);

			  switch (pulsanteDaScegliere) {
			  case 0:
			  {
						impostaColoreBottoni(ROSSO, GIALLO, VERDE, BLU);

						break;
			  }
			  case 1:
			  {
						impostaColoreBottoni(GIALLO, ROSSO, VERDE, BLU);

						break;
			  }
			  case 2:
			  {
						impostaColoreBottoni(GIALLO, BLU, ROSSO, VERDE);

						break;
			  }
			  case 3:
			  {
						impostaColoreBottoni(GIALLO, VERDE, BLU, ROSSO);

						break;
			  }

			  default:
				  break;
			  }
			  break;

	}

	case 3:
	{
			  if (modalitaScelta != 2)
				  playTrack(AUDIO_GIALLO);

			  switch (pulsanteDaScegliere) {
			  case 0:
			  {
						impostaColoreBottoni(GIALLO, ROSSO, VERDE, BLU);

						break;
			  }
			  case 1:
			  {
						impostaColoreBottoni(BLU, GIALLO, VERDE, ROSSO);

						break;
			  }
			  case 2:
			  {
						impostaColoreBottoni(VERDE, BLU, GIALLO, ROSSO);

						break;
			  }
			  case 3:
			  {
						impostaColoreBottoni(VERDE, BLU, ROSSO, GIALLO);


						break;
			  }

			  default:
				  break;

			  }

			  break;
	}
	default:
		break;
	}

}

//riceve in input 4 colori e li associa ai pulsanti corrispondenti 
void impostaColoreBottoni(int ledColore1, int ledColore2, int ledColore3, int ledColore4)
{
	spegniLed();

	if (ledColore1 == VERDE)
	{
		digitalWrite(LED_VERDE_1, LOW);
	}

	if (ledColore1 == ROSSO)
	{
		digitalWrite(LED_ROSSO_1, LOW);
	}

	if (ledColore1 == BLU)
	{
		digitalWrite(LED_BLU_1, LOW);
	}

	if (ledColore1 == GIALLO)
	{
		digitalWrite(LED_VERDE_1, LOW);
		digitalWrite(LED_ROSSO_1, LOW);

	}

	if (ledColore2 == VERDE)
	{
		digitalWrite(LED_VERDE_2, LOW);
	}

	if (ledColore2 == ROSSO)
	{
		digitalWrite(LED_ROSSO_2, LOW);
	}

	if (ledColore2 == BLU)
	{
		digitalWrite(LED_BLU_2, LOW);
	}

	if (ledColore2 == GIALLO)
	{
		digitalWrite(LED_VERDE_2, LOW);
		digitalWrite(LED_ROSSO_2, LOW);

	}
	if (ledColore3 == VERDE)
	{
		digitalWrite(LED_VERDE_3, LOW);
	}

	if (ledColore3 == ROSSO)
	{
		digitalWrite(LED_ROSSO_3, LOW);
	}

	if (ledColore3 == BLU)
	{
		digitalWrite(LED_BLU_3, LOW);
	}

	if (ledColore3 == GIALLO)
	{
		digitalWrite(LED_VERDE_3, LOW);
		digitalWrite(LED_ROSSO_3, LOW);

	}
	if (ledColore4 == VERDE)
	{
		digitalWrite(LED_VERDE_4, LOW);
	}

	if (ledColore4 == ROSSO)
	{
		digitalWrite(LED_ROSSO_4, LOW);
	}

	if (ledColore4 == BLU)
	{
		digitalWrite(LED_BLU_4, LOW);
	}

	if (ledColore4 == GIALLO)
	{
		digitalWrite(LED_VERDE_4, LOW);
		digitalWrite(LED_ROSSO_4, LOW);

	}


}

void ventola() {
	playTrack(AUDIO_SOFFIA);
}

void scuoti() {
	playTrack(AUDIO_SCUOTI);
}

void schiaccia() {

	digitalWrite(LED_BLU_GRANDE_1, LOW);

	playTrack(AUDIO_SCHIACCIA);
}

void gira(){
	digitalWrite(LED_BLU_MANIGLIA, LOW);

	playTrack(AUDIO_GIRA);

}


void controlloAzioni() {
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
				  mossaSbagliata();
			  }
			  if ((pulsanteDaScegliere == 0 && bottonePremuto1 == 1)
				  || (pulsanteDaScegliere == 1 && bottonePremuto2 == 1)
				  || (pulsanteDaScegliere == 2 && bottonePremuto3 == 1)
				  || (pulsanteDaScegliere == 3 && bottonePremuto4 == 1)) {

				  //	  ++punteggioGiocatori[giocatoreCorrente-1];
				  mossaGiustaColorati();


			  }
			  break;
	}
		//soffia
	case 1:
	{
			  if (bottoniColoratiPremuti() || bottoneGrandePremuto() || bottoneManigliaPremuto()) {
				  Serial.println("soffia sbagliati");

				  mossaSbagliata();
			  }
			  if (ventolaSoffiata()) {
				  //	  punteggioGiocatori[giocatoreCorrente-1] = punteggioGiocatori[giocatoreCorrente-1] + 1;
				  mossaGiustaSoffia();
			  }
			  break;
	}
		//BOTTONE_GRANDE
	case 2:
	{
			  if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneManigliaPremuto() /*|| scosso() */) {
				  Serial.println("bottone grande sbagliati");

				  mossaSbagliata();
			  }
			  if (bottoneGrandePremuto()) {

				  //  punteggioGiocatori[giocatoreCorrente-1] = punteggioGiocatori[giocatoreCorrente-1] + 1;

				  mossaGiustaSchiaccia();
			  }
			  break;
	}
		//scuoti
	case 3:
	{
			  if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneManigliaPremuto() || bottoneGrandePremuto()) {
				  Serial.println("scuoti sbagliati");

				  mossaSbagliata();
			  }
			  if (scosso()) {
				  //  punteggioGiocatori[giocatoreCorrente - 1] = punteggioGiocatori[giocatoreCorrente - 1] + 1;
				  mossaGiustaScuoti();

			  }
			  break;
	}
		//BOTTONE_MANIGLIA
	case 4:
	{
			  if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneGrandePremuto() /*|| scosso()*/) {
				  Serial.println("maniglia sbagliati");

				  mossaSbagliata();
			  }

			  if (bottoneManigliaPremuto()) {
				  //	  punteggioGiocatori[giocatoreCorrente - 1] = punteggioGiocatori[giocatoreCorrente - 1] + 1;
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

void resettaAccelerometro() {
	accelerazioneParziale = 0;
	inizioAccelerazione = millis();
	sommaAccelerazione = 0;
}

void mossaGiustaColorati() {

	playTrack(AUDIO_GIUSTO);
	spegniLed();
	int ledDaIlluminare;
	switch (pulsanteDaScegliere) {
	case 0:
	{
			  ledDaIlluminare = LED_VERDE_1;
			  break;
	}
	case 1:
	{
			  ledDaIlluminare = LED_VERDE_2;
			  break;
	}
	case 2:
	{
			  ledDaIlluminare = LED_VERDE_3;
			  break;
	}
	case 3:
	{
			  ledDaIlluminare = LED_VERDE_4;
			  break;
	}

	default:
		break;


	}

	digitalWrite(ledDaIlluminare, LOW);
	delay(attesaNuovaAzione / 10);
	digitalWrite(ledDaIlluminare, HIGH);
	delay(attesaNuovaAzione / 10);
	digitalWrite(ledDaIlluminare, LOW);
	delay(attesaNuovaAzione / 10);
	digitalWrite(ledDaIlluminare, HIGH);


	resettaAccelerometro();

	// if(modalitaScelta != 3)
	azioneFatta = true;
	mosseGiuste++;

	return;
}

void mossaGiustaScuoti() {
	playTrack(AUDIO_GIUSTO);
	spegniLed();
	delay(attesaNuovaAzione / 3);
	resettaAccelerometro();
	//  if(modalitaScelta != 3)
	azioneFatta = true;
	mosseGiuste++;

	return;
}

void mossaGiustaManiglia() {

	playTrack(AUDIO_GIUSTO);
	spegniLed();

	digitalWrite(LED_VERDE_MANIGLIA, LOW);
	delay(attesaNuovaAzione / 10);
	digitalWrite(LED_VERDE_MANIGLIA, HIGH);
	delay(attesaNuovaAzione / 10);
	digitalWrite(LED_VERDE_MANIGLIA, LOW);
	delay(attesaNuovaAzione / 10);
	digitalWrite(LED_VERDE_MANIGLIA, HIGH);


	azioneFatta = true;
	mosseGiuste++;
	resettaAccelerometro();
	// if(modalitaScelta != 3)


	return;
}

void mossaGiustaSoffia() {
	playTrack(AUDIO_GIUSTO);
	spegniLed();
	analogWrite(PIN_VENTOLA_OUT, 255);
	delay(attesaNuovaAzione / 3);
	analogWrite(PIN_VENTOLA_OUT, 0);
	resettaAccelerometro();
	// if(modalitaScelta != 3)
	azioneFatta = true;
	mosseGiuste++;

	return;
}

void mossaGiustaSchiaccia() {
	playTrack(AUDIO_SBAAM);
	spegniLed();
	digitalWrite(LED_VERDE_GRANDE_1, LOW);
	delay(attesaNuovaAzione / 10);
	digitalWrite(LED_VERDE_GRANDE_1, HIGH);
	delay(attesaNuovaAzione / 10);
	digitalWrite(LED_VERDE_GRANDE_1, LOW);
	delay(attesaNuovaAzione / 10);
	digitalWrite(LED_VERDE_GRANDE_1, HIGH);





	resettaAccelerometro();
	//  if(modalitaScelta != 3)
	azioneFatta = true;
	mosseGiuste++;

	return;
}

void mossaSbagliata() {

	if (giocatoriInPartita > 1){
		punteggioGiocatori[giocatoreCorrente] = mosseGiuste;
	}

	inPartita = false;
	playTrack(AUDIO_SBAGLIATO);
	spegniLed();
	accendiLedRosso();
	avviaVibrazione();
	delay(1000);
	spegniLed();
	fermaVibrazione();
	resettaAccelerometro();
	azioneFatta = true;

	//if (giocatoreCorrente == giocatoriInPartita - 1)
		resettaPartita();
	//else resettaPartitaMultiplayer();


	return;
}

void accendiLedRosso()
{
	digitalWrite(LED_ROSSO_1, LOW);
	digitalWrite(LED_ROSSO_2, LOW);
	digitalWrite(LED_ROSSO_3, LOW);
	digitalWrite(LED_ROSSO_4, LOW);
	digitalWrite(LED_ROSSO_GRANDE_1, LOW);
	digitalWrite(LED_ROSSO_MANIGLIA, LOW);
}

void avviaVibrazione()
{
	analogWrite(PIN_VIBRAZIONE, 255);
}

void fermaVibrazione()
{
	analogWrite(PIN_VIBRAZIONE, 0);

}





