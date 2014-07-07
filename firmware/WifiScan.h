#include "application.h"

typedef struct WifiScanResults {
    uint32_t networks;
    uint32_t status;
    uint8_t rssi;
    uint8_t security_ssidlen;
    uint16_t time;
    uint8_t ssid[32];
    uint8_t bssid[6];
} WifiScanResults_t;


class WifiScan {
    public:
        int startScan();
        bool Next(char *line, uint8_t len);
        
};

void wipeStr(char *str, int len);

