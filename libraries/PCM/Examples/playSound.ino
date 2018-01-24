
// SpeakerPin = 11 

#include "PCM.h"
// #include "PCM_Sound.h"
#include "Gonghi.h"

void setup()
{
  // startPlayback(gonghi_PCM, gonghi_Len); // gros gresillement
  startPlayback(data, NUM_ELEMENTS); 
  
}

void loop()
{
	delay (5000);
   startPlayback(data, NUM_ELEMENTS); 
}


