
import serial
import serial.tools.list_ports

arduino_ports = [
    p.device
    for p in serial.tools.list_ports.comports()
    if 'Silicon' in p.description  # may need tweaking to match new arduinos
]

try:
    ser = serial.Serial(arduino_ports[0])
    print(f"ESP32 encontrado na porta -->", arduino_ports[0])
except IndexError:
    print("ESP32 não encontrado!!!")
    