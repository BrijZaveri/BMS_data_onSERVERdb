
void all_battery_params() {

  Counter = 0;
  int packetSize = CAN.parsePacket();
  //****************************************************************HARDWARE NUMBER***************************************************
      // Counter = 0;
      // int packetSize = CAN.parsePacket();
      const int MAX_SERIAL_LENGTH = 8;  // Maximum length of the serial number
      byte hardwarenumber[MAX_SERIAL_LENGTH];
      if (CAN.packetId() == 175705353)  // Green Tiger Serialnumber
      {
        while (CAN.available()) {
          byte Stored = CAN.read();
          hardwarenumber[Counter] = Stored;
          Counter++;

          if (Counter == MAX_SERIAL_LENGTH) {
            String asciiString = "";

            for (int i = 0; i < Counter; i++) {
              // char asciiChar = (char)hardwarenumber[i];
              char asciiChar = static_cast<char>(hardwarenumber[i]);
              if (isPrintable(asciiChar)) {
                asciiString += asciiChar;
              }
            }
            // Remove leading and trailing spaces
            asciiString.trim();

            // Concatenate the extracted serial number to the existing string
            concatenatedSerialNumber.concat(asciiString + "");
            Counter = 0;
            // Serial.print("BATTERY SERIAL NUMBER = ");
            // Serial.println(concatenatedSerialNumber.substring(0,16));
          }
        }
      }
  //************************************************************VOLTAGE & CURRENT**********************************************
  if (packetSize) {
    if (CAN.packetExtended()) {
      if (CAN.packetId() == 174918921)  // Green Tiger Battery Voltage & Current
      {
        while (CAN.available()) {
          Stored = CAN.read();
          Counter++;
          if (Counter == 1) {
            GTvBytes[0] = Stored;
          }

          if (Counter == 2) {
            GTvBytes[1] = Stored;
            Voltage = (GTvBytes[0] << 8) + GTvBytes[1];
          }

          if (Counter == 3) {
            GTcBytes[2] = Stored;
          }

          if (Counter == 4) {
            GTcBytes[3] = Stored;
            Current = (GTcBytes[2] << 8) + GTcBytes[3];
          }
          if (Counter == 5) {
            GTahBytes[4] = Stored;
          }
          if (Counter == 6) {
            GTahBytes[5] = Stored;
            remainingAmpereHour = (((GTahBytes[4] << 8) + GTahBytes[5]) / 10);
          }
        }
      }

      //**********************************************************************TEMPERATURE****************************************

      if (CAN.packetId() == 241962249)  // Green Tiger Battery Temp1,2,3,4,5
      {
        while (CAN.available()) {
          Stored = CAN.read();
          Counter++;

          if (Counter == 1) {
            temp[1] = Stored;
          }

          if (Counter == 2) {
            temp[2] = Stored;
          }

          if (Counter == 3) {
            temp[3] = Stored;
          }

          if (Counter == 4) {
            temp[4] = Stored;
          }

          if (Counter == 5) {
            temp[5] = Stored;
          }
        }
      }

      //****************************************************************SOC***********************************************************

      if (CAN.packetId() == 174984457)  // Green Tiger SOC
      {
        while (CAN.available()) {
          Stored = CAN.read();
          Counter++;

          if (Counter == 1) {
            GTsocBytes[2] = Stored;
          }

          if (Counter == 2) {
            GTsocBytes[2] = Stored;
            stateOfCharge = (GTsocBytes[1] << 8) + GTsocBytes[2];
            // Serial.println();
          }
        }
      }
      //*********************************************************CELL VOLTAGE 1 to 4*********************************************
      if (CAN.packetId() == 241437961)  // Green Tiger Battery 4 Cell voltages
      {
        while (CAN.available()) {
          Stored = CAN.read();
          Counter++;
          if (Counter == 1) {
            GTcellVBytes[0] = Stored;
          }

          if (Counter == 2) {
            GTcellVBytes[1] = Stored;
            CellVoltage[1] = (GTcellVBytes[0] << 8) + GTcellVBytes[1];
          }

          if (Counter == 3) {
            GTcellVBytes[2] = Stored;
          }

          if (Counter == 4) {
            GTcellVBytes[3] = Stored;
            CellVoltage[2] = (GTcellVBytes[2] << 8) + GTcellVBytes[3];
          }
          if (Counter == 5) {
            GTcellVBytes[4] = Stored;
          }
          if (Counter == 6) {
            GTcellVBytes[5] = Stored;
            CellVoltage[3] = (GTcellVBytes[4] << 8) + GTcellVBytes[5];
          }
          if (Counter == 7) {
            GTcellVBytes[6] = Stored;
          }
          if (Counter == 8) {
            GTcellVBytes[7] = Stored;
            CellVoltage[4] = (GTcellVBytes[6] << 8) + GTcellVBytes[7];
          }
        }
      }

      //**********************************************************CELL VOLTAGE 5 to 8*********************************************

      if (CAN.packetId() == 241503497)  // Green Tiger Battery 4 Cell voltages
      {
        while (CAN.available()) {
          Stored = CAN.read();
          Counter++;
          if (Counter == 1) {
            GTcellVBytes[8] = Stored;
          }

          if (Counter == 2) {
            GTcellVBytes[9] = Stored;
            CellVoltage[5] = (GTcellVBytes[8] << 8) + GTcellVBytes[9];
          }

          if (Counter == 3) {
            GTcellVBytes[10] = Stored;
          }

          if (Counter == 4) {
            GTcellVBytes[11] = Stored;
            CellVoltage[6] = (GTcellVBytes[10] << 8) + GTcellVBytes[11];
          }
          if (Counter == 5) {
            GTcellVBytes[12] = Stored;
          }
          if (Counter == 6) {
            GTcellVBytes[13] = Stored;
            CellVoltage[7] = (GTcellVBytes[12] << 8) + GTcellVBytes[13];
          }
          if (Counter == 7) {
            GTcellVBytes[14] = Stored;
          }
          if (Counter == 8) {
            GTcellVBytes[15] = Stored;
            CellVoltage[8] = (GTcellVBytes[14] << 8) + GTcellVBytes[15];
          }
        }
      }

      //*******************************************************CELL VOLTAGE 9 to 12*********************************************

      if (CAN.packetId() == 241569033)  // Green Tiger Battery 4 Cell voltages
      {
        while (CAN.available()) {
          Stored = CAN.read();
          Counter++;
          if (Counter == 1) {
            GTcellVBytes[16] = Stored;
          }

          if (Counter == 2) {
            GTcellVBytes[17] = Stored;
            CellVoltage[9] = (GTcellVBytes[16] << 8) + GTcellVBytes[17];
          }

          if (Counter == 3) {
            GTcellVBytes[18] = Stored;
          }

          if (Counter == 4) {
            GTcellVBytes[19] = Stored;
            CellVoltage[10] = (GTcellVBytes[18] << 8) + GTcellVBytes[19];
          }
          if (Counter == 5) {
            GTcellVBytes[20] = Stored;
          }
          if (Counter == 6) {
            GTcellVBytes[21] = Stored;
            CellVoltage[11] = (GTcellVBytes[20] << 8) + GTcellVBytes[21];
          }
          if (Counter == 7) {
            GTcellVBytes[22] = Stored;
          }
          if (Counter == 8) {
            GTcellVBytes[23] = Stored;
            CellVoltage[12] = (GTcellVBytes[22] << 8) + GTcellVBytes[23];
          }
        }
      }

      //*******************************************************CELL VOLTAGE 13 to 16*********************************************

      if (CAN.packetId() == 241634569)  // Green Tiger Battery 4 Cell voltages
      {
        while (CAN.available()) {
          Stored = CAN.read();
          Counter++;
          if (Counter == 1) {
            GTcellVBytes[24] = Stored;
          }

          if (Counter == 2) {
            GTcellVBytes[25] = Stored;
            CellVoltage[13] = (GTcellVBytes[24] << 8) + GTcellVBytes[25];
          }

          if (Counter == 3) {
            GTcellVBytes[27] = Stored;
          }

          if (Counter == 4) {
            GTcellVBytes[28] = Stored;
            CellVoltage[14] = (GTcellVBytes[27] << 8) + GTcellVBytes[28];
          }
          if (Counter == 5) {
            GTcellVBytes[29] = Stored;
          }
          if (Counter == 6) {
            GTcellVBytes[30] = Stored;
            CellVoltage[15] = (GTcellVBytes[29] << 8) + GTcellVBytes[30];
          }
          if (Counter == 7) {
            GTcellVBytes[31] = Stored;
          }
          if (Counter == 8) {
            GTcellVBytes[32] = Stored;
            CellVoltage[16] = (GTcellVBytes[31] << 8) + GTcellVBytes[32];
          }
        }
      }

      //**********************************************************CELL VOLTAGE 17 to 20*********************************************

      if (CAN.packetId() == 241700105)  // Green Tiger Battery Cell voltages
      {
        while (CAN.available()) {
          Stored = CAN.read();
          Counter++;
          if (Counter == 1) {
            GTcellVBytes[33] = Stored;
          }

          if (Counter == 2) {
            GTcellVBytes[34] = Stored;
            CellVoltage[17] = (GTcellVBytes[33] << 8) + GTcellVBytes[34];
          }

          if (Counter == 3) {
            GTcellVBytes[35] = Stored;
          }

          if (Counter == 4) {
            GTcellVBytes[36] = Stored;
            CellVoltage[18] = (GTcellVBytes[35] << 8) + GTcellVBytes[36];
          }
          if (Counter == 5) {
            GTcellVBytes[37] = Stored;
          }
          if (Counter == 6) {
            GTcellVBytes[38] = Stored;
            CellVoltage[19] = (GTcellVBytes[37] << 8) + GTcellVBytes[38];
          }
          if (Counter == 7) {
            GTcellVBytes[39] = Stored;
          }
          if (Counter == 8) {
            GTcellVBytes[40] = Stored;
            CellVoltage[20] = (GTcellVBytes[39] << 8) + GTcellVBytes[40];
          }
        }
      }
    }
    // delay(1000);
  }
}
