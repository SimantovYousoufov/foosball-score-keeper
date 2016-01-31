# foosball-score-keeper
An LED foosball scorekeeper powered by Particle Photon.


Parts
---
* [Particle Photon](https://store.particle.io/) (or any microcontroller)
* [An LED display matrix](https://www.adafruit.com/product/420) - Adafruit has great documentation
* Lots and lots of wires

Dependencies
---
* [pkourany's RGBMatrix library for Aruinos and Particle Photons](https://github.com/pkourany/RGBmatrixPanel_IDE)
* [pkourany's fork of Adafruit's GFX Library](https://github.com/pkourany/Adafruit_mfGFX_IDE)

All dependencies can be found in Particle's Web IDE library browser.

Wiring
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
