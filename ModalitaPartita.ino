//const int DECREMENTO_TEMPO_MOD_SPEED = 100;

//Modalità speed: Parte elencando cose da fare lasciando  sempre meno tempo per compiere l’azione. Alla prima risposta sbagliata o fuori tempo la partita finisce.
/*
void modalitaSpeed(){

  //se non è la prima mossa guardo se il tempo è scaduto
  if(primaMossa)
  {
    primaMossa=false;
  }


  if (azioneFatta && inPartita) {


    azioneFatta = false;
    scegliAzione();
    timeOutAzione -= (timeOutAzione * 0.1);
    Serial.println("timeOutAzione= ");
    Serial.println(timeOutAzione);

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

  if(!primaMossa && inPartita)
  {
    tempoScaduto();

  }

}*/




/*
//Modalità audio: Come prima, ma solo audio.

void modalitaAudio(){

  //se non è la prima mossa guardo se il tempo è scaduto
  if(primaMossa)
  {
    primaMossa=false;
  }


  if (azioneFatta && inPartita) {

    timeOutAzione -= (timeOutAzione * 0.1);
    azioneFatta = false;
    scegliAzione();


    switch (azioneDaEseguire) {

    case 0: 
      {
        pulsantiColorati();
        break;
      }
    case 1: 
      {
        //ventola();
        break;
      }
    case 2: 
      {
        //schiaccia();
        break;
      }
    case 3: 
      {
        //scuoti();
        break;
      }

    case 4: 
      {
        //gira();
        break;
      }

    default:
      {
        //non dovrei mai entrare, ma meglio metterlo per sicurezza.
        break;
      }
    }

  }

  if(!primaMossa && inPartita)
  {
    tempoScaduto();

  }

}*/









void tempoScaduto() {
  if (((millis() - inizioAzione) > timeOutAzione)) {

    Serial.println("tempo scaduto con   ");
    Serial.print((millis() - inizioAzione));
    mossaSbagliata();		
  }
}



