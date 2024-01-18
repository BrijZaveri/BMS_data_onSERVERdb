
void ApI() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    //    http.begin("http://192.168.0.6:8091/api/DATAofESP");
    http.begin("http://intranet.joyebike.com:8092/api/BatteryTest");
    http.addHeader("ward-wizard", "272D3463-95A6-4611-9C52-17BC77E50BC8");
    http.addHeader("Content-Type", "application/json");


    StaticJsonDocument<1024> doc;
    float tolerance = 0.001;  // Adjust this tolerance value as needed
    doc["Battery_data_logger_ID"] = "CYCLER_36";
    doc["voltage"] = (Voltage * 0.1);
    doc["CurrentI"] = String(Current * 0.1,2);
    doc["soc"] = (stateOfCharge * 0.1);
    doc["remainingAh"] = remainingAmpereHour;
    doc["cellvoltage1"] = (CellVoltage[1] * 0.001);
    doc["cellvoltage2"] = (CellVoltage[2] * 0.001);
    doc["cellvoltage3"] = (CellVoltage[3] * 0.001);
    doc["cellvoltage4"] = (CellVoltage[4] * 0.001);
    doc["cellvoltage5"] = (CellVoltage[5] * 0.001);
    doc["cellvoltage6"] = (CellVoltage[6] * 0.001);
    doc["cellvoltage7"] = (CellVoltage[7] * 0.001);
    doc["cellvoltage8"] = (CellVoltage[8] * 0.001);
    doc["cellvoltage9"] = (CellVoltage[9] * 0.001);
    doc["cellvoltage10"] = (CellVoltage[10] * 0.001);
    doc["cellvoltage11"] = (CellVoltage[11] * 0.001);
    doc["cellvoltage12"] = (CellVoltage[12] * 0.001);
    doc["cellvoltage13"] = (CellVoltage[13] * 0.001);
    doc["cellvoltage14"] = (CellVoltage[14] * 0.001);
    doc["cellvoltage15"] = (CellVoltage[15] * 0.001);
    doc["cellvoltage16"] = (CellVoltage[16] * 0.001);
    doc["cellvoltage17"] = (CellVoltage[17] * 0.001);
    doc["cellvoltage18"] = (CellVoltage[18] * 0.001);
    doc["cellvoltage19"] = (CellVoltage[19] * 0.001);
    doc["cellvoltage20"] = (CellVoltage[20] * 0.001);
    doc["temp1"] = temp[1];
    doc["temp2"] = temp[2];
    doc["temp3"] = temp[3];
    doc["temp4"] = temp[4];
    doc["temp5"] = temp[5];

    // Assuming concatenatedSerialNumber contains the serial number
    if (concatenatedSerialNumber.length() > 16) {
      concatenatedSerialNumber = concatenatedSerialNumber.substring(0, 16);  // Truncate to 16 characters
    }

    doc["serialnumber"] = concatenatedSerialNumber;  // Assign the truncated serial number

    // Serial.print("DOC_SERIAL = ");
    // Serial.println(doc["serialnumber"].as<const char*>());  // Explicit conversion
    // Serial.println("Entire JSON Document:");
    serializeJson(doc, Serial);

    String payload;
    Serial.println(payload);
    serializeJson(doc, payload);
    // size_t payloadSize = measureJson(doc);

    // Print the calculated payload size
    // Serial.print("Payload size: ");
    // Serial.println(payloadSize);

    int httpCode = http.POST(payload);
    if (httpCode > 0) {
      String response = http.getString();
    //   Serial.print("HTTP Response Code: ");
    //   Serial.println(httpCode);
    //   Serial.print("HTTP Response: ");
    //   Serial.println(response);
    // } else {
      // Serial.println("Error on HTTP request");
    }
    http.end();
  }
  delay(7000);
}
