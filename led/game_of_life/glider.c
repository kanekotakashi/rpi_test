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
int world[5]={
            0b00000,
            0b00000,
            0b00111,
            0b00100,
            0b00010 };

void alive(int x,int y) {
    int i;
    for (i=0;i<5;i++) {
        bcm2835_gpio_write(pinY[i], HIGH);
        bcm2835_gpio_write(pinX[i], LOW);
    }
    bcm2835_gpio_write(pinY[y], LOW);
    bcm2835_gpio_write(pinX[x], HIGH);
    bcm2835_delay(1);
}
int count(int now[],int cellX,int cellY) {
    int line,x,y;
    int count=0;
    for (y=cellY-1;y<=cellY+1;y++) {
        if (y<0||y>4)
            continue;
        line=now[y];
        for (x=cellX-1;x<=cellX+1;x++) {
            if (x<0||x>4)
                continue;
            if (((line<<x) & 0b10000) && !(x==cellX && y==cellY)) {
                count++;
            }
        }
    }
    return count;
}
int step(int now[],int time) {
    int next[5]={0,0,0,0,0};
    int c,end=0;
    int line,t,x,y;
    for (t=0;t<time;t++) {
        for (y=0;y<5;y++) {
            line=now[y];
            for (x=0;x<5;x++) {
                c = count(now,x,y);
                if ((line<<x) & 0b10000){
                    alive(x,y);
                    if (c==2||c==3){
                        next[y] |= 0b10000>>x;
                    } else {
                        next[y] &= ~0b10000>>x;
                    }
                } else {
                    if (c==3){
                        next[y] |= 0b10000>>x;
                    } else {
                        next[y] &= ~0b10000>>x;
                    }
                }
                printf("%d (%d,%d)\n",c,x,y);
            }
        }
    }
    for (y=0;y<5;y++) {
         line=now[y];
         if (line==next[y]) 
             end++;
    }
    if (end==5) {
        //restart
        end=0;
        step(world,time);
    } else {
        step(next,time);
    }
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

    printf("start\n");
 
    step(world,40);

    bcm2835_close();
    return 0;
}
        
        

