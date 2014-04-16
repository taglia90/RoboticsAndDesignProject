
float tempoVentolaSoffiata = 0;
float timeOldCycle;

void leggiInput()
{
	//Serial.println("leggo input");
	aggiornaAccelerazione();

	bottonePremutoGrande = digitalRead(bottoneGrande);
	bottonePremuto1 = digitalRead(bottone1);
	bottonePremuto2 = !digitalRead(bottone2);
	bottonePremuto3 = digitalRead(bottone3);
	bottonePremuto4 = !digitalRead(bottone4);
	intensitaVentola = analogRead(pinVentolaIn);


	//Serial.println("intensitaVentola");

	//Serial.println(intensitaVentola);
	bottonePremutoManiglia = digitalRead(bottoneManiglia);
	//  Serial.println("bottone1   ");
	// Serial.println(bottonePremuto1);
	// Serial.println("bottone2   ");
	// Serial.println(bottonePremuto2);
	// Serial.println("bottone3   ");
	// Serial.println(bottonePremuto3);
	// Serial.println("bottone4   ");
	// Serial.println(bottonePremuto4);
	// Serial.println("bottonePremutoGrande   ");
	// Serial.println(bottonePremutoGrande);
	// Serial.println("bottonePremutoManiglia   ");
	// Serial.println(bottonePremutoManiglia);
	// Serial.println("intensitaVentola   ");
	// Serial.println(intensitaVentola);
	// Serial.println("sommaAccelerazione   ");
	// Serial.println(sommaAccelerazione);


}


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



boolean bottoniColoratiPremuti()
{
	if ((bottonePremuto1 + bottonePremuto2 + bottonePremuto3 + bottonePremuto4) == 0)
	{
		return false;
	}
	return true;
}

boolean bottoneGrandePremuto()
{
	if (bottonePremutoGrande == 0)
	{
		return false;
	}
	return true;
}

boolean bottoneManigliaPremuto()
{
	if (bottonePremutoManiglia == 0)
	{
		return false;
	}
	return true;

}

boolean ventolaSoffiata()
{
	if (1023 - intensitaVentola > limiteVelocitaVentola && (millis() - tempoVentolaSoffiata) > 4000)
	{
		tempoVentolaSoffiata = millis();
		return true;
	}
	return false;
}


boolean scosso()
{
	if (sommaAccelerazione > limiteAccelerazione)
	{
		return true;
	}
	return false;
}




