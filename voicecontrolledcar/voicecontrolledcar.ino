//INSTALL ADDITIONAL LIBRARIES ACCORDINGLY 

/************************ Adafruit IO Configuration *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME    "-->username---<"
#define IO_KEY         "-->inputkey---<"

/******************************* WIFI Configuration **************************************/

#define WIFI_SSID       "--->wifissid---<"
#define WIFI_PASS       "---->wifipass---<"

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

/************************ Main Program Starts Here *******************************/
#include <ESP8266WiFi.h>
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include <ArduinoHttpClient.h>

// These are used to set the direction of the bridge driver.
#define ENB D3      //ENB
#define MOTORB_1 D4 //IN3
#define MOTORB_2 D5 //IN4
#define MOTORA_1 D7 //IN1
#define MOTORA_2 D6 //IN2
#define ENA D8      //ENA

AdafruitIO_Feed *command = io.feed("voice-commands"); // Set up the 'command' feed

// SETUP
void setup()
{
  // Configure pins
  pinMode(ENA, OUTPUT);
  pinMode(MOTORA_1, OUTPUT);
  pinMode(MOTORA_2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(MOTORB_1, OUTPUT);
  pinMode(MOTORB_2, OUTPUT);

  // disable both motors
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  
  // Start serial communication
  Serial.begin(9600);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'command' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  command->onMessage(handleMessage);  

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(50);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

// MAIN CODE
void loop()
{
  io.run();
}

// this part of the code runs whenever there's a new message on Adafruit.io feed
void handleMessage(AdafruitIO_Data *data) {
  
  String commandStr = data->toString(); // store the incoming commands in a string
  
  // received message
  Serial.print("received <- ");
  Serial.println(commandStr);

  String cmd;
  int angle;

  // separate text and number ingredients
  for (int i = 0; i < commandStr.length(); i++) {
    if (commandStr.substring(i, i+1) == ",") {
      cmd = commandStr.substring(0, i);
      angle = commandStr.substring(i+2).toInt();
      break;
    }
  }

  // print command
  Serial.println("Printing command : ");
  Serial.println(cmd);
  Serial.println("Printing angle : ");
  Serial.println(angle);
  
  // perform movements
  // LEFT
  if (cmd.equalsIgnoreCase("left")){    
    Serial.println("Turning left");
    digitalWrite(ENA,HIGH);
    digitalWrite(ENB,HIGH);
    digitalWrite(MOTORA_1,HIGH);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,HIGH);
    digitalWrite(MOTORB_2,LOW);
    delay(angle*9);
    Serial.println("Stop");
    digitalWrite(ENA,LOW);
    digitalWrite(ENB,LOW);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,LOW); 
  }
  // RIGHT
  if (cmd.equalsIgnoreCase("right")){    
    Serial.println("Turning right");
    digitalWrite(ENA,HIGH);
    digitalWrite(ENB,HIGH);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,HIGH);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,HIGH);
    delay(angle*9 );
    Serial.println("Stop");
    digitalWrite(ENA,LOW);
    digitalWrite(ENB,LOW);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,LOW);
  }
  //  
  if (cmd.equalsIgnoreCase("forward")){    
    Serial.println("Moving forward");
    digitalWrite(ENA,HIGH);
    digitalWrite(ENB,HIGH);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,HIGH);
    digitalWrite(MOTORB_1,HIGH);
    digitalWrite(MOTORB_2,LOW);
    delay(angle*100);
    Serial.println("Stop");
    digitalWrite(ENA,LOW);
    digitalWrite(ENB,LOW);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,LOW);
  }
  // back
  if (cmd.equalsIgnoreCase("back")){    
    Serial.println("Moving back");
    digitalWrite(ENA,HIGH);
    digitalWrite(ENB,HIGH);
    digitalWrite(MOTORA_1,HIGH);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,HIGH);
    delay(angle*100);
    Serial.println("Stop");
    digitalWrite(ENA,LOW);
    digitalWrite(ENB,LOW);
    digitalWrite(MOTORA_1,LOW);
    digitalWrite(MOTORA_2,LOW);
    digitalWrite(MOTORB_1,LOW);
    digitalWrite(MOTORB_2,LOW);
  }  
} 
