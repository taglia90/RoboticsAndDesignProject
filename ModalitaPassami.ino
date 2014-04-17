//Modalità multigiocatore Passami!!!!: ogni rand() di azioni bisogna passarlo al giocatore di colore ROSSO/VERDE/BLU

int azioniResidue = 0;
int giocatore = 0;
int vecchioGiocatore;

void loopModalitaPassami()
{
	Serial.println("Entro in passamiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii");
	// se non è ancora stata fatta un'azione
	if (!azioneFatta)
	{
		//leggo tutti gli input
		leggiInput();

		//controllo gli input
		controlloAzioni();
	}


	//se non è la prima mossa guardo se il tempo è scaduto

	if (primaMossa)
	{
		primaMossa = false;
		timeOutAzione = 4000;
		giocatore = -1;
		azioneFatta = true;
		azioniResidue = 0;
		Serial.println("resett prima mossa");
	}


	if (azioneFatta && inPartita) {

		azioneFatta = false;
		scegliAzione();
		timeOutAzione -= (timeOutAzione * 0.1);
		Serial.println("hoscelto l'azione");

		if (timeOutAzione < 3000)
		{
			MP3player.setPlaySpeed(1);
			if (timeOutAzione < 2000)
			{
				MP3player.setPlaySpeed(2);

			}

			Serial.println("timeOutAzione= ");
			Serial.println(timeOutAzione);


			if (azioniResidue == 0)
			{

				azioniResidue = 3 + random(6);

				vecchioGiocatore = giocatore;


				giocatore = random(giocatoriInPartita);
				Serial.println("ho esattamente    giocatore   ");
				Serial.println(giocatoriInPartita);

				while (vecchioGiocatore == giocatore)
				{
					giocatore = random(giocatoriInPartita);
				}

				Serial.println("giocatore   dopo ");
				Serial.println(giocatore);


				switch (coloreGiocatori[giocatore]){
				case 0:
				{
						  playTrack(AUDIO_PASSAMI_AL_VERDE);
						  break;
				}
				case 1:
				{
						  playTrack(AUDIO_PASSAMI_AL_ROSSO);
						  break;
				}
				case 2:
				{
						  playTrack(AUDIO_PASSAMI_AL_BLU);
						  break;
				}
				case 3:
				{
						  playTrack(AUDIO_PASSAMI_AL_GIALLO);
						  break;
				}
				default:
					break;
				}

				delay(timeOutAzione / 2);
			}

			switch (azioneDaEseguire) {
				azioniResidue--;
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
			tempoScaduto();

		}



	}
}

