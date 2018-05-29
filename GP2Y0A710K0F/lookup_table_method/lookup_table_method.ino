//SHARP GP2Y0A02
//Yellow Vout
//Black GND
//Red 5V
//100~550, 70~550

extern float distance[];
extern float voltage[];

typedef struct {
  float maxDistance;  //cm
  float minDistance;  //cm
  float offset; //cm
  float distance; //cm, 
  int frequency;  //Hz
  int pin;
}SHARP;

SHARP Sharp = {150, 20, 0, 0, 40, A0};

void getDistance(SHARP* Sharp) {
  float v = analogRead(Sharp->pin);
  v = v / 1024.0 * 5;
  int index = 0;
  for(index = 0; index < 49; index++) {
    if(v >= voltage[index]) {
      break;
    }
  }
  if(index == 0) {
    Sharp->distance = 70;
  } else if(index == 49) {
    Sharp->distance = 550;
  } else {
    Sharp->distance = map(v, voltage[index], voltage[index-1], distance[index], distance[index-1]);
  }
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  static unsigned long lastTime = millis();
  if(millis() - lastTime > 1000/Sharp.frequency) {
    lastTime = millis();
    getDistance(&Sharp);
    Serial.println(Sharp.distance);
  }  
}
