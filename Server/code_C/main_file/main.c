#include <stdio.h>
#include <stdlib.h>

int main() {
  
    system("/www/c-bin/gps");
    system("python3 dht11.py");
    system("sudo python3 sql.py");
    system(" sudo /home/saad/a.out");	


    return 0;
}
