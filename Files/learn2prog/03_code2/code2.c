#include<stdio.h>

int count=0;

int printTriangle(int size){  // 修改返回类型为int
    count = 0;  // 重置count
    for(int i=1; i<=size; i++){  // 循环应从1开始，以打印正确数量的星号
        for(int j=1; j<=i; j++){
            printf("*");
            count++;
        }
        printf("\n");
    }
    return count;  // 现在可以返回count值
}

int main()
{
    int sum;

    printf("Here is a triangle with height 4\n");
    sum = printTriangle(4);  // 调用函数，并接收返回值
    printf("That triangle had %d total stars\n", sum);  // 应输出 "That triangle had 10 total stars"

    printf("Here is a triangle with height 7\n");
    sum = printTriangle(7);  // 调用函数，并接收返回值
    printf("That triangle had %d total stars\n", sum);  // 应输出 "That triangle had 28 total stars"

    return 0;
}
