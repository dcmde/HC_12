#include <stdlib.h>
#include <ctype.h>
#include <curses.h>
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

char *intprtkey(int ch);

void send(char *buffer, size_t size) {
    RS232_SendBuf(cport_nr, buffer, size);
    usleep(200000);
}

void receive(char *buffer, size_t size) {
    RS232_PollComport(cport_nr, buffer, size);
}

int main(int argc, char *argv[]) {

    WINDOW *mainwin;
    int ch, bdrate = 9600;
    char mode[] = {'8', 'N', '1', 0}, *recv_val;

    hc12_t hc12;
    hc12.receive = &receive;
    hc12.send = &send;

    if (argc != 2) {
        printf("Please enter: port com number.\n");
        printf(portsArray);
        return 0;
    }

    cport_nr = atoi(argv[1]);

    if (RS232_OpenComport(cport_nr, bdrate, mode, 0)) {
        printf("Can not open comport. Check that the set pin is High.\n");
        return (0);
    }

    if ((mainwin = initscr()) == NULL) {
        fprintf(stderr, "Error initializing ncurses.\n");
        exit(EXIT_FAILURE);
    }

    noecho();
    keypad(mainwin, TRUE);

    mvaddstr(0, 0, "Press a key ('q' to quit)");
    mvprintw(1, 0, "You pressed: ");
    refresh();

    while ((ch = getch()) != 'q') {
        deleteln();
        recv_val = intprtkey(ch);
        mvprintw(1, 0, "You pressed: 0x%x (%s)", ch, recv_val);
        hc12_send(&hc12, recv_val, 1);
        refresh();
    }

    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
}

struct keydesc {
    int code;
    char name[20];
};

char *intprtkey(int ch) {

    static struct keydesc keys[] = {{KEY_UP,        "Up arrow"},
                                    {KEY_DOWN,      "Down arrow"},
                                    {KEY_LEFT,      "Left arrow"},
                                    {KEY_RIGHT,     "Right arrow"},
                                    {KEY_HOME,      "Home"},
                                    {KEY_END,       "End"},
                                    {KEY_BACKSPACE, "Backspace"},
                                    {KEY_IC,        "Insert"},
                                    {KEY_DC,        "Delete"},
                                    {KEY_NPAGE,     "Page down"},
                                    {KEY_PPAGE,     "Page up"},
                                    {KEY_F(1),      "Function key 1"},
                                    {KEY_F(2),      "Function key 2"},
                                    {KEY_F(3),      "Function key 3"},
                                    {KEY_F(4),      "Function key 4"},
                                    {KEY_F(5),      "Function key 5"},
                                    {KEY_F(6),      "Function key 6"},
                                    {KEY_F(7),      "Function key 7"},
                                    {KEY_F(8),      "Function key 8"},
                                    {KEY_F(9),      "Function key 9"},
                                    {KEY_F(10),     "Function key 10"},
                                    {KEY_F(11),     "Function key 11"},
                                    {KEY_F(12),     "Function key 12"},
                                    {-1,            "<unsupported>"}
    };
    static char keych[2] = {0};

    if (isprint(ch) && !(ch & KEY_CODE_YES)) {
        keych[0] = ch;
        return keych;
    } else {
        int n = 0;
        do {
            if (keys[n].code == ch)
                return keys[n].name;
            n++;
        } while (keys[n].code != -1);

        return keys[n].name;
    }
}