#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Wifi network station credentials
#define WIFI_SSID "Hola"
#define WIFI_PASSWORD "123456789"
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "5678564680:AAGJUVXPG7G3Rr673oe09fR-4sq3SqlSZJo"

// Use @myidbot (IDBot) to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "1213424209"

#define message1 D0
#define message2 D1

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

void setup() {
  pinMode(message1, INPUT);
  pinMode(message2, INPUT);
  Serial.begin(115200);
  Serial.println();

 // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  bot.sendMessage(CHAT_ID, "Starting", "");
  Serial.println("Starting");
}

void loop() {
  if ((digitalRead(message1)  == HIGH) && (digitalRead(message2)  == HIGH)){
    bot.sendMessage(CHAT_ID, "The Basket is full", "");
    delay(15000); // 15 sec
  }
    
}
