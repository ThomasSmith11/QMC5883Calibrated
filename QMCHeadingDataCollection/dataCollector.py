import csv
import serial
import subprocess
import serial.tools.list_ports
command = "idevicesyslog"
baudrate = 9600

ports = serial.tools.list_ports.comports()

for i, port in enumerate(ports, start=1):
            print(f"{i}. {port.device}: {port.description}")

choice = int(input("Enter the number of the serial port you want to use: "))
port = str(ports[choice-1]).split(" ")[0]

ser = serial.Serial(port, baudrate)

proc = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)

f = open("compassAndHeadingData.csv", "w")
writer = csv.writer(f)
writer.writerow(["Heading", "X", "Y", "Z"])

while True:
  try:
    line = proc.stdout.readline().decode()
    if not line:
      break
    if "dataClient(Foundation)[73350] <Notice>: " in line:
      ser.write(b"send\n")
      compassData = ser.readline().decode().strip().split(",")
      heading = line.split(" ")[-1].strip()
      csvRow = [heading]+compassData
      writer.writerow(csvRow)
  except KeyboardInterrupt:
    print("Closing")
  finally:
    ser.close()
    f.close()
    

