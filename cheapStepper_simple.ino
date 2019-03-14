

/*
 * cheapStepper_simple.ino
 * ///////////////////////////////////////////
 * using CheapStepper Arduino library v.0.2.0
 * created by Tyler Henry, 7/2016
 * ///////////////////////////////////////////
 * 
 * this sketch illustrates basic step() functionality of the library:
 * the stepper performs a full rotation, pauses 1 second,
 * then does a full rotation in the other direction, and so on
 * 
 * //////////////////////////////////////////////////////
 */

// first, include the library :)
#include <CheapStepper.h>
#include <Bridge.h>
#include <Blynk.h>
#include <BlynkSimpleYun.h>

CheapStepper stepper;
// here we declare our stepper using default pins:
// arduino pin <--> pins on ULN2003 board:
// 8 <--> IN1
// 9 <--> IN2
// 10 <--> IN3
// 11 <--> IN4

char auth[] = "1e3559d0b8154744a50ecaa67c360527";

 // let's create a boolean variable to save the direction of our rotation

boolean moveClockwise = true;
int buttonStatus = 0;

void setup() {
  
  // let's just set up a serial connection and test print to the console
  
  Serial.begin(9600);
  
  Serial.println("Ready to start moving!");
  pinMode(3, INPUT);
  Blynk.begin(auth);
}

void loop() {
  
  Blynk.run();
  // let's move a full rotation (4096 mini-steps)
  // we'll go step-by-step using the step() function
  buttonStatus = digitalRead(3);
  
  
  if (buttonStatus == HIGH){
    for(int x=0; x<2; x++){
  for (int s=0; s<2048; s++){
    //make number go up every loop to 2 times then reset the number
    //4096
    // this will loop 4096 times
    // 4096 steps = full rotation using default values
    /* Note:
     * you could alternatively use 4076 steps... 
     * if you think your 28BYJ-48 stepper's internal gear ratio is 63.68395:1 (measured) rather than 64:1 (advertised)
     * for more info, see: http://forum.arduino.cc/index.php?topic=71964.15)
     */

    // let's move one "step" (of the 4096 per full rotation)
    
    stepper.step(moveClockwise);
    /* the direction is based on moveClockwise boolean:
     * true for clockwise, false for counter-clockwise
     * -- you could also say stepper.stepCW(); or stepper.stepCCW();
     */

    // now let's get the current step position of motor
    
    int nStep = stepper.getStep();

    // and if it's divisible by 64...
    
    if (nStep%64==0){ 

      // let's print the position to the console
      
      Serial.print("current step position: "); Serial.print(nStep);
      Serial.println();

      
    }
    
  }
  delay(1000);

  // and switch directions before starting loop() again
  
  moveClockwise = !moveClockwise;
  }
}
  
}


