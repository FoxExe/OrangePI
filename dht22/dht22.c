#include <wiringPi.h>   // GPIO lib

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_TIMINGS    85
#define DHT_PIN        25

int main( void )
{
        if ( wiringPiSetup() == -1 )
                exit( 1 );

        int data[5] = { 0, 0, 0, 0, 0 };
        uint8_t laststate = HIGH;
        uint8_t counter = 0;
        uint8_t j = 0, i;
        pinMode(DHT_PIN, OUTPUT);
        digitalWrite(DHT_PIN, LOW);
        delay(18);
        pinMode(DHT_PIN, INPUT);

        for ( i = 0; i < MAX_TIMINGS; i++ )
        {
                counter = 0;

                while (digitalRead( DHT_PIN ) == laststate)
                {
                        counter++;
                        delayMicroseconds(1);
                        if (counter == 255)
                                break;
                }

                laststate = digitalRead( DHT_PIN );

                if ( (i >= 4) && (i % 2 == 0) )
                {
                        data[j / 8] <<= 1;
                        if ( counter > 16 )
                                data[j / 8] |= 1;
                        j++;
                }
        }

        /*
        * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
        * print it out if data is good
        */
        if ( (j >= 40) && (data[4] == ( (data[0] + data[1] + data[2] + data[3]) & 0xFF) ) )
        {
                float h = (float)((data[0] << 8) + data[1]) / 10;
                if ( h > 100 )
                        h = data[0];    // for DHT11

                float c = (float)(((data[2] & 0x7F) << 8) + data[3]) / 10;
                if ( c > 125 )
                        c = data[2];    // for DHT11

                if ( data[2] & 0x80 )
                        c = -c;

                printf("Humidity: %.1f%%\nTemperature: %.1f%cC\n", h, c, 0xDF);         // Print data
        } else {
                return(1);
        }

        return(0);
}
