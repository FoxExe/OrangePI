#include <stdio.h>
#include <string.h>

#include <wiringPi.h>
#include <lcd.h>

int main(int argc, char **argv)
{
        if (argc < 2 || argc > 3) {
                printf("Usage: %s string [string]\n", argv[0]);
                return 1;
        }

        if (wiringPiSetup() == -1) {
                printf("GPIO Setup failed!\n");
                return 2;
        }

        int fd;

        //lcdInit(int rows, int cols, int bits, int rs, int strb, int d0, int d1, int d2, int d3, int d4, int d5, int d6, int d7)
        fd = lcdInit(2, 16, 4, 10, 11, 6, 5, 4, 1, 0, 0, 0, 0);

        if (fd == -1) {
                printf("Initialization failed\n");
                return 3;
        }

        lcdClear(fd);
        lcdPosition(fd, 0, 0);
        lcdPuts(fd, argv[1]);
        if (argc > 2) {
                lcdPosition(fd, 0, 1);
                lcdPuts(fd, argv[2]);
        }
        return 0;
}
