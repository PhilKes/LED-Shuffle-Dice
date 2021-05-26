# LED Shuffle Dice
### Attiny85 with Shiftregister and Accelerometer
#### Parts
* Attiny85 Microcontroller
* **74HC595** Shiftregister
* 7 **Red LEDs**
* Coin Cell Battery + Holder
* ADXL345 Accelerometer
#### Schematic
![Schematic](./doc/schematic.PNG)
* Minimal I/O Pins required (in total: 4)
* 2 Pin Connection to Shiftregister (CLK and DATA to **Attiny85** + LATCH connected to DATA)
* Accelerometer for Shake Detection
* "Shuffle" Animation
* LEDs logically connected in Pairs


#### 3D Printed Case
<p>
  <img src="/doc/case.png" width="360px" >
  <img src="/doc/shuffle.gif" width="360px" >
</p>
