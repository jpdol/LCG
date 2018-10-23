#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

double chiSquared(int obtained[], int expected[]){
    double chi = 0;
    for(int j = 0; j < 10; j++){
        chi += pow(obtained[j] - expected[j], 2)/expected[j];
    }
    return chi;
}

unsigned long long randomLCG(unsigned long long x){
    unsigned long long a = 3935559000370003845;
    unsigned long long c = 2691343689449507681;
    unsigned long long mod = pow(2, 64);

    return ((x*a + c)%mod);
}

int main(){

    unsigned long long x = 6798466340874578877; //seed
    
    int period;
    
    printf("Número de Gerações:\n");
    scanf("%d", &period);

    int obtainedC[10] ={};
    int obtainedRand[10] = {};
    int expected[10]  ={period/10, period/10, period/10, period/10, period/10, period/10, 
        period/10, period/10, period/10, period/10};
    
    double critVal = 16.919;
    
    clock_t initTC = clock();
    for(int i = 0; i < period; i++){
        x = randomLCG(x);
        obtainedC[x%10]++;
    }
    clock_t finishTC = clock();
    

    double deltaTC = (double) (finishTC - initTC) / CLOCKS_PER_SEC;
    printf("%lf \n", deltaTC);
    
    double chi = chiSquared(obtainedC, expected);
    printf("%f\n", chi);
    
    unsigned int y;
    clock_t initRand = clock();
    for(int k = 0; k < period; k++){
        y = rand();
        obtainedRand[y%10]++;   
    }
    clock_t finishRand = clock();
    double deltaRand = (double)(finishRand - initRand) / CLOCKS_PER_SEC;
    printf("%lf\n", deltaRand);
    double chiRand = chiSquared(obtainedRand, expected);
    printf("%lf", chiRand);
    return 0;
}
