#include <SoftwareSerial.h>
SoftwareSerial mySerial(8,9);

#include <LiquidCrystal.h>
LiquidCrystal lcd(6, 7, 5, 4, 3, 2);


 char rcv,pastnumber[11];

void serialFlush()
{
  while(Serial.available() > 0) 
  {
    char t = Serial.read();
  }
} 
void myserialFlush()
{
  while(mySerial.available() > 0) 
  {
    char t = mySerial.read();
  }
} 

void okcheck1()
{
  unsigned char rcr;
  do{
      rcr = mySerial.read();
    }while(rcr != 'K');
}


char face_string[10];
char face_status=0;

int idk = 0,eid=0;


int button = A0;

int buzzer = 13;

void beep()
{
  digitalWrite(buzzer, LOW);delay(3000);digitalWrite(buzzer, HIGH);
}
 
void setup() 
{   
  pinMode(buzzer, OUTPUT); 
  pinMode(button, INPUT_PULLUP);
  
  digitalWrite(buzzer, HIGH);
  
  Serial.begin(9600);
  mySerial.begin(9600);
    
    
  
 //AI Enabled smart door for identifying persons with SMS notification
  lcd.begin(16,2);
  lcd.clear();       lcd.print("AI Enabled Smart");
  lcd.setCursor(0,1);lcd.print("Door For Identif");
  delay(2500);
  lcd.clear();
  lcd.setCursor(0,0);lcd.print("ying Persons With");
  lcd.setCursor(0,1);lcd.print("SMS Notifictaion");
     delay(3000); 
     

  gsminit();

  lcd.clear();
} 


char face_id_s='x';
void loop()
{
  mn: 
if(digitalRead(button) == LOW)
{
  lcd.clear();lcd.setCursor(0, 0);lcd.print("Identifing Face..");
  
  serialFlush();
  int rtz=0;
  
  face_loop:
  memset(face_string,'\0',strlen(face_string));
  do{
      rcv = Serial.read();  
    }while(rcv != '*');
      readSerial(face_string);
      face_status  = face_string[0];
      if(face_status == 'N')
        {
          rtz++;
          lcd.setCursor(0,1);convertl(rtz);
          delay(1000);  
          if(rtz >= 7)
            {
             goto fp_loop; 
            }
          goto face_loop;
        }
      if(face_status >= '0' && face_status <= '9')
        {
           face_id_s = face_status;
           face_status='Y';         
        }

    fp_loop:   
    if(face_status == 'N')
      {
        delay(1000);lcd.clear();lcd.print("No-Face Recognised");
      
        digitalWrite(buzzer, LOW);delay(2000);delay(2000);digitalWrite(buzzer, HIGH);
      
             delay(5000);  delay(5000); delay(5000);
        mySerial.write("AT+CMGS=\"");
        mySerial.write(pastnumber);
        mySerial.write("\"\r\n"); delay(3000);
        mySerial.write("Face Not Recongnised\r\n");
        mySerial.write(0x1A);    
             delay(5000);  delay(5000);  delay(5000);
    
      
      }
    if(face_status == 'Y')
      {
        delay(1000);lcd.clear();lcd.print("Face Recongnised");
        lcd.setCursor(0,1);lcd.print("Id:");lcd.write(face_id_s);
        
               delay(5000);  delay(5000);delay(5000);
        mySerial.write("AT+CMGS=\"");
        mySerial.write(pastnumber);
        mySerial.write("\"\r\n"); delay(3000);
        mySerial.write("Face Recongnised_");
        mySerial.write(face_id_s);
        mySerial.write(0x1A);    
             delay(5000);  delay(5000);  delay(5000);
    
      
      }

   lcd.clear();   
}
    
delay(500);
}

int readSerial(char result[]) 
{
  int i = 0;
  while (1) 
  {
    while (Serial.available() < 0) 
    {
      char inChar = Serial.read();
      if (inChar == '\n') 
         {
          result[i] = '\0';
          Serial.flush();
          return 0;
         }
      if (inChar != '\r') 
         {
          result[i] = inChar;
          i++;
         }
    }
  }
}

int readSerial1(char result[]) 
{
  int i = 0;
  while (1) 
  {
    while (mySerial.available() < 0) 
    {
      char inChar = mySerial.read();
      if (inChar == '\n') 
         {
          return 0;
         }
      if (inChar != '\r') 
         {
          result[i] = inChar;
          i++;
         }
    }
  }
}

void gsminit()
{
  mySerial.write("AT\r\n");                   okcheck1();
  mySerial.write("ATE0\r\n");                 okcheck1();
  mySerial.write("AT+CMGF=1\r\n");            okcheck1();
  mySerial.write("AT+CNMI=1,2,0,0\r\n");      okcheck1();
  mySerial.write("AT+CSMP=17,167,0,0\r\n");   okcheck1();
    
  lcd.clear();
  lcd.print("SEND MSG STORE");
  lcd.setCursor(0,1);
  lcd.print("MOBILE NUMBER");  
  do{
     rcv = mySerial.read();
    }while(rcv == '*');
     readSerial1(pastnumber);
     pastnumber[10]='\0';
     
  lcd.clear();
  lcd.print(pastnumber);

    mySerial.write("AT+CMGS=\"");
    mySerial.write(pastnumber);
    mySerial.write("\"\r\n"); delay(3000);
    mySerial.write("Mobile no. registered\r\n");
    mySerial.write(0x1A);    
    delay(5000);  delay(5000);  
}


void converts(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
   Serial.write(a);
   Serial.write(c);
   Serial.write(e); 
   Serial.write(g);
   Serial.write(h);
}

void convertl(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
   lcd.write(a);
   lcd.write(c);
   lcd.write(e); 
   lcd.write(g);
   lcd.write(h);
}
