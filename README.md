# Particle-Concentration-Sensor-using-Arduino
This project is about creating a sensor to measure the amount of particles in the air using an Arduino. The sensor detects tiny particles and provides data on air quality.

# What-you-need
  - Arduino
  - Breadboard
  - MATLAB
  - MEMS microphone
  - PMS5003 Digital universal particle concentration sensor ([https://www.digikey.com/en/htmldatasheets/production/2903006/0/0/1/pms5003-series-manual](url))
  - Jumper cables

# How-to-use
Complete the circuit by doing the following:  
  - Connect the output of the MEMS microphone to analog output pin A0.
  - Power the MEMS microphone using 3.3V and ground it.
  - Connect the PMS5003 sensor to the breadboard.
  - SET -> PIN4
  - RX -> PIN3  
  - TX -> PIN2  
Then, upload the .ino file to the Arduino using Arduino IDE. Once uploaded run the MATLAB code. The number of lines you want to read can be changed in the code. You can also change the in the .ino file to be able to change how fast the data is sampled. The data is output as a Nx7 matrix of the data.  

# Data.txt file
Column 1: Particles > 0.3um / 0.1L air  
Column 2: Particles > 0.5um / 0.1L air  
Column 3: Particles > 1.0um / 0.1L air  
Column 4: Particles > 2.5um / 0.1L air  
Column 5: Particles > 5.0um / 0.1L air  
Column 6: Particles > 10.0um / 0.1L air  
Column 7: Voltage data from the MEMS microphone  

# Common-problems
  - Make sure that the circuit is correctly made. 
  - Clear the MATLAB workspace after each use.
  - Check the connections on the PMS5003.

  
