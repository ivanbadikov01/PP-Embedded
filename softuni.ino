const int t = 500; //delay between turning the LEDs on and off
bool previousButtonState1; //stops the players from cheating
bool previousButtonState2; //stops the players from cheating
int ledNum;

void setup() {

  for(int i = 2; i<11; ++i){ //setting all of the pins connected to the LEDS as outputs
    pinMode(i, OUTPUT);
  }
  
  pinMode(11, INPUT); //button pin for player1
  pinMode(12, INPUT); //button pin for player2
}

void loop() {
  runLeft();
  runRight();
}

void runLeft(){ //light runs to the left
  for(ledNum = 2; ledNum<10; ++ledNum){
  digitalWrite(ledNum, HIGH);
    nonBlockingDelay();
  digitalWrite(ledNum, LOW);
  }
}
void runRight(){ //light runs to the right
  for(ledNum = 10; ledNum>2; --ledNum){
  digitalWrite(ledNum, HIGH);
    nonBlockingDelay();
  digitalWrite(ledNum, LOW);
  }
}

void winCondition(){ //checks if the winning conditions were met
  switch(ledNum){
    case 2: if(detectButtonState(11)) {
      winScreen();
      } break;
    case 10: if(detectButtonState(12)) {
      winScreen();
    } break;
  }
}

int detectButtonState(int bttnPin) { //detects if the button is pressed and not hold
  int buttonState = digitalRead(bttnPin);
  if(buttonState && comparePreviousButtonStates(previousButtonState1, previousButtonState2)){
    return 1;
  }
  return 0;
}

void nonBlockingDelay(){ //creates a delay without blocking the whole mc
  int timeNow = millis();
  int timeToStop = timeNow + t;
  
  previousButtonState1 = digitalRead(11);
  previousButtonState2 = digitalRead(12);
  
  while(timeNow < timeToStop){
    timeNow = millis();
    winCondition();
  }
}
void winScreen(){ //winning screen
  for(int i = 2; i < 12; ++i){
    digitalWrite(i, LOW);
  }
      
      
  for(int i = 0; i<5; ++i){
   digitalWrite(ledNum, HIGH);
   delay(250);
   digitalWrite(ledNum, LOW);
   delay(250);
  } 
}

bool comparePreviousButtonStates(bool a, bool b) { //compares the previous states of the two buttons
  if (a == false && b == false) {
      return 1;
    }
  return 0;
}
