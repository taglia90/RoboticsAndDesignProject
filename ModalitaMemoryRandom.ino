//Come la modalita' memory, solo che ogni volta le azioni sono diverse

//entro in questo loop quando viene scelta la modalita' memory random
void loopModalitaMemoryRandom()
{

	if (!primaMossa && inPartita)
	{
		//Serial.println("guardo tempoScaduto");
		tempoScadutoMemory();

	}

	// se non è ancora stata fatta un'azione
	if (!totaleAzioniFatto)
	{
		Serial.print("totaleAzioniFatto= ");
		Serial.println(totaleAzioniFatto);
		//leggo tutti gli input
		leggiInput();

		//controllo gli input
		controlloAzioniModalitaMemory();

	}

	//se non è la prima mossa guardo se il tempo è scaduto
	if (primaMossa && inPartita)
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





