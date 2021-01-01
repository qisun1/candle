# Candle with ATTINY412

It is a electronic candle. Tilt the candle to turn it on, and blow to the candle to turn it off. It consumes only 0.1 microamp when off, no need for an extra power switch. The color of the RGB LED can be adjusted by how long you tilt the candle. 

It uses the microcontroller Attiny 412, which uses extremely low current in sleep mode (0.1 microamp). The UPDI single-wire interface makes it easier to do updating of the code on the circuit board. 

Two sensers are used as switches, the SW-520D Tilt Sensor as the on-switch, and an electret microphone as the off-switch. The WS2811 chip is used to drive the RGB LED. 

The case  was made with a 3D printer.  3 AAA batteries are used as the power source. 

## License

This code is released under the MIT License.