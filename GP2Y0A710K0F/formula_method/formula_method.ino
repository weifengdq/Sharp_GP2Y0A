//SHARP GP2Y0A710
//Blue GND
//GREEN Vout
//Yellow 5V
//Black 5V
//Red GND

typedef struct {
  float maxDistance;  //cm
  float minDistance;  //cm
  float offset; //cm
  float distance; //cm, 
  int frequency;  //Hz
  int pin;
}SHARP;

SHARP Sharp = {550, 100, 0, 0, 40, A0};

void getDistance(SHARP* Sharp) {
  int v = analogRead(Sharp->pin);
  //v = v / 1024.0 * 5;
  //Sharp->distance = 138.89/(v - 1.11);
  Sharp->distance = 28444 / (v - 227) + Sharp->offset;
  if(Sharp->distance > Sharp->maxDistance) {
    Sharp->distance = Sharp->maxDistance;
  } else if(Sharp->distance < Sharp->minDistance) {
    Sharp->distance = Sharp->minDistance;
  } else {
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  static unsigned long lastTime = millis();
  if(millis() - lastTime > 1000/Sharp.frequency) {
    lastTime = millis();
    getDistance(&Sharp);
    Serial.println(Sharp.distance);
//    int v = analogRead(Sharp.pin);
//    Serial.println(v);
  }  
}
