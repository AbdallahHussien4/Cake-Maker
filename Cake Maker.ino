// I considered the decorating arm as a servo motor that moves horizontally and have the Two Valves at the end of it.
// When the servo is in 90 Degree it points to the center of the cake and when it is in 180 degree it points to the last track in the cake (biggest radius)
// Between 90 Degree and 180 Degree it can reach any track from the cake(different degree=different track).
unsigned long previousMillisM=0,previousMillisL=0; 
int lastStepM=0,LSM=0,LedState=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(19,INPUT);
  for(byte i=0;i<=18;i++)pinMode(i,OUTPUT);
}


void loop ()
{
  MoveServo(0,180);
  delay(500);
  MoveServo(0,90);

  while(LSM<40)
    MoveMixer(5,10);
  lastStepM=0;
  LSM=0;

  MoveServo(1,180);
  delay(100);
  MoveServo(1,90);
  
  while(LSM<32)
    MoveMixer(4,10);
  LSM=0;
  lastStepM=0;
  LSM=0;
  
  MoveServo(2, 180);
  delay(200); 
  MoveServo(2, 90);
     
  while(LSM<80)
    MoveMixer(10,10);
  LSM=0;  
  
  for(int i=0;i<3;i++)
  {
    MoveServo(3,180);
    delay(100);
    MoveServo(3,90);
    while(LSM<32)
      MoveMixer(4,5);
    LSM=0  ;
    lastStepM=0;
  }
    
  while(LSM<8)
    MoveProductLine();
  LSM=0;
  lastStepM=0;  
  
  digitalWrite(16,HIGH);
  delay(1000);
  digitalWrite(16,LOW);
  
  while(LSM<8)
    MoveProductLine();
  LSM=0;
  lastStepM=0;
  
  delay(1000);
  
Decorate();

}

void MoveProductLine()
{
  
  if(millis() - previousMillisM > 100)
    { 
      Move(10,11,lastStepM);
      previousMillisM = millis();  
      lastStepM++;
      LSM++;
    }
   if(lastStepM>3)
      lastStepM=0;
}

void MoveCakeHandler()
{
  
  if(millis() - previousMillisM > 500)
    { 
      Move(12,13,lastStepM);
      previousMillisM = millis();  
      lastStepM++;
      LSM++;
    }
   if(lastStepM>3)
      lastStepM=0;
  
}

void MoveMixer(int Rotations,int Speed)
{

  int TimePerStep=1000/Speed/8;
  if(millis() - previousMillisM > TimePerStep)
    { 
      Move(8,9,lastStepM);
      previousMillisM = millis();  
      lastStepM++;
      LSM++;
    }
   if(lastStepM>3)
      lastStepM=0;
  
}
 
void MoveServo (int pin, int angle)
{
  int DutyCycle = (angle*11) + 500;
  digitalWrite(pin, HIGH);
  delayMicroseconds(DutyCycle);
  digitalWrite(pin, LOW);
  delay(100);
}

void Move(int i, int j,int s )
{
      switch(s)
      {
          case 0:
            digitalWrite(i,LOW);
            digitalWrite(j,LOW);  
            break;
          case 1:
            digitalWrite(i,LOW);
            digitalWrite(j,HIGH);
            break;
          case 2:
            digitalWrite(i,HIGH);
            digitalWrite(j,HIGH);
            break;
          case 3:
            digitalWrite(i,HIGH);
            digitalWrite(j,LOW);
            break;
   }
}

void Decorate(){
    if(analogRead(19)==993)
    {
      MoveServo(4, 180);
      while(LSM<8)
      {
        digitalWrite(17,HIGH);
        MoveCakeHandler();
      }
      digitalWrite(17,LOW);
      LSM=0;
      lastStepM=0;
      delay(100);
      MoveServo(4, 110);
      while(LSM<8)
      {
        digitalWrite(18,HIGH);
        MoveCakeHandler();
      }
      digitalWrite(18,LOW);
      LSM=0;
      lastStepM=0;
      MoveServo(4, 90);
    }
  else if(analogRead(19)==964)
  {
    MoveServo(4, 180);
      while(LSM<8)
      {        
        if(LSM%2==0)
          digitalWrite(17,HIGH);
        else
          digitalWrite(17,LOW);  
        MoveCakeHandler();
      }
      digitalWrite(17,LOW);
      LSM=0;
      lastStepM=0;
      delay(100);
      MoveServo(4, 110);
      while(LSM<8)
      {
        if(LSM%2==1)
          digitalWrite(18,HIGH);
        else
          digitalWrite(18,LOW);  
        MoveCakeHandler();
      }
      digitalWrite(18,LOW);
      LSM=0;
      lastStepM=0;
      MoveServo(4, 90);
  }
  else if(analogRead(19)==938)
    {
      MoveServo(4, 180);
      while(LSM<8)
      {
        if(millis() - previousMillisL > 143)  //143=Speed of motor( time[500MS]*Steps[8]/#of toggles[14*2])
        {
          LedState=!LedState;
          digitalWrite(17,LedState);
          previousMillisL=millis(); 
        }  
        MoveCakeHandler();
      }
      digitalWrite(17,LOW);
      LSM=0;
      lastStepM=0;
      delay(100);
      MoveServo(4, 90);
      digitalWrite(18,HIGH);
      delay(500);
      digitalWrite(18,LOW);
      LSM=0;
      lastStepM=0;
    }
  else if(analogRead(19)==913)
    {
      MoveServo(4, 180);
      while(LSM<8)
      {
        if(millis() - previousMillisL > 428 &&!LedState)  //428=Speed of motor( time[500MS]*Steps[8]/#of toggles[14*2])*3[to skip three toggles].
        {
          LedState=!LedState;
          digitalWrite(18,LedState);
          previousMillisL=millis(); 
        }  
        if(millis() - previousMillisL > 142 && LedState)  //428=Speed of motor( time[500MS]*Steps[8]/#of toggles[14*2])*3[to skip three toggles].
        {
          LedState=!LedState;
          digitalWrite(18,LedState);
          previousMillisL=millis(); 
        }  
        MoveCakeHandler();
      }
      digitalWrite(18,LOW);
      LSM=0;
      lastStepM=0;
      
      while(LSM<4)    //Move the CakeHandler 4 steps to put the servo valve in the right position #ofcreams/#ofsteps *4 (14/8*4)=7(OddPosition to avoid putting yellow cream on red cream)
        MoveCakeHandler();
      LSM=0;
      lastStepM=0; 
        
      while(LSM<8)
      {
        if(millis() - previousMillisL > 428 &&!LedState) 
        {
          LedState=!LedState;
          digitalWrite(17,LedState);
          previousMillisL=millis(); 
        }  
        if(millis() - previousMillisL > 142 && LedState)  
        {
          LedState=!LedState;
          digitalWrite(17,LedState);
          previousMillisL=millis(); 
        }  
        MoveCakeHandler();
      }
      digitalWrite(17,LOW);
      MoveServo(4, 100);
      while(LSM<8)
      {
        digitalWrite(18,HIGH);  
        MoveCakeHandler();
      }
      digitalWrite(18,LOW);
      delay(1000);
      LSM=0;
      lastStepM=0;
      MoveServo(4, 90);
      digitalWrite(17,HIGH);
      delay(500);
      digitalWrite(17,LOW);
      LSM=0;
      lastStepM=0;
    }
  else Decorate();  
 
}
