#include <SoftwareSerial.h>         // serial library

SoftwareSerial esp8266(2, 3);       // get object from serial
#define BaudRate 9600               // baud rate
#define DEBUG true                  // option for debug or not

#define redLED 13                   // define red led
#define GreenLED 12                 // define green led
#define BlueLED 11                  // define blue led
#define YellowLED 10                // define yellow led

String data;                        // variable contains responsed data
int pinNumber;                      // pinNumber which its button push
int connectionID;                   // connection ID to close it after open
String test = "+IPD,";              // to search for it "+IPD,0,314,GET /:80/?pin=13 HTTP/1.1"

void setup()                        // setup function
{
  Serial.begin(BaudRate);           // setup serial to selected baud rate
  esp8266.begin(BaudRate);          // setup serial to selected baud rate

  pinMode(redLED, OUTPUT);          // define red led as output
  pinMode(GreenLED, OUTPUT);        // define green led as output
  pinMode(BlueLED, OUTPUT);         // define blue led as output
  pinMode(YellowLED, OUTPUT);       // define yellow led as output

  digitalWrite(redLED, HIGH);       // put higth on red led at beginning
  digitalWrite(GreenLED, LOW);      // put low on green led
  digitalWrite(BlueLED, LOW);       // put low on blue led
  digitalWrite(YellowLED, LOW);     // put low on yellow led

  InitWifiModule();                 // wifi_init function to setup esp8266 (reset, join acess point, get IP address ..... )

  digitalWrite(redLED, LOW);        // for indication low red led  
}
void loop()                                               // loop function
{
  if (esp8266.available())    
  {
    data = esp8266.readString();
    Serial.println(data);
    Get_Pin_Number(data, &connectionID, &pinNumber);
    Serial.print("connectionID: ");
    Serial.println(connectionID);
    Serial.print("pinNumber: ");
    Serial.println(pinNumber);
    Serial.print("pinState: ");
    Serial.println(!digitalRead(pinNumber));
    digitalWrite(pinNumber, !digitalRead(pinNumber));
    String closeCommand = "AT+CIPCLOSE=";
    closeCommand += connectionID;
    closeCommand += "\r\n";
    sendData(closeCommand, 1000, DEBUG);
  }
  if (Serial.available())
  {
    esp8266.print(Serial.readString());
    Serial.print(esp8266.readString());
  }
}
void Get_Pin_Number(String data, int* connectionID, int* pinNumber)
{
  int count = 0;
  int count2 = 0;
lable:
  if (data[count] == test[count2])
  {
    count++;
    count2++;
  }
  else
    count++;
  if (count2 <= 4)
    goto lable;
  *connectionID =  data[count] - '0';
  while (data[count] != '=')
    count++;
  count++;
  *pinNumber = (data[count++] - '0') * 10 + data[count++] - '0';
  //*pinState = data[count] - '0';
}
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      char c = esp8266.read();
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}
void InitWifiModule()
{
  sendData("AT\r\n", 1000, DEBUG);                                      // AT test command
  delay(1000);          
  sendData("AT+RST\r\n", 2000, DEBUG);                                  // reset module
  delay(1000);  
  sendData("AT+GMR\r\n", 1000, DEBUG);                                  // get esp version
  delay(1000);
  sendData("AT+CWJAP=\"THEKING\",\"862021TOKA##\"\r\n", 2000, DEBUG);   // join local network 
  delay (5000);
  sendData("AT+CWMODE=3\r\n", 1500, DEBUG);                             // set esp mode 1 = station, 2 = AP, 3 = station/AP
  delay (2000);
  sendData("AT+CIPMUX=1\r\n", 1500, DEBUG);                             // set multiple connection
  delay (2000);
  sendData("AT+CIPSERVER=1,80\r\n", 1500, DEBUG);                       // creat server on port 80
  delay (2000);
  sendData("AT+CIFSR\r\n", 1500, DEBUG);                                // get IP address
  delay (2000);
}
