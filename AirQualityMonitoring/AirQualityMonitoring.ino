/**
 * @file AirQualityMonitoring.ino
 * @brief Arduino sketch for monitoring air quality using a PMS5003 sensor and a microphone.
 * 
 * This sketch reads data from a PMS5003 sensor and a microphone to monitor air quality.
 * It uses the SoftwareSerial library to communicate with the PMS5003 sensor and reads
 * the analog output from the microphone. The air quality data is then printed to the serial
 * monitor.
 * 
 * @author Kevin Hernandez
 * @date 7/12/24
 */


#include <SoftwareSerial.h>

SoftwareSerial pmsSerial(2, 3);
int mic = A0;    // Microphone pin
int micOut;      // Variable to hold analog values from mic
int setPin = 4;  // Pin for SET functionality
int resetPin = 5; // Not neccesary at this moment
bool headerPrinted = false;
float Vmeas;

void setup() {
  // Initialize serial communications
  Serial.begin(9600);     // Higher baud rate for faster communication
  pmsSerial.begin(9600);  // Sensor baud rate is 9600

  pinMode(setPin, OUTPUT);     // Configure setPin as output
  digitalWrite(setPin, HIGH);  // Set SET pin high for normal operation

  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
}

struct pms5003data {
  uint16_t framelen;
  uint16_t pm10_standard, pm25_standard, pm100_standard;
  uint16_t pm10_env, pm25_env, pm100_env;
  uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
  uint16_t unused;
  uint16_t checksum;
};

struct pms5003data data;

void loop() {


  if (!headerPrinted) {
    // Print headers for particle data once
    Serial.println("Particles > 0.3um / 0.1L air,Particles > 0.5um / 0.1L air,Particles > 1.0um / 0.1L air,Particles > 2.5um / 0.1L air,Particles > 5.0um / 0.1L air,Particles > 10.0um / 0.1L air");
    headerPrinted = true;     // Set flag to true after printing
    // Reset the PMS5003
    //pinMode(resetPin, OUTPUT); 
    //digitalWrite(resetPin, HIGH);
    //delay(10);
    //digitalWrite(resetPin, LOW);
  }
  if (readPMSdata(&pmsSerial)) {
    // Reading data was successful!
    Serial.print(data.particles_03um);
    Serial.print(" ");
    Serial.print(data.particles_05um);
    Serial.print(" ");
    Serial.print(data.particles_10um);
    Serial.print(" ");
    Serial.print(data.particles_25um);
    Serial.print(" ");
    Serial.print(data.particles_50um);
    Serial.print(" ");
    Serial.print(data.particles_100um);
    Serial.print(" ");

    // Read the input on analog pin 0:
    micOut = analogRead(mic);
    Vmeas = micOut * (5.0 / 1023.0);  // compute voltage

    Serial.println(Vmeas, 3);  // send voltage data with 3 decimal places
  }

  delay(350);  // Adjust delay as needed for your application
}


/**
 * @brief Reads data from a stream and parses it into a structured format.
 * 
 * This function reads data from the specified stream and parses it into a structured format.
 * It expects the data to start with a special start byte (0x42 or 0x4d) and reads 32 bytes of data.
 * The data is then checked for validity and converted into a struct.
 * 
 * @param s The stream to read data from.
 * @return Returns true if the data was successfully read and parsed, false otherwise.
 */
boolean readPMSdata(Stream *s) {
  if (!s->available()) {
    return false;
  }

  // Read a byte at a time until we get to the special '0x42' or '0x4d' start-byte
  while (s->peek() != 0x42 && s->peek() != 0x4d) {
    s->read();  // Discard any bytes until we find a valid start byte
    if (!s->available()) {
      Serial.print("Finding start bit...");
      return false;  // No valid start byte found
    }
  }

  // Now read all 32 bytes
  if (s->available() < 32) {
    return false;  // Not enough data bytes available
  }

  uint8_t buffer[32];
  uint16_t sum = 0;
  s->readBytes(buffer, 32);

  // Check for valid start byte
  if (buffer[0] != 0x42 && buffer[0] != 0x4d) {
    return false;  // Invalid start byte
  }

  // Get checksum ready
  for (uint8_t i = 0; i < 30; i++) {
    sum += buffer[i];
  }

  // The data comes in endian'd, this solves it so it works on all platforms
  uint16_t buffer_u16[15];
  for (uint8_t i = 0; i < 15; i++) {
    buffer_u16[i] = buffer[2 + i * 2 + 1];
    buffer_u16[i] += (buffer[2 + i * 2] << 8);
  }

  // Put it into a nice struct :)
  memcpy((void *)&data, (void *)buffer_u16, 30);

  if (sum != data.checksum) {
    Serial.println("Checksum failure");
    return false;
  }

  // Success!
  return true;
}
