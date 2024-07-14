# Particle-Concentration-Sensor-using-Arduino
The goal of this project is to measure the amount of particles in the air using a sensor connected to an Arduino. The sensor detects tiny particles, helping us calculate air quality. We can use the collected data to understand the relationship between noise levels (dB) and particulate matter concentration in the air. When noise levels increase near busy roads, you can observe and plot an increase in particulate matter.

![image](https://github.com/user-attachments/assets/a16f43f7-e0a9-4836-a3f6-bba29bd5cadd)
_(Shu, Yang, & Zhu, 2014)_

# What-you-need
  - Arduino
  - Breadboard
  - MATLAB
  - MEMS microphone
  - PMS5003 Digital Universal Particle Concentration Sensor
  - Jumper cables

# How-to-use
Complete the circuit by doing the following:  
  - Connect the output of the MEMS microphone to analog output pin A0.
  - Power the MEMS microphone using 3.3V and ground it.
  - Connect the PMS5003 sensor to the breadboard.
  - Power the PMS5003 sensor with 5V and ground it.
  - SET -> PIN4
  - RX -> PIN3  
  - TX -> PIN2  
Then, upload the .ino file to the Arduino using Arduino IDE. Once uploaded run the MATLAB code. The number of lines you want to read can be changed in the code. You can also change the in the .ino file to be able to change how fast the data is sampled. The data is output as a Nx7 matrix of the data.

NOTE: Be sure to change the MATLAB code to reflect the serial port you are using. Also, confirm the baud rate.

# Data.txt file
Column 1: Particles > 0.3um / 0.1L air  
Column 2: Particles > 0.5um / 0.1L air  
Column 3: Particles > 1.0um / 0.1L air  
Column 4: Particles > 2.5um / 0.1L air  
Column 5: Particles > 5.0um / 0.1L air  
Column 6: Particles > 10.0um / 0.1L air  
Column 7: Voltage data from the MEMS microphone  

# Common-problems
  - Make sure that the circuit is correctly made and check all connections.
  - Clear the MATLAB workspace after each use.
  - Check the connections on the PMS5003.
  - If the output on ths PMS5003 is all 0's then use the reset pin to reset the device.


# References
Shu, S., Yang, P., & Zhu, Y. (2014). Correlation of noise levels and particulate matter concentrations near two major freeways in Los Angeles, California. Environmental Pollution, 193, 130-137. https://doi.org/10.1016/j.envpol.2014.06.025




  
