# Lego NXT2.0 - RS485 - Arduino - i2c - mpu6050
Arduino Sketch & NXC Sketch

Arduino ждет от Lego NXT2.0 через RS485 на SoftwareSerial команду "1" = "передать угол Z c гироскопа MPU6050"

Pins:

10 - RX SoftSerial (RO MAX485)

11 - TX SoftSerial (DI MAX485)

12 - RE/DE MAX485 (low - recive, high - send)

A5 - SCL MPU6050 (i2c)

A4 - SDA MPU6050 (i2c)

 LEGO NXT2.0:

Blue (1 pin) A MAX485

Yellow (2 pin) B MAX485

Green (3 pin) Vin Arduino

Red (4 pin) GND Arduino & GND RS485 & GND MPU6050

Black - no

White - no
