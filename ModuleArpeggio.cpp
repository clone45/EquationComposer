#include "Arduino.h"
#include "ModuleArpeggio.h"
#include "Defines.h"

ModuleArpeggio::ModuleArpeggio()
{
  this->clocked = false;
  this->step = 0;
  this->my_output = 0;
  
  this->arpeggiations = {
    {0,12,0,12,0,12,0,12},
    {0,12,0,12,0,12,-2,10},
    {0,10,12,0,10,12,0,0},
    {0,3,7,10,0,3,7,10},
    {0,3,7,10,12,10,7,3},
    {0,-2,0,3,0,-2,-5,-2},
    {0,0,12,0,0,0,12,0},
    {0,1,4,5,7,5,4,1}
  };

  // Initialize all inputs
  this->root_note_input = NULL;
  this->pattern_input = NULL;
  this->clock_input = NULL;
}

uint32_t ModuleArpeggio::compute()
{
  uint32_t clock = this->readInput(clock_input);
  
  if((clock < MID_CV) && clocked) clocked = false;
  
  if((clock >= MID_CV) && !clocked) 
  {
    clocked = true;
    
    // Read scale input.
    // Convert the standard 12 bit CV value to a 3-bit value, which ranges from 0 to 7
    uint32_t pattern = this->readInput(pattern_input, CONVERT_TO_3_BIT);
    
    // Read root note
    uint32_t root_note = this->readInput(root_note_input); 

    my_output = (arpeggiations[pattern][step] << 5) + root_note;
    
    step++;
    if(step == 8) step = 0;
  }
  
  return(my_output);
}