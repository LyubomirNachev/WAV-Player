#include <TMRpcm.h>
#include <SPI.h>
#include <SdFat.h>
#define CHIP_SELECT_PIN  10
#define SPEAKER_PIN      9
TMRpcm tmrpcm;
SdFat sd;
void setup( ) {
    Serial.begin( 9600 );
  tmrpcm.speakerPin = SPEAKER_PIN;
  
  while ( !Serial ) /*mt*/ ;
  if ( !sd.begin( CHIP_SELECT_PIN ) )
    Serial.println( "SD fail" );
  else {
    tmrpcm.play( "MBT Polov Jivot.wav" );
    delay( 5 );
  }
}

void loop( ) {
}
