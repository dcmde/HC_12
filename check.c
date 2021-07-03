#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "include/hc12.h"
#include "include/rs232.h"

char *portsArray = "0   ttyS0\n"
                   "1   ttyS1\n"
                   "2   ttyS2\n"
                   "3   ttyS3\n"
                   "4   ttyS4\n"
                   "5   ttyS5\n"
                   "6   ttyS6\n"
                   "7   ttyS7\n"
                   "8   ttyS8\n"
                   "9   ttyS9\n"
                   "10  ttyS10\n"
                   "11  ttyS11\n"
                   "12  ttyS12\n"
                   "13  ttyS13\n"
                   "14  ttyS14\n"
                   "15  ttyS15\n"
                   "16  ttyUSB0\n"
                   "17  ttyUSB1\n"
                   "18  ttyUSB2\n"
                   "19  ttyUSB3\n"
                   "20  ttyUSB4\n"
                   "21  ttyUSB5\n"
                   "22  ttyAMA0\n"
                   "23  ttyAMA1\n"
                   "24  ttyACM0\n"
                   "25  ttyACM1\n";

int cport_nr;

void send(char *buffer, size_t size) {
    RS232_SendBuf(cport_nr, buffer, size);
    usleep(2000000);
}

void receive(char *buffer, size_t size) {
    RS232_PollComport(cport_nr, buffer, size);
}

int main(int argc, char *argv[]) {
    FILE *fp;

    time_t rawtime;
    struct tm *timeinfo;
    int n, bdrate = 9600;
    char mode[] = {'8', 'N', '1', 0}, buffer[80] = {0};

    hc12_t hc12;
    hc12.receive = &receive;
    hc12.send = &send;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "HC12_%d-%m-%Y-%H-%M-%S.txt", timeinfo);
    fp = fopen(buffer, "w+");

    if (argc != 2) {
        printf("Please enter port com number\n");
        printf(portsArray);
        return 0;
    }

    cport_nr = atoi(argv[1]);

    if (RS232_OpenComport(cport_nr, bdrate, mode, 0)) {
        printf("Can not open comport. Check that the set pin is Low.\n");
        return (0);
    }

    RS232_flushRXTX(cport_nr);

    if (hc12_check(&hc12)) {
        printf("Failed check HC12. Check that the set pin is Low.\n");
    }
    hc12_status(&hc12);
    hc12_set_baud_rate(&hc12, HC_9600);
//    printf("%s %i\n", (char *) buffer, n);
}
