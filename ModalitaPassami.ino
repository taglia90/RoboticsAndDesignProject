//Modalità multigiocatore Passami!!!!: ogni rand() di azioni bisogna passarlo al giocatore di colore rosso/verde/blu


int azioniResidue;
int giocatore=0;
int vecchioGiocatore;

void loopModalitaPassami()
{


  // se non è ancora stata fatta un'azione
  if(!azioneFatta)
  {
    //leggo tutti gli input
    leggiInput();

    //controllo gli input
    controlloAzioni();
  }

  //se non è la prima mossa guardo se il tempo è scaduto







  //se non è la prima mossa guardo se il tempo è scaduto

  if (primaMossa)
  {
    primaMossa=false;
    timeOutAzione=4000;
    giocatore=-1;
  }


  if (azioneFatta && inPartita) {


    azioneFatta = false;
    scegliAzione();
    timeOutAzione -= (timeOutAzione * 0.1);

    if(timeOutAzione<3000)
    {
      MP3player.setPlaySpeed(1);
      if(timeOutAzione<2000)
      {
        MP3player.setPlaySpeed(2);

      }   
      Serial.println("timeOutAzione= ");
      Serial.println(timeOutAzione);


      if(azioniResidue==0)
      {


        azioniResidue=3 + random(6);

        vecchioGiocatore=giocatore;

        giocatore=random(giocatoriInPartita);


        while(vecchioGiocatore==giocatore)
        {
          giocatore=random(giocatoriInPartita);
        }

        switch (coloreGiocatori[giocatore]){
        case 0 : 
          {  
            playTrack(audioPassamiAlVerde); 
            break; 
          }
        case 1 : 
          {  
            playTrack(audioPassamiAlRosso); 
            break; 
          }
        case 2 : 
          {  
            playTrack(audioPassamiAlBlu); 
            break; 
          }
        case 3 : 
          {  
            playTrack(audioPassamiAlGiallo); 
            break; 
          }
        default: 
          break;
        }

        delay(timeOutAzione/2);
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

    if(!primaMossa && inPartita)
    {
      tempoScaduto();

    }



  }
}
