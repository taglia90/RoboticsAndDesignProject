float tempoVentolaSoffiata = 0;
float timeOldCycle;

//funzione che legge gli input
void leggiInput()
{
	//Serial.println("leggo input");
	aggiornaAccelerazione();

	bottonePremutoGrande = !digitalRead(BOTTONE_GRANDE);
	bottonePremuto1 = digitalRead(BOTTONE_1);
	bottonePremuto2 = digitalRead(BOTTONE_2);
	bottonePremuto3 = digitalRead(BOTTONE_3);
	bottonePremuto4 = digitalRead(BOTTONE_4);
	intensitaVentola = analogRead(PIN_VENTOLA_IN);


	//Serial.println("intensitaVentola");

	//Serial.println(intensitaVentola);
	bottonePremutoManiglia = !digitalRead(BOTTONE_MANIGLIA);
	  Serial.println("BOTTONE_1   ");
	 Serial.println(bottonePremuto1);
	 Serial.println("BOTTONE_2   ");
	 Serial.println(bottonePremuto2);
	 Serial.println("BOTTONE_3   ");
	 Serial.println(bottonePremuto3);
	 Serial.println("BOTTONE_4   ");
	 Serial.println(bottonePremuto4);
	 Serial.println("bottonePremutoGrande   ");
	 Serial.println(bottonePremutoGrande);
	 Serial.println("bottonePremutoManiglia   ");
	 Serial.println(bottonePremutoManiglia);
	 Serial.println("intensitaVentola   ");
	 Serial.println(intensitaVentola);
	 Serial.println("sommaAccelerazione   ");
	 Serial.println(sommaAccelerazione);
	 delay(100);

}

//ogni tot millisecondi vado a vedere quant'e' l'accelerazione
void aggiornaAccelerazione() {

	if (millis() - timeOldCycle<200)
	{

		accelerazioneIstantanea = abs(accelero.getTotalVector())*(millis() - timeOldCycle);
		accelerazioneParziale += abs(accelerazioneIstantanea - vecchiaAccelerazioneIstantanea);
		vecchiaAccelerazioneIstantanea = accelerazioneIstantanea;
	}
	if ((float)millis() - inizioAccelerazione > 200) {
		inizioAccelerazione = (float)millis();
		sommaAccelerazione = accelerazioneParziale;

		Serial.print("sommaAccelerazione                   ");

		Serial.print(sommaAccelerazione);

		Serial.println("");

		accelerazioneParziale = 0;
	}

	timeOldCycle = millis();
}

//torna true se sono stati premuti i bottoni, 0 altrimenti
boolean bottoniColoratiPremuti()
{
	if ((bottonePremuto1 + bottonePremuto2 + bottonePremuto3 + bottonePremuto4) == 0)
	{
		return false;
	}
	return true;
}

//torna true se e' stato premuto il pulsantone, 0 altrimenti
boolean bottoneGrandePremuto()
{
	if (bottonePremutoGrande == 0)
	{
		return false;
	}
	return true;
}

//torna true se e' stata tirata la maniglia, 0 altrimenti
boolean bottoneManigliaPremuto()
{
	if (bottonePremutoManiglia == 0)
	{
		return false;
	}
	return true;

}

//torna true se e' si è soffiato sulla ventola, 0 altrimenti
boolean ventolaSoffiata()
{
	if (1023 - intensitaVentola > limiteVelocitaVentola && (millis() - tempoVentolaSoffiata) > 4000)
	{
		tempoVentolaSoffiata = millis();
		return true;
	}
	return false;
}

//torna true se e' stato scosso il gioco, 0 altrimenti
boolean scosso()
{
	if (sommaAccelerazione > limiteAccelerazione)
	{
		return true;
	}
	return false;
}




