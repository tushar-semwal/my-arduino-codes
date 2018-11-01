
/*****REMEMBER TO USE NO LINE ENDING IN SERIAL MONITOR*****/

#include <SoftwareSerial.h>  

int bluetoothTx = 12;  // TX pin of bluetooth HM10, Arduino D2
int bluetoothRx = 13;  // RX pin of bluetooth HM10, Arduino D3

char incoming_char = 0;
String content = "";
char inChar = 0;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  Serial.begin(115200);  // Begin the serial monitor at 9600bps

  bluetooth.begin(9600);  // The Bluetooth  defaults to 9600
  delay(100);  // Short delay,
}
//
void loop()
{

  delay(1);
  if(bluetooth.available())
  {
    incoming_char = bluetooth.read();
    Serial.write(incoming_char);
    content.concat(incoming_char);
  }
  if(Serial.available())  // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    content = "";
    bluetooth.write(Serial.read());
  }
  //show1();
  
  
  
  // and loop forever and ever!
}

String show1()
{
  content = "";
  while(bluetooth.available()!=0)
  {
   if( bluetooth.available() > 0 )
   {
 //Get the character from the cellular serial port.
 incoming_char = bluetooth.read();
 content = content + String(incoming_char);
 //content.concat(String(incoming_char));
// swSer.write(incoming_char);
 delay(10);
   }
  }
 
  Serial.print(content);
   
  return content;
  
}
