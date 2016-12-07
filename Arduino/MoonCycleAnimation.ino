/* 
  Animate 14 led rows to simulate a moon cycle
  Led rows have need be place in a circular shape 
  More info at: https://github.com/clementducerf/MoonCycleAnimation/
  
  For Arduino Mega 2560 (Need 14 pwm outputs)
  
  Clément Ducerf
  www.clementducerf.com
  Released under MIT license

*/

// 14 led rows in my setup.
int ledRows = 14;


// Function for declaring pins with numbers fron 0 to 14 & 15 to 28 (PWM pins on Arduino MEGA 2560 are 2-13 and 44-45)
int ledpins(int num){
  // We are going to cycle from 0 to 28 
  // So let's start with 0-14 : Half Cycle
  if (num <= 14) {
    if (num>=0 && num <=12){ return num+2;}
    else if (num==13 || num==14){ return num+31;} 
    }
    // Second part of the cycle : 15-28
    else if (num >= 15) {
     if(num>=15 && num <=26){ return num-13; } 
     else if(num==27 || num==28){ return num+17; } 
    }
    // Just in case
    else { return 0; }
};

void setup() {
  // I'm checking if everything is okay with the console
  Serial.begin(9600);

  // Pins declarations of all pins to OUTPUT using the previously created function ledpins
  for (int i = 0; i <= 14; i++) {
    pinMode(ledpins(i), OUTPUT); 
  }
}

// We need somes variables 

int curRows = 0;
int curBrightness = 0;

// For a total duration of 30 seconds.
long totalDuration = 10000;

// Total duration of 1 minute.
// long totalDuration = 60000;

// Total duration of 5 minutes.
// long totalDuration = 300000;

long durationPerRows = totalDuration/(2*ledRows);

void loop() {

  Serial.print('\n');
  Serial.print("--START--");
  Serial.print('\n');

  // First part of the cycle: turning on the leds
  if (curRows <= ledRows) {
    
  Serial.print("FIRST PART");
  Serial.print('\n');

  while (curRows <= ledRows) {  
    
    // I'm counting the rows as they are switched on
    Serial.print(curRows, DEC);
    Serial.print('\n');

    while (curBrightness < 255) {
      curBrightness++;
      analogWrite(ledpins(curRows), curBrightness);
      delay(durationPerRows/255);
      
    }
    curRows++;
    curBrightness = 0;
     }
  }
  
  // Second part of the cycle: turning off the leds
  else if (curRows > ledRows && curRows <= 28) {
    curBrightness = 255;
    Serial.print("SECOND PART");
    Serial.print('\n');
    
    while (curRows > ledRows && curRows <= 28) {     
        
        // I'm counting the rows as they are switched off
        Serial.print(curRows, DEC);
        Serial.print('\n');
        
        while (curBrightness != 0) {
          curBrightness--;
          analogWrite(ledpins(curRows), curBrightness);
          delay(durationPerRows/255);
        }
        curRows++;
        curBrightness = 255;
    }
  }
    
    // Last part of the cycle: resetting the counter
  else if (curRows > 28) {
    // Reset the variables when the cycle as ended
    curRows = 0;
    curBrightness = 0;
    
    Serial.print("RESET PART");
    Serial.print('\n');      
    }
}
