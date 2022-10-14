//this is where bot is in mode 2 where right turn is a priority


void linefollow2()
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
        //i think i should make this situation a turn right but it would affect the code really bad 
      }
      
    else if ((left == LOW) && (mid == HIGH) && (right == HIGH))//priority to go RIGHT
      {
        error = 100;
      }
  
    else if ((left == HIGH) && (mid == HIGH) && (right == LOW))//priority to go straight though bot should move totally to left 
      {
       error = 101;
      }
      
    else if ((left == HIGH) && (mid == HIGH) && (right == HIGH))//when the second stop is achieved bot switches to maze mode
      {
//      error = 102;        
        flag = 2; //this records the second stop when bot is about to get into maze  
        //NB: ineed to find a way to move foward kiac to start the maze part       
      }
}
