const int TIMEOUT_LED_GIOCATORI = 2000;
const int CONTROLLO_DOPPIO_CLICK = 600;
const int CONTROLLO_DOPPIO_CLICK_MANIGLIA = 1000;
const int TIMEOUT_SCELTA_GIOCATORE = 10000;
const int MODALITA_DI_GIOCO[5] = {
	1, 2, 3, 4, 5 };

boolean giocatoriSelezionati[4] = {
	false, false, false, false };
boolean vecchioBottoniSelezionati[4] = {
	false, false, false, false };
float tempoSceltaBottoni[4] = {
	0, 0, 0, 0 };

float inizioSceltaModalita;

int modalitaTemporanea = 0;
float tempoSceltaModalita;

//faccio partitre l'audio accendo i pulsanti e dopo "TIMEOUT_LED_GIOCATORI" li spengo
void  avviaSceltaGiocatori()
{
	playTrack(AUDIO_SCEGLI_GIOCATORI);
	impostaColoreBottoni(VERDE, BLU, GIALLO, ROSSO);
	delay(TIMEOUT_LED_GIOCATORI);
	spegniLed();
}

//ogni volta che un tasto viene premuto lo illumino del colore corrispondente, uso CONTROLLO_DOPPIO_CLICK per assicurarmi che non mi arrivino segnali strani
//la prima volta che si schiaccia mi salvo la situazione pei pulsanti e infine avvio la scelta della modallita'
void aggiornaSceltaGiocatori()
{


	if (digitalRead(BOTTONE_1) && ((millis() - tempoSceltaBottoni[0]) > CONTROLLO_DOPPIO_CLICK))
	{

		// Serial.println();
		// Serial.println();
		giocatoriSelezionati[0] = !giocatoriSelezionati[0];
		Serial.println("giocatori selezionati");
		Serial.println(giocatoriSelezionati[0]);

		Serial.println("tempo selezionati");
		Serial.println((millis() - tempoSceltaBottoni[0]));


		tempoSceltaBottoni[0] = millis();
		digitalWrite(LED_VERDE_1, !digitalRead(LED_VERDE_1));
		//  delay(400);
	}
	if (!digitalRead(BOTTONE_2) && ((millis() - tempoSceltaBottoni[1]) > CONTROLLO_DOPPIO_CLICK))
	{
		giocatoriSelezionati[1] = !giocatoriSelezionati[1];
		tempoSceltaBottoni[1] = millis();
		digitalWrite(LED_BLU_2, !digitalRead(LED_BLU_2));
		//  delay(400);
	}
	if (digitalRead(BOTTONE_3) && ((millis() - tempoSceltaBottoni[2]) > CONTROLLO_DOPPIO_CLICK))
	{
		giocatoriSelezionati[2] = !giocatoriSelezionati[2];
		tempoSceltaBottoni[2] = millis();
		digitalWrite(LED_VERDE_3, !digitalRead(LED_VERDE_3));
		digitalWrite(LED_ROSSO_3, !digitalRead(LED_ROSSO_3));
		//    delay(400);
	}
	if (!digitalRead(BOTTONE_4) && ((millis() - tempoSceltaBottoni[3]) > CONTROLLO_DOPPIO_CLICK))
	{
		giocatoriSelezionati[3] = !giocatoriSelezionati[3];
		tempoSceltaBottoni[3] = millis();
		digitalWrite(LED_ROSSO_4, !digitalRead(LED_ROSSO_4));
		// delay(400);
	}


	if (digitalRead(BOTTONE_GRANDE))
	{
		if (giocatoriSelezionati[0])
		{
			coloreGiocatori[0] = VERDE;
			giocatoriInPartita++;

		}
		if (giocatoriSelezionati[1])
		{
			coloreGiocatori[1] = BLU;
			giocatoriInPartita++;

		}
		if (giocatoriSelezionati[2])
		{
			coloreGiocatori[2] = GIALLO;
			giocatoriInPartita++;

		}
		if (giocatoriSelezionati[3])
		{
			coloreGiocatori[3] = ROSSO;
			giocatoriInPartita++;

		}
		if (modalitaScelta > 0)
		{
			avviaSceltaModalita();
		}
	}


}

//faccio partire l'audio e inizializzo il countdown per far ripartire la voce
void  avviaSceltaModalita()
{

	playTrack(AUDIO_SCEGLI_MODALITA);

	inizioSceltaModalita = millis();
	spegniLed();

}

//se e passato piu' di "TIMEOUT_SCELTA_GIOCATORE" ripeto l'audio, se no mi metto in ascolto dei segnali sulla mangilia, quando si preme push salvo la modalita scelta e avvio la partita
void scegliModalita()
{
	if ((millis() - inizioSceltaModalita) > TIMEOUT_SCELTA_GIOCATORE)
	{
		/*for (i = 0; i < 4; i++){
			punteggioGiocatori[i] = -1;
		}*/
		avviaSceltaModalita();
	}



	if (digitalRead(BOTTONE_MANIGLIA) && ((millis() - tempoSceltaModalita) > CONTROLLO_DOPPIO_CLICK_MANIGLIA))
	{
		tempoSceltaModalita = millis();
		inizioSceltaModalita = millis();

		modalitaTemporanea++;

		if ((giocatoriInPartita == 1 && modalitaTemporanea == 5) || (giocatoriInPartita > 1 && modalitaTemporanea == 6))
		{
			modalitaTemporanea = 1;
		}


		switch (modalitaTemporanea) {

		case 1:
		{
				  playTrack(AUDIO_MODALITA_SPEED);
				  break;
		}

		case 2:
		{
				  playTrack(AUDIO_MODALITA_AUDIO);
				  break;
		}

		case 3:
		{
				  playTrack(AUDIO_MODALITA_MEMORY);
				  break;
		}

		case 4:
		{
				  playTrack(AUDIO_MODALITA_MEMORY_RANDOM);
				  break;
		}

		case 5:
		{
				  playTrack(AUDIO_MODALITA_PASSAMI);
				  break;
		}
		default:
		{
				   break;
		}
		}
		Serial.println("modalita selezionata=         ");
		Serial.println(modalitaTemporanea);
		// delay(400);


	}

	if (digitalRead(BOTTONE_GRANDE))
	{

		Serial.println("  if(digitalRead(BOTTONE_GRANDE))");
		modalitaScelta = modalitaTemporanea;
		Serial.print("modalitaScelta=         ");
		Serial.println(modalitaScelta);
		avviaPartita();
	}

}

void avviaPartita()
{
	if (modalitaScelta != 0)
	{
		Serial.println("  avvvvvvvvvvviiiiiiiiiiiiiiiooooooooooooooooooooo");

		playTrack(AUDIO_START);
	}
	inPartita = true;
	primaMossa = true;
	delay(2000);
}


