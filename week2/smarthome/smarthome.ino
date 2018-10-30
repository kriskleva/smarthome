/******************************************************************************
 * Basic Example for us to post interesting info to our datastore
 *****************************************************************************/

#include "backoff.h"
#include "esp8266_wifi.h"
#include "cli.h"

// remember our setup
void setup(){

  // listen
  Serial.begin(115200);

  // time to talk about wifi
  setupWifi();

  // turn it on
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  // if we are killing our connection, backoff
  if (backoff()) {

    // send sensor data
    sendTelemetry();
    
    delay(1000);
    
    getConfig();
  }
  delay(10);
  cliLoop();
}

/*
void loop(){
  analogWrite(RED, random(0,1023));
  analogWrite(GREEN, random(0,1023));
  digitalWrite(BLUE, HIGH);
  
  delay(1000);

  buttonValue = digitalRead(BUTTON);
  digitalWrite(BLUE, LOW);
  Serial.print("BUTTON: ");
  Serial.println(buttonValue);

  sensorValue = analogRead(sensorPin);
  Serial.print("SENSOR: ");
  Serial.println(sensorValue, DEC);
}
*/
