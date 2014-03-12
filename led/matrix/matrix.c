#include <stdio.h>
#include <bcm2835.h>
int main()
{
    int i,x,y;
    int pinX[5]={
            RPI_GPIO_P1_26,
            RPI_GPIO_P1_24,
            RPI_GPIO_P1_22,
            RPI_GPIO_P1_18,
            RPI_GPIO_P1_16};
    int pinY[5]={
            RPI_GPIO_P1_07,
            RPI_GPIO_P1_11,
            RPI_GPIO_P1_12,
            RPI_GPIO_P1_15,
            RPI_GPIO_P1_19};
    int high_low[2]={LOW,HIGH};

    if (!bcm2835_init()) {
        return 1;
    }
    
    // setup(output) and reset
    for(x=0;x<5;x++) {
        for(y=0;y<5;y++) {
            bcm2835_gpio_fsel(pinY[y], BCM2835_GPIO_FSEL_OUTP);
            bcm2835_gpio_write(pinY[y], LOW);
            bcm2835_gpio_fsel(pinX[x], BCM2835_GPIO_FSEL_OUTP);
            bcm2835_gpio_write(pinX[x], LOW);
        }
    }

    i=0;
    while (1)
    {

        for(x=0;x<5;x++) {
            for(y=0;y<5;y++) {
                if (y==i) {
               	    bcm2835_gpio_write(pinY[y], LOW);
                } else {
               	    bcm2835_gpio_write(pinY[y], HIGH);
                }
                if (x==i) {
               	    bcm2835_gpio_write(pinX[x], HIGH);
                } else {
               	    bcm2835_gpio_write(pinX[x], LOW);
                }
            }
        }
        // wait a bit
        bcm2835_delay(5);
        i++;
        if (i == 5) i=0;

    }
    bcm2835_close();
    return 0;
}
        
        

