

// *****************************************************
// Constantes
// *****************************************************
// Les étapes (mode) de la séquence:
#define WAITING     0
#define ADJUSTING   1
#define COUNTDOWN   2
#define ALARME      3
#define GONG        4
#define SHUTDOWN    5

#define UNTOUCHED   20       // valeur retournée par le potentiometre quand il n'est pas utilisé
//#define COEF_POS    3.3      // (3000/1023=2.93)  Position max de 1023 donne un Timer de 50 minutes (1 heure: 3600/1023=3.52)
//#define COEF_VUM    0.085   // (255/3000=0.085)  Timer max de 50 minutes donne Aiguille de 255     (1 heure: 255/3600=0.07)

// *******************************************************************************
// Mapping du cablage ARDUINO MINI
// *******************************************************************************
// unused         1     // TX
// unused         0     // RX
// unused         2     // PD2  (avec hardware interrupt 0)
#define VUMETRE   3     // PD3  PWM (avec hardware interrupt 1) 
// unused         4     // PD4  
#define LED_1     5     // PD5  PWM  : LED AMBRE (pour vumetre)
#define LED_2     6     // PD6  PWM  : LED ROUGE (pour alarme)
#define LED_3     7     // PD7       : LED AMBRE (pour décoration)
// unused         8     // PB0  
// unused         9     // PB1  PWM
// unused        10     // PB2  PWM SPI SS  
#define HP       11     // PB3  PWM SPI MOSI (output) : HAUT PARLEUR (pour Gong). Pin 11 imposé par la library PCM
// unused        12     // PB4  SPI MISO (input) 
#define AUTO_ON  13     // PB5  SPI SCK  (output)
#define LED_T    13     // LED de Test (Allumé tant que AUTO_ON est actif)

// unused         A0     // PC0  (analog)
// unused         A1     // PC1  (analog)
// unused         A2     // PC2  (analog)
#define POT_IN    A3     // PC3  (analog) : Potentiometre tactile
// unused         A4     // PC4  (analog) (SDA)
// unused         A5     // PC5  (analog) (SDL)
// unused         A6     // ADC6 (analog)
// unused         A7     // ADC7 (analog)


// *******************************************************************************
// Constantes
// *******************************************************************************

// durée (en ms) des états de la LED déco, qui clignotte par moment.
const int LedON[]  = {    40,    80,    630,   90,    60,   80,    70,    1200,    5000,    130,   60,    20000};
const int LedOFF[] = {100,    40,    80,    80,   60,   70,    80,    180,     80,      90,     60,   80};

// *******************************************************************************
// caracteristiques techniques
// *******************************************************************************
#define LED1_SEUIL_1      30
#define LED1_SEUIL_5      100
#define LED1_NB_STEPS     LED1_SEUIL_1+(LED1_SEUIL_5-LED1_SEUIL_1)/5+(255-LED1_SEUIL_5)/10+5   // 64
#define DIMMEDLED         50  // valeur pour avoir un éclairage atténué de la LED Vumetre

#define LED2_SEUIL_1      40
#define LED2_SEUIL_5      100
#define LED2_NB_STEPS     LED2_SEUIL_1+(LED2_SEUIL_5-LED2_SEUIL_1)/5+(255-LED2_SEUIL_5)/10+5   // 77


// *******************************************************************************
// Fonctions appelées par le SimpleTimer
// *******************************************************************************
  
void adjustVumetre(); 
void switchOnLED1();
void switchOnLED2();
void switchOnLED3();
void dimmingLED1();
void switchOffLED1();
void switchOffLED2();
void switchOffLED3();
void alarmTimeout();
void gongTimeout();
void shutdownTimeout();

