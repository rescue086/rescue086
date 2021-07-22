#include <ESP8266WiFi.h> // Include WiFi library
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3c

#define LED_BUILTIN 2
#define BLINK_SETUP_COMPLETE 1
#define BLINK_CLIENT_CONNECT 2
#define BLINK_SEND_OLED 3
#define BLINK_SEND_LINE 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define Url           "http://espex.tk/duinocoin/z/"
#define Url2           "http://espex.tk/duinocoin/mb/"
#define Port          80
#define LINE_TOKEN    "FMpOkDjjN6zF8ZlBDVXj9AVAEZRZaHVKDxJYweg2hVN" // LINE ACCESS TOKEN
#define Miners        "rescur086"  // Duino Coin User ID
#define Miners1        "oonarongrit"  // Duino Coin User ID
#define Miners2        "rescue086"  // Duino Coin User ID

long Wtime = millis();
long wtime = millis();
long Wtime1 = millis();
long wtime1 = millis();
long Wtime2 = millis();
long wtime2 = millis();

int Ctime = 20000; // Time Check Miners
int Ctime2 = 60000; // Time Check Miners

void blink(uint8_t count, uint8_t pin = LED_BUILTIN) {
  uint8_t state = HIGH;

  for (int x = 0; x < (count << 1); ++x) {
    digitalWrite(pin, state ^= HIGH);
    delay(50);
  }
}

namespace {
//const char* SSID          = "DUINO";   // Change this to your WiFi name
//const char* PASSWORD      = "16055089";    // Change this to your WiFi password
const char* SSID          = "CopterService 2.4G";   // Change this to your WiFi name
const char* PASSWORD      = "Oo16055089";    // Change this to your WiFi password
const char* USERNAME      = "rescur086";     // Change this to your Duino-Coin username
const char* USERNAME1      = "oonarongrit";     // Change this to your Duino-Coin username
const char* USERNAME2      = "rescue086";     // Change this to your Duino-Coin username


WiFiClient client;
void SetupWifi() {
  Serial.println("Connecting to: " + String(SSID));
  WiFi.mode(WIFI_STA); // Setup ESP in client mode
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.begin(SSID, PASSWORD);

  int wait_passes = 0;
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (++wait_passes >= 10) {
      WiFi.begin(SSID, PASSWORD);
      wait_passes = 0;
    }
  }

