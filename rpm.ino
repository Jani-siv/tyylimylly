/* Example code with timer intyerrutp that will create an interruption each 
 *  500ms using timer1 and prescalar of 256.
Calculations (for 500ms): 
  System clock 16 Mhz and Prescalar 256;
  Timer 1 speed = 16Mhz/256 = 62.5 Khz    
  Pulse time = 1/62.5 Khz =  16us  
  Count up to = 500ms / 16us = 31250 (so this is the value the OCR register should have)*/
  #define SECOND 1
  #define TIMETOREAD 18
bool state = false;
bool LED_STATE = true;
int clockPulse = 0;
int rotation = 0;
bool READ_STATE = true;
int volt = 0;
float res;
float voltage = 5 / 1024;
void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode (3,INPUT); //Set the pin to be OUTPUT
  cli();                      //stop interrupts for till we make the settings
  /*1. First we reset the control register to amke sure we start with everything disabled.*/
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 7812;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();                     //Enable back the interrupts
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(3);
 // Serial.println(val);
  if (val == 1 && READ_STATE == true)
  {
    rotation++;
    volt = analogRead(A0);
    res += volt * (5.0/1023.0)*11;
    READ_STATE = false;
  }
  else if (val == 0 && READ_STATE == false)
  {
    READ_STATE = true;
  }
}

//With the settings above, this IRS will trigger each 500ms.
ISR(TIMER1_COMPA_vect){
  if (clockPulse == (SECOND*TIMETOREAD))
  {
    if (state == true)
    {
    Serial.print((rotation * 6));
    Serial.print(":");
    if (rotation > 0)
      {
        Serial.println(res/rotation);
      }
    state = false;
    }
    else
    {
      TCNT1  = 0;                  //First, set the timer back to 0 so it resets for next interrupt
  LED_STATE = !LED_STATE;      //Invert LED state
  digitalWrite(9,LED_STATE);  //Write new state to the LED on pin D5
    clockPulse = 0;
    rotation = 0;
    res = 0;
    state = true;
    }
  }
  else {
 clockPulse++;
  }

}
