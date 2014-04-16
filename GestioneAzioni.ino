

//decido un pulsante che si deve illuminare di un colore casuale tra i 4
void pulsantiColorati() {

  coloreDaScegliere = random(4); //scelgo un colore
  pulsanteDaScegliere = random(4); //scelgo un pulsante

  impostaColoreBottoni(verde, blu, rosso ,giallo);
  delay(timeOutAzione/20);
  impostaColoreBottoni(giallo, verde, blu ,rosso);
  delay(timeOutAzione/20);
  impostaColoreBottoni(rosso, giallo, verde ,blu);
  delay(timeOutAzione/20);
  impostaColoreBottoni(blu, rosso, giallo ,verde);
  delay(timeOutAzione/20);
  impostaColoreBottoni(verde, blu, rosso ,giallo);
  delay(timeOutAzione/20);
  spegniLed();


  switch (coloreDaScegliere) {

  case 0: 
    {

      if(modalitaScelta != 2)
        playTrack(audioVerde);


      switch (pulsanteDaScegliere) {


      case 0: 
        {

          impostaColoreBottoni(verde, blu, rosso ,giallo);

          break;
        }
      case 1: 
        {
          impostaColoreBottoni(giallo, verde, rosso ,blu);

          break;
        }
      case 2: 
        {
          impostaColoreBottoni(rosso, giallo, verde ,blu);

          break;
        }
      case 3: 
        {
          impostaColoreBottoni(rosso, giallo, blu, verde);

          break;
        }

      default:
        break;
      }
      break;

    }
  case 1: 
    {

      if(modalitaScelta != 2)
        playTrack(audioBlu);

      switch (pulsanteDaScegliere) {
      case 0: 
        {
          impostaColoreBottoni(blu, giallo, rosso, verde);

          break;
        }
      case 1: 
        {
          impostaColoreBottoni( giallo, blu, verde, rosso);

          break;
        }
      case 2: 
        {
          impostaColoreBottoni( giallo,  rosso, blu, verde );

          break;
        }
      case 3: 
        {
          impostaColoreBottoni(   rosso,  giallo, verde, blu );

          break;
        }


      default:
        break;
      }
      break;
    }
  case 2: 
    {
      if(modalitaScelta != 2)
        playTrack(audioRosso);

      switch (pulsanteDaScegliere) {
      case 0: 
        {
          impostaColoreBottoni(   rosso,  giallo, verde, blu );

          break;
        }
      case 1: 
        {
          impostaColoreBottoni(   giallo ,  rosso, verde, blu );

          break;
        }
      case 2: 
        {
          impostaColoreBottoni(     giallo, blu, rosso,verde  );

          break;
        }
      case 3: 
        {
          impostaColoreBottoni(   giallo, verde, blu, rosso   );

          break;
        }

      default:
        break;
      }
      break;

    }

  case 3: 
    {
      if(modalitaScelta != 2)
        playTrack(audioGiallo);

      switch (pulsanteDaScegliere) {
      case 0: 
        {
          impostaColoreBottoni(   giallo, rosso,   verde, blu );

          break;
        }
      case 1: 
        {
          impostaColoreBottoni(     blu,giallo , verde, rosso  );

          break;
        }
      case 2: 
        {
          impostaColoreBottoni(    verde, blu, giallo, rosso   );

          break;
        }
      case 3: 
        {
          impostaColoreBottoni(    verde,  blu, rosso,giallo  );


          break;
        }

      default:
        break;

      }

      break;
    }
  default:
    break;
  }

}

