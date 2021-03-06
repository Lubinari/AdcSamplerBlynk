#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// blynk token and wifi config
char auth[] = "XXX-XXXX-XXXXXXXXXXX";
char ssid[] = "XXXXXXX";
char pass[] = "XXXXXXXXXXXXXXXX";

#define Analog_R 34
#define Analog_G 35
#define Analog_B 32

#define Led_R 19
#define Led_G 18
#define Led_B 5

int valor_R = 0;
int valor_G = 0;
int valor_B = 0;
int cell_recept = 0;

BLYNK_WRITE(V4){
  valor_R = param.asInt();
}
BLYNK_WRITE(V5){
  valor_G = param.asInt();
}
BLYNK_WRITE(V6){
  valor_B = param.asInt();
}

BLYNK_WRITE(V0){
  cell_recept = param.asInt();
  if(cell_recept == 1){
    digitalWrite(12, HIGH);
  } else{
      digitalWrite(12, LOW);   
  }
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  
  pinMode(12, OUTPUT);
  pinMode(Led_R, OUTPUT);
  pinMode(Led_G, OUTPUT);
  pinMode(Led_B, OUTPUT);
  
  ledcAttachPin(Led_R,1);
  ledcAttachPin(Led_G,2);
  ledcAttachPin(Led_B,3);
  
  ledcSetup(1, 10000, 12);
  ledcSetup(2, 10000, 12);
  ledcSetup(3, 10000, 12); 
  delay(1000);
}

void loop()
{
  Blynk.run();
  if(cell_recept == 0){
    valor_R = analogRead(Analog_R);
    Blynk.virtualWrite(V1, valor_R);
    Blynk.virtualWrite(V4, valor_R);
  
    valor_G = analogRead(Analog_G);
    Blynk.virtualWrite(V2, valor_G);
    Blynk.virtualWrite(V5, valor_G);
  
    valor_B = analogRead(Analog_B);
    Blynk.virtualWrite(V3, valor_B);
    Blynk.virtualWrite(V6, valor_B);

    ledcWrite(1, valor_R);
    ledcWrite(2, valor_G);
    ledcWrite(3, valor_B);
  }
  else{
    Blynk.virtualWrite(V1, valor_R);
    Blynk.virtualWrite(V2, valor_G);
    Blynk.virtualWrite(V3, valor_B);
    ledcWrite(1, valor_R);
    ledcWrite(2, valor_G);
    ledcWrite(3, valor_B);
  }
}
