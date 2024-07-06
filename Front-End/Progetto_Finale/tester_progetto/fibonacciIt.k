def fibo(n) {
   var a = 0;
   var b = 1;
   for (var i = 1; i<n; i=i+1) {
       var oldb = b;
       b = a+b;
       a = oldb
   };
   b 
};
