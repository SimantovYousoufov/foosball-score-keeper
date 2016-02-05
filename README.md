# foosball-score-keeper
An LED foosball scorekeeper powered by Particle Photon.

![Scorekeeping in action](http://i.imgur.com/6NM9DyP.jpg)

Parts
---
* [Particle Photon](https://store.particle.io/) (or any microcontroller)
* [An LED display matrix](https://www.adafruit.com/product/420) - Adafruit has great documentation
* [At least two sets of IR break beam sensors](https://www.adafruit.com/products/2168)
* Lots and lots of wires

Dependencies
---
* [pkourany's RGBMatrix library for Aruinos and Particle Photons](https://github.com/pkourany/RGBmatrixPanel_IDE)
* [pkourany's fork of Adafruit's GFX Library](https://github.com/pkourany/Adafruit_mfGFX_IDE)

All dependencies can be found in Particle's Web IDE library browser.

Wiring (LED)
---
Wiring between the Spark and 16x32 or 32x32 display is as follows:

```
Panel Pin	Core Pin	Photon Pin
----------------------------------
  GND				GND			GND
  CLK 				D6          D6
  OE  				D7          D7
  LAT 				A4          A4
  A   				A0          A0
  B   				A1          A1
  C   				A2          A2
  D					A3			A3		//32x32 display only
  R1				D0			D0
  G1				D1			D1
  B1				D2			D2
  R2				D3			D3
  G2				D4			D4
  B2				D5			D5
```

Wiring (Sensor Circuits and Reset Switch)
---
We can use the leftover pins (A3, A5, A6) to wire our two sensors and reset switch. With the magic of the Photon, we can also use analog pins as digital pins and just read a HIGH/LOW so we can use them as switches in our circuits. Our table has a single ball collection tray so both return ducts end in the same tray. I opted to place the sensors at the end of the ball return ducts, right before they enter the collection tray because 1) a ball is less likely to be traveling fast enough and at an angle that will damage the sensor and 2) because the ball is traveling significantly slower by the time it reaches the sensor, I don't have to solve for a fast enough detection time.

Each break beam sensor has two components: the transmitter (power and ground) and receive (power, ground, signal). Note that the pins you decide to use will require a pull up resitor to be enabled. If you're not sure how to wire these, you can keep to these basic guidelines:
* 3.3V is enough, and both sets of transmitters/receivers can be connected to the same power source (ex: the 3V3 pin on the Photon)
* Both sets of Transmitters/receivers should be connected to the same ground on the Photon
* Signal wires should be connected to their respective pins

As for the reset switch, I used a simple button with one wire going to power and to other to A6.
