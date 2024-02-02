# Stop Watch based on ATmega32
> The Requirments of the Stop Watch System.

### Implement the following Stop Watch system with the specifications listed below:
1. Use ATmega32 Microcontroller with ***frequency 1Mhz***.
2. Configure ***Timer1*** in ATmega32 with ***CTC mode*** to count the Stop Watch time.
3. Use six Common Anode 7-segments.
4. Connect the six 7-segments in the project using the *multiplexed technique*. You 
  should use one **7447 decoder** for all 7-segments and control the enable/disable for 
  each 7-segement using a **NPN BJT transistor** connect to one of the MCU pins. Like the 
  below image:
<img width="500" alt="main 7-segment" src="https://github.com/Salahbendary/Stop_Watch_ATmega32/blob/main/283995578-921c57b6-cfd6-4c3b-b683-fdea8f508fa9.png">


> [!NOTE]
> The above image is just to illustrate the basic idea about the multiplexed 7-segments.
> Use The common anode decoder 7447 instead of the IC in the image.
> 
> <img width="475" alt="7-segment" src="https://github.com/Salahbendary/Stop_Watch_ATmega32/blob/main/283995599-1a2477c3-2b46-425c-bf0d-b595e79c99b5.png">


6. We can connect more than one 7-segment display by using the Multiplexing method. In 
this method, ***at a time one 7-segment display is driven by the Microcontroller and the rest 
are OFF. It keeps switching the displays using transistors. Due to the persistence of vision, 
it appears as a normal display**.
7. Connect 7447 decoder *4-pins* to the first *4-pins* in **PORTC**.
8. Use first *6-pins* in **PORTA** as the enable/disable pins for the six 7-segments.
9. Stop Watch counting should **start once the power is connected to the MCU**.
10. Configure External Interrupt ***INT0 with falling edge***. Connect a *push button* with the 
***internal pull-up resistor***. If a **falling edge** detected the Stop Watch time should be
**reset**.
11. Configure External Interrupt ***INT1 with raising edge***. Connect a *push button* with the 
***external pull-down resistor***. If a **raising edge** detected the Stop Watch time should be
**paused**.
12. Configure External Interrupt ***INT2 with falling edge***. Connect a *push button* with the 
***internal pull-up resistor***. If a **falling edge** detected the Stop Watch time should be
**resumed**.
### Check this video: https://youtu.be/emp-musYxII
