//Blynk Code:-

#define BLYNK_TEMPLATE_ID "TMPL3qG3Y4CK0"
#define BLYNK_TEMPLATE_NAME "Smoke Detector"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define WIFI_SSID "YOUR_WIFI"
#define WIFI_PASSWORD "YOUR_PASSWORD"

#define MQ2_PIN 34
#define BUZZER_PIN 25

int smokeThreshold = 750;
int mq2Value = 0;

bool smokeActive = false; 
bool ackDone = false; 
bool blynkSent = false;

unsigned long smokeStartTime = 0; 
unsigned long sensorTimer = 0;

BLYNK_WRITE(V3) {	// ACK Button
int val = param.asInt(); 
if (val == 1) {
ackDone = true;

digitalWrite(BUZZER_PIN, LOW); 
Blynk.virtualWrite(V3, 0);
}
}

void setup() { Serial.begin(115200); 
pinMode(BUZZER_PIN, OUTPUT);

WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);
}

void loop() { 
Blynk.run();

if (millis() - sensorTimer >= 500) { 
sensorTimer = millis();

mq2Value = analogRead(MQ2_PIN);

if (mq2Value >= smokeThreshold) { 
if (!smokeActive) {
smokeActive = true; 
smokeStartTime = millis(); 
ackDone = false; 
blynkSent = false;
}

if (!ackDone) 
digitalWrite(BUZZER_PIN, HIGH);

if (!blynkSent && millis() - smokeStartTime >= 8000) { 
Blynk.logEvent("smoke_alert", "Smoke detected!"); 
blynkSent = true;
}

} else {
smokeActive = false; 
digitalWrite(BUZZER_PIN, LOW);
}

Blynk.virtualWrite(V0, mq2Value);
Blynk.virtualWrite(V1, smokeActive ? "SMOKE DETECTED" : "NORMAL");
}
}



//Firebase Code:-

#include <WiFi.h>
#include <Firebase_ESP_Client.h> 
#include "addons/TokenHelper.h" 
#include "addons/RTDBHelper.h" 
#include <time.h>

#define WIFI_SSID "YOUR_WIFI"
#define WIFI_PASSWORD "YOUR_PASSWORD"

#define API_KEY "YOUR_API_KEY"
#define DATABASE_URL "YOUR_DATABASE_URL"

FirebaseData fbdo; 
FirebaseAuth auth; 
FirebaseConfig config;

#define MQ2_PIN 34
int smokeThreshold = 750; int mq2Value = 0;

unsigned long sensorTimer = 0;

unsigned long getTimestamp() { 
time_t now;
time(&now);
return (unsigned long)now;
}

void addLog(String action, int level) { 
FirebaseJson json;
json.set("action", action); 
json.set("sensor_value", level); 
json.set("timestamp", getTimestamp());

Firebase.RTDB.pushJSON(&fbdo, "/smoke/logs", &json);
}

void setup() { 
Serial.begin(115200);

WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
while (WiFi.status() != WL_CONNECTED) { 
delay(500);
}

config.api_key = API_KEY; 
config.database_url = DATABASE_URL;

Firebase.signUp(&config, &auth, "", ""); 
Firebase.begin(&config, &auth); 
Firebase.reconnectWiFi(true);
}

void loop() {

if (millis() - sensorTimer >= 1000) { 
sensorTimer = millis();

mq2Value = analogRead(MQ2_PIN);

if (mq2Value >= smokeThreshold) { 
addLog("Smoke Detected", mq2Value);
}
}
}



//Telegram Code:-

#include <WiFi.h>
#include <HTTPClient.h>

#define WIFI_SSID "YOUR_WIFI"
#define WIFI_PASSWORD "YOUR_PASSWORD"

#define MQ2_PIN 34
int smokeThreshold = 750;

String BOT_TOKEN = "YOUR_BOT_TOKEN"; 
String CHAT_ID	= "YOUR_CHAT_ID";

bool smokeActive = false; 
bool telegramSent = false;

unsigned long smokeStartTime = 0; 
unsigned long sensorTimer = 0;

void sendTelegram(String message) { 
HTTPClient http;

String url = "https://api.telegram.org/bot" + BOT_TOKEN + "/sendMessage?chat_id=" + CHAT_ID +
"&text=" + message;

http.begin(url); 
http.GET();
http.end();
}

void setup() { 
Serial.begin(115200);

WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
while (WiFi.status() != WL_CONNECTED) { delay(500);
}
}

void loop() {

if (millis() - sensorTimer >= 1000) { 
sensorTimer = millis();

int mq2Value = analogRead(MQ2_PIN);

if (mq2Value >= smokeThreshold) { 
if (!smokeActive) {
smokeActive = true; 
smokeStartTime = millis(); 
telegramSent = false;
}

if (!telegramSent && millis() - smokeStartTime >= 60000) { 
sendTelegram("SMOKE ALERT! Please check immediately.");
telegramSent = true;
}
} else {
smokeActive = false;
}
}
}

