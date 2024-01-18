/*
 *      Copyright (c) 2022 Joy ebike.
 *      All rights reserved.
 *      Use of copyright notice does not imply publication.
 *      @author: Brij Zaveri
 *      Date & Time: 01-03-2022, 15:00:00
 *
 *
 *                      CONFIDENTIAL INFORMATION
 *                      ------------------------
 *      This Document contains Confidential Information or Trade Secrets,
 *      or both, which are the property of Joy ebike.
 *      This document may not be copied, reproduced, reduced to any
 *      electronic medium or machine readable form or otherwise
 *      duplicated and the information herein may not be used,
 *      disseminated or otherwise disclosed, except with the prior
 *      written consent of Joy ebike.
 *
 */

/************************************************************************
 * Include Header Files
 ************************************************************************/


#include <Arduino.h>
#include <CAN.h>
#include <variables.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <sender.h>
#include <DALY_sender.h>
#include <GT_receiver.h>
#include <sending_to_server.h>
#include <DALY_receiver.h>
// **************************************************************************
TaskHandle_t Task1;
TaskHandle_t Task2;


// Constants and Definitions
// #define NUMBER_OF_CELLS 20
// #define NUMBER_OF_WIFI_CREDENTIALS 3
#define CAN_BAUD_RATE 250E3
// #define TASK_STACK_SIZE 10000
// #define TASK_PRIORITY 1

// Function declarations
void Task1code(void* pvParameters);
void Task2code(void* pvParameters);

struct WiFiCredential {
  const char* ssid;
  const char* password;
};
WiFiCredential wifiCredentials[] = {                    //company's on-workfloor wifi credentials.
  {"WWBatt", "Ward@2023bat"},
  {"WARDJOY", "WaRd@2023#"},
  {"joyebike", "joyebike"},
  // Add more SSID and password pairs as needed
};

WiFiClient wifiClient;

void connectToWiFi() {
  int numNetworks = sizeof(wifiCredentials) / sizeof(wifiCredentials[0]);

  while (true) {
    for (int i = 0; i < numNetworks; i++) {
      Serial.printf("Connecting to %s...\n", wifiCredentials[i].ssid);

      WiFi.begin(wifiCredentials[i].ssid, wifiCredentials[i].password);
      int attempts = 0;

      while (WiFi.status() != WL_CONNECTED && attempts < 10) {
        delay(1000);
        Serial.print(".");
        digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
        attempts++;
      }

      if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("\nConnected to %s\n", wifiCredentials[i].ssid);
        digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
        return;                            // Exit the function if connected
      } else {
        Serial.printf("\nFailed to connect to %s\n", wifiCredentials[i].ssid);
      }
    }

    // Add a delay before retrying to connect
    delay(5000); // You can adjust the delay time as needed
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  //************************************************connect to WiFi****************/
  connectToWiFi();
  //***************************************************Establish CAN****************
  while (!CAN.begin(CAN_BAUD_RATE)) {
    // Serial.println("Starting CAN failed!");
  }
  xTaskCreatePinnedToCore(
    Task1code, /* Task function. */
    "Task1",   /* name of task. */
    10000,     /* Stack size of task */
    NULL,      /* parameter of the task */
    1,         /* priority of the task */
    &Task1,    /* Task handle to keep track of created task */
    0);        /* pin task to core 0 */
  delay(500);

  xTaskCreatePinnedToCore(
    Task2code, /* Task function. */
    "Task2",   /* name of task. */
    10000,     /* Stack size of task */
    NULL,      /* parameter of the task */
    1,         /* priority of the task */
    &Task2,    /* Task handle to keep track of created task */
    1);        /* pin task to core 1 */
  delay(500);
}

void Task1code(void* pvParameters) {
  for (;;) {
    CANSender_all();                      //GT sender
    CANSender0();                         //DALY sender
    CANSender3();                         //DALY sender
    CANSender5();                         //DALY sender
    CANSender6();                         //DALY sender
    send_hardware_serial_number_query();  //GT hardware number
    send_hardware_serial_number_query2(); //DALY hardware number 
    ApI();
  }
}

void Task2code(void* pvParameters) {
  for (;;) {
    Battery();              //DALY receiver
    all_battery_params();  //GT receiver
  }
}

void loop() {
}
