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
IPAddress BlackboardIP(192,168,1,211);
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

boolean reading01;

//  const TickType_t xDelay100ms = pdMS_TO_TICKS(100); 
// TaskHandle_t Task1 = NULL;
// TaskHandle_t Task2 = NULL;



/*debounce*/
const int buttonPin01 = 23;
const int buttonPin02 = 22;
const int buttonPin03 = 18;
const int buttonPin04 = 5;
const int buttonPin05 = 21;
const int buttonPin06 = 19;

const int LEDPin01 = 15;
const int LEDPin02 = 2;
const int LEDPin03 = 4;
const int LEDPin04 = 16;
const int LEDPin05 = 17;
int counterbuttonPin01 = 0;
int counterbuttonPin02 = 0;
int counterbuttonPin03 = 0;
int counterbuttonPin04 = 0;
int counterbuttonPin05 = 0;
int counterbuttonPin06 = 0;



void setup() {
  Serial.begin(115200);
  // WiFi.mode(WIFI_AP);
  // WiFi.softAP("KOMG","");
  WiFi.begin("micro_2.4G", "micro001");
  
  pinMode(buttonPin01, INPUT);
  pinMode(buttonPin02, INPUT);
  pinMode(buttonPin03, INPUT);
  pinMode(buttonPin04, INPUT);
  pinMode(buttonPin05, INPUT);
  pinMode(buttonPin06, INPUT);

  pinMode(LEDPin01,OUTPUT);
  pinMode(LEDPin02,OUTPUT);
  pinMode(LEDPin03,OUTPUT);
  pinMode(LEDPin04,OUTPUT);
  pinMode(LEDPin05,OUTPUT);
  

  digitalWrite(LEDPin01,LOW);
  digitalWrite(LEDPin02,LOW);
  digitalWrite(LEDPin03,LOW);
  digitalWrite(LEDPin04,LOW);
  digitalWrite(LEDPin05,LOW);

  if (!WiFi.config(BlackboardIP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
  //WiFi.softAPConfig(BlackboardIP,gateway,subnet);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  //xTaskCreatePinnedToCore(TaskFunction,  ชื่อฟังก์ชันที่จะให้ทำงานเป็น Task ซึ่งในฟังก์ชันนั้นควรจะเขียนโปรแกรมแบบทำงานวนลูป( infinite loop )
  //                         TaskName,      ชื่อของ Task ( ข้อมูลตรงส่วนนี้จะใช้ตอน Debug ไม่มีผลต่อการทำงานของโปรแกรมโดยตรง )
  //                         StackDepth,     ขนาด Stack ของ Task (เพื่อจอง memory)
  //                         PassParameter,   ชื่อตัวแปรที่จะส่งค่าเข้ามาทำงานต่อใน Task
  //                         TaskPriority,    กำหนดเลข Priority ให้ Task ซึ่งค่า 0 คือ Priority ที่ต่ำที่สุด
  //                         TaskHandle,      ชื่อตัวแปรของ Task ที่จะนำไปใช้ในการ Handle ทำงานอื่นๆต่อ
  //                         core);
  mb.server();
  sl.client();
  mb.addHreg(TEST_HREG,0,10);
  // xTaskCreatePinnedToCore(func1_Task,"Task1",10000,NULL,1,&Task1,0);
  // xTaskCreatePinnedToCore(func2_Task,"Task2",10000,NULL,1,&Task2,1);


}
  uint16_t res = 9999; //for slave Redboard
  bool c;
  uint16_t val = 8888; //for slave Blackboard
  uint8_t show = LOOP_COUNT; //for slave
void loop() {
      //  Serial.print("Redboard Reg[0] = ");
      // Serial.println(mb.Hreg(100));
      //    //delay(100);
      func1();
      func2();
        
        mb.task();
        sl.task();
}

//void func1_Task(void *pvParam)
void func2()
{
  
   
      if(mb.Hreg(100)==1)
        {
          digitalWrite(LEDPin01,HIGH);
          counterbuttonPin01 = 1;
        }
        if(mb.Hreg(100)==0)
        {
          digitalWrite(LEDPin01,LOW);
          counterbuttonPin01 = 0;
          // sl.Hreg(105)==0;
        }
        if(mb.Hreg(101)==1)
        {
          digitalWrite(LEDPin02,HIGH);
          counterbuttonPin02 = 1;
        }
        if(mb.Hreg(101)==0)
        {
          digitalWrite(LEDPin02,LOW);
          counterbuttonPin02 = 0;
          // sl.Hreg(105)==0;
        }
        if(mb.Hreg(102)==1)
        {
          digitalWrite(LEDPin03,HIGH);
          counterbuttonPin03 = 1;
        }
        if(mb.Hreg(102)==0)
        {
          digitalWrite(LEDPin03,LOW);
          counterbuttonPin03 = 0;
          // sl.Hreg(105)==0;
        }
        if(mb.Hreg(103)==1)
        {
          digitalWrite(LEDPin04,HIGH);
          counterbuttonPin04 = 1;
        }
        if(mb.Hreg(103)==0)
        {
          digitalWrite(LEDPin04,LOW);
          counterbuttonPin04 = 0;
          // sl.Hreg(105)==0;
        }
        if(mb.Hreg(104)==1)
        {
          digitalWrite(LEDPin05,HIGH);
          counterbuttonPin05 = 1;
        }
        if(mb.Hreg(104)==0)
        {
          digitalWrite(LEDPin05,LOW);
          counterbuttonPin05 = 0;
          // sl.Hreg(105)==0;
        }
    
      
      //vTaskDelay(xDelay100ms);
  
}

//void func2_Task(void *pvParam)
void func1()
{
        if( digitalRead(buttonPin01) ==  LOW )
      {
        delay(400);
        counterbuttonPin01++;
        if(counterbuttonPin01%2!= 0)
        {
          
            mb.Hreg(100,1);
          
          digitalWrite(LEDPin01,HIGH);
          Serial.print("Redboard Reg[0] = ");
          Serial.println(mb.Hreg(100));
        }
        else if (counterbuttonPin01%2== 0) 
        {
         
            mb.Hreg(100,0);
          
          digitalWrite(LEDPin01,LOW);
          Serial.print("Redboard Reg[0] = ");
          Serial.println(mb.Hreg(100));
        }
      }
      
      if(digitalRead(buttonPin02) ==  LOW)
      {
        delay(400);
        counterbuttonPin02++;
        if(counterbuttonPin02%2!= 0)
        {
          mb.Hreg(101,1);
          digitalWrite(LEDPin02,HIGH);
          Serial.print("Redboard Reg[1] = ");
          Serial.println(mb.Hreg(101));
        }
        else if(counterbuttonPin02%2== 0)
        {
          mb.Hreg(101,0);
          digitalWrite(LEDPin02,LOW);
          Serial.print("Redboard Reg[1] = ");
          Serial.println(mb.Hreg(101));
        }
      }
      if(digitalRead(buttonPin03) ==  LOW)
      {
        delay(400);
        counterbuttonPin03++;
        if(counterbuttonPin03%2!= 0)
        {
          mb.Hreg(102,1);
          digitalWrite(LEDPin03,HIGH);
          Serial.print("Redboard Reg[2] = ");
          Serial.println(mb.Hreg(102));
        }
        else if(counterbuttonPin03%2== 0)
        {
          mb.Hreg(102,0);
          digitalWrite(LEDPin03,LOW);
          Serial.print("Redboard Reg[2] = ");
          Serial.println(mb.Hreg(102));
        }
      }
      if(digitalRead(buttonPin04) ==  LOW)
      {
        delay(400);
        counterbuttonPin04++;
        if(counterbuttonPin04%2!= 0)
        {
          mb.Hreg(103,1);
          digitalWrite(LEDPin04,HIGH);
          Serial.print("Redboard Reg[3] = ");
          Serial.println(mb.Hreg(103));
        }
        else if(counterbuttonPin04%2== 0)
        {
          mb.Hreg(103,0);
          digitalWrite(LEDPin04,LOW);
          Serial.print("Redboard Reg[3] = ");
          Serial.println(mb.Hreg(103));
        }
      }
      if(digitalRead(buttonPin05) ==  LOW)
      {
        delay(400);
        counterbuttonPin05++;
        if(counterbuttonPin05%2!= 0)
        {
          mb.Hreg(104,1);
          digitalWrite(LEDPin05,HIGH);
          Serial.print("Redboard Reg[4] = ");
          Serial.println(mb.Hreg(104));
        }
        else if(counterbuttonPin05%2== 0)
        {
          mb.Hreg(104,0);
          digitalWrite(LEDPin05,LOW);
          Serial.print("Redboard Reg[4] = ");
          Serial.println(mb.Hreg(104));
        }
      }
      if(digitalRead(buttonPin06) ==  LOW)
      {
        delay(400);
        counterbuttonPin06++;
        if(counterbuttonPin06%2!= 0)
        {
          mb.Hreg(105,1);
          digitalWrite(LEDPin01,HIGH);
          counterbuttonPin01 = 1;
          mb.Hreg(100,1);
          digitalWrite(LEDPin02,HIGH);
          counterbuttonPin02 = 1;
          mb.Hreg(101,1);
          digitalWrite(LEDPin03,HIGH);
          counterbuttonPin03 = 1;
          mb.Hreg(102,1);
          digitalWrite(LEDPin04,HIGH);
          counterbuttonPin04 = 1;
          mb.Hreg(103,1);
          digitalWrite(LEDPin05,HIGH);
          counterbuttonPin05 = 1;
          mb.Hreg(104,1);
          Serial.print("Redboard Reg[5] = ");
          Serial.println(mb.Hreg(105));
        }
        else if(counterbuttonPin06%2== 0)
        {
          mb.Hreg(105,0);
          digitalWrite(LEDPin01,LOW);
          counterbuttonPin01 = 0;
          mb.Hreg(100,0);
          digitalWrite(LEDPin02,LOW);
          counterbuttonPin02 = 0;
          mb.Hreg(101,0);
          digitalWrite(LEDPin03,LOW);
          counterbuttonPin03 = 0;
          mb.Hreg(102,0);
          digitalWrite(LEDPin04,LOW);
          counterbuttonPin04 = 0;
          mb.Hreg(103,0);
          digitalWrite(LEDPin05,LOW);
          counterbuttonPin05 = 0;
          mb.Hreg(104,0);
          Serial.print("Redboard Reg[5] = ");
          Serial.println(mb.Hreg(105));
        }

      }
      
        //vTaskDelay(xDelay100ms);
  

}
