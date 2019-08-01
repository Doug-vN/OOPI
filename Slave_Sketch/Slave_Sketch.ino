#include <SPI.h>
#include <Arduino.h>

template <typename T> unsigned int SPI_writeAnything (const T& value)
  {
    const byte * p = (const byte*) &value;
    unsigned int i;
    for (i = 0; i < sizeof value; i++)
          SPI.transfer(*p++);
    return i;
  }  // end of SPI_writeAnything

template <typename T> unsigned int SPI_readAnything(T& value)
  {
    byte * p = (byte*) &value;
    unsigned int i;
    for (i = 0; i < sizeof value; i++)
          *p++ = SPI.transfer (0);
    return i;
  }  // end of SPI_readAnything
  
  
template <typename T> unsigned int SPI_readAnything_ISR(T& value)
  {
    byte * p = (byte*) &value;
    unsigned int i;
    *p++ = SPDR;  // get first byte
    for (i = 1; i < sizeof value; i++)
          *p++ = SPI.transfer (0);
    return i;
  }  // end of SPI_readAnything_ISR  

typedef enum sInstruct{
  DisplayInstructionAndWait,
  DisplayInstructionAndWaitForUser,
  DontDisplayAndWait,
  DontDisplayAndContinue,
  ACK,
  Yes,
  No,
  NAK,
  ReferToInt,
  ReferToFloat,
  ReferToString
};

typedef enum mInstruct{
  PauseMeasurementForiParam,
  RestartMeasurementProcedure,
  ResetDevice,
  HowManyInstructions,
  NextCommandPlease,
  IsThereData,
  SendDataPlease,
  WhoAreYou,
  HowLongShouldIWait,
  BeginMeasurement
};

typedef struct sCmd{
  sInstruct Instruction; 
  char sParam[128];
  int iParam;
  float fParam;
};

typedef struct mCmd{
  mInstruct Instruction;
  int iParam;
  float fParam;
};




void setup (void)
{

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);

  // turn on SPI in slave mode
  SPCR |= _BV(SPE);

  // turn on interrupts
  SPCR |= _BV(SPIE);

}  // end of setup


// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR;

  if (c == '?'){
    SPI.transfer(0x06);
  }


/////////////////////////////////////////////////////////////////

  mCmd Request;
  SPI_readAnything(Request);

  if (Request.Instruction == IsThereData){
     sCmd Reply = {Yes,"This is a test message",Request.iParam +1, Request.fParam*2.0};
     SPI_writeAnything(Reply);
  }


}  // end of interrupt service routine (ISR) SPI_STC_vect

void loop (void)
{
  
}  // end of loop