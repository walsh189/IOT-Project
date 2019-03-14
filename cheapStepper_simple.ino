/*
 *///////////////////////////////////////////////////////
 * Internet of Things Project
 * Aaron Walsh, Robert Moore, Olujide Egberongbe
 * //////////////////////////////////////////////////////
 */

//libraries included
#include <CheapStepper.h>
#include <Bridge.h>
#include <Blynk.h>
#include <BlynkSimpleYun.h>

CheapStepper stepper;
//here we declare our stepper using default pins:
//arduino pin <--> pins on ULN2003 board:
//8 <--> IN1
//9 <--> IN2
//10 <--> IN3
//11 <--> IN4

//characters for authentication
char auth[] = "1e3559d0b8154744a50ecaa67c360527";

//boolean variable to save the direction of our rotation
boolean moveClockwise = true;

//set button status at 0
int buttonStatus = 0;

void setup() 
{
	//set up a serial connection and test print to the console
	Serial.begin(9600);
  
	//set the PIN and begin blynk
	pinMode(3, INPUT);
	Blynk.begin(auth);
}

void loop() {
	Blynk.run();
  
	//button status reads in PIN
	buttonStatus = digitalRead(3);
  
  
	if (buttonStatus == HIGH)
	{
		for(int x=0; x<2; x++)
		{
			for (int s=0; s<2048; s++)
			{
				// 4096 steps = full rotation using default values
				// this will loop 2048 times for a half rotation

				// let's move one "step" (of the 2048 per full rotation)
				stepper.step(moveClockwise);
				
				/* the direction is based on moveClockwise boolean:
				* true for clockwise, false for counter-clockwise
				*/

				//get the current step position of motor
				int nStep = stepper.getStep();

				//and if it's divisible by 64...
				if (nStep%64==0)
				{ 
					//let's print the position to the console
      
					Serial.print("current step position: "); Serial.print(nStep);
					Serial.println();
				}
			}
			//short delay
			delay(1000);

			//and switch directions for one more rotation
			moveClockwise = !moveClockwise;
		}
	} 
}


