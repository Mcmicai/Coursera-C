#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int *array,size_t n){
    if(n==0){
        return 0;
    }
    size_t max_length =1;
    size_t current_length =1;
    for (size_t i = 1; i < n; i++)
    {
        if (array[i]>array[i-1])
        {
            current_length++;
            if(current_length>max_length){
                max_length = current_length;
            }
        }
        else{
            current_length = 1;
        }
    }
    return max_length;
}
