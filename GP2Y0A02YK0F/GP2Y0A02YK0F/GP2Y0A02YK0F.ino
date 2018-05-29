//SHARP GP2Y0A02
//Yellow Vout
//Black GND
//Red 5V

float distance[] = {20, 30, 40, 50, 60, 70, 80, 90, 100,  110,  120,  130,  140,  150};
float voltage[14] = {2.5, 2, 1.55, 1.25, 1.1, 0.85, 0.8, 0.73, 0.7, 0.65, 0.6, 0.5, 0.45, 0.4};

typedef struct {
  float maxDistance;  //cm
  float minDistance;  //cm
  float offset; //cm
  float distance; //cm, 
  int frequency;  //Hz
  int pin;
}SHARP;

SHARP Sharp = {150, 20, 0, 0, 20, A0};

void getDistance(SHARP* Sharp) {
  float v = analogRead(Sharp->pin);
  v = v / 1024.0 * 5;
  int index = 0;
  for(index = 0; index < 14; index++) {
    if(v >= voltage[index]) {
      break;
    }
  }
  if(index == 0) {
    Sharp->distance = 20;
  } else if(index == 14) {
    Sharp->distance = 150;
  } else {
    Sharp->distance = map(v, voltage[index], voltage[index-1], distance[index], distance[index-1]);
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
