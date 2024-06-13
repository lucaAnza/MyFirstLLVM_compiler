void twoloops(int a[] , int b[] , int c[] , int d[] ){
    int i;

    for(i=0 ; i<100 ; i++)
        a[i] = b[i] + c[i];
    
    for(i=0 ; i<100 ; i++)
        d[i] = a[i] * a[i];
}