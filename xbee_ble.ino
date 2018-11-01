
#include <SoftwareSerial.h>

int bluetoothTx = 12;  // TX pin of bluetooth HM10, Arduino D2
int bluetoothRx = 13;  // RX pin of bluetooth HM10, Arduino D3

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

SoftwareSerial swSer(5, 6);

char incoming_char = 0;
String content = "";
char inChar = 0;

void setup() {
  Serial.begin(115200);
  swSer.begin(9600);
  bluetooth.begin(9600);  // The Bluetooth  defaults to 9600
  delay(100);  // Short delay
  delay(800);
  Serial.println("\nSoftware serial test started");

  for (char ch = 'a'; ch <= 'z'; ch++) {
    swSer.write(ch);
  }
  swSer.println("");

}

  
void loop() {
 
//  while (Serial.available() > 0) {
  //  swSer.write(Serial.read());
  //}
//  delay(10);
  //show();
  
delay(1);
 /* while(bluetooth.available())  // If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
    
    //Serial.write(bluetooth.read()); 
    swSer.write(bluetooth.read()); 
    
    swSer.write('\n'); 
  }
 */ 
  if(Serial.available())  // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.write(Serial.read());
  }
  if( bluetooth.available() > 0 )
  {
  show1();
  }
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
 //content = content + String(incoming_char);
 content.concat(String(incoming_char));
// swSer.write(incoming_char);
 delay(50);
   }
  }
  Serial.print(content);
  for(int i =0;i<content.length();i++)
  {
    swSer.write(content[i]);
    delay(10);
  }
  
  swSer.println("");
  
  return content;
  
}

String show()
{
  content = "";
  while(swSer.available()!=0)
  {
   if( swSer.available() > 0 )
   {
 //Get the character from the cellular serial port.
 incoming_char = swSer.read();
 content = content + String(incoming_char);
 delay(50);
   }
  }
  Serial.print(content);
  return content;
  
}
