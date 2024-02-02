# Stop Watch System using ATmega32

## Overview
This project implements a Stop Watch system based on the ATmega32 microcontroller, operating at a frequency of 1MHz. The system incorporates Timer1 in CTC mode for precise time measurement and utilizes six Common Anode 7-segment displays arranged in a multiplexed configuration.

## Components Used
1. **Microcontroller:** ATmega32 operating at 1MHz.
2. **Timer Configuration:** Timer1 configured in CTC mode for accurate timekeeping.
3. **Display:** Six Common Anode 7-segment displays using multiplexed technique.
   - Each 7-segment display is controlled by a 7447 decoder and a NPN BJT transistor for enable/disable.
   - Multiplexing method is employed, allowing one display to be driven at a time for a seamless appearance.
4. **Port Connections:**
   - 7447 decoder connected to the first 4 pins in PORTC.
   - First 6 pins in PORTA used as enable/disable pins for the six 7-segments.
5. **User Controls:**
   - Start: Stopwatch begins counting upon connecting power to the MCU.
   - Reset: External Interrupt INT0 with falling edge detects a button press, resetting the stopwatch time.
   - Pause: External Interrupt INT1 with rising edge detects a button press, pausing the stopwatch time.
   - Resume: External Interrupt INT2 with falling edge detects a button press, resuming the stopwatch time.
6. **Buttons:**
   - Connected with appropriate pull-up/pull-down resistors based on the specified requirements.
7. **Connection Example:**
   - Refer to the provided image for a visual representation of the main 7-segment display setup.
     ![Main 7-Segment Display](https://github.com/Salahbendary/Stop_Watch_ATmega32/blob/main/283995578-921c57b6-cfd6-4c3b-b683-fdea8f508fa9.png)

> [!NOTE]
> The image is for illustration purposes only. Replace the depicted IC with a common anode decoder 7447 in the actual setup.

8. **Reference Image:**
   - For a detailed view of the 7-segment display, consult the provided image.
     ![7-Segment Display](https://github.com/Salahbendary/Stop_Watch_ATmega32/blob/main/283995599-1a2477c3-2b46-425c-bf0d-b595e79c99b5.png)

