# Exploring tilt compensation for magnemometers using machine learning instead of secondary sensors
The QMC5883L is a standalone magnemometer, without a gyro, accelorometer, or other way to determine which way is down.
Because of this, tilt compensation is difficult if not impossible without other sensors.
This library explores using machine learning to compensate for tilt specifically for the QMC5883L, but should be easily extensible to any standalone magnemometer

### How to set up for yourself:
1. I used an iPhone compass to collect accurate heading data for the model to train on, so if you choose to follow the same route, set up an Apple developer account, and sideload the swift app provided (dataClient) onto your phone
3. Load the compass data collection sketch onto your arduino
4. Mount the magnemometer and phone to a flat plane (I used a piece of wood), with the direction you want the magemometer to detect facing the same direction the phone does
5. Install libimobiledevice (brew or apt install libimobiledevice)
6. Install pyserial (pip install pyserial)
7. Run dataCollector.py with everything connected to your computer and move the plank around tilting it every way possible to generate your data
8. Train your model using the provided ...
9. Load your model into a header file using the provided ...
10. Use the model as shown in example_usage.ino
