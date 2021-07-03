#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/hc12.h"

const char *HC_CMD_AT = "AT";
const char *HC_CMD_BDR = "AT+B"; // Change the serial port baud rate.
const char *HC_CMD_CH = "AT+C";  // Change wireless communication channel, optional from 001 to 127.
const char *HC_CMD_FU = "AT+FU";
const char *HC_CMD_P = "AT+P";   // Set transmitting power of module.
const char *HC_CMD_R = "AT+R";   // Obtain single parameter of module.
const char *HC_CMD_RX = "AT+RX"; //Obtain all parameters of module.
const char *HC_CMD_U = "AT+U";   // Set data bits,check bit and stop bit of serial port communication.
const char *HC_CMD_V = "AT+V";
const char *HC_CMD_SLEEP = "AT+SLEEP";
const char *HC_CMD_DEFAULT = "AT+DEFAULT";
const char *HC_STATUS_OK = "OK";

const char *HC_12_BAUD_RATE_ARRAY[] = {"1200", "2400", "4800", "9600", "19200", "38400", "57600"};

uint8_t hc_12_init(hc12_t *hc12) {

}

uint8_t hc_12_check(hc12_t *hc12) {
    char buffer[2];
    hc12->send(HC_CMD_AT, strlen(HC_CMD_AT));
    hc12->receive(buffer, 2);
    if (!strcmp(buffer, HC_STATUS_OK)) {
        return 0;
    }
    return 1;
}

uint8_t hc_12_status(hc12_t *hc12) {
    char buffer[45] = {0};
    hc12->send(HC_CMD_RX, strlen(HC_CMD_RX));
    hc12->receive(buffer, 45);
    printf("%s\n", buffer);
}

uint8_t hc_12_set_baud_rate(hc12_t *hc12, HC_12_BAUD_RATE baudRate) {
    char buffer[40] = {0};
    strncat(buffer, HC_CMD_BDR, strlen(HC_CMD_BDR));
    strncat(buffer, HC_12_BAUD_RATE_ARRAY[baudRate], strlen(HC_12_BAUD_RATE_ARRAY[baudRate]));
    hc12->send(buffer, strlen(buffer));
    printf("Sent %s\n", buffer);
    hc12->receive(buffer, 12);
    printf("Received %s\n", buffer);
}

void hc_12_receive(hc12_t *hc12, char *buffer, uint8_t size) {
    hc12->receive(buffer, size);
}

void hc_12_send(hc12_t *hc12, char *buffer, uint8_t size) {
    hc12->send(buffer, size);
}