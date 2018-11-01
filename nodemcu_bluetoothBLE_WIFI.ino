/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>
#include  <SoftwareSerial.h>
#include <string.h>

int bluetoothTx = D2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = D3;  // RX-I pin of bluetooth mate, Arduino D3

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

const char* ssid     = "SHIVA";
const char* password = "";
char incoming_char = 0;
String content = "";
char inChar = 0;
//const char* host = "192.168.137.74";
const char* host = "192.168.0.109";
const char* streamId   = "....................";
const char* privateKey = "....................";

String para = ".\r";
void setup() {
  Serial.begin(115200);
  delay(10);

  bluetooth.begin(9600);  // The Bluetooth Mate defaults to 115200bps
  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  
  bluetooth.print("AT+DISI?");
  delay(10);
  String data = show();
  delay(1000);
  data.concat(para);
  
  WiFiClient client;
  const int httpPort = 8888;
  
  // Check if a client has connected
  if (!client.connect(host, httpPort)) {
  //  Serial.println("connection failed");
    return;
  }
  

  // This will send the request to the server
  
  client.println(data);

  // Read all the lines of the reply from server and print them to Serial
//
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  //Serial.println("closing connection");
}

//Function to print the bluetooth data as a whole string i.e by collecting all the character!
String show()
{
  content = "";
  while(bluetooth.available()!=0)
  {
   if( bluetooth.available() > 0 )
   {
 //Get the character from the cellular serial port.
 incoming_char = bluetooth.read();
 content = content + String(incoming_char);
 delay(50);
   }
  }
  Serial.print(content);
  return content;
  
}
