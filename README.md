# ESP32-Seat-Control
This project provides a reliable asynchronous web server firmware for the ESP32-S microcontroller, designed for automotive seat adjustment and accessory switching. It implements a hybrid control model featuring a latching switch mode for accessory management and four momentary push channels for precise motor positioning.

# Key Features
Hybrid Control Interface:

Latching Channel (Pin 12): Operates as a toggle switch with persistent on/off state tracking.

Momentary Channels (Pins 14, 27, 26, 25): Active only while buttons are pressed, utilizing touch and mouse event listeners (onmousedown/ontouchstart) to prevent accidental continuous motor engagement.

Embedded Access Point (AP): Creates an independent local Wi-Fi network (Control_Relee_Hadef) for direct smartphone or tablet connectivity without requiring an external router.

Asynchronous Web Server: Built on ESPAsyncWebServer for fast, non-blocking HTTP request handling and responsive mobile UI rendering.

Active-Low Relay Logic: Safely configures and handles standard multi-channel relay modules, ensuring proper state initialization on boot.

# RELAY

<img width="753" height="355" alt="image" src="https://github.com/user-attachments/assets/efcc5a57-51c4-4ca2-95f1-be7407317c6f" />

# ESP 32

<img width="462" height="293" alt="image" src="https://github.com/user-attachments/assets/c57fadcf-1d0a-4a32-876f-509d68833be2" />

# Mini DC-DC Step-Down Power Module (5 V, 3 A) 

<img width="410" height="272" alt="image" src="https://github.com/user-attachments/assets/7571c0cb-df6f-4ba1-86a8-18f4363845e6" />

# How I Designed the Project


I used the step-down converter to reduce the 12V supply from the car cigarette lighter to 5V. I used this to power both the relays and the ESP32 (via its 5V pin). Then, I routed wires from the programmed ESP32 pins to each individual relay.

The interesting part of the project is the motor connection setup: each motor is connected to two relays at their common (COM) terminals. The Normally Closed (NC) terminals are wired directly to the chassis ground, while the Normally Open (NO) terminals connect to the 12V line from the fuse box—allowing the motors to rotate in both directions.

It's also worth noting that the seat still operates via its original factory buttons, as I kept them fully functional alongside the new system.


