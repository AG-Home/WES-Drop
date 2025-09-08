#!/usr/bin/env python3
import serial

DEVICE = "/dev/ttyUSB0"
BAUDRATE = 9600

def checksum(b0, b1, b2):
    return (b0 + b1 + b2) & b0

ser = serial.Serial(DEVICE, BAUDRATE, timeout=1)
print("Leyendo datos del SR04M...")

buffer = bytearray()

while True:
    b = ser.read(1)
    if not b:
        continue
    
    buffer.append(b[0])

    while len(buffer) >= 4:
        if buffer[0] == 0xFF:
            b1, b2, b3, b4 = buffer[:4]

            if checksum(b1, b2, b3) == b4:
                dist = (b2 << 8) + b3
                print(f"Distancia: {dist} mm")
            else:
                print(f"Checksum inválido: {b1:02X} {b2:02X} {b3:02X} {b4:02X}")

            buffer = buffer[4:]
        else:
            buffer = buffer[1:]
