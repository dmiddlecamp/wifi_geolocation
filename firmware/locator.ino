// This #include statement was automatically added by the Spark IDE.
//#include "Geolocate.h"

// This #include statement was automatically added by the Spark IDE.
#include "WifiScan.h"
  
 
WifiScan WifiScanner;
//Geolocate geolocator;
uint8_t scanning = 0;
int startTime = 0;
  

void setup() {
    pinMode(D7,OUTPUT);
    Serial.begin(115200);
}  

int lastScan = 0; 
int lastStep = 0;
void loop() {
    unsigned int now = millis();
    
    if ((now - lastScan) > 60000) {
        if (!scanning) {
            WifiScanner.startScan();
        }
        scanning = 1;
        startTime = millis();
        lastScan = now;
    }

    //auto scan
    if ((now - lastStep) > 100) {
        scanNext("");
        lastStep = now;
    }
    
    //TODO: how to report this?
    //Spark.publish("wifi/scan")
}



int scanNext(String command) {
    if ((millis() - startTime) > 60000) {
        scanning = 0;
    }
    
    if (!scanning) {
        return 0;
    }

    
    char scanResult[220];
    if (!WifiScanner.Next(scanResult, 220)) {
        Serial.println("Hit the end, stopping for now...");
        scanning = 0;
    }
    Serial.println(scanResult);
    
    Spark.publish("FindMe", scanResult, 60, PRIVATE);
    
    return scanning;
}


