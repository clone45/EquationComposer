#ifndef ModuleSpeechSound_h
#define ModuleSpeechSound_h

#include "Module.h"

#define FORMANT_SZ 7

class ModuleSpeechSound : public Module
{
  public:
    ModuleSpeechSound();
    uint16_t compute();
	
    // Inputs
    Module *sound_input;
	Module *param1_input;
    Module *param2_input;
	Module *pitch_input;    
    
  private:
  
    uint32_t output;

    uint16_t pitchPhase, form1Phase,form2Phase,form3Phase;
    uint16_t pitchPhaseInc,form1PhaseInc,form2PhaseInc,form3PhaseInc;
    uint8_t form1Amp,form2Amp,form3Amp;
    uint8_t noiseMod;    

    int frameTime;
    uint16_t basePitch;
    int formantScale;
    
    int8_t noise;
};
    

#endif

