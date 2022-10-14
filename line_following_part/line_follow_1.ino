void linefollow1()
{
  if ((left == LOW) && (mid == HIGH) && (right == LOW))//Straight 
      {
       error = 0;
      }
  
    else if ((left == HIGH) && (mid == LOW) && (right == LOW))//move left
      {
       error = -2;
      }
  
    else if ((left == LOW) && (mid == LOW) && (right == HIGH))//move right
      {
        error = 2;    
      }
      
//    else if ((left == LOW) && (mid == HIGH) && (right == HIGH))//code removed since priority is to go straight always
//      {
//        error = 100;
//      }
//  
//    else if ((left == HIGH) && (mid == HIGH) && (right == LOW))//code removed since priority is to go straight always
//      {
//       error = 101;
//      }
      
    else if ((left == HIGH) && (mid == HIGH) && (right == HIGH))//priority to move straight but checking the sensors help to know when first stop is reached
      {
//       error = 102;
      
       if ((df<10) && (dl<10) && (dr<10))//to check if it has reached first stop
        {
          flag = 1;//this records the first stop 
          delay(3000);
          reverse();
          do {
              readirsensors();
              linefollow2();
              motor1.setSpeed(160);
              motor2.setSpeed(160);
              motor3.setSpeed(200);
              motor4.setSpeed(200);
              turnright();
            } while (error != 0);
            
          //bot turns to make it move back to line but at a priority to the right(line_follow_2 begins here)     
        }
      }
}
