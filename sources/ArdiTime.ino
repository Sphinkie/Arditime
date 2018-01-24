
/* ************************************************************************************************

    ARDUINO-TIMER (ArdiTime)

Software pour le timer Arduino ArdiTime 

Pilotage par Arduino-Mini (flash = 32 kB)


Note:
The F() macro tells the compiler to leave this particular array in PROGMEM (Flash). 
(cela economise de la RAM programme)
Then when it is time to access it, one byte of the data is copied to RAM at a time. 
There’s a small performance overhead for this extra work. However, printing strings 
over Serial or to a LCD is a really slow process, so a few extra clock cycles really won’t matter.

*************************************************************************************************** 
* 1.0  05/02/2017  Version initiale.
*************************************************************************************************** 
* 2.0  20/03/2017  Utilisation de la library SimpleTimer
*                  Allumage progressif des LED
*************************************************************************************************** 
* 3.0 23/03/2017  Utilisation de la library Speaker_PCM
*                 Cette library utilise le speaker sur la pin 11 (or je l'ai cable sur la pin 10)
*                 Elle utilise le Timer1 (16-bit) pour le 8000 Hz. Ceci bloque le PWM (analogWrite()) sur les pins Arduino 9 et 10. 
*                 Elle utilise le Timer2 (8-bit) pour la modulation des impulsions. Ceci bloque le PWM (analogWrite()) sur les pins Arduino 11 et 3. 
*                 Le fichier audio doit être en unsigned bytes (8-bit), 8000 Hz, mono, et suffisamment court pour tenir dans la mémoire flash. (10kB à 20kB, cad 1 à 2 secondes)
*                 Convertir le MP3 en WAV (8-bits, mono, 8kHz) avec Audacity, puis en fichier .h avec WaveToCode.
*************************************************************************************************** 
* 3.1 24/03/2017  Clignotement de la LED DECO
* 3.2 25/03/2017  Variations de la LED ALARME (PWM)
* 3.3 30/03/2017  Gestion du potentiometre tactile
* 3.4 19/04/2017  Ajout du circuit Auto-OFF
* 3.5 25/05/2017  Mise dans le boitier. Etalonnages.
* 3.6 06/06/2017  Led rouge: intense pendant les 20 dernières secondes.
* 3.7 11/06/2017  Led Déco: allumage dès le mode Waiting
* * *************************************************************************************************** 
*/

#include <SimpleTimer.h>   // Librairie patchée pour permettre 16 timers
#include <PCM.h>          
#include "ArdiTime.h"
#include "Gonghi.h"

// *******************************************************************************
// variables globales
// *******************************************************************************
byte         Mode=WAITING;
static int   Luminosity_LED1=0;     // ambre (vumetre)
static int   Luminosity_LED2=0;     // red (alarme)
static byte  i=1;                   // clignotage
static bool  LED3enabled=true;
static int   Aiguille=0;
int          Value=0;               // 0 .. 1023
int          Position=0;            // 0 .. 1023
unsigned int Timer=0;               // 0 .. 65.535 (en secondes) MAX = 18 heures. En pratique, on se limite à 1 heure (3600 sec)
SimpleTimer  TimerManager;
// Les timout longue durée 
int          Id_CountdownTimer;
int          Id_AlarmTimout;
int          Id_GongTimout;
int          Id_ShutdownTimout;
int          Id_Led2FullTimout;
int          Id_Led3Timout;
int          Id_WatchdogTimout;
// les petits timers servant aux effets de fading
int          Id_Led1TimerOn;
int          Id_Led1TimerOff;
int          Id_Led1TimerDimm;
int          Id_Led2TimerOff;
int          Id_Led2TimerDimm;



