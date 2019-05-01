/*
 * //////////////////////////////////////////////////////
 * Internet of Things Project
 * Aaron Walsh, Robert Moore, Olujide Egberongbe
 * //////////////////////////////////////////////////////
 */

//libraries included
#include <CheapStepper.h>
#include <Bridge.h>
#include <Blynk.h>
#include <BlynkSimpleYun.h>
#include <HttpClient.h>

CheapStepper stepper;
//here we declare our stepper using default pins:
//arduino pin <--> pins on ULN2003 board:
//8 <--> IN1
//9 <--> IN2
//10 <--> IN3
//11 <--> IN4

//characters for authentication
//olujide
char auth[] = "1e3559d0b8154744a50ecaa67c360527";

//aaron
//char auth[] = "b38cce33fe464f1492fb5bb940f1c0a3";

// Add your PushingBox Scenario DeviceID here:
char devid[] = "vF068878514F39A5";

char serverName[] = "api.pushingbox.com";
boolean DEBUG = true;

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
//int sensorValue;
void loop() 
{
  Blynk.run();
  
  //button status reads in PIN
  buttonStatus = digitalRead(3);
  
  if (buttonStatus == HIGH)
  {
    for(int x=0; x<2; x++)
    {
      for (int s=0; s<512; s++)
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
    
    // Initialize the client library
    HttpClient client;

    //Setup sensorValue to read a value from Analog Port A0
    int sensorValue = analogRead(A0);
  
    //Testing value - when sensor is not connected - comment out when sketch is shown to be working - and take value from A0 instead
    //sensorValue=1500;

    // Make a HTTP request:  
    String APIRequest;
    APIRequest = String(serverName) + "/pushingbox?devid=" + String(devid)+ "&IDtag=100&TimeStamp=50&TempC=200"+sensorValue;
    client.get (APIRequest);
  
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (client.available()) {
    char c = client.read();
  }
  
  Serial.flush();
  String UploadMessage;
  Serial.print("\n Uploaded temp value: ");
  //Serial.print(sensorValue);
  delay(5000);
  }
}
