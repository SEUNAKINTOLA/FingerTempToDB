// Created by Akintola Oluwaseun
// Connect yellow of sensor 1 to pin7, and blue to pin 6
// Connect yellow of sensor 2 to pin5, and blue to pin4
// use enrol sketch to enrol a print to ID8 of sensor 1
// use this sketch to send the template from sensor 1 to 2
// this would also delete the template from sensor 1
// use fingerprint sketch to confirm if the sketch is now on sensor 2


/*
TODO:
1. send buff to a server online, use a php code to receive "buff" and
save in database
2. Write a php code that can read the the value of "buff"
from db given the user code, name, or id
3. arduino sketch to receive the code from the php file and 
store it as "buff" thus update fingerprint sensor connected
*/

#include <SoftwareSerial.h>
#include <FPM.h>
#include <SPI.h>
#include <Ethernet.h>
  EthernetClient client;

#define BUFF_SZ 512
// Download a template, delete it, print it, and upload it to a different flash location

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE/YELLOW wire)
SoftwareSerial mySerial(7, 6);

FPM finger;
String aaa;
String bbb;
String ccc;
String ddd;
String eee;
String fff;

char resource; 

void setup()  
{

  Serial.begin(9600);
  Serial.println("fingertest");
  mySerial.begin(57600);

  
  if (finger.begin(&mySerial)) {
    Serial.println("Found fingerprint sensor!");
    Serial.print("Capacity: "); Serial.println(finger.capacity);
    Serial.print("Packet length: "); Serial.println(finger.packetLen);
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }
  Serial.println("Send any character to continue...");
  
  while (Serial.available() == 0);
  
  getTemplate(1);  // download template at #4 (if it exists) to the buffer; first enroll a finger at that location

 // sendTemplate(4);   // upload template in buffer to #8; run fingerprint match example to verify that the new template is now at #8
//getTemp2();
//aaa +=fff;
//getTemp3();
//aaa +=fff;
//getTemp4();
//aaa +=fff;
//getTemp5();
}

void loop()
{

}

uint8_t buff[BUFF_SZ];

void getTemplate(uint16_t id)
{
 uint8_t p = finger.loadModel(id);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.print("template "); Serial.print(id); Serial.println(" loaded");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return;
    default:
      Serial.print("Unknown error "); Serial.println(p);
      return;
  }

  // OK success!

  p = finger.getModel();
  switch (p) {
    case FINGERPRINT_OK:
      break;
   default:
      Serial.print("Unknown error "); Serial.println(p);
      return;
  }
  
  bool last;
  int count = 0;
  uint16_t buflen = 512;
  uint16_t pos = 0;
  
  while (true){
    bool ret = finger.readRaw(buff + pos, ARRAY_TYPE, &last, &buflen);
    if (ret){
      count++;
      pos += buflen;
      buflen = BUFF_SZ - pos;
      if (last)
        break;
    }
    else {
      Serial.println("Error receiving packet");
      return;
    }
  }
  
 /* 
int cc;
Serial.println("got here1");
  for (int i = 0; i < 100; i++){
     cc = buff[i];
      fff +=String(cc)+" ";
    }
      Serial.println(fff);
sendRequest(fff);
return;
*/

  
int cc;

Serial.println("got here1");
  for (int i = 0; i < 32; i++){
    for (int j = 0; j < 16; j++){
     //Serial.print(buff[i*16 + j], HEX);
     cc = buff[i*16 + j];
     Serial.print(cc);
Serial.print(" ");
    }
   Serial.println();
  }

}


void getTemp2(){
    int cc;
    fff = " ";
Serial.println("got here2");
  for (int i = 100; i < 200; i++){
     cc = buff[i];
   
          fff +=String(cc, HEX)+" ";
     }
  Serial.println(fff);
bbb = fff;
  return;
}

void getTemp3(){
    int cc;
    fff = " ";
Serial.println("got here3");
  for (int i = 200; i < 300; i++){
     cc = buff[i];
   
          fff +=String(cc, HEX)+" ";
     }
  Serial.println(fff);
ccc = fff;
  return;
}

void getTemp4(){
    int cc;
    fff = " ";
Serial.println("got here4");
  for (int i = 300; i < 400; i++){
     cc = buff[i];
   
          fff +=String(cc, HEX)+" ";
     }
  Serial.println(fff);
ddd = fff;
  return;
}

void getTemp5(){
  int cc;
fff = " ";
Serial.println("got here5");
  for (int i = 400; i < 513; i++){
     //Serial.print(buff[i*16 + j], HEX);
     cc = buff[i];  
          fff +=String(cc, HEX)+" ";
 }

   Serial.println(fff);

 Serial.println("got here final");
  
}

void sendTemplate(uint16_t id){
      
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 2);

      Ethernet.begin(mac, ip);
    delay(7000);



  char server[] = "whistleblower.ng";    // change server to get file from here

    if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /getwhistlefeed.php?email="+bbb+" HTTP/1.0");  // change resource to get here
    client.println("Host: whistleblower.ng");                 // change resource host here
    client.println("Connection: close");
    client.println();
    }
    if(client.available()){
    char c = client.read();
    Serial.println(c);
    }
   
  return;
}


// Send the HTTP GET request to the server
void sendRequest(String resource) {
  Serial.print("GET ");
  Serial.println(resource);
  client.print("GET ");
  client.print(resource);
  client.println(" HTTP/1.0");
  client.print("Host: ");
  client.println("whistleblower.ng");
  client.println("Connection: close");
  client.println();
}


