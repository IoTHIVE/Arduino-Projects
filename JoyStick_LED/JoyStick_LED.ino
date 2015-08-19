

// These constants won't change.  They're used to give names
// to the pins used:
const int xInPin = A0;  
const int yInPin = A1;  
const int swInPin = 2;  

//define outputs
const int leftLED = 3;
const int rightLED = 4;
const int upLED = 5;
const int downLED = 6;
const int pressLED = 8;

//define thresholds
const int LEFT_THRESHOLD = 100;
const int RIGHT_THRESHOLD = 900;
const int UP_THRESHOLD = 100;
const int DOWN_THRESHOLD = 900;

//define containers(variables)
int xValue;
int yValue;
int swState;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 

  pinMode(swInPin,INPUT);
  digitalWrite(swInPin, HIGH);

  pinMode(leftLED,OUTPUT);
  pinMode(rightLED,OUTPUT);
  pinMode(upLED,OUTPUT);
  pinMode(downLED,OUTPUT);
  pinMode(pressLED,OUTPUT);

}

void loop() {
  // read the analog in value:
  xValue = analogRead(xInPin);            
  yValue = analogRead(yInPin);            
  swState = digitalRead(swInPin);




  /* LED lighting pattern
                 0 UP
   
   
   LEFT 0        0 PRESS     0 RIGHT
   
   
                 0 DOWN
   
   */
   
   //check for left
  if(xValue < LEFT_THRESHOLD)
  {
    digitalWrite(leftLED,HIGH);
    Serial.println("LEFT LED ON");
  }
  else
  {
    digitalWrite(leftLED,LOW);
  }

  // check for right
  if(xValue > RIGHT_THRESHOLD)
  {
    digitalWrite(rightLED,HIGH);
    Serial.println("RIGHT LED ON");
  }
  else
  {
    digitalWrite(rightLED,LOW);
  }

  // check for up
  if(yValue < UP_THRESHOLD)
  {
    digitalWrite(upLED,HIGH);
    Serial.println("UP LED ON");
  }
  else
  {
    digitalWrite(upLED,LOW);
  }

  // check for down
  if(yValue > DOWN_THRESHOLD)
  {
    digitalWrite(downLED,HIGH);
    Serial.println("DOWN LED ON");
  }
  else
  {
    digitalWrite(downLED,LOW);
  }

  // check for press
  if(swState == LOW)  // active low input
  {
    digitalWrite(pressLED,HIGH);
    Serial.println("PRESS LED ON");
  }
  else
  {
    digitalWrite(pressLED,LOW);
  }

  // increase delay for debugging
  delay(1);                     
}