// *******************************************************************************
// Fonction appelée toutes les X secondes, pendant la durée du décompte
// *******************************************************************************
void adjustVumetre()
{
    // On décrémente le timer de 10 secondes
    if (Timer>10) Timer=Timer-10;
    else Timer=0;
    Serial.print("  Timer="); Serial.print(Timer);
    // on ajuste la valeur de l'aiguille
    Aiguille = convertToVumetre(Timer); 
    Serial.print(" Vumetre="); Serial.print(Aiguille);
    Serial.print(" Reste="); int Minuts=Timer/60; Serial.print(Minuts);Serial.print("m"); Serial.print(Timer-(Minuts*60));Serial.println("s");
    analogWrite(VUMETRE,Aiguille); 
}

// *******************************************************************************
// Allume la LED_1 (Vumetre) de façon progressive PWM.
// (appelée N fois pour faire un allumage progressif)
// *******************************************************************************
void switchOnLED1() 
{
  // On incrémente la luminosité.
  if      (Luminosity_LED1 < 0)             {      Luminosity_LED1  = 0;      }
  else if (Luminosity_LED1 < LED1_SEUIL_1)  {      Luminosity_LED1 += 1;      }
  else if (Luminosity_LED1 < LED1_SEUIL_5)  {      Luminosity_LED1 += 5;      }
  else if (Luminosity_LED1 < 256)           {      Luminosity_LED1 += 10;     }
  else                                      {      Luminosity_LED1  = 255;    }
  // on sature la valeur à 255
  Luminosity_LED1 = min(Luminosity_LED1,255);
  // on regle l'intensité de la LED
  // Serial.print("+");Serial.print(Luminosity_LED1);   
  analogWrite(LED_1,Luminosity_LED1);
}

// *******************************************************************************
// Passe la LED_1 en luminosité moyenne (valeur cible = DIMMEDLED).
// (appelée N fois pour une transition progressive)
// *******************************************************************************
void dimmingLED1() 
{
  int delta = 0;
  int ecart = (Luminosity_LED1 - DIMMEDLED);
  if (ecart == 0)
    {
    // On a atteint la valeur cible
    }
  else
    {
    delta = (ecart/20) +1;
    }
  Luminosity_LED1 = Luminosity_LED1 - delta; 
  analogWrite(LED_1,Luminosity_LED1);
  //Serial.print(Luminosity_LED1);Serial.print('(');Serial.print(delta);Serial.print(")-");
}

// *******************************************************************************
// Passe la LED_2 en luminosité moyenne (valeur cible = DIMMEDLED).
// (appelée N fois pour une transition progressive)
// *******************************************************************************
void dimmingLED2() 
{
  int delta = 0;
  int ecart = (Luminosity_LED2 - DIMMEDLED);
  if (ecart == 0)
    {
    // On a atteint la valeur cible
    }
  else
    {
    delta = (ecart/20) +1;
    }
  Luminosity_LED2 = Luminosity_LED2 - delta; 
  analogWrite(LED_2,Luminosity_LED2);
}

// *******************************************************************************
// Eteint la LED_1 de façon progressive PWM.
// (appelée N fois pour une transition progressive)
// *******************************************************************************
void switchOffLED1() 
{
  if      (Luminosity_LED1 <=0)             {      Luminosity_LED1  = 0;   }
  else if (Luminosity_LED1 < LED1_SEUIL_1)  {      Luminosity_LED1 -= 1;   }
  else if (Luminosity_LED1 < LED1_SEUIL_5)  {      Luminosity_LED1 -= 5;   }
  else                                      {      Luminosity_LED1 -= 10;  }
  // on sature la valeur à 0
  Luminosity_LED1 = max(0,Luminosity_LED1);
  //Serial.print("-");Serial.print(Luminosity_LED1);   
  analogWrite(LED_1,Luminosity_LED1);
}

