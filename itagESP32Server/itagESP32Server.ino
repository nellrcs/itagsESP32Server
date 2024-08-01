#include <ArduinoBLE.h>
#define DELAY 1000
#define ARRAYSIZE 2 //total number of tags id

String tagList[ARRAYSIZE] = { 
  "ff:ff:ff:ff:ff:ff",//You tag id 
  "ff:ff:ff:ff:ff:ff" 
};

BLEDevice tag[ARRAYSIZE];
void setup() {
  Serial.begin(115200, SERIAL_8N1);
  Serial.println("SERIAL START:");
  if (!BLE.begin()) {
    while (1);
  }
}

void loop() {
  for (int i =0; i< ARRAYSIZE; i++) {
    tagCheck(tagList[i],i);
  };
  delay(DELAY);
}

void connectTags(String id,int i){
  BLE.scanForAddress(id);
  BLEDevice peripheral = BLE.available();
  if (peripheral){ 
      BLE.stopScan();
      if (peripheral.connect()){
        tag[i] = peripheral;
        Serial.println("Connect!! ");
        Serial.println("iTags List :: ");
      }else{
        Serial.println("fail !!");
      }    
  }
}

void tagCheck(String id,int e){
  bool newTag = false;
  for (int i =0; i< ARRAYSIZE; i++) {
    if(tag[i].address() == id){
      if(tag[i].connected()){ 
        Serial.print("iIag (");
        Serial.print(i+1);
        Serial.print(") - ");
        Serial.print(id);
        Serial.print(" - RSSi:");
        Serial.println(tag[i].rssi());
      }else{
        if (tag[i].connect()){
          Serial.print("iIag (");
          Serial.print(i+1);
          Serial.println(") - Reconnect!! ");
        }else{
          Serial.print("iIag (");
          Serial.print(i+1);
          Serial.println(") - Offline ");
        }
      }
    }else{
      newTag = true;
    }
  };

  if(newTag){
    connectTags(id,e);
  }
}

