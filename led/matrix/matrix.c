#include <stdio.h>
#include <bcm2835.h>

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
void high(int x,int y) {
    int i;
    for (i=0;i<5;i++) {
        bcm2835_gpio_write(pinY[i], HIGH);
        bcm2835_gpio_write(pinX[i], LOW);
    }
    bcm2835_gpio_write(pinY[y], LOW);
    bcm2835_gpio_write(pinX[x], HIGH);
    bcm2835_delay(1);
}
int main()
{
    int i,x,y;
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

    while (1)
    {

        for (i=0;i<50;i++) {
            //"A"
            high(2,0);
            high(1,1);
            high(3,1);
            high(0,2);
            high(4,2);
            high(0,3);
            high(1,3);
            high(2,3);
            high(3,3);
            high(4,3);
            high(0,4);
            high(4,4);
        }

    }
    bcm2835_close();
    return 0;
}
        
        

