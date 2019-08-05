
// ensure this library description is only included once
#ifndef Instructable_h
#define Instructable_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"
#include "Communicative.h"
// library interface description
class Instructable
{
  // user-accessible "public" interface
  public:

    //Instructable(void);
    Instructable(const int ChipSelect = SS);

    int issueCommand(mInstruct);
    int issueCommand(mInstruct, int);
    int issueCommand(mInstruct, float);
    int issueCommand(mInstruct, int, float);

    bool areYouConnected(void);

  // library-accessible "private" interface
  private:
    Communicative CommsModule;

};

#endif
