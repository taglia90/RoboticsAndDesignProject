


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

				  mossaGiustaSoffia();

				  posizioneAzione++;
			  }
			  break;
	}
		//bottoneGrande
	case 2:
	{
			  if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneManigliaPremuto() || scosso()) {
				  Serial.println("bottone grande sbagliati");
				  mossaSbagliata();
				  posizioneAzione = 0;
			  }
			  if (bottoneGrandePremuto()) {

				  Serial.println("Bottone grande OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK");
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
				  mossaGiustaScuoti();

				  posizioneAzione++;

			  }
			  break;
	}
		//bottoneManiglia
	case 4:
	{
			  if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneGrandePremuto() || scosso()) {
				  Serial.println("maniglia sbagliati");
				  mossaSbagliata();
				  posizioneAzione = 0;
			  }

			  if (bottoneManigliaPremuto()) {
				  Serial.println("Maniglia OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK");
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


	impostaColoreBottoni(verde, blu, rosso, giallo);
	delay(timeOutAzione / 20);
	impostaColoreBottoni(giallo, verde, blu, rosso);
	delay(timeOutAzione / 20);
	impostaColoreBottoni(rosso, giallo, verde, blu);
	delay(timeOutAzione / 20);

	spegniLed();


	switch (coloreDaScegliere) {

	case 0:
	{

			  if (modalitaScelta != 2)
				  playTrack(audioVerde);


			  switch (pulsanteDaScegliere) {


			  case 0:
			  {

						impostaColoreBottoni(verde, blu, rosso, giallo);

						break;
			  }
			  case 1:
			  {
						impostaColoreBottoni(giallo, verde, rosso, blu);

						break;
			  }
			  case 2:
			  {
						impostaColoreBottoni(rosso, giallo, verde, blu);

						break;
			  }
			  case 3:
			  {
						impostaColoreBottoni(rosso, giallo, blu, verde);

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
				  playTrack(audioBlu);

			  switch (pulsanteDaScegliere) {
			  case 0:
			  {
						impostaColoreBottoni(blu, giallo, rosso, verde);

						break;
			  }
			  case 1:
			  {
						impostaColoreBottoni(giallo, blu, verde, rosso);

						break;
			  }
			  case 2:
			  {
						impostaColoreBottoni(giallo, rosso, blu, verde);

						break;
			  }
			  case 3:
			  {
						impostaColoreBottoni(rosso, giallo, verde, blu);

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
				  playTrack(audioRosso);

			  switch (pulsanteDaScegliere) {
			  case 0:
			  {
						impostaColoreBottoni(rosso, giallo, verde, blu);

						break;
			  }
			  case 1:
			  {
						impostaColoreBottoni(giallo, rosso, verde, blu);

						break;
			  }
			  case 2:
			  {
						impostaColoreBottoni(giallo, blu, rosso, verde);

						break;
			  }
			  case 3:
			  {
						impostaColoreBottoni(giallo, verde, blu, rosso);

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
				  playTrack(audioGiallo);

			  switch (pulsanteDaScegliere) {
			  case 0:
			  {
						impostaColoreBottoni(giallo, rosso, verde, blu);

						break;
			  }
			  case 1:
			  {
						impostaColoreBottoni(blu, giallo, verde, rosso);

						break;
			  }
			  case 2:
			  {
						impostaColoreBottoni(verde, blu, giallo, rosso);

						break;
			  }
			  case 3:
			  {
						impostaColoreBottoni(verde, blu, rosso, giallo);


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


