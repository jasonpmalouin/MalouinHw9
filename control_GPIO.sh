#!/bin/bash
config-pin p9.12 gpio
config-pin p8.16 gpio_pu
g++ -o control_GPIO control_GPIO.cpp
