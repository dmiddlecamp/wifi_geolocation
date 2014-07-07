#include "WifiScan.h"
#include "application.h"

void parseScanResultToJson(WifiScanResults_t result, char *line);
void bytesToHex(unsigned char *data, int length, char* buffer);

void wipeStr(char *str, int len) {
    for(int i = 0; i < len ;i++) {
        str[i] = 0;
    }
}

int WifiScan::startScan() {
   const unsigned long intervalTime[16] = { 2000, 2000, 2000, 2000,  2000,
        2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000 };

    wlan_ioctl_set_scan_params(4000, 20, 100, 5, 0x7FF, -120, 0, 300, 
        (unsigned long * ) &intervalTime);

    return 0;
}


bool WifiScan::Next(char *line, uint8_t len) {
    WifiScanResults_t scanResult;
    
    wipeStr(line, len);
    wipeStr((char *)scanResult.ssid, 32);
    
    long err = wlan_ioctl_get_scan_results(0, (uint8_t* ) &scanResult);
    
    if(err == 0) {
        parseScanResultToJson(scanResult, line);
    }
    else {
        const char *msg = (String("Error ") + String(err)).c_str();
        strncpy(line, msg, strlen(msg));
    }
    
    if (String(line).indexOf("00:00:00:00:00:00") >= 0) {
        return false;
    }
    return true;
}




/**
 * Format a SSID Scan result into a GeoLocation API Wifi Object 
 */
void parseScanResultToJson(WifiScanResults_t result, char *line) {
    //uint8_t idx = 0;
    
    uint8_t length = (result.security_ssidlen >> 2);
    uint8_t rssi = (result.rssi >> 1);
 
    char ssidStr[32];
    strncpy(ssidStr, (char *)result.ssid, length);
    ssidStr[length] = 0;
    
 
    char bssidStr[24];
    bytesToHex((unsigned char *)result.bssid, 6, bssidStr);
 
    //more standard geolocation format
    //String json = "{ \"macAddress\": \"" + String(bssidStr) + "\", \"signalStrength\": "+ String(rssi) +", \"age\": 0, \"name\": \""+String(ssidStr)+"\" }";
    
    //mozilla's location format
    String json = "{ \"key\": \"" + String(bssidStr) + "\", \"signal\": -"+ String(rssi) +" }";
    strncpy(line, json.c_str(), json.length());
}



void bytesToHex(unsigned char *data, int length, char* buffer) {	
	const char * hex = "0123456789ABCDEF";	
	int i=0, a=0;

	for(i=0;i<length;i++) {
		unsigned char c = data[i];
		buffer[a] = hex[(c>>4) & 0xF];
		buffer[a+1] = hex[(c) & 0xF];
		buffer[a+2] = ':';
		a+=3;
	}
	buffer[a-1] = 0;	//null
	buffer[a] = 0;
}




