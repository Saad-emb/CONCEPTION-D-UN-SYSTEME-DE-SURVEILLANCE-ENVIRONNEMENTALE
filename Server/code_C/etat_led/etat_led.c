#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<time.h>

#include "io.h"

int main() {
    FILE *file;
    float first, second;
    S_GPIO_LINE s_line8, s_line9;
    load_gpio_line(&s_line8, "27", OUT);// red led
    load_gpio_line(&s_line9, "22", OUT);//green led
    // Open file for reading
    file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Read first two numbers
    fscanf(file, "%f %f", &first, &second);

    // Close file
    fclose(file);

    // Check if first number is greater than 30
    if (first > 30) {
        
	set_gpio_line(&s_line8, 1);
	set_gpio_line(&s_line9, 0);
    }
    else{
       
	set_gpio_line(&s_line8, 0);
	set_gpio_line(&s_line9, 1);
    }

    return 0;
}
