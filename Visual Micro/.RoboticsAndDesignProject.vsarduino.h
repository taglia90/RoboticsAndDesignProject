/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Mega 2560 or Mega ADK, Platform=avr, Package=arduino
*/

#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
#define __AVR_ATmega2560__
#define _VMDEBUG 1
#define ARDUINO 105
#define ARDUINO_MAIN
#define __AVR__
#define __avr__
#define F_CPU 16000000L
#define __cplusplus
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__

#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int
            
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}

//
//
void spegniLed();
void resettaPartita();
void accendiLedPunteggio();
void spegniLedPunteggio();
void playTrack(int track);
void scegliAzione();
void  avviaSceltaGiocatori();
void aggiornaSceltaGiocatori();
void  avviaSceltaModalita();
void scegliModalita();
void avviaPartita();
void pulsantiColorati();
void impostaColoreBottoni(int ledColore1,int ledColore2, int ledColore3, int ledColore4);
void ventola();
void scuoti();
void controlloAzioni();
void resettaAccelerometro();
void mossaGiustaColorati();
void mossaGiustaScuoti();
void mossaGiustaManiglia();
void mossaGiustaSoffia();
void mossaGiustaSchiaccia();
void mossaSbagliata();
void schiaccia();
void gira();
void accendiLedRosso();
void avviaVibrazione();
void fermaVibrazione();
void inizializzaVentola();
void inizializzaMp3Shield();
void inizializzaAccelerometro();
void inizializzaLed();
void inizializzaBottoni();
void loopModalitaAudio();
void loopModalitaMemory();
void inizializzaArrayMemory();
void  controlloAzioniModalitaMemory();
void loopModalitaMemoryRandom();
void tempoScaduto();
void loopModalitaPassami();
void loopModalitaSpeed();
void leggiInput();
void aggiornaAccelerazione();
boolean bottoniColoratiPremuti();
boolean bottoneGrandePremuto();
boolean bottoneManigliaPremuto();
boolean ventolaSoffiata();
boolean scosso();

#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\mega\pins_arduino.h" 
#include "C:\Users\Marco\Documents\Arduino\RoboticsAndDesignProject\RoboticsAndDesignProject.ino"
#include "C:\Users\Marco\Documents\Arduino\RoboticsAndDesignProject\FasiIniziali.ino"
#include "C:\Users\Marco\Documents\Arduino\RoboticsAndDesignProject\GestioneAzioni.ino"
#include "C:\Users\Marco\Documents\Arduino\RoboticsAndDesignProject\Inizializzazioni.ino"
#include "C:\Users\Marco\Documents\Arduino\RoboticsAndDesignProject\ModalitaAudio.ino"
#include "C:\Users\Marco\Documents\Arduino\RoboticsAndDesignProject\ModalitaMemory.ino"
#include "C:\Users\Marco\Documents\Arduino\RoboticsAndDesignProject\ModalitaMemoryRandom.ino"
#include "C:\Users\Marco\Documents\Arduino\RoboticsAndDesignProject\ModalitaPartita.ino"
#include "C:\Users\Marco\Documents\Arduino\RoboticsAndDesignProject\ModalitaPassami.ino"
#include "C:\Users\Marco\Documents\Arduino\RoboticsAndDesignProject\ModalitaSpeed.ino"
#include "C:\Users\Marco\Documents\Arduino\RoboticsAndDesignProject\lettureInput.ino"
#endif