//riceve in input 4 colori e li associa ai pulsanti corrispondenti 
void impostaColoreBottoni(int ledColore1,int ledColore2, int ledColore3, int ledColore4)
{
  spegniLed();

  if(ledColore1==verde)
  { 
    digitalWrite(ledVerde1, LOW);
  }

  if(ledColore1==rosso)
  { 
    digitalWrite(ledRosso1, LOW);
  }

  if(ledColore1==blu)
  { 
    digitalWrite(ledBlu1, LOW);
  }

  if(ledColore1==giallo)
  { 
    digitalWrite(ledVerde1, LOW);
    digitalWrite(ledRosso1, LOW);

  }

  if(ledColore2==verde)
  { 
    digitalWrite(ledVerde2, LOW);
  }

  if(ledColore2==rosso)
  { 
    digitalWrite(ledRosso2, LOW);
  }

  if(ledColore2==blu)
  { 
    digitalWrite(ledBlu2, LOW);
  }

  if(ledColore2==giallo)
  { 
    digitalWrite(ledVerde2, LOW);
    digitalWrite(ledRosso2, LOW);

  }
  if(ledColore3==verde)
  { 
    digitalWrite(ledVerde3, LOW);
  }

  if(ledColore3==rosso)
  { 
    digitalWrite(ledRosso3, LOW);
  }

  if(ledColore3==blu)
  { 
    digitalWrite(ledBlu3, LOW);
  }

  if(ledColore3==giallo)
  { 
    digitalWrite(ledVerde3, LOW);
    digitalWrite(ledRosso3, LOW);

  }
  if(ledColore4==verde)
  { 
    digitalWrite(ledVerde4, LOW);
  }

  if(ledColore4==rosso)
  { 
    digitalWrite(ledRosso4, LOW);
  }

  if(ledColore4==blu)
  { 
    digitalWrite(ledBlu4, LOW);
  }

  if(ledColore4==giallo)
  { 
    digitalWrite(ledVerde4, LOW);
    digitalWrite(ledRosso4, LOW);

  }


}

void ventola() {
  playTrack(audioSoffia);
}

void scuoti() {
  playTrack(audioScuoti);
}

void controlloAzioni() {
  switch (azioneDaEseguire) {

    //bottoni colorati
  case 0: 
    {
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
      }
      if ((pulsanteDaScegliere == 0 && bottonePremuto1 == 1)
        || (pulsanteDaScegliere == 1 && bottonePremuto2 == 1)
        || (pulsanteDaScegliere == 2 && bottonePremuto3 == 1)
        || (pulsanteDaScegliere == 3 && bottonePremuto4 == 1)) {


        mossaGiustaColorati();
      }		
      break;
    }
    //soffia
  case 1: 
    {
      if (bottoniColoratiPremuti() || bottoneGrandePremuto() || bottoneManigliaPremuto() || scosso() ) {
        Serial.println("soffia sbagliati"); 

        mossaSbagliata();
      }
      if (ventolaSoffiata()) {
        mossaGiustaSoffia();
      }
      break;
    }
    //bottoneGrande
  case 2: 
    {
      if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneManigliaPremuto() || scosso() ) {
        Serial.println("bottone grande sbagliati"); 

        mossaSbagliata();
      }
      if (bottoneGrandePremuto()) {



        mossaGiustaSchiaccia();
      }
      break;
    }
    //scuoti
  case 3: 
    {
      if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneManigliaPremuto() || bottoneGrandePremuto() ) {
        Serial.println("scuoti sbagliati"); 

        mossaSbagliata();
      }
      if (scosso()) {

        mossaGiustaScuoti();

      }
      break;
    }
    //bottoneManiglia
  case 4: 
    {
      if (bottoniColoratiPremuti() || ventolaSoffiata() || bottoneGrandePremuto() || scosso() ) {
        Serial.println("maniglia sbagliati"); 

        mossaSbagliata();
      }

      if (bottoneManigliaPremuto()) {

        mossaGiustaManiglia();
      }
      break;
    }

  default: 
    {
      break;
    }
  }
}

void resettaAccelerometro() {
  accelerazioneParziale = 0;
  inizioAccelerazione = millis();
  sommaAccelerazione = 0;
}

