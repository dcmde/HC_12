#ifndef HC_12_H
#define HC_12_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    HC_1200 = 0,
    HC_2400,
    HC_4800,
    HC_9600,
    HC_19200,
    HC_38400,
    HC_57600
} HC_12_BAUD_RATE;

typedef enum {
    HC_FU1,
    HC_FU2,
    HC_FU3
} HC_12_FU;

typedef enum {
    HC_P1 = 1,
    HC_P2,
    HC_P3,
    HC_P4,
    HC_P5,
    HC_P6,
    HC_P7,
    HC_P8,
} HC_12_TX_POWER;

typedef struct {
    HC_12_BAUD_RATE baudRate;
    HC_12_TX_POWER txPower;
    HC_12_FU fu;
    uint8_t channel;

    void (*send)(char *, size_t);

    void (*receive)(char *, size_t);
} hc12_t;

uint8_t hc12_init(hc12_t *hc12);

uint8_t hc12_check(hc12_t *hc12);

uint8_t hc12_status(hc12_t *hc12);

uint8_t hc12_set_baud_rate(hc12_t *hc12, HC_12_BAUD_RATE baudRate);

void hc12_receive(hc12_t *hc12, char *buffer, uint8_t size);

void hc12_send(hc12_t *hc12, char *buffer, uint8_t size);

#ifdef __cplusplus
}
#endif

#endif //HC_12_H
