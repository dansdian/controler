/*
    This sketch demonstrates how to scan WiFi networks.
    The API is almost the same as with the WiFi Shield library,
    the most obvious difference being the different file you need to include:
*/
#include "ESP8266WiFi.h"
const char* SSID = "Danur Dyantoro";
#define relay1 2
int32_t getRSSI(const char* target_ssid) {
  byte available_networks = WiFi.scanNetworks();

  for (int network = 0; network < available_networks; network++) {
    if (WiFi.SSID(network).compareTo(target_ssid) == 0) {     //stringOne.compareTo(stringTwo) < 0
      return WiFi.RSSI(network);
    }
  }
  return 0;
}
void setup() {
  Serial.begin(115200);
  pinMode(relay1, OUTPUT);
  
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
}

void loop() {

  int32_t rssi = getRSSI(SSID);


  // For debugging purpose only
  Serial.print("Signal strength: ");
  Serial.print(rssi);
  Serial.println("dBm");

  if (rssi > (-80) && rssi != 0) // if rssi is greater then -70 dbm or it's 0 dbm, then the light will turn ON
  {
    digitalWrite(relay1, LOW);
    Serial.println("ON");
  }
  else // else, the light will be turned OFF.
  {
    digitalWrite(relay1, HIGH);
    Serial.println("OFF");
  }

  
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(1500);
}
