#include<stdio.h>
#include<stdlib.h>


unsigned power(unsigned x, unsigned y){
    if (y==0){
        return 1;
    }
    if (y==1){
        return x;
    }
    else{
        return x*power(x,y-1);
    }
}
