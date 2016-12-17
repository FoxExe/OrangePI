#!/bin/bash
LANG=C

while (true); do
# ========================
        read str1 h str2 t <<< `./readsensor`
        if [ -z "$t" ] || [ -z "$h" ]; then
                continue
        fi
        ./lcd_print "Temp:   $t" "Hum:    $h"
        sleep 5
# ========================
        ./lcd_print "`hostname`"\
                 "`ifconfig eth0 | awk '/inet addr/{print substr($2,6)}'`"
        sleep 3
# ========================
        ./lcd_print "Load avg: `cat /proc/loadavg | cut -d ' ' -f 3`"\
                 "Mem free: `free -m | awk 'NR==2{printf "%.2f", $3*100/$2}'`%"
        sleep 3
# ========================
        # Usage: $3 of $2 ($5 %)
        ./lcd_print "Root: `df -h | awk '$NF=="/"{printf "%s (%s)\n", $3,$5}'`"\
                 "Temp: `df -h | awk '$NF=="/tmp"{printf "%s (%s)\n", $3,$5}'`"
        sleep 5
# ========================
        for i in `seq 1 10`
        do
                ./lcd_print "   `date +"%d.%m.%Y"`"\
                         "    `date +"%T"`"
                sleep 1
        done
done
