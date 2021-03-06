
# File Communicative.h

[**File List**](files.md) **>** [**Communicative.h**](_communicative_8h.md)

[Go to the documentation of this file.](_communicative_8h.md) 


````cpp

// ensure this library description is only included once
#ifndef Communicative_h
#define Communicative_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"
// library interface description


class Communicative
{
  // user-accessible "public" interface
  public:

    Communicative(const int CS);

    ~Communicative(void);

    bool isPeripheralConnected(void);
  
  //protected:  

    sCmd RequestReply(const mCmd);

    Identity RequestIdentity(const mCmd);

    Data RequestData(const mCmd);


  // library-accessible "private" interface
  private:

    void SPISetup(void);

    byte transferAndPause(const byte);

    template <typename T> unsigned int SPI_write (const T& value);

    template <typename T> unsigned int SPI_read(T& value);

    byte areYouAlive();

    int ChipSelect;
   // Identity ThisSensor;
};

#endif
````