// *******************************************************************************
// Allume la LED_2 de façon progressive PWM. 
// (appelée N fois pour faire un allumage progressif)
// *******************************************************************************
void switchOnLED2() 
{
  // On incrémente la luminosité.
  if      (Luminosity_LED2 < 0)             {      Luminosity_LED2  = 0;      /*Serial.print("+0");  */  }
  else if (Luminosity_LED2 < LED2_SEUIL_1)  {      Luminosity_LED2 += 1;      /*Serial.print("+1");  */  }
  else if (Luminosity_LED2 < LED2_SEUIL_5)  {      Luminosity_LED2 += 5;      /*Serial.print("+5");  */  }
  else if (Luminosity_LED2 < 256)           {      Luminosity_LED2 += 10;     /*Serial.print("+10"); */  }
  else                                      {      Luminosity_LED2  = 255;    /*Serial.print("*");   */  }
  // on sature la valeur à 255
  Luminosity_LED2 = min(255,Luminosity_LED2);
  // on regle l'intensité de la LED
  analogWrite(LED_2,Luminosity_LED2);
}

// *******************************************************************************
// Allume la LED_2 de façon immediate.
// *******************************************************************************
void turnOnLED2() 
{
    // On allume la LED
    // Serial.print("Lum=");Serial.print(Luminosity_LED2);
    Serial.println(" LED 2 Full light");
    Luminosity_LED2 = 255;
    analogWrite(LED_2,Luminosity_LED2);
}

// *******************************************************************************
// Eteint la LED_2 de façon progressive PWM.
// (appelée N fois pour une transition progressive)
// *******************************************************************************
void switchOffLED2() 
{
  if      (Luminosity_LED2 <=0)             {      Luminosity_LED2  = 0;   }
  else if (Luminosity_LED2 < LED2_SEUIL_1)  {      Luminosity_LED2 -= 1;   }
  else if (Luminosity_LED2 < LED2_SEUIL_5)  {      Luminosity_LED2 -= 5;   }
  else                                      {      Luminosity_LED2 -= 10;  }
  // on sature la valeur à 0
  Luminosity_LED2 = max(0,Luminosity_LED2);
  analogWrite(LED_2,Luminosity_LED2);
}

// *******************************************************************************
// Allume la LED_3 de façon immediate.
// *******************************************************************************
void turnOnLED3() 
{
    // on allume la LED
    digitalWrite(LED_3,HIGH);
}

// *******************************************************************************
// Allume la LED DECO (pour effet de clignotements)
// *******************************************************************************
void switchOnLED3() 
{
      if (LED3enabled)
      {
          // on allume la LED
          digitalWrite(LED_3,HIGH);
          // on laisse allumé pour une certaine durée, prévue dans le tableau LedON
          Id_Led3Timout = TimerManager.setTimeout(LedON[i], switchOffLED3);
      }
}

// *******************************************************************************
// Eteint la LED DECO (pour effet de clignotements)
// *******************************************************************************
void switchOffLED3() 
{
    // on éteint la LED
    digitalWrite(LED_3,LOW);
    // Si actif, on programme un nouvel allumage, en laissant éteint pendan la durée prévue dans le tableau LedOFF
    i++;
    if (i>12) i=0;
    if (LED3enabled) Id_Led3Timout=TimerManager.setTimeout(LedOFF[i], switchOnLED3);
}

// *******************************************************************************
// Fonction de passage en mode ALARME (déclenchée par Timer)
// *******************************************************************************
void alarmTimeout() 
{
    Mode=ALARME;
    Serial.println(F("mode ALARME")); 
    // ----------------------------------------------
    // On allume la LED ALARME (rouge) à mi-luminosité
    // ----------------------------------------------
    Serial.println("switchOnLED2 (progressif)");
    Luminosity_LED2=0;
    Id_Led2TimerDimm = TimerManager.setTimer(40, dimmingLED2, LED2_NB_STEPS); // 40 ms - Y fois
}


