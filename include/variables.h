#include <Arduino.h>


// TaskHandle_t taskHandle1;
// TaskHandle_t taskHandle2;

// CAN variables
byte Counter = 0;
byte Stored;
float Voltage;
float Current;
float modifiedCurrent;
int speed = 0;
int rpm;
int stateOfCharge, remainingAmpereHour, maxParallelVoltage, minParallelVoltage;
int unitVoltage[3] = {0, 0, 0};
int CellVoltage[20] = {0};
byte temp[5];
// DALY specific bytes
byte dal90Bytes[8] = {0};
byte dal91Bytes[7] = {0};
byte dal92Bytes[4] = {0};
byte dal93Bytes[8] = {0};
byte dal94Bytes[5] = {0};
byte dal95Bytes[7] = {0};
byte dal96Bytes[2] = {0};

// GT specific bytes
byte GTvBytes[2] = {0};
byte GTcBytes[2] = {0};
byte GTahBytes[2] = {0};
byte GTsocBytes[8] = {0};
byte GTcellVBytes[20] = {0};

// Other variables
String concatenatedSerialNumber;
String asciiString;  // To store ASCII characters
String combinedString;  // To store combined substrings
long decimalValue;
int seconds;
char firstByte;


// Function Declarations
void connectToWiFi();
void setup();
void task1Code(void* pvParameters);
void task2Code(void* pvParameters);