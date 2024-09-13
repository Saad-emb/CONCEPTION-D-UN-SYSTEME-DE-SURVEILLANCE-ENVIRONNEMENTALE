import Adafruit_DHT

# Sensor should be set to Adafruit_DHT.DHT11,
# Adafruit_DHT.DHT22, or Adafruit_DHT.AM2302.
sensor = Adafruit_DHT.DHT11

# Example using a Beaglebone Black with DHT sensor
# connected to pin P8_11.
#pin = 'P8_11'

# Example using a Raspberry Pi with DHT sensor
# connected to GPIO4.
pin = 4

# Try to grab a sensor reading.  Use the read_retry method which will retry up
# to 15 times to get a sensor reading (waiting 2 seconds between each retry).

humidity, temperature = Adafruit_DHT.read_retry(sensor, pin)
print('Temp={0:0.1f}*C  Humidity={1:0.1f}%'.format(temperature, humidity))
    
# Write the temperature and humidity values to a file named data.txt, overwriting previous data
with open('data.txt', 'w') as f:
    f.write('{:.1f} {:.1f}'.format(temperature, humidity))
