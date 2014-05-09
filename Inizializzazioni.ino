
void inizializzaVentola()
{
	//fermo la ventola
	analogWrite(PIN_VENTOLA_OUT, 0);
	altoVentola = digitalRead(PIN_VENTOLA_IN);
}

void inizializzaMp3Shield()
{
	//Initialize the SdCard.
	if (!sd.begin(SD_SEL, SPI_HALF_SPEED))
		sd.initErrorHalt();
	if (!sd.chdir("/"))
		sd.errorHalt("sd.chdir");

	//Initialize the MP3 Player Shield
	MP3player.begin();
	//check result, see readme for error codes.
	playTrack(AUDIO_MUSICA);

}

void inizializzaAccelerometro()
{
	accelero.begin(47, 49, 46, 48, A8, A9, A10);
	accelero.setSensitivity(HIGH);               //sets the sensitivity to +/-6G
	accelero.calibrate();

}

void inizializzaLed() {

	for (i = 0; i < 6; i++)
	{
		pinMode(LED_PUNTEGGIO[i], OUTPUT);
	}


	pinMode(LED_ROSSO_1, OUTPUT);
	pinMode(LED_BLU_1, OUTPUT);
	pinMode(LED_VERDE_1, OUTPUT);

	digitalWrite(LED_ROSSO_1, HIGH);
	digitalWrite(LED_BLU_1, HIGH);
	digitalWrite(LED_VERDE_1, HIGH);

	pinMode(LED_ROSSO_2, OUTPUT);
	pinMode(LED_BLU_2, OUTPUT);
	pinMode(LED_VERDE_2, OUTPUT);

	digitalWrite(LED_ROSSO_2, HIGH);
	digitalWrite(LED_BLU_2, HIGH);
	digitalWrite(LED_VERDE_2, HIGH);

	pinMode(LED_ROSSO_3, OUTPUT);
	pinMode(LED_BLU_3, OUTPUT);
	pinMode(LED_VERDE_3, OUTPUT);

	digitalWrite(LED_ROSSO_3, HIGH);
	digitalWrite(LED_BLU_3, HIGH);
	digitalWrite(LED_VERDE_3, HIGH);

	pinMode(LED_ROSSO_MANIGLIA, OUTPUT);
	pinMode(LED_BLU_MANIGLIA, OUTPUT);
	pinMode(LED_VERDE_MANIGLIA, OUTPUT);

	digitalWrite(LED_ROSSO_MANIGLIA, HIGH);
	digitalWrite(LED_BLU_MANIGLIA, HIGH);
	digitalWrite(LED_VERDE_MANIGLIA, HIGH);

	pinMode(LED_ROSSO_4, OUTPUT);
	pinMode(LED_BLU_4, OUTPUT);
	pinMode(LED_VERDE_4, OUTPUT);

	digitalWrite(LED_ROSSO_4, HIGH);
	digitalWrite(LED_BLU_4, HIGH);
	digitalWrite(LED_VERDE_4, HIGH);

	pinMode(LED_ROSSO_GRANDE_1, OUTPUT);
	pinMode(LED_BLU_GRANDE_1, OUTPUT);
	pinMode(LED_VERDE_GRANDE_1, OUTPUT);

	digitalWrite(LED_ROSSO_GRANDE_1, HIGH);
	digitalWrite(LED_BLU_GRANDE_1, HIGH);
	digitalWrite(LED_VERDE_GRANDE_1, HIGH);

}

void inizializzaBottoni() {
	pinMode(BOTTONE_1, INPUT);
	pinMode(BOTTONE_2, INPUT);
	pinMode(BOTTONE_3, INPUT);
	pinMode(BOTTONE_GRANDE, INPUT);
}


