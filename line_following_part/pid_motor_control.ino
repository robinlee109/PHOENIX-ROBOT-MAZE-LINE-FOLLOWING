float calculate_pid()
{ 
  int kp = 25;
  pid = (kp * error);
  return pid;
}

void motorspeed()
{
  int lspeed = initspeed - pid;
  int rspeed = initspeed + pid;
  lspeed = constrain(lspeed,0,255);
  rspeed = constrain(rspeed,0,255);
  //lines below make the bot move forward with stabilization
  Forward();
  motor1.setSpeed(lspeed);//Right Motor Speed *0
  motor2.setSpeed(lspeed);
  motor3.setSpeed(rspeed);//Left Motor Speed *120
  motor4.setSpeed(rspeed); 
}
