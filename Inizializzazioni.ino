
void inizializzaVentola()
{
  //fermo la ventola
  analogWrite(pinVentolaOut,0);

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
  playTrack(audioMusica);


}


void inizializzaAccelerometro()
{
  accelero.begin(47, 49, 46, 48, A8, A9, A10);
  accelero.setSensitivity(HIGH);               //sets the sensitivity to +/-6G
  accelero.calibrate();


}

void inizializzaLed() {

  for(i=0;i<6;i++)
  {
  pinMode(ledPunteggio[i], OUTPUT);
  }
  

  pinMode(ledRosso1, OUTPUT);
  pinMode(ledBlu1, OUTPUT);
  pinMode(ledVerde1, OUTPUT);

  digitalWrite(ledRosso1, HIGH);
  digitalWrite(ledBlu1, HIGH);
  digitalWrite(ledVerde1, HIGH);

  pinMode(ledRosso2, OUTPUT);
  pinMode(ledBlu2, OUTPUT);
  pinMode(ledVerde2, OUTPUT);

  digitalWrite(ledRosso2, HIGH);
  digitalWrite(ledBlu2, HIGH);
  digitalWrite(ledVerde2, HIGH);

  pinMode(ledRosso3, OUTPUT);
  pinMode(ledBlu3, OUTPUT);
  pinMode(ledVerde3, OUTPUT);

  digitalWrite(ledRosso3, HIGH);
  digitalWrite(ledBlu3, HIGH);
  digitalWrite(ledVerde3, HIGH);

  pinMode(ledRossoManiglia, OUTPUT);
  pinMode(ledBluManiglia, OUTPUT);
  pinMode(ledVerdeManiglia, OUTPUT);

  digitalWrite(ledRossoManiglia, HIGH);
  digitalWrite(ledBluManiglia, HIGH);
  digitalWrite(ledVerdeManiglia, HIGH);
  
   pinMode(ledRosso4, OUTPUT);
  pinMode(ledBlu4, OUTPUT);
  pinMode(ledVerde4, OUTPUT);

  digitalWrite(ledRosso4, HIGH);
  digitalWrite(ledBlu4, HIGH);
  digitalWrite(ledVerde4, HIGH);
  
   pinMode(ledRossoGrande1, OUTPUT);
  pinMode(ledBluGrande1, OUTPUT);
  pinMode(ledVerdeGrande1, OUTPUT);

  digitalWrite(ledRossoGrande1, HIGH);
  digitalWrite(ledBluGrande1, HIGH);
  digitalWrite(ledVerdeGrande1, HIGH);
  
}



void inizializzaBottoni() {
  pinMode(bottone1, INPUT);
  pinMode(bottone2, INPUT);
  pinMode(bottone3, INPUT);
  pinMode(bottoneGrande, INPUT);
}


