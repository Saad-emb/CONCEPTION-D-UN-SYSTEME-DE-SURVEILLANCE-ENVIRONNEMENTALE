#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>

#define BUFFER_SIZE 256
#define FILE_NAME "data_gps.txt"

int main()
{
    // Open the serial port for reading
    int serial_port = open("/dev/serial0", O_RDONLY);

    if (serial_port < 0) {
        printf("Error %i from open: %s\n", errno, strerror(errno));
        return -1;
    }

    // Open the file for writing
    FILE *file = fopen(FILE_NAME, "w");

    if (file == NULL) {
        printf("Error %i from fopen: %s\n", errno, strerror(errno));
        return -1;
    }

    // Read data from the serial port
    char buffer[BUFFER_SIZE];

    
        memset(buffer, 0, BUFFER_SIZE);

        int bytes_read = read(serial_port, buffer, BUFFER_SIZE);

        if (bytes_read < 0) {
            printf("Error %i from read: %s\n", errno, strerror(errno));
            return -1;
        }

        if (bytes_read > 0) {
            // Look for the GPRMC sentence in the data
            char* gprmc = strstr(buffer, "$GPRMC");

            if (gprmc != NULL) {
                // Parse the GPRMC sentence to get the latitude and longitude
                char* pch = strtok(gprmc, ",");
                int i = 0;
                double lat_degrees = 0.0;
                double lat_minutes = 0.0;
                double lng_degrees = 0.0;
                double lng_minutes = 0.0;

                while (pch != NULL) {
                    if (i == 3) {
                        double lat = atof(pch);
                        lat_degrees = floor(lat / 100.0);
                        lat_minutes = fmod(lat, 100.0);
                    } else if (i == 5) {
                        double lng = atof(pch);
                        lng_degrees = floor(lng / 100.0);
                        lng_minutes = fmod(lng, 100.0);
                    }

                    pch = strtok(NULL, ",");
                    i++;
                }

                // Print the latitude and longitude in decimal degrees
                double latitude = lat_degrees + lat_minutes / 60.0;
                double longitude = lng_degrees + lng_minutes / 60.0;
//                if (gprmc[20] == 'W') {
                    longitude = -longitude;
  //              }

                // Write the latitude and longitude to the file in one line
                fseek(file, 0, SEEK_SET);
                fprintf(file, "Latitude: %f, Longitude: %f", latitude, longitude);
                fflush(file);

                printf("Latitude: %f, Longitude: %f\n", latitude, longitude);
            }
        }
    

    // Close the file and serial port
    fclose(file);
    close(serial_port);

    return 0;
}
