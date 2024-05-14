#include <stdio.h>

int main() {
    int i, j, k, count;
	int d = 3;
	int f = 6;

    // Primo ciclo while
    i = 0;
    while (i < 10) {
        i++;
    }

    // Secondo ciclo while
    j = 20;
    while (j >= 10) {
        j -= 2;
    }

    // Terzo ciclo while
    k = 0;
    count = 0;
    while (count < 5) {
        if (k % 2 == 0) {
            count++;
        }
        k++;
    }
   

    // Quarto ciclo while
    i = 1;
    while (i <= 100) {
        if (i % 3 == 0 && i % 5 == 0) {
            f = f+4;
        }
        i++;
    }

    // Quinto ciclo while
    j = 1;
    while (j <= 20) {
        if (j % 2 != 0) {
            d = d-3;
        }
        j++;
    }


    // Primo ciclo for
    for (i = 0; i < 10; i++) {
        f = f+d;
    }


    // Secondo ciclo for
    for (j = 1; j <= 10; j++) {
        printf("%d ", j * j);
    }


	int a = 3;
    // Terzo ciclo for
    for (k = 1; k <= 5; k++) {
        for (j = 1; j <= 10; j++) {
			a = a+1;
		}
    }


    return 0;
}
