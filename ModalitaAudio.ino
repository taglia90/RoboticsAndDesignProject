//entro in questo loop quando viene scelta la modalita' audio
void loopModalitaAudio()
{

	// se non è ancora stata fatta un'azione
	if (!azioneFatta)
	{
		//leggo tutti gli input
		leggiInput();

		//controllo gli input
		controlloAzioni();
	}

	
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


		primaMossa = false;
		timeOutAzione = 4000;

		MP3player.setPlaySpeed(0);
		Serial.println("velocitaaaa");
		Serial.println(playspeed);


		//MP3player.setPlaySpeed(playspeed);
	}


	if (azioneFatta && inPartita) {


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

		}
		//Serial.println("timeOutAzione= ");
		//Serial.println(timeOutAzione);

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

	//se non è la prima mossa guardo se il tempo è scaduto
	if (!primaMossa && inPartita)
	{
		tempoScaduto();

	}

}

