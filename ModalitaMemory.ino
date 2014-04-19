//Modalità memory: Compiere diverse azioni una dopo l’altra senza che la voce le ripeta.
//Le azione sono del tipo 1 12 123 1234….

float timeOutAzioneMemory;

void loopModalitaMemory()
{

	if (!primaMossa && inPartita)
	{
		Serial.println("guardo tempoScaduto");
		tempoScadutoMemory();

	}

	// se non è ancora stata fatta un'azione
	if (!totaleAzioniFatto)
	{
		//leggo tutti gli input
		leggiInput();

		//controllo gli input
		controlloAzioniModalitaMemory();

	}

	//se non è la prima mossa guardo se il tempo è scaduto
	if (primaMossa)
	{

		if (giocatoriInPartita > 1){
			if (giocatoreCorrente == 0){
				playTrack(AUDIO_PASSAMI_AL_VERDE);
				delay(2000);
			}
			else if (giocatoreCorrente == 1){
				playTrack(AUDIO_PASSAMI_AL_BLU);
				delay(2000);
			}
			else if (giocatoreCorrente == 2){
				playTrack(AUDIO_PASSAMI_AL_GIALLO);
				delay(2000);
			}
			else if (giocatoreCorrente == 3){
				playTrack(AUDIO_PASSAMI_AL_ROSSO);
				delay(2000);
			}
		}




		//   inAttesaUtente=false;
		Serial.println("prima mossa");
		inizioAzione = millis();
		primaMossa = false;
		inizializzaArrayMemory();
		contaMosse = 0;
		timeOutAzione = 4000;
		totaleAzioniFatto = true;
		azioneFatta = true;

	}


	if (azioneFatta &&  totaleAzioniFatto) {

		Serial.println("creo azione");
		azioneFatta = false;
		totaleAzioniFatto = false;



		for (j = 0; j <= contaMosse; j++){   //cosi' faccio un ciclo in piu' di contaMosse
			Serial.println("j= ");
			Serial.println(j);


			if (mosseModalitaMemory[j][0] != -1){
				azioneDaEseguire = mosseModalitaMemory[j][0];
				if (azioneDaEseguire == 0){
					pulsanteDaScegliere = mosseModalitaMemory[j][1];
					coloreDaScegliere = mosseModalitaMemory[j][2];
				}

				//    Serial.println("mossa tipo: ");
				//  Serial.println(mosseModalitaMemory[j][0]);

				//  Serial.println("Conta mosse: ");
				//  Serial.println(contaMosse);

				//        Serial.println();
			}
			else{
				posizioneAzione = 0;
				scegliAzione();

				mosseModalitaMemory[j][0] = azioneDaEseguire;
				if (azioneDaEseguire == 0){
					mosseModalitaMemory[j][1] = pulsanteDaScegliere;
					mosseModalitaMemory[j][2] = coloreDaScegliere;
				}





				Serial.println("nuova azione: ");
				Serial.println(azioneDaEseguire);

				Serial.println("Conta mosse: ");
				Serial.println(contaMosse);
				Serial.println();
			}


			switch (azioneDaEseguire) {

			case 0:
			{
					  pulsantiColoratiMemory();
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
			delay(1000);
			spegniLed();


		}

		contaMosse++;

		timeOutAzioneMemory = timeOutAzione*contaMosse;
		timeOutAzione -= timeOutAzione*0.1;
		inizioAzione = millis();
		Serial.println("inizializzo inizio Azine");

	}


}

void inizializzaArrayMemory(){
	for (j = 0; j < 100; j++){
		for (k = 0; k < 3; k++){
			mosseModalitaMemory[j][k] = -1;
		}
	}
}

void  controlloAzioniModalitaMemory()
{


	switch (mosseModalitaMemory[posizioneAzione][0]) {

		//bottoni colorati
	case 0:
	{

			  pulsanteDaScegliere = mosseModalitaMemory[posizioneAzione][1];

			  if ((pulsanteDaScegliere == 0 && (bottonePremuto2 + bottonePremuto3 + bottonePremuto4 > 0))
				  || (pulsanteDaScegliere == 1 && (bottonePremuto1 + bottonePremuto3 + bottonePremuto4 > 0))
				  || (pulsanteDaScegliere == 2 && (bottonePremuto1 + bottonePremuto2 + bottonePremuto4 > 0))
				  || (pulsanteDaScegliere == 3 && (bottonePremuto1 + bottonePremuto2 + bottonePremuto3 > 0))
				  || bottoneManigliaPremuto()
				  || bottoneGrandePremuto()
				  || ventolaSoffiata()
				  || scosso()) {
				  Serial.println("bottoni colorati sbagliati");
				  mossaSbagliata();
				  posizioneAzione = 0;
			  }
			  if ((pulsanteDaScegliere == 0 && bottonePremuto1 == 1)
				  || (pulsanteDaScegliere == 1 && bottonePremuto2 == 1)
				  || (pulsanteDaScegliere == 2 && bottonePremuto3 == 1)
				  || (pulsanteDaScegliere == 3 && bottonePremuto4 == 1)) {

				  Serial.println("pulsante OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK");
				  ++punteggioGiocatori[giocatoreCorrente];
				  mossaGiustaColorati();


				  posizioneAzione++;
			  }
			  break;
	}
		//soffia
	case 1:
	{
			  if (bottoniColoratiPremuti() || bottoneGrandePremuto() || bottoneManigliaPremuto() || scosso()) {
				  Serial.println("soffia sbagliati");
				  mossaSbagliata();
				  //  totaleAzioniFatto
				  posizioneAzione = 0;
			  }
			  if (ventolaSoffiata()) {

				  Serial.println("Ventola OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK");
				  ++punteggioGiocatori[giocatoreCorrente];
				  mossaGiustaSoffia();

				  posizioneAzione++;
			  }
			  break;
	}
		//BOTTONE_GRANDE
	case 2:
	{
			  if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneManigliaPremuto() || scosso()) {
				  Serial.println("bottone grande sbagliati");
				  mossaSbagliata();
				  posizioneAzione = 0;
			  }
			  if (bottoneGrandePremuto()) {

				  Serial.println("Bottone grande OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK");
				  ++punteggioGiocatori[giocatoreCorrente];
				  mossaGiustaSchiaccia();

				  posizioneAzione++;
			  }
			  break;
	}
		//scuoti
	case 3:
	{
			  if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneManigliaPremuto() || bottoneGrandePremuto()) {
				  Serial.println("scuoti sbagliati");
				  mossaSbagliata();
				  posizioneAzione = 0;
			  }
			  if (scosso()) {

				  Serial.println("Scosso OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK");
				  ++punteggioGiocatori[giocatoreCorrente];
				  mossaGiustaScuoti();

				  posizioneAzione++;

			  }
			  break;
	}
		//BOTTONE_MANIGLIA
	case 4:
	{
			  if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneGrandePremuto() || scosso()) {
				  Serial.println("maniglia sbagliati");
				  mossaSbagliata();
				  posizioneAzione = 0;
			  }

			  if (bottoneManigliaPremuto()) {
				  Serial.println("Maniglia OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK");
				  ++punteggioGiocatori[giocatoreCorrente];
				  mossaGiustaManiglia();

				  posizioneAzione++;
			  }
			  break;
	}

	default:
	{
			   break;
	}
	}


	if (mosseModalitaMemory[posizioneAzione][0] == -1 && azioneFatta){
		Serial.println("ENTRO IFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");

		totaleAzioniFatto = true;
	}

}

void tempoScadutoMemory()
{

	if (((millis() - inizioAzione) > timeOutAzioneMemory)) {

		Serial.println("tempo scaduto con   ");
		Serial.print((millis() - inizioAzione));
		mossaSbagliata();
	}

}

void pulsantiColoratiMemory() {


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


