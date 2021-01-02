# Candle with ATTINY412

It is a electronic candle. Tilt the candle to turn it on, and blow to the candle to turn it off. It consumes only 0.1 microamp when off, no need for an extra power switch. The color of the RGB LED can be adjusted by how long you tilt the candle. 

It uses the microcontroller Attiny 412, which consumes extremely low current in sleep mode (0.1 microamp). What I like most about this chip is the UPDI single-wire interface, which makes it so much easier to update the chip on the PCB. 

To achieve low current in sleep, it is very important to set all the pins before the "sleep_cpu()" step, leaving no pins floating.  I set all the pins to ground (pinMode: output, digitalWrite: LOW), except the pins for the P-channel mosfet gate and SW-520D which need to be at VCC level.  As the internal pullup resistor is 35 kΩ,  INPUT_PULLUP would have significant current if connected to grounded pins. 

Two sensors are used as switches, the SW-520D Tilt Sensor as the on-switch, and an electret microphone as the off-switch. The candle is off when SW-520D is upside down (open state). The WS2811 chip is used to drive the RGB LED. A p-channel mosfet AO3401 is used to switch on the LED. 

The case  was made with a 3D printer.  3 AAA batteries are used as the power source. 

Spence Konde's library megaTinyCore https://github.com/SpenceKonde/megaTinyCore was used for the code.

![Circuit](https://raw.githubusercontent.com/qisun1/candle/main/candle.jpg)

![Circuit](https://raw.githubusercontent.com/qisun1/candle/main/candle_circuit.png)


## License

This code is released under the MIT License.