  Serial.println("\nConnected to WiFi!");
  blink(BLINK_SETUP_COMPLETE);
  Serial.println("Local IP address: " + WiFi.localIP().toString());
}
}

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  // Start serial connection
  Serial.begin(115200);
  Serial.println("\n\nDuino Coin Miners & Balances Monitor");
  WiFi.mode(WIFI_STA);
  Serial.println();
  Wire.begin(5,4);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2); display.setCursor(0, 0); display.println( "Duino Coin");
  display.setTextSize(2); display.setCursor(0, 25); display.println("  Miners");
  display.setTextSize(2); display.setCursor(0, 45); display.println("  Wellet");
  display.display();
  SetupWifi();
}
void _Miners()
{
  Serial.flush();
  if (WiFi.status() == WL_CONNECTED)
  {
    WiFiClient client;
    HTTPClient http;
    String web = Url2 + String("?id=") + String(Miners) + "&tk=" + String(LINE_TOKEN);
    Serial.println("\nWait!...\t"+ String(Miners) + " Data Send Line Notify");
    if (http.begin(client, web))
    {
      int httpCode = http.GET();
      while (client.connected())
      {
        if (client.available())
        {
          break;
        }
      }
      http.end();
    }
  }
  wtime = millis();
}
void _Miners1()
{
  Serial.flush();
  if (WiFi.status() == WL_CONNECTED)
  {
    WiFiClient client;
    HTTPClient http;
    String web = Url2 + String("?id=") + String(Miners1) + "&tk=" + String(LINE_TOKEN);
    Serial.println("\nWait!...\t"+ String(Miners1) + " Data Send Line Notify");
    if (http.begin(client, web))
    {
      int httpCode = http.GET();
      while (client.connected())
      {
        if (client.available())
        {
          break;
        }
      }
      http.end();
    }
  }
  wtime1 = millis();
}void _Miners2()
{
  Serial.flush();
  if (WiFi.status() == WL_CONNECTED)
  {
    WiFiClient client;
    HTTPClient http;
    String web = Url2 + String("?id=") + String(Miners2) + "&tk=" + String(LINE_TOKEN);
    Serial.println("\nWait!...\t"+ String(Miners2) + " Data Send Line Notify");
    if (http.begin(client, web))
    {
      int httpCode = http.GET();
      while (client.connected())
      {
        if (client.available())
        {
          break;
        }
      }
      http.end();
    }
  }
  wtime2 = millis();
}
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void GET()
{
  WiFiClient client;
  Serial.flush();
  client.flush();
  if (!client.connect("espex.tk", Port))
  {
    Serial.println("Connection failed");
  }
  String web = "GET /duinocoin/z/?id=" + String(USERNAME) + " HTTP/1.1\r\n" + "Host: espex.tk\r\n\r\n";
  client.print(String(web));
  long t = millis();
  String s = "";
  while (client.connected() || client.available())
  {
    s = client.readString();
    if ((millis() - t ) > 50000)
    {
      Serial.println("Time Out");
      return;
    }
  }
  client.stop();
  s.replace(" ", "");
  String ss = s.substring(s.indexOf("@") + 1, s.lastIndexOf("@"));
  if (ss != "Not")
  {
    String iWallet = getValue(ss, ',', 0);
    String iMiners = getValue(ss, ',', 1);
    String iBalance = getValue(ss, ',', 2);
    Serial.println();
    Serial.println("Wallet\t" + iWallet);
    Serial.println("Miners\t" + iMiners);
    Serial.println("Balance\t" + iBalance);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2); display.setCursor(0, 0); display.println(iWallet);
    display.setTextSize(2); display.setCursor(0, 20); display.println("Miners " + iMiners);
    display.setTextSize(2); display.setCursor(0, 45); display.println("$");
    display.setTextSize(1); display.setCursor(20, 50); display.println(iBalance);
    display.display();
  }
  Wtime = millis();
}
void GET1()
{
  WiFiClient client;
  Serial.flush();
  client.flush();
  if (!client.connect("espex.tk", Port))
  {
    Serial.println("Connection failed");
  }
  String web = "GET /duinocoin/z/?id=" + String(USERNAME1) + " HTTP/1.1\r\n" + "Host: espex.tk\r\n\r\n";
  client.print(String(web));
  long t = millis();
  String s = "";
  while (client.connected() || client.available())
  {
    s = client.readString();
    if ((millis() - t ) > 50000)
    {
      Serial.println("Time Out");
      return;
    }
  }
  client.stop();
  s.replace(" ", "");
  String ss = s.substring(s.indexOf("@") + 1, s.lastIndexOf("@"));
  if (ss != "Not")
  {
    String iWallet = getValue(ss, ',', 0);
    String iMiners = getValue(ss, ',', 1);
    String iBalance = getValue(ss, ',', 2);
    Serial.println();
    Serial.println("Wallet\t" + iWallet);
    Serial.println("Miners\t" + iMiners);
    Serial.println("Balance\t" + iBalance);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2); display.setCursor(0, 0); display.println(iWallet);
    display.setTextSize(2); display.setCursor(0, 20); display.println("Miners " + iMiners);
    display.setTextSize(2); display.setCursor(0, 45); display.println("$");
    display.setTextSize(1); display.setCursor(20, 50); display.println(iBalance);
    display.display();
  }
  Wtime1 = millis();
}void GET2()
{
  WiFiClient client;
  Serial.flush();
  client.flush();
  if (!client.connect("espex.tk", Port))
  {
    Serial.println("Connection failed");
  }
  String web = "GET /duinocoin/z/?id=" + String(USERNAME2) + " HTTP/1.1\r\n" + "Host: espex.tk\r\n\r\n";
  client.print(String(web));
  long t = millis();
  String s = "";
  while (client.connected() || client.available())
  {
    s = client.readString();
    if ((millis() - t ) > 50000)
    {
      Serial.println("Time Out");
      return;
    }
  }
  client.stop();
  s.replace(" ", "");
  String ss = s.substring(s.indexOf("@") + 1, s.lastIndexOf("@"));
  if (ss != "Not")
  {
    String iWallet = getValue(ss, ',', 0);
    String iMiners = getValue(ss, ',', 1);
    String iBalance = getValue(ss, ',', 2);
    Serial.println();
    Serial.println("Wallet\t" + iWallet);
    Serial.println("Miners\t" + iMiners);
    Serial.println("Balance\t" + iBalance);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2); display.setCursor(0, 0); display.println(iWallet);
    display.setTextSize(2); display.setCursor(0, 20); display.println("Miners " + iMiners);
    display.setTextSize(2); display.setCursor(0, 45); display.println("$");
    display.setTextSize(1); display.setCursor(20, 50); display.println(iBalance);
    display.display();
  }
  Wtime2 = millis();
}
void loop() {

  if ((millis() - Wtime) > Ctime)
  {
    GET();
    blink(BLINK_SEND_OLED);
  }
  if ((millis() - Wtime1) > Ctime)
  {
    GET1();
    blink(BLINK_SEND_OLED);
  }
  if ((millis() - Wtime2) > Ctime)
  {
    GET2();
    blink(BLINK_SEND_OLED);
  }
   if ((millis() - wtime) > Ctime2)
  {
    _Miners();
    blink(BLINK_SEND_LINE);
  }
   if ((millis() - wtime1) > Ctime2)
  {
    _Miners1();
    blink(BLINK_SEND_LINE);
  }
   if ((millis() - wtime2) > Ctime2)
  {
    _Miners2();
    blink(BLINK_SEND_LINE);
  }
 yield();
}
