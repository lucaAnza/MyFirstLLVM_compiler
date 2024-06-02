int const N = 100;

void twoloops(int a[] , int b[] , int c[] , int d[]){
    int i;

    for(i=0 ; i<N ; i++)
        a[i] = b[i] + c[i];
    
    for(i=0 ; i<N ; i++)
        d[i] = a[i] * a[i];
}