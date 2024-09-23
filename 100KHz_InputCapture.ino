#define SDA_PIN 31  // DUT SDA line connected to GPIO pin 31.
#define SCL_PIN 33  // DUT SDA line connected to GPIO pin 33.
// GND from device pin goes into Arduino board's common GND pin 53
int enable_debug_print = 0;
unsigned long edge_detection_timestamp[1024] = {0};
int clock_signal[1024] = {0};
int timer = 0;
int occurence = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(SCL_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SCL_PIN), isr, CHANGE);
}
void loop()
{
  if (enable_debug_print) {
    for(int occurence=0;occurence<timer;occurence++)
    {
      Serial.print(clock_signal[occurence]);
      Serial.print(":");
      Serial.println(edge_detection_timestamp[occurence]);
    }
    enable_debug_print = 0;
  }
}
void isr()
{
  clock_signal[timer] = digitalRead(SCL_PIN);
  edge_detection_timestamp[timer++] = micros();
  if(timer > 216 ) {
      enable_debug_print = 1;
  }
}