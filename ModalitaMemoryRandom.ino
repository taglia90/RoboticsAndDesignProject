//Modalità memory casuale: come memory normale, però ogni volta cambiano le azioni

void loopModalitaMemoryRandom()
{
  // se non è ancora stata fatta un'azione
  if(!totaleAzioniFatto)
  {
    Serial.print("totaleAzioniFatto= ");
    Serial.println(totaleAzioniFatto);
    //leggo tutti gli input
    leggiInput();

    //controllo gli input
    controlloAzioniModalitaMemory();

  }

  //se non è la prima mossa guardo se il tempo è scaduto
  if(primaMossa)
  {
 //   inAttesaUtente=false;
    primaMossa=false;
    inizializzaArrayMemory();
    contaMosse=0;
    timeOutAzione=4000;
  }


  if (azioneFatta && inPartita && totaleAzioniFatto) {

    azioneFatta = false;
    totaleAzioniFatto = false;


    for(j=0;j<=contaMosse;j++){   //cosi' faccio un ciclo in piu' di contaMosse
      Serial.println("j= ");
      Serial.println(j);

        posizioneAzione=0;
        scegliAzione();    

        mosseModalitaMemory[j][0]=azioneDaEseguire;
        if (azioneDaEseguire == 0){
          mosseModalitaMemory[j][1]=pulsanteDaScegliere;
          mosseModalitaMemory[j][2] =coloreDaScegliere;
        }

        Serial.println("nuova azione: ");
        Serial.println(azioneDaEseguire);

        Serial.println("Conta mosse: ");
        Serial.println(contaMosse);
        Serial.println();


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
      delay(1000);
      spegniLed();


    }

    contaMosse++;

  }

  if(!primaMossa && inPartita && totaleAzioniFatto)
  {
    tempoScaduto();

  }

}

/*
void inizializzaArrayMemory(){
  for(j=0;j<100;j++){
    for(k=0;k<3;k++){
      mosseModalitaMemory[j][k] = -1;
    } 
  }
}*/



/*void  controlloAzioniModalitaMemory()
{

  Serial.print("posizioneAzione= ");
  Serial.println(posizioneAzione);
  Serial.print("mosseModalitaMemory[posizioneAzione][0]= ");
  Serial.println(mosseModalitaMemory[posizioneAzione][0]);


  switch (mosseModalitaMemory[posizioneAzione][0]) {

    //bottoni colorati
  case 0: 
    {

      pulsanteDaScegliere=mosseModalitaMemory[posizioneAzione][1];

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
        posizioneAzione=0;
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
      if (bottoniColoratiPremuti() || bottoneGrandePremuto() || bottoneManigliaPremuto() || scosso() ) {
        Serial.println("soffia sbagliati"); 
        mossaSbagliata();
        posizioneAzione=0;
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
      if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneManigliaPremuto() || scosso() ) {
        Serial.println("bottone grande sbagliati"); 
        mossaSbagliata();
        posizioneAzione=0;
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
      if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneManigliaPremuto() || bottoneGrandePremuto() ) {
        Serial.println("scuoti sbagliati"); 
        mossaSbagliata();
        posizioneAzione=0;
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
      if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneGrandePremuto() || scosso() ) {
        Serial.println("maniglia sbagliati"); 
        mossaSbagliata();
        posizioneAzione=0;
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


  if(mosseModalitaMemory[posizioneAzione][0]==-1 && azioneFatta){
    Serial.println("ENTRO IFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");

    totaleAzioniFatto=true;
  }

}*/



























