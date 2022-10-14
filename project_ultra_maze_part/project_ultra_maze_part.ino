//int maxd;
//int error;
//float preverror;
//float totalerror;
//float differror;
//int setdistance;
//const float kp = ;//tuning constant
//const float ki = ;//  
//const float kd = ;//cushions the response
//float pid;
//void setup(){
//  // put your setup code here, to run once:
//
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
////maxspeed =  maxerror*kp;otalerror+=error;
//error = setdistance - dst;
//totalerror += prevtotalerror; 
//differror = error - preverror;
//pid = (kp*error)+(ki*totalerror)+(kd*differror);
//prevtotalerror = totalerror;
//preverror = error;






# include <EEPROM.h>
#include<NewPing.h>
# include <AFMotor.h>
#define ltrig A0
#define lecho A1
#define ftrig A2
#define fecho A3
#define rtrig A4
#define recho A5
#define max_distance 600
int df;
int dr;
int dl;
int j = 255;
int DIS = 6;[
NewPing front(ftrig,fecho,max_distance);
NewPing right(rtrig,recho,max_distance);
NewPing left(ltrig,lecho,max_distance);
AF_DCMotor motor1(1,MOTOR12_1KHZ); //define motor 1 and required frequency
AF_DCMotor motor2(2,MOTOR12_1KHZ);//define motor 2 and required frequency
AF_DCMotor motor3(3,MOTOR34_1KHZ);//define motor 3 and required frequency
AF_DCMotor motor4(4,MOTOR34_1KHZ);//define motor 4 and required frequency

//bool goesRover = false;
//bool updateMemory = false;
//int addr_Start=1; //End point of data
//int addr_End=0; //start point of data
int i = 200; //speed
char cmd;//variable which holds data read from EEPROM
int addr=0; //variable which will hold address of EEPROM
char newaddr;//variable that holds new resolved data from EEPROM
char newcmd;//variable which will hold calculated move of 
int button1 = 12;
int button2 = 11;
int buttonVal1;
int buttonVal2;



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
cmd = "";

pinMode(button1,INPUT);
digitalWrite(button1,HIGH);
buttonVal1=digitalRead(button1);
pinMode(button2,INPUT);
digitalWrite(button2,HIGH);
buttonVal2=digitalRead(button2);
}


void  STOP()
{
  cmd = 'H';
  STORE_MEMORY();
  motor1.run(RELEASE);
  motor1.run(RELEASE);
  motor1.run(RELEASE);
  motor1.run(RELEASE);
  delay(50);
}


void FORWARD()
{
  cmd = 'F';
  STORE_MEMORY();
  motor1.setSpeed(i);
  motor1.run(FORWARD);
  motor2.setSpeed(i);
  motor2.run(FORWARD);
  motor3.setSpeed(i);
  motor3.run(FORWARD);
  motor4.setSpeed(i);
  motor3.run(FORWARD);
  delay(50);
}


void BACK()
{
  cmd = 'B';
  STORE_MEMORY();
  motor1.setSpeed(i+3);
  motor1.run(BACKWARD);
  motor2.setSpeed(i+3);
  motor2.run(BACKWARD); 
  motor3.setSpeed(i-27);
  motor3.run(BACKWARD); 
  motor4.setSpeed(i-27);
  motor4.run(BACKWARD);   
  delay(50);
} 


void RIGHT()
{
  cmd = 'R';
  STORE_MEMORY();
  while(1){
    motor1.setSpeed(i);
    motor1.run(FORWARD);
    motor2.setSpeed(i);
    motor2.run(FORWARD);
    motor3.setSpeed(i);
    motor3.run(BACKWARD);
    motor4.setSpeed(i);
    motor3.run(BACKWARD);
    delay(50);
    STOP();
  }
}


void LEFT()
{
  cmd = 'L';
  STORE_MEMORY();
  while(1)
  {
    motor1.setSpeed(255);
    motor1.run(BACKWARD);
    motor2.setSpeed(255);
    motor2.run(BACKWARD);
    motor3.setSpeed(150);
    motor3.run(FORWARD);
    motor4.setSpeed(150);
    motor4.run(FORWARD);
    delay(50);
    STOP();
  }
}

void STORE_MEMORY()//store the moves that the robot takes in arduino memory 
{
  for (addr = 0; addr < 124; addr ++)
  {
    //  EEPROM.update(addr,cmd);
    EEPROM.write(addr,cmd);
    addr++;
    delay(10);
  }
}

  
void RETRIEVE_MEMORY(){
for(addr = 0; addr < 124; addr ++)
{
  cmd = EEPROM.read(addr);
  addr++;
  delay(100);
}
  SHORTEST_PATH_CALCULATION();
  GO_SHORTEST_PATH();}


void SHORTEST_PATH_CALCULATION()
{
addr = 1;
for(newaddr = 125; newaddr < 255; newaddr ++){
 if (EEPROM.read(addr) == 'B'){
   if(EEPROM.read(addr-1) == 'L' && EEPROM.read(addr+1) == 'R')
   {
      EEPROM.write(newaddr,'B');
      addr++;
    }
            
    else if (EEPROM.read(addr-1) == 'L' && EEPROM.read(addr+1) == 'F')
    { 
      EEPROM.write(newaddr,'R');
      addr++;
    }
            
    else if (EEPROM.read(addr-1) == 'R' && EEPROM.read(addr+1) == 'L')
    {
      EEPROM.write(newaddr,'B');
      addr++;
    }
      
    else if (EEPROM.read(addr-1) == 'F' && EEPROM.read(addr+1) == 'L')
    { 
      EEPROM.write(newaddr,'R');
      addr++;
    }
            
    else if (EEPROM.read(addr-1) == 'S' && EEPROM.read(addr+1) == 'S')
    { 
      EEPROM.write(newaddr,'B');
      addr++;
    }
            
    else if (EEPROM.read(addr-1) == 'L' && EEPROM.read(addr+1) == 'L')
    { 
      EEPROM.write(newaddr,'S');
      addr++;
    }
    else if (EEPROM.read(addr) == 'H')
    {
      EEPROM.write(newaddr,'H');
      addr++;
    }
   
    else{
    addr++;}
 }
 }
} 
            
void GO_SHORTEST_PATH()
{
  for (newaddr=125; newaddr<=255; newaddr++){
    newcmd=EEPROM.read(newaddr);
      i=250;
    if (newcmd=='F'){
      FORWARD();
      delay(50);}
    else if(newcmd=='B'){
      BACK();
      delay(50);}
    else if(newcmd=='R'){
      RIGHT();
      delay(50);}
    else if(newcmd=='L'){
      LEFT();
      delay(50);}
    else if(newcmd=='H'){
      STOP();
      delay(50);}
  }
}


    
void loop(){ 
delay(10000);
read_ultra();
if (df > dl && df > dr )
{ 
      FORWARD();  
}
else if (dl > df && dl > dr )
{ 
  LEFT();  
  FORWARD();
}
else if (dr > df && dr > dl )
{
  RIGHT(); 
  FORWARD();
 
}      

else if(button2 == LOW) {         //SWITCH, switch two and robot goes round the maze using shortest path
     i = 255;
     delay(5000);
     RETRIEVE_MEMORY();
}
}

read_ultra()
{
delayMicroseconds(30);
df = fsonar.ping_cm();
delayMicroseconds(30);
dl = lsonar.ping_cm();
delayMicroseconds(30);
dr = rsonar.ping_cm();
delayMicroseconds(30);
if (df==0){df=500;}
if (dl==0){dl=500;}
if (dr==0){dr=500;}
}
  
}
