void CANSender0()     //x90
{
  CAN.beginExtendedPacket(0x18900140);                // SOC & Voltage
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.endPacket();
  // delay(1000);
}

void CANSender3()  //x93
{
  CAN.beginExtendedPacket(0x18930140);            //Remaining Ah
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.endPacket();
  // delay(1000);
}

void CANSender5()  //x95
{
  CAN.beginExtendedPacket(0x18950140);              //Cell voltage 1~48
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.endPacket();
  // delay(1000);
}

void CANSender6()
{
  CAN.beginExtendedPacket(0x18960140);            //Monomer temperature 1~16
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.write('0');
  CAN.endPacket();
  // delay(1000);
}

void send_hardware_serial_number_query2()                                       
{
  CAN.beginExtendedPacket(0x18570140);            //getting hardware serial number    
  CAN.write(00);
  CAN.write(00);
  CAN.write(00);
  CAN.write(00);
  CAN.write(00);
  CAN.write(00);
  CAN.write(00);
  CAN.write(00);
  CAN.endPacket();
  //  Serial.println("done");
  delay(3);
}
