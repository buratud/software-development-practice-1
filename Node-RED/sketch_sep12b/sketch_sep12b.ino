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

int numLEDs = 3;
int ledPins[] = { LED_R_PIN, LED_G_PIN, LED_B_PIN };  // Array to store LED pins
//int blinkSpeeds[] = { 0, 0, 0 };               // Array to store blinking speeds (in milliseconds)
int blinkSpeed = 0;
unsigned long long previousMilli = 0;
//unsigned long previousMillis[] = { 0, 0, 0 };  // Array to store previous times for blinking
String mode = "";
int prevButtonState, currentButtonState;
int clickTime = 500;      // Countdown before it count as a long press in millisec
bool pressState = false;  // Keep Pressing State (True when press ; False when release)
bool doubleClickState = false;    // Keep Double Click State to prevent auto reset (True when press ; False when release)
unsigned int currentPwm, prevPwm, prevClick;

void setup() {
  Serial.begin(115200);
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
  pinMode(INPUT_DIGITAL, INPUT_PULLUP);
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
    if (mode.compareTo("turn") == 0) {
      handleTurn();
    } else if (mode.compareTo("blink") == 0) {
      handleBlink();
    } else if (mode.compareTo("pwm") == 0) {
      handlePwm();
    }
  }
  if (mode.compareTo("blink") == 0) {
    if (blinkSpeed > 0) {
      if (millis() - previousMilli >= blinkSpeed) {
        // for (int i = 0; i < numLEDs; i++) {
        //   int pin = ledPins[i];
        //   previousMilli = millis();
        //   digitalWrite(pin, !digitalRead(pin));
        // }
        int pin = LED_R_PIN;
        previousMilli = millis();
        digitalWrite(pin, !digitalRead(pin));
      }
    }
  }
  currentButtonState = digitalRead(INPUT_DIGITAL);
  currentPwm = analogRead(INPUT_ANALOG);
  if (currentButtonState != prevButtonState) {
    if (currentButtonState == LOW) {
      doubleClickState = false;
      if(millis() - prevClick < clickTime){
        doubleClickState = true;
        //Click after first click less than 0.5 sec
        Serial.println("db,Double Click");
      }
      prevClick = millis();
      pressState = true;
    } else {
      pressState = false;
      if (millis() - prevClick < clickTime) {
        prevClick = millis();
      }
    }
  }
  if (millis() - prevClick >= clickTime) {
    if(pressState){
      //If button is press more than 0.5 second
      Serial.println("db,Long Press");
    }
    else if (!doubleClickState) {
      //If button is not press for 0.5 second after last click
      Serial.println("db,Click");
    }
  }
  if (currentPwm != prevPwm) {
    String message = "an," + String(currentPwm);
    Serial.println(message.c_str());
  }
  prevButtonState = currentButtonState;
  prevPwm = currentPwm;
}

void handleTurn() {
  int pin = Serial.readStringUntil(',').toInt();
  String mode = Serial.readStringUntil('\n');
  if (mode.compareTo("on") == 0) {
    digitalWrite(pin, LOW);
  } else if (mode.compareTo("off") == 0) {
    digitalWrite(pin, HIGH);
  }
}

void handleBlink() {
  int pin = Serial.readStringUntil(',').toInt();
  String mode = Serial.readStringUntil('\n');
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
  int pin = Serial.readStringUntil(',').toInt();
  int value = Serial.readStringUntil('\n').toInt();
  value = constrain(value, 0, 255);
  analogWrite(pin, value);
}
