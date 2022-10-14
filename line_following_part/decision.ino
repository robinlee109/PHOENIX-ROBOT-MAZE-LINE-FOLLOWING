void decision(){

if (error == 100) {               //turn right till line is observed by mid sensor
    do {
      readirsensors();
      motor1.setSpeed(160);
      motor2.setSpeed(160);
      motor3.setSpeed(200);
      motor4.setSpeed(200);
      turnright();
      readirsensors();
      linefollow2();
    } 
    while (error != 0);

}

//this part is not done....to be checked later
  
else{
    calculate_pid();
    motorspeed();
    }
}
   
