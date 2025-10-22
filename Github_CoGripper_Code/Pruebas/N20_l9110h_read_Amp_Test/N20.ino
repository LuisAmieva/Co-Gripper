
#define A_IN1 3 
#define A_IN2 4 

void setup() {
  Serial.begin(115200);
  ledcAttach(3,1000,10);
  ledcAttach(4,1000,10);
}

void loop() {

  ledcWrite(A_IN1, 500);
  ledcWrite(A_IN2,0);
  delay(1000); 

  ledcWrite(A_IN1, 0);
  ledcWrite(A_IN2, 500);
  delay(1000); 

  int valor= analogRead(1);
  Serial.println(valor);

}