#!/usr/bin/env python3
import serial

# Device and communication settings
DEVICE = "/dev/ttyUSB0"   # Serial port where the SR04M is connected
BAUDRATE = 9600            # Baud rate for UART communication

# Function to calculate checksum according to SR04M logic
def checksum(b0, b1, b2):
    """
    Calculate the checksum of a packet.
    Returns a single byte to validate the packet.
    """
    return (b0 + b1 + b2) & b0

# Open serial port for reading sensor data
ser = serial.Serial(DEVICE, BAUDRATE, timeout=1)

print("Reading SR04M sensor data...")

buffer = bytearray()  # Store incoming bytes until a complete packet is received

while True:
    # Read one byte from the sensor
    b = ser.read(1)
    if not b:
        continue  # Skip if no data received (timeout)

    buffer.append(b[0])  # Collect bytes in the buffer

    # Process full packets of 4 bytes
    while len(buffer) >= 4:
        # Check if the packet starts with the header byte 0xFF
        if buffer[0] == 0xFF:
            b1, b2, b3, b4 = buffer[:4]  # Extract one packet

            # Validate packet using checksum
            if checksum(b1, b2, b3) == b4:
                # Extract distance from the two middle bytes (big endian)
                dist = (b2 << 8) + b3
                print(f"Distance: {dist} mm")
            else:
                print(f"Invalid checksum: {b1:02X} {b2:02X} {b3:02X} {b4:02X}")

            # Remove processed packet from buffer
            buffer = buffer[4:]
        else:
            # Discard bytes until the next header is found
            buffer = buffer[1:]
