const int timeoutLedGiocatori = 2000;
const int controlloDoppioClick = 600;
const int controlloDoppioClickManiglia = 1000;

const int timeoutSceltaModalita = 10000;
float tempoSceltaBottoni[4] = {
	0, 0, 0, 0 };
boolean giocatoriSelezionati[4] = {
	false, false, false, false };
boolean vecchioBottoniSelezionati[4] = {
	false, false, false, false };

float inizioSceltaModalita;
const int modalitaDiGioco[5] = {
	1, 2, 3, 4, 5 };
int modalitaTemporanea = 0;
float tempoSceltaModalita;


//faccio partitre l'audio accendo i pulsanti e dopo "timeoutLedGiocatori" li spengo
void  avviaSceltaGiocatori()
{
	playTrack(AUDIO_SCEGLI_GIOCATORI);
	impostaColoreBottoni(VERDE, BLU, GIALLO, ROSSO);
	delay(timeoutLedGiocatori);
	spegniLed();
}

//ogni volta che un tasto viene premuto lo illumino del colore corrispondente, uso controlloDoppioClick per assicurarmi che non mi arrivino segnali strani
//la prima volta che si schiaccia mi salvo la situazione pei pulsanti e infine avvio la scelta della modallita'
void aggiornaSceltaGiocatori()
{


	if (digitalRead(BOTTONE_1) && ((millis() - tempoSceltaBottoni[0]) > controlloDoppioClick))
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
	if (!digitalRead(BOTTONE_2) && ((millis() - tempoSceltaBottoni[1]) > controlloDoppioClick))
	{
		giocatoriSelezionati[1] = !giocatoriSelezionati[1];
		tempoSceltaBottoni[1] = millis();
		digitalWrite(LED_BLU_2, !digitalRead(LED_BLU_2));
		//  delay(400);
	}
	if (digitalRead(BOTTONE_3) && ((millis() - tempoSceltaBottoni[2]) > controlloDoppioClick))
	{
		giocatoriSelezionati[2] = !giocatoriSelezionati[2];
		tempoSceltaBottoni[2] = millis();
		digitalWrite(LED_VERDE_3, !digitalRead(LED_VERDE_3));
		digitalWrite(LED_ROSSO_3, !digitalRead(LED_ROSSO_3));
		//    delay(400);
	}
	if (!digitalRead(BOTTONE_4) && ((millis() - tempoSceltaBottoni[3]) > controlloDoppioClick))
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
			coloreGiocatori[giocatoriInPartita] = VERDE;
			giocatoriInPartita++;

		}
		if (giocatoriSelezionati[1])
		{
			coloreGiocatori[giocatoriInPartita] = BLU;
			giocatoriInPartita++;

		}
		if (giocatoriSelezionati[2])
		{
			coloreGiocatori[giocatoriInPartita] = GIALLO;
			giocatoriInPartita++;

		}
		if (giocatoriSelezionati[3])
		{
			coloreGiocatori[giocatoriInPartita] = ROSSO;
			modalitaScelta++;

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

//se e passato piu' di "timeoutSceltaModalita" ripeto l'audio, se no mi metto in ascolto dei segnali sulla mangilia, quando si preme push salvo la modalita scelta e avvio la partita
void scegliModalita()
{
	if ((millis() - inizioSceltaModalita) > timeoutSceltaModalita)
	{
		avviaSceltaModalita();
	}



	if (digitalRead(BOTTONE_MANIGLIA) && ((millis() - tempoSceltaModalita) > controlloDoppioClickManiglia))
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


