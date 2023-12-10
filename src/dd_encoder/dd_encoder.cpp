#include "dd_encoder.h"
#include "Arduino.h"


/*     Arduino Rotary Encoder Tutorial
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */
 


 uint16_t counter = 0; 
 int aState;
 int aLastState;  

 uint16_t  dd_encoder_get_counter(){
    return counter;
 }

uint16_t  dd_encoder_set_counter(uint16_t cnt){
    counter = cnt;
    return counter;
}
uint16_t  dd_encoder_reset_counter(){
    counter = dd_encoder_set_counter(0);
    return counter;
}

 void dd_encoder_setup() { 
   pinMode (DD_ENCODER_PH_A,INPUT);
   pinMode (DD_ENCODER_PH_B,INPUT);
   
   // Reads the initial state of the outputA
   aLastState = digitalRead(DD_ENCODER_PH_A);   
 } 

 void dd_encoder_loop() { 
   aState = digitalRead(DD_ENCODER_PH_A); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(DD_ENCODER_PH_B) != aState) { 
       counter ++;
     } else {
       counter --;
     }
    //  Serial.print(F("Position: "));
    //  Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
 }

 void dd_encoder_report(){
    uint16_t cnt = dd_encoder_get_counter();
    Serial.print(F("ED_ENCD: Counter = "));
    Serial.println(cnt);
 }