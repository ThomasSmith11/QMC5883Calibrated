
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
port = ports[choice-1].device
ser = serial.Serial(port, baudrate)

proc = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)

with open("../QMCModelTrainer/compassAndHeadingData.csv", "w") as f:
  writer = csv.writer(f)
  writer.writerow(["Heading", "X", "Y", "Z", "YXatan"])
f = open("../QMCModelTrainer/compassAndHeadingData.csv", "a")

while True:
  try:
    line = proc.stdout.readline().decode()
    if not line:
      break
    if "dataClient(Foundation)" in line:
      ser.write(b"send\n")
      compassData = ser.readline().decode().strip().split(",")
      heading = line.split(" ")[-1].strip()
      csvRow = [heading]+compassData
      print(heading+','+','.join(compassData))
      writer.writerow(csvRow)
  except KeyboardInterrupt:
    print("Closing Serial")
    ser.close()
    print("Closing CSV")
    f.close()
    proc.kill()
    break
    
