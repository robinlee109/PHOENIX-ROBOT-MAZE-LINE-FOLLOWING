int readirsensors()
{
  left = digitalRead(irl); //left mid right represent ir sensors
  mid = digitalRead(irm);
  right = digitalRead(irr);
  return left;
  return mid;
  return right;
}

int readsonicsensors()
{
  delayMicroseconds(45);//df dl dr ultrasonic sensors
  df = sfront.ping_cm(); 
  delayMicroseconds(45);
  dl = sleft.ping_cm();
  delayMicroseconds(45);
  dr = sright.ping_cm();
  delayMicroseconds(45);
  return left;
  return mid;
  return right;
}