// *******************************************************************************
// Fonction de passage en mode GONG (déclenchée par Timer)
// *******************************************************************************
void gongTimeout() 
{
    Mode=GONG;
    Serial.println("mode GONG");
    // ----------------------------------------------
    // On éteint la LED DECO
    // ----------------------------------------------
    Serial.println("switchOffLED3");
    LED3enabled=false;
    // ----------------------------------------------
    // On éteint la LED ALARME
    // ----------------------------------------------
    Serial.println("switchOffLED2 (progressif)");
    Id_Led2TimerOff=TimerManager.setTimer(20, switchOffLED2, LED2_NB_STEPS); // 20 ms
    // ----------------------------------------------
    // on joue le son 
    // ----------------------------------------------
    // tone(HP, 440, 100); // son de test
     startPlayback(data, NUM_ELEMENTS);  // Library PCM
    // ----------------------------------------------
    // On éteint la LED VUMETRE (progressif)
    // ----------------------------------------------
    Serial.println("switchOffLED1 (progressif)");
    Id_Led1TimerOff=TimerManager.setTimer(20, switchOffLED1, LED1_NB_STEPS); // 20 ms 
}

// *******************************************************************************
// Fonction de passage en mode SHUTDOWN (déclenchée par Timer)
// *******************************************************************************
void shutdownTimeout() 
{
    Mode=SHUTDOWN;
    Serial.println(F("mode SHUTDOWN")); 
    // ----------------------------------------------
    // On arrete la gestion de l'aiguille du vumetre
    // ----------------------------------------------
    TimerManager.deleteTimer(Id_CountdownTimer);
    //Serial.println("countdownTimer deleted"); 
    // ----------------------------------------------
    // On envoie une commande AUTO-OFF
    // ----------------------------------------------
    Serial.println("Auto OFF");
    digitalWrite(AUTO_ON,LOW);
    // ----------------------------------------------
    // On force l'extinction complete des LED
    // au cas où l'extinction progressive ne serait pas terminée...
    // ----------------------------------------------
    Luminosity_LED1 = 0;
    Luminosity_LED2 = 0;
    analogWrite(LED_1,0);
    analogWrite(LED_2,0);
    digitalWrite(LED_3,LOW);
}


// *******************************************************************************
// The setup function runs once when you press reset or power the board
// *******************************************************************************
void setup() 
{
    pinMode(AUTO_ON, OUTPUT);     // Commande de l'Auto-OFF
    digitalWrite(AUTO_ON,HIGH);   // En première chose, on positionne à HIGH, pour garantir l'alimentation du circuit.

    Serial.begin(115200);
    while (!Serial)   { ; } // wait for serial port to connect. Needed for native USB port only
  
    Serial.println(F("========================="));
    Serial.println(F("ArdiClock by David (2017)"));
    Serial.println(F("========================="));
    Serial.print  (F("CPU Frequency: ")); Serial.print(F_CPU/1000000); Serial.println(" MHz");

    pinMode(LED_1,    OUTPUT); // PWM - Led AMBER (mode adjusting)
    pinMode(LED_2,    OUTPUT); // PWM - Led AMBER (décoration)
    pinMode(LED_3,    OUTPUT); // Led RED (Alarme)
    pinMode(HP,       OUTPUT); // PWM - Haut-parleur
    pinMode(VUMETRE,  OUTPUT); // PWM - VUmetre [0 .. 255}
    pinMode(POT_IN,   INPUT);  // Potentiometre linéaire tactile [0 .. 1023]

    Mode = WAITING;
    // Watchdog : au bout de 3 minutes en mode waiting, le système s'éteint tout seul
    Id_WatchdogTimout = TimerManager.setTimeout(180000, shutdownTimeout);
    Serial.println(F("mode WAITING"));
    turnOnLED3();

    //---------------------------------------------------------
    // Test AUTO OFF
    //---------------------------------------------------------
    // for (int i=0; i<3; i++) {digitalWrite(LED_T,HIGH);delay(1000); digitalWrite(LED_T,LOW);delay(1000); };
    // digitalWrite(AUTO_OFF,LOW);
    //---------------------------------------------------------
    randomSeed(analogRead(0));
    delay (100);
    analogRead(POT_IN);    // On initialise la lecture du potard. La première valeur est souvent parasite.
    delay (100);
}


