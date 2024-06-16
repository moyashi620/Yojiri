#define SERIAL

#ifdef SERIAL
#define SERIAL 1
#elif
#define SERIAL 0
#endif

void setup() {
  // put your setup code here, to run once:
  pinMode(14,INPUT_PULLUP);
  pinMode(15,INPUT_PULLUP);
  pinMode(16,INPUT_PULLUP);
  pinMode(17,INPUT_PULLUP);
  pinMode(18,INPUT_PULLUP);
  pinMode(19,INPUT_PULLUP);

  // Indicator LED
  pinMode(2, OUTPUT);
  
  // R Motor
  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);
  
  // L Motor
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  // Change of PWM Frequency
  TCCR2B &= B11111000;  // 31.4kHz
  TCCR2B |= B00000001;
  TCCR1B &= B11111000;
  TCCR1B |= B00000001;
  
  Serial.begin(9600);
}

int a = 0;
int pwmCalc1, pwmCalc2;
int pwmOut1, pwmOut2;

void loop() {
  // put your main code here, to run repeatedly:
  a = !a;
  int i = (!digitalRead(16)<<2 | !digitalRead(15)<<1 | !digitalRead(14));
  int j = (!digitalRead(19)<<2 | !digitalRead(18)<<1 | !digitalRead(17));

  // Conversion to PWM Signal
  pwmCalc1 = map(i, 0, 7, 30, 255);
  pwmOut1 = constrain(pwmCalc1, 0, 255);
  pwmCalc2 = map(j, 0, 7, 30, 255);
  pwmOut2 = constrain(pwmCalc2, 0, 255);

  analogWrite(3,pwmOut1);
  digitalWrite(11, LOW);
  analogWrite(9, pwmOut2);
  digitalWrite(10, LOW); 
  
  if(SERIAL){  
    Serial.print(pwmOut1);
    Serial.print("   ");
    Serial.println(pwmOut2);
  }
  digitalWrite(2, a);
  delay(100);
}
