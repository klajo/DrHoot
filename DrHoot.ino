#define MOTION_SENSOR 2
#define SOUND_TRIGGER 4
#define STATUS_LED 13
#define EYES_LED 6

boolean hooting = false;
int brightness = 0;
int fadeAmount = 5;

void setup() {
  Serial.begin(115200);
  pinMode(MOTION_SENSOR, INPUT);
  pinMode(SOUND_TRIGGER, OUTPUT);
  pinMode(EYES_LED, OUTPUT);
}

void loop() {
  int motionSensor = digitalRead(MOTION_SENSOR);
  if ((motionSensor == HIGH) && (hooting == false))
  {
    digitalWrite(STATUS_LED, HIGH);    
    digitalWrite(SOUND_TRIGGER, HIGH);
    hooting = true;
  }
  else if ((motionSensor == LOW) && (hooting == true))
  {
    digitalWrite(STATUS_LED, LOW);
    digitalWrite(SOUND_TRIGGER, LOW);
    analogWrite(EYES_LED, LOW);
    brightness = 0;
    hooting = false;
  }

  if (hooting == true)
  {
    analogWrite(EYES_LED, brightness);
    brightness = brightness + fadeAmount;
    if (brightness <= 0)
    {
      fadeAmount = -fadeAmount;
      brightness = 0;
    }
    else if (brightness >= 255)
    {
      fadeAmount = -fadeAmount;
      brightness = 255;
    }
  }
  delay(60);
}
