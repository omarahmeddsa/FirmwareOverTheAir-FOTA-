import serial
import time

# Configure the serial port
ser = serial.Serial('COM8', 9600, timeout=3)  # Change 'COM1' to your serial port and 115200 to the baud rate
time.sleep(2)  # Wait for the serial connection to initialize

# Convert values to bytes

# Send values to UART
ser.write(str(5).encode('utf-8')')
ser.write(15)
ser.write(b'#')

# Close the serial port
ser.close()


# Close the serial port
ser.close()
