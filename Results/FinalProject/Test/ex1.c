#include <stdio.h>
#include <stdlib.h>

int main() {


    int *ip;    /* pointer to an integer */

    /* ip = &i; */

    ip = malloc(8);

    /* printf("Address of i is %p", &i); */
    /* printf("Address of i is %p", ip); */

    *ip = 99;

    printf("value of i is %d", *ip);




}
