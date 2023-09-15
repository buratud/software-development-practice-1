#define LED_R 3
#define LED_G 5
#define LED_B 6
#define INPUT_DIGITAL 2
#define INPUT_ANALOG A0

#define FAST_SPEED 100
#define SLOW_SPEED 1000

void handleTurn();
void handleBlink();
void handlePwm();

int numLEDs = 3;
int ledPins[] = { LED_R, LED_G, LED_B };  // Array to store LED pins
//int blinkSpeeds[] = { 0, 0, 0 };               // Array to store blinking speeds (in milliseconds)
int blinkSpeed = 0;
unsigned long long previousMilli = 0;
//unsigned long previousMillis[] = { 0, 0, 0 };  // Array to store previous times for blinking
String mode = "";
int prevButtonState, currentButtonState;
unsigned int currentPwm, prevPwm;

void setup() {
  Serial.begin(115200);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(INPUT_DIGITAL, INPUT_PULLUP);
  pinMode(INPUT_ANALOG, INPUT);
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_G, HIGH);
  digitalWrite(LED_B, HIGH);
  prevButtonState = digitalRead(INPUT_DIGITAL);
  currentButtonState = prevButtonState;
  prevPwm = analogRead(INPUT_ANALOG);
  currentPwm = prevPwm;
  Serial.println("db,0");
  Serial.println("an,0");
  Serial.setTimeout(50);
}


void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    mode = Serial.readStringUntil(',');
    if (mode == "turn") {
      handleTurn();
    } else if (mode == "blink") {
      handleBlink();
    } else if (mode == "pwm") {
      handlePwm();
    }
  }
  if (mode == "blink") {
    if (blinkSpeed > 0) {
      if (millis() - previousMilli >= blinkSpeed) {
        // for (int i = 0; i < numLEDs; i++) {
        //   int pin = ledPins[i];
        //   previousMilli = millis();
        //   digitalWrite(pin, !digitalRead(pin));
        // }
        int pin = LED_R;
        previousMilli = millis();
        digitalWrite(pin, !digitalRead(pin));
      }
    }
  }
  currentButtonState = digitalRead(INPUT_DIGITAL);
  currentPwm = analogRead(INPUT_ANALOG);
  if (currentButtonState != prevButtonState) {
    if (currentButtonState == LOW) {
      Serial.println("db,1");
    } else {
      Serial.println("db,0");
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
  if (mode == "on") {
    digitalWrite(pin, LOW);
  } else if (mode == "off") {
    digitalWrite(pin, HIGH);
  }
}

void handleBlink() {
  int pin = Serial.readStringUntil(',').toInt();
  String mode = Serial.readStringUntil('\n');
  if (mode == "off") {
    blinkSpeed = 0;
    digitalWrite(LED_R, HIGH);
  } else if (mode == "slow") {
    blinkSpeed = SLOW_SPEED;
  } else if (mode == "fast") {
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