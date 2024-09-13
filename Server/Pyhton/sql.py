import sqlite3
import time

# Connect to database
conn = sqlite3.connect('/home/saad/data_db.db')
c = conn.cursor()

# Create table if it doesn't exist
c.execute('''CREATE TABLE IF NOT EXISTS sensor_data
             (temperature REAL, humidity REAL, latitude REAL, longitude REAL, timestamp INTEGER)''')

# Read temperature and humidity from data.txt
with open('data.txt', 'r') as f:
    temp, hum = f.read().split()

# Read latitude and longitude from data_gps.txt
with open('data_gps.txt', 'r') as f:
    data = f.read()
    latitude = float(data.split(',')[0].replace('Latitude: ', '').strip())
    longitude = float(data.split(',')[1].replace('Longitude: ', '').strip())

# Get current timestamp
timestamp = int(time.time())

# Insert data into table
c.execute("INSERT INTO data VALUES (?, ?, ?, ?, ?)", (temp, hum, latitude, longitude, timestamp))

# Commit changes and close connection
conn.commit()
conn.close()
