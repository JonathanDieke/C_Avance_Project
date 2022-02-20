#include <stdio.h>


int main(){
    int fib0 = 0, fib1 = 1;
    int fib = 0;

    for(int i = 0; i<5; i++){
        fib = fib1 + fib0 ;
        fib0 = fib1 ;
        fib1 = fib ;
    }

    printf("\nresultat : %d\n", fib);
    return fib ;

    // fib5 = fib4 + fib3 = fib3+fib2+fib2+fib1 = 1+1+1+1+1
    // fib6 = fib5 + fib4 = (1+1+1+1+1) + 1+1+1 = 8

}