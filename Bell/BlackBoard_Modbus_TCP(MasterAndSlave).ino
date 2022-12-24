/*
  Modbus-Arduino Example - Test Holding Register (Modbus IP ESP8266)
  Configure Holding Register (offset 100) with initial value 0xABCD
  You can get or set this holding register
  Original library
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino

  Current version
  (c)2017 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
*/

#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else //ESP32
 #include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>

// Modbus Registers Offsets
const int TEST_HREG = 100;
//ตััง Static IP
IPAddress BlackboardIP(192,168,1,160);
IPAddress RedboardIP(192,168,1,152);
IPAddress DoitboardIP(192,168,1,170);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255, 255, 254, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

const int LOOP_COUNT = 10; //for slave
//ModbusIP object
ModbusIP mb;
ModbusIP sl;
/*debounce*/
boolean buttonState;
boolean lastState;
boolean state = HIGH;
boolean reading;
/*debounce*/
const int buttonPin = 2;//2
  
void setup() {
  Serial.begin(115200);
 
  WiFi.begin("micro_2.4G", "micro001");
  pinMode(0, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(0,LOW);
  /*case upload to Black board*/
  // if (!WiFi.config(BlackboardIP, gateway, subnet, primaryDNS, secondaryDNS)) {
  //   Serial.println("STA Failed to configure");
  // }
  /*case upload to Black board*/

  /*case upload to red board*/
  // if (!WiFi.config(RedboardIP, gateway, subnet, primaryDNS, secondaryDNS)) {
  //   Serial.println("STA Failed to configure");
  // }
  /*case upload to red board*/

  /*case upload to Doit board*/
  if (!WiFi.config(BlackboardIP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
  /*case upload to Doit board*/

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mb.server();
  sl.client();
  mb.addHreg(TEST_HREG,0,10);
  // mb.Hreg(TEST_HREG,16);
  // mb.addCoil(101,false,10);
}
  uint16_t res = 9999; //for slave Redboard
  bool c;
  uint16_t val = 8888; //for slave Blackboard
  uint8_t show = LOOP_COUNT; //for slave
void loop() {
   //Call once inside loop() - all magic here
   /*case upload to black board*/
  //  for(int i = 0 ;i<5900;i++)
  //  {
        //sl.writeHreg(RedboardIP,100,i);    
        //sl.writeHreg(RedboardIP,100,70);
/*debounce*/
      reading = digitalRead(buttonPin);
      // if(reading == LOW && lastState == HIGH)
      // {
      //   delay(10);
      //   if(digitalRead(buttonPin) == LOW)
      //   {
      //     state = !state;
      //   }
      //   sl.Hreg(101,1);
      //   lastState = reading;
      // }
      if(reading ==  LOW)
      {
        
        sl.Hreg(101,1);
        Serial.println(reading);
      }
/*debounce*/
        // sl.writeCoil(RedboardIP,100,false);
        // if(mb.Hreg(101) == 1)
        // {
        //   digitalWrite(0,HIGH);
        // }
        // else
        // {
        //    digitalWrite(0,LOW);
        // }
        // /*case upload to Black board*/
        // if(sl.isConnected(RedboardIP))
        // {
        //   //sl.readHreg(RedboardIP, 100, &res); // 100 คือที่ Register 100
        //   sl.readCoil(RedboardIP,100,&c);
        // }
        // else 
        // {
        //   sl.connect(RedboardIP);
        //   Serial.println("Reconnecting...");           // Try to connect if no connection
        //}
        /*case upload to Black board*/
      
        mb.task();
        sl.task();
        // delay(100);
        
        // if (!show--) 
        // {                   // Display Slave register value one time per second (with default settings)
        //   Serial.print("Redboard Reg[0] = ");
        //   Serial.println(c);
        //   show = LOOP_COUNT;
        // }
    // }
}
