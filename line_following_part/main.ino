//2,5,7,8,11,12 pins availlable for connection for IR

#include<NewPing.h>
#include <AFMotor.h>
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
#define ltrig 3
#define lecho 4
#define ftrig A2
#define fecho A3
#define rtrig 2
#define recho 1
#define max_distance 600
NewPing sfront(ftrig,fecho,max_distance);//sonic front right left
NewPing sright(rtrig,recho,max_distance);
NewPing sleft(ltrig,lecho,max_distance);
int df;
int dr;
int dl;
int DIS = 6;
int irl = A0;
int irm = A4;
int irr = A1;

int pid;
int j = 255;
int initspeed = 150 ;
int lspeed;
int rspeed;
int left; //left ir
int mid;//left ir
int right;//left ir

byte error;
int flag = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(irl,INPUT);
  pinMode(irm,INPUT);
  pinMode(irr,INPUT);
}

void loop() {

readsonicsensors();

if (flag==0)
  { 
    readirsensors();
    linefollow1();
    decision();
  }

else if (flag==1)
  { 
    readirsensors();
    linefollow2();
    decision();
  } 

else if (flag==2){}//MAZE CODE BEGINS HERE yet to be written
}
void Forward()
{ 
  Serial.println("GO FORWARD");
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD); 
}


void moveright()
{
  Serial.println("MOVE RIGHT");
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void moveleft()
{  
    Serial.println("MOVE LEFT");
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
}

void turnleft()
{  
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
}

void turnright()
{
  
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void reverse()
{ 
  Serial.println("GO FORWARD");
  motor1.setSpeed(200);
  motor3.setSpeed(200);
  motor2.setSpeed(200);
  motor4.setSpeed(200);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD); 
}
void botstop()
{
  motor1.run(RELEASE);
  motor1.run(RELEASE);
  motor1.run(RELEASE);
  motor1.run(RELEASE);
}