void mossaGiustaColorati() {

  playTrack(audioGiusto);
  spegniLed();
  int ledDaIlluminare;
  switch (pulsanteDaScegliere) {
  case 0:
    {
      ledDaIlluminare=ledVerde1;
      break;
    }
  case 1:
    {
      ledDaIlluminare=ledVerde2;
      break;
    }
  case 2:
    {
      ledDaIlluminare=ledVerde3;
      break;
    }
  case 3:
    {
      ledDaIlluminare=ledVerde4;
      break;
    }

  default: 
    break;      


  }

  digitalWrite(ledDaIlluminare,LOW);
  delay(attesaNuovaAzione/6);
  digitalWrite(ledDaIlluminare,HIGH);
  delay(attesaNuovaAzione/6);
  digitalWrite(ledDaIlluminare,LOW);
  delay(attesaNuovaAzione/6);
  digitalWrite(ledDaIlluminare,HIGH);
  delay(attesaNuovaAzione/6);
  digitalWrite(ledDaIlluminare,LOW);
  delay(attesaNuovaAzione/6);
  digitalWrite(ledDaIlluminare,HIGH);
  delay(attesaNuovaAzione/6);


  resettaAccelerometro();

 // if(modalitaScelta != 3)
    azioneFatta = true;
  mosseGiuste++;

  return;
}


void mossaGiustaScuoti() {
  playTrack(audioGiusto);
  spegniLed();
  delay(attesaNuovaAzione);
  resettaAccelerometro();
//  if(modalitaScelta != 3)
    azioneFatta = true;
  mosseGiuste++;

  return;
}

void mossaGiustaManiglia() {

  playTrack(audioGiusto);
  spegniLed();

  digitalWrite(ledVerdeManiglia,LOW);
  delay(attesaNuovaAzione/6);
  digitalWrite(ledVerdeManiglia,HIGH);
  delay(attesaNuovaAzione/6);
  digitalWrite(ledVerdeManiglia,LOW);
  delay(attesaNuovaAzione/6);
  digitalWrite(ledVerdeManiglia,HIGH);
  delay(attesaNuovaAzione/6);
  digitalWrite(ledVerdeManiglia,LOW);
  delay(attesaNuovaAzione/6);
  digitalWrite(ledVerdeManiglia,HIGH);
  delay(attesaNuovaAzione/6);

  resettaAccelerometro();
 // if(modalitaScelta != 3)
    azioneFatta = true;
  mosseGiuste++;

  return;
}




void mossaGiustaSoffia() {
  playTrack(audioGiusto);
  spegniLed();
  analogWrite(pinVentolaOut,255);
  delay(attesaNuovaAzione);
  analogWrite(pinVentolaOut,0);
  resettaAccelerometro();
 // if(modalitaScelta != 3)
    azioneFatta = true;
  mosseGiuste++;

  return;
}



void mossaGiustaSchiaccia() {
  playTrack(audioSbaam);
  spegniLed();
  digitalWrite(ledVerdeGrande1,LOW);
  delay(attesaNuovaAzione/6);
  digitalWrite(ledVerdeGrande1,HIGH);
  delay(attesaNuovaAzione/6);
  digitalWrite(ledVerdeGrande1,LOW);
  delay(attesaNuovaAzione/6);
  digitalWrite(ledVerdeGrande1,HIGH);
  delay(attesaNuovaAzione/6);
  digitalWrite(ledVerdeGrande1,LOW);
  delay(attesaNuovaAzione/6);
  digitalWrite(ledVerdeGrande1,HIGH);
  delay(attesaNuovaAzione/6);




  resettaAccelerometro();
//  if(modalitaScelta != 3)
    azioneFatta = true;
  mosseGiuste++;

  return;
}



void mossaSbagliata() {
  inPartita=false;
  playTrack(audioSbagliato);
  spegniLed();
  accendiLedRosso();
  avviaVibrazione();
  //avviaVibrazione();
  delay(1000);
  spegniLed();
  fermaVibrazione();
  resettaAccelerometro();
  azioneFatta = true;
  resettaPartita();

  return;
}


void schiaccia() {

  digitalWrite(ledBluGrande1,LOW);

  playTrack(audioSchiaccia);
}

void gira(){
  digitalWrite(ledBluManiglia,LOW);

  playTrack(audioGira);

}

void accendiLedRosso()
{
  digitalWrite(ledRosso1, LOW);
  digitalWrite(ledRosso2, LOW);
  digitalWrite(ledRosso3, LOW);
  digitalWrite(ledRosso4, LOW);
  digitalWrite(ledRossoGrande1, LOW);
  digitalWrite(ledRossoManiglia, LOW); 
}

void avviaVibrazione()
{
  analogWrite(pinVibrazione,255);
}

void fermaVibrazione()
{
  analogWrite(pinVibrazione,0);

}





