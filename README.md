# ESP32-S-Seat-Control
This project provides a reliable asynchronous web server firmware for the ESP32-S microcontroller, designed for automotive seat adjustment and accessory switching. It implements a hybrid control model featuring a latching switch mode for accessory management and four momentary push channels for precise motor positioning.

# Key Features
Hybrid Control Interface:

Latching Channel (Pin 12): Operates as a toggle switch with persistent on/off state tracking.

Momentary Channels (Pins 14, 27, 26, 25): Active only while buttons are pressed, utilizing touch and mouse event listeners (onmousedown/ontouchstart) to prevent accidental continuous motor engagement.

Embedded Access Point (AP): Creates an independent local Wi-Fi network (Control_Relee_Hadef) for direct smartphone or tablet connectivity without requiring an external router.

Asynchronous Web Server: Built on ESPAsyncWebServer for fast, non-blocking HTTP request handling and responsive mobile UI rendering.

Active-Low Relay Logic: Safely configures and handles standard multi-channel relay modules, ensuring proper state initialization on boot.