// *******************************************************************************
// BOUCLE PRINCIPALE
// *******************************************************************************
void loop() 
{
    // --------------------------------------------------------------
    // Mode WAITING
    // On attend que le doigt se pose sur le Potentiometre
    // --------------------------------------------------------------
    if (Mode == WAITING)
   {
      Value = analogRead(POT_IN);
      // Si le potentiometre renvoie une valeur, on passe en mode ADJUSTING
      if (Value > UNTOUCHED) 
      {
        Position = Value;
        Serial.print(F("  Position= "));  Serial.println(int(Position));
        // ----------------------------------------------
        // On allume progressivement la LED VUMETRE
        // ----------------------------------------------
        //Serial.print("switchOnLED1 (progressif "); Serial.print(LED1_NB_STEPS); Serial.println(" steps)");
        Id_Led1TimerOn = TimerManager.setTimer(20, switchOnLED1, LED1_NB_STEPS); // 20 ms 
        Serial.print("Id_Led1TimerOn created: "); Serial.println(Id_Led1TimerOn);
        // Gestion de la Led DECO
        i=0;
        // Arrêt du watchdog
        TimerManager.deleteTimer(Id_WatchdogTimout);
        Serial.println(F("mode ADJUSTING"));
        Mode=ADJUSTING;
      }
  }
  
  // --------------------------------------------------------------
  // Mode ADJUSTING
  // --------------------------------------------------------------
  if (Mode == ADJUSTING)
  {
    Value = analogRead(POT_IN);    // On lit la position du doigt
    Serial.print(F("  Value = "));  Serial.println(int(Value ));
    // Tant que le doigt touche la glissière:
    if (Value > UNTOUCHED) 
      {
        // on mémorise la valeur lue.
        Position = Value;
        // On ajuste la position de l'aiguille.
        int Secs = convertToSeconds(Position); 
        Aiguille = convertToVumetre(Secs); 
        // Serial.print(" Vumetre="); Serial.println(Aiguille);
        analogWrite(VUMETRE,Aiguille); 
      }
    // Si le doigt ne touche plus, on considère que c'est la valeur finale,
    // et on déclenche le décompte
    if (Value < UNTOUCHED) 
      {
        Serial.print(F("Potentiometer UNTOUCHED at position "));Serial.println(Position);
        // On met la LED_1 (vumetre) à mi-intensité
        Serial.println("dimmingLED1 (progressif)");
//        TimerManager.deleteTimer(Id_Led1TimerOn);       // on arrête un éventuel allumage progressif en cours
        Id_Led1TimerDimm = TimerManager.setTimer(40, dimmingLED1, LED1_NB_STEPS); // 40 ms 
        // On initialise le décompte
        Timer = convertToSeconds(Position);   // Conversion en secondes
        // Blindage: On ne peut pas avoir un decompte inférieur à 2 minutes
        if (Timer <120) Timer=120;            // Le minimum est un timer à 2 minutes.
        // --------------------------------------------------------------
        // On positionne un reveil regulier pour actualiser le vumetre
        // --------------------------------------------------------------
        Serial.print(F("   Countdown     = "));Serial.print(Timer);Serial.print(" sec");Serial.print(" = "); int Minuts=Timer/60; Serial.print(Minuts); Serial.print("m");Serial.print(Timer-(Minuts*60));Serial.println("s");
        Id_CountdownTimer = TimerManager.setInterval(10000, adjustVumetre); // ajustement toutes les 10 secondes.
        // --------------------------------------------------------------
        // On positionne un reveil à 60 secondes de la fin
        // --------------------------------------------------------------
        long AlarmDelay    = (Timer-60)*1000L;
        Serial.print(F("   AlarmDelay    = ")); Serial.print(AlarmDelay/1000); Serial.println(" sec (countdown-60s)");
        Id_AlarmTimout = TimerManager.setTimeout(AlarmDelay, alarmTimeout); 
        // ----------------------------------------------
        // On positionne un reveil à 20 secondes de la fin
        // ----------------------------------------------
        long Led2FullDelay = (Timer-20)*1000L;
        Serial.print(F("   Led2FullDelay = ")); Serial.print(Led2FullDelay/1000); Serial.println(" sec (countdown-20s)");
        Id_Led2FullTimout  = TimerManager.setTimeout(Led2FullDelay, turnOnLED2);
        // --------------------------------------------------------------
        // On positionne un reveil à 5 secondes de la fin
        // --------------------------------------------------------------
        long GongDelay     = (Timer-5)*1000L;
        Serial.print(F("   GongDelay     = ")); Serial.print(GongDelay/1000); Serial.println(" sec (countdown-5s)");
        Id_GongTimout = TimerManager.setTimeout(GongDelay, gongTimeout); 
        // --------------------------------------------------------------
        // On positionne un reveil à la fin
        // --------------------------------------------------------------
        long ShutdownDelay = Timer*1000L;
        Serial.print(F("   ShutdownDelay = ")); Serial.print(ShutdownDelay/1000); Serial.println(" sec");
        Id_ShutdownTimout = TimerManager.setTimeout(ShutdownDelay, shutdownTimeout); 
        // --------------------------------------------------------------
        // On allume la LED DECO avec clignotement
        // --------------------------------------------------------------
        Serial.println("switchOnLED3 (flashes)");
        Id_Led3Timout = TimerManager.setTimeout(LedOFF[0], switchOnLED3);
        // --------------------------------------------------------------
        // et on passe en mode COUNTDOWN.
        Mode=COUNTDOWN;
        Serial.print(TimerManager.getNumTimers()); 
        Serial.println(F(" mode COUNTDOWN"));
      }
  }

    // --------------------------------------------------------------
    // Mode COUNTDOWN
    // Si le doigt se re-pose sur le Potentiometre, on repasse en mode WAITING+ADJUSTING
    // --------------------------------------------------------------
    if (Mode == COUNTDOWN)
    {
       Value = analogRead(POT_IN);    // On lit la position du doigt
       if (Value > UNTOUCHED) 
       {
          Serial.println("clear all timers");
          // On annule les timeouts en cours
          TimerManager.deleteTimer(Id_CountdownTimer);
          TimerManager.deleteTimer(Id_AlarmTimout);
          TimerManager.deleteTimer(Id_Led2FullTimout); // LED alarme
          TimerManager.deleteTimer(Id_GongTimout);
          TimerManager.deleteTimer(Id_ShutdownTimout);
          TimerManager.deleteTimer(Id_Led3Timout);     // LED deco
          // On repasse en mode Waiting
          Mode=WAITING;
          Serial.print(TimerManager.getNumTimers()); 
          Serial.println(" mode WAITING");
       }
    }
  // --------------------------------------------------------------
  // Temporisation de la boucle 
  // --------------------------------------------------------------
  TimerManager.run();
  // aucun timer ne doit être inférieur à cette valeur, sinon ils se déclenchent mal.
  delay(20);      
}
  
 
// *******************************************************************************
// Fonction de conversion: Value lue sur Potard => Secondes
// (approximation de la courbe par plusieurs segments de droite)
// *******************************************************************************
int convertToSeconds(int value) 
{
  if (value < UNTOUCHED) return (0);          // segment0
  if (value < 180) return (4.50*value-90);    // segment1
  if (value < 450) return (2.89*value+200);   // segment2
  if (value < 770) return (2.25*value+487);   // segment3
  return (3.39*value-391);                    // segment4
}

// *******************************************************************************
// Fonction de conversion: Secondes => valeur pour le Vumetre
// (approximation de la courbe par plusieurs segments de droite)
// Aiguille varie entre [0..255] 
// *******************************************************************************
int convertToVumetre(int seconds) 
{
     if (seconds < 720)  return (0.037*seconds);      // segment1
     if (seconds < 1500) return (0.058*seconds-14);   // segment2
     if (seconds < 2200) return (0.117*seconds-104);  // segment3
     int Retour = 0.126*seconds -124;                 // segment4
     return min(Retour, 255);
}



