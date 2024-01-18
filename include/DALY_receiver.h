
void processVoltageCurrentSoc() {
    for (int i = 0; CAN.available() && i < 8; ++i) {
        byte stored = CAN.read();
        switch (i) {
            case 0:
                dal90Bytes[0] = stored;
                break;
            case 1:
                dal90Bytes[1] = stored;
                Voltage = (dal90Bytes[0] << 8) + dal90Bytes[1];
                break;
            case 4:
                dal90Bytes[4] = stored;
                break;
            case 5:
                dal90Bytes[5] = stored;
                Current = (dal90Bytes[4] << 8) + dal90Bytes[5];
                modifiedCurrent = (30000 - Current) * 0.1f;
                break;
            case 6:
                dal90Bytes[6] = stored;
                break;
            case 7:
                dal90Bytes[7] = stored;
                stateOfCharge = (dal90Bytes[6] << 8) + dal90Bytes[7];
                break;
        }
    }
}

void processRemainingAh() {
    for (int i = 0; CAN.available() && i < 8; ++i) {
        byte stored = CAN.read();
        switch (i) {
            case 0:
                dal93Bytes[0] = stored;
                break;
            case 1:
                dal93Bytes[1] = stored;
                break;
            case 2:
                dal93Bytes[2] = stored;
                break;
            case 3:
                dal93Bytes[3] = stored;
                break;
            case 4:
                dal93Bytes[4] = stored;
                break;
            case 5:
                dal93Bytes[5] = stored;
                break;
            case 6:
                dal93Bytes[6] = stored;
                break;
            case 7:
                dal93Bytes[7] = stored;
                remainingAmpereHour = ((dal93Bytes[4] << 8) + (dal93Bytes[5] << 8) + (dal93Bytes[6] << 8) + dal93Bytes[7]);
                break;
        }
    }
}

void processCellVoltage() {
    for (int i = 0; CAN.available() && i < 7; ++i) {
        byte stored = CAN.read();
        switch (i) {
            case 0:
                dal91Bytes[0] = stored;
                break;
            case 1:
                dal91Bytes[1] = stored;
                break;
            case 2:
                dal91Bytes[2] = stored;
                unitVoltage[0] = (dal91Bytes[1] << 8) + dal91Bytes[2];
                break;
            case 3:
                dal91Bytes[3] = stored;
                break;
            case 4:
                dal91Bytes[4] = stored;
                unitVoltage[1] = (dal91Bytes[3] << 8) + dal91Bytes[4];
                break;
            case 5:
                dal91Bytes[5] = stored;
                break;
            case 6:
                dal91Bytes[6] = stored;
                unitVoltage[2] = (dal91Bytes[5] << 8) + dal91Bytes[6];
                break;
        }
    }
}

void processMonomerTemperature() {
    for (int i = 0; CAN.available() && i < 2; ++i) {
        byte stored = CAN.read();
        switch (i) {
            case 0:
                dal96Bytes[0] = stored;
                break;
            case 1:
                dal96Bytes[1] = stored;
                temp[1] = dal96Bytes[1] - 40;
                break;
        }
    }
}

void processHardwareNumber() {
    byte hardwareNumber[8];
    int counter = 0;
    while (CAN.available() && counter < 8) {
        hardwareNumber[counter++] = CAN.read();
    }
    if (counter == 8) {
        String asciiString;
        for (int i = 0; i < 8; ++i) {
            char asciiChar = static_cast<char>(hardwareNumber[i]);
            if (isPrintable(asciiChar)) {
                asciiString += asciiChar;
            }
        }
        asciiString.trim();
        concatenatedSerialNumber.concat(asciiString);
    }
}

void Battery() {
    Counter = 0;
    int packetSize = CAN.parsePacket();

    if (!packetSize) return;

    if (CAN.packetExtended()) {
        switch (CAN.packetId()) {
            case 412106753:  // VOLTAGE CURRENT SOC
                processVoltageCurrentSoc();
                break;
            case 412303361:  // REMAINING AH
                processRemainingAh();
                break;
            case 412434433:  // CELL VOLTAGE 1~48
                processCellVoltage();
                break;
            case 412499969:  // MONOMER TEMPERATURE 1~16
                processMonomerTemperature();
                break;
            case 408371201:  // HARDWARE NUMBER
                processHardwareNumber();
                break;
            default:
                // Handle unknown packet ID or do nothing
                break;
        }
    }
}
