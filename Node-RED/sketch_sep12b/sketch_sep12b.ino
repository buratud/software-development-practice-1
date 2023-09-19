#define LED_R_PIN 32
#define LED_G_PIN 33
#define LED_B_PIN 25
#define INPUT_DIGITAL 34
#define INPUT_ANALOG 35

#define FAST_SPEED 100
#define SLOW_SPEED 1000

void handleTurn();
void handleBlink();
void handlePwm();
void handlLED();

int numLEDs = 3;
int ledPins[] = { LED_R_PIN, LED_G_PIN, LED_B_PIN };  // Array to store LED pins
int colorValue[] = { 255, 255, 255 };                       // Contain {Red,Green,Blue} value for coloring led
//int blinkSpeeds[] = { 0, 0, 0 };               // Array to store blinking speeds (in milliseconds)
int blinkSpeed = 0;                                   // Time between blink (in millisecond)
unsigned long long previousMilli = 0, prevClick = 0;  // Time from last point for blinking and clicking
//unsigned long previousMillis[] = { 0, 0, 0 };  // Array to store previous times for blinking
String mode = "";
int prevButtonState, currentButtonState;
int clickTime = 500;        // Countdown before it count as a long press in millisec
//bool pressState = false;    // Keep Pressing State (True when press ; False when release)
bool preventReset = true;  // Prevent to change label to click when release button
bool blinkState = false;    // Keep Blinking State
unsigned int currentPwm, prevPwm;     // Keep value from analog input to send data to Node-red

void setup() {
  Serial.begin(115200);
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
  pinMode(INPUT_DIGITAL, INPUT);
  pinMode(INPUT_ANALOG, INPUT);
  digitalWrite(LED_R_PIN, HIGH);
  digitalWrite(LED_G_PIN, HIGH);
  digitalWrite(LED_B_PIN, HIGH);
  prevButtonState = digitalRead(INPUT_DIGITAL);
  currentButtonState = prevButtonState;
  prevPwm = analogRead(INPUT_ANALOG);
  currentPwm = prevPwm;
  prevClick = 0;
  Serial.println("db,0");
  Serial.println("an,0");
  Serial.setTimeout(50);
}


void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    mode = Serial.readStringUntil(',');
    Serial.println("Mode : " + mode);
    if (mode.compareTo("turn") == 0) {
      // On/Off LED
      handleTurn();
    } else if (mode.compareTo("blink") == 0) {
      // Blinking LED
      handleBlink();
    } else if (mode.compareTo("pwm") == 0) {
      // LED Brightness
      handlePwm();
    } else if (mode.compareTo("color") == 0) {
      // Set LED Color
      handleLED();
    }
  }
  if (mode.compareTo("blink") == 0) {
    if (blinkSpeed > 0) {
      if (millis() - previousMilli >= blinkSpeed) {
        for (int i = 0; i < numLEDs; i++) {
          int pin = ledPins[i];
          previousMilli = millis();
          analogWrite(pin, blinkState ? 255 : 255-colorValue[i]);
        }
        blinkState = !blinkState;
      }
    }
  }
  currentButtonState = digitalRead(INPUT_DIGITAL);
  currentPwm = analogRead(INPUT_ANALOG);
  if (currentButtonState != prevButtonState) {
    if (currentButtonState == LOW) {
      preventReset = false;
      if (millis() - prevClick < clickTime) {
        preventReset = true;
        //Click after first click less than 0.5 sec
        Serial.println("db,Double Click");
      }
      prevClick = millis();
      //pressState = true;
    } else {
      //pressState = false;
      if (millis() - prevClick < clickTime) {
        // Keep time when release button
        prevClick = millis();
      }
    }
  }
  if (millis() - prevClick >= clickTime) {
    if (currentButtonState == LOW && !preventReset) {
      //If button is press more than 0.5 second
      Serial.println("db,Long Press");
      preventReset = true;
    } else if (!preventReset) {
      //If button is not press for 0.5 second after last click
      Serial.println("db,Click");
      preventReset = true;
    }
  }
  if (currentPwm-prevPwm > 5) {
    // Send value to Node-red when analog value change more than or equal to 5
    String message = "an," + String(currentPwm);
    Serial.println(message.c_str());
  }
  prevButtonState = currentButtonState;
  prevPwm = currentPwm;
}

void handleTurn() {
  String strPIN = Serial.readStringUntil(',');
  int pin =isInteger(strPIN) ? strPIN.toInt() : 0;
  String mode = Serial.readStringUntil('\n');
  Serial.println("Turn : " + mode);
  if (mode.compareTo("on") == 0) {
    //    digitalWrite(pin, LOW);
    for (int i = 0; i < numLEDs; i++) {
      analogWrite(ledPins[i], 255 - colorValue[i]); // Set light on base on color
    }
  } else if (mode.compareTo("off") == 0) {
    //    digitalWrite(pin, HIGH);
    for (int i = 0; i < numLEDs; i++) {
      analogWrite(ledPins[i], 255);                 // Set light off for all color
    }
  }
}

void handleBlink() {
  String strPIN = Serial.readStringUntil(',');
  int pin =isInteger(strPIN) ? strPIN.toInt() : 0;
  String mode = Serial.readStringUntil('\n');
  //Serial.println("Blink : " + mode);
  blinkSpeed = false;
  if (mode.compareTo("off") == 0) {
    blinkSpeed = 0;
    digitalWrite(LED_R_PIN, HIGH);
  } else if (mode.compareTo("slow") == 0) {
    blinkSpeed = SLOW_SPEED;
  } else if (mode.compareTo("fast") == 0) {
    blinkSpeed = FAST_SPEED;
  }
  previousMilli = millis();
}

void handlePwm() {
  String strPIN = Serial.readStringUntil(',');
  String strValue = Serial.readStringUntil('\n');
  int pin =isInteger(strPIN) ? strPIN.toInt() : 0;
  int value =isInteger(strValue) ? strValue.toInt() : 0;
  for (int i = 0; i < numLEDs; i++) {
    analogWrite(ledPins[i], (int)(value));    // Set color and brightness
  }
}

void handleLED() {
  String value = Serial.readStringUntil(',');
  int r = isInteger(value) ? value.toInt() : 0;
  value = Serial.readStringUntil(',');
  int g = isInteger(value) ? value.toInt() : 0;
  value = Serial.readStringUntil('\n');
  int b = isInteger(value) ? value.toInt() : 0;
  colorValue[0] = r;
  colorValue[1] = g;
  colorValue[2] = b;
  for (int i = 0; i < numLEDs; i++) {
    analogWrite(ledPins[i], (int)(255-colorValue[i]));    // Set color and brightness
  }
}

boolean isInteger(String s){
  for (int i = 0; i < s.length(); i++) {
    char currentChar = s.charAt(i);
    if (!isdigit(currentChar)) {
      return false;  // The string contains a non-digit character
    }
  }
  return true;
}
