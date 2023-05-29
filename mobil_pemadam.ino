#define motor1 A0
#define motor2 A1
#define motor3 A2
#define motor4 A3
#define pwmA 3
#define pwmB 5
#define echo1 A4
#define trig1 A5
#define echo2 2
#define trig2 4
#define echo3 6
#define trig3 7
#define flame1 8
#define flame2 9
#define flame3 10
#define flame4 11
#define flame5 12

void setup() {
  pinMode(motor1, OUTPUT); pinMode(motor2, OUTPUT); pinMode(motor3, OUTPUT); pinMode(motor4, OUTPUT);
  pinMode(pwmA, OUTPUT); pinMode(pwmB, OUTPUT);
  pinMode(echo1, INPUT); pinMode(trig1, OUTPUT);
  pinMode(echo2, INPUT); pinMode(trig2, OUTPUT);
  pinMode(echo3, INPUT); pinMode(trig3, OUTPUT);
  pinMode(flame1, INPUT); pinMode(flame2, INPUT); pinMode(flame3, INPUT); pinMode(flame4, INPUT); pinMode(flame5, INPUT);
}

void loop() {
  int jarakKiri = ultrasonic(echo1, trig1);
  int jarakDepan = ultrasonic(echo2, trig2);
  int jarakKanan = ultrasonic(echo3, trig3);
  int api1 = digitalRead(flame1);
  int api2 = digitalRead(flame2);
  int api3 = digitalRead(flame3);
  int api4 = digitalRead(flame4);
  int api5 = digitalRead(flame5);

  maju();
  if(jarakDepan < 20) {
    if(jarakKiri > jarakKanan) {
      belokKiri();
    } else {
      belokKanan();
    }
  } else {
    if(api1 == HIGH || api2 == HIGH && api3 == LOW && api4 == LOW && api5 == LOW) {
      geserKiri();
    } else if(api1 == LOW && api2 == LOW && api3 == LOW && api4 == HIGH || api5 == HIGH) {
      geserKanan();
    } else if(api1 == LOW && api2 == HIGH || api3 == HIGH || api4 == HIGH && api5 == LOW) {
      mati();
    } else {
      maju();
    }
  }
}

void maju() {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
  analogWrite(pwmA, 200);
  analogWrite(pwmB, 180);
}

void geserKanan() {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, HIGH);
  analogWrite(pwmA, 150);
  analogWrite(pwmB, 130);
}

void geserKiri() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
  analogWrite(pwmA, 130);
  analogWrite(pwmB, 150);
}

void belokKanan() {
  geserKanan();
  delay(500);
  maju();
  delay(500);
}

void belokKiri() {
  geserKiri();
  delay(500);
  maju();
  delay(500);
}

void mati() {
  analogWrite(pwmA, 0);
  analogWrite(pwmB, 0);
}

int ultrasonic(int echo, int trig) {
  digitalWrite(trig, LOW); delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH);
  return duration*0.034/2;
}