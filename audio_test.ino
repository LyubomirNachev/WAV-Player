#include <TMRpcm.h>
#include <SPI.h>
#include <SD.h>
#define CHIP_SELECT_PIN  10
#define SPEAKER_PIN      9
TMRpcm tmrpcm;

void setup( ) {
    Serial.begin( 9600 );
  tmrpcm.speakerPin = SPEAKER_PIN;
  
  while ( !Serial ) /*mt*/ ;
  if ( !SD.begin( CHIP_SELECT_PIN ) )
    Serial.println( "SD fail" );
  else {
    tmrpcm.play( "2.WAV" );
    delay( 5 );
  }
}

void loop( ) {
}
