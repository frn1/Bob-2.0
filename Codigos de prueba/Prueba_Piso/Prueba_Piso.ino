constexpr uint8_t TATAMI_L = A9;
constexpr uint8_t TATAMI_R = A10;

void setup() {
  Serial.begin(115200);
  pinMode(TATAMI_L, INPUT);
  pinMode(TATAMI_R, INPUT);
}

void loop() {
  Serial.print(analogRead(TATAMI_L));
  Serial.print('\t');
  Serial.println(analogRead(TATAMI_R));
}
