#include <stdio.h> 
#include <stdlib.h>
  
  
int main() {  
int i=0,days=0,last,cnt, m_o=0, mikos=0, megisto= 0,begin=0,eftase=0,mid=0;
      

	  
    //edo imaste//  
      
      
      
long long int sum = 0, megisto_sum = 0;  
      
  
scanf( "%d%d", &days, &m_o );  
int *a=(int*)malloc((days+1)*sizeof(int));
int *out=(int*)malloc((days+1)*sizeof(int));
int *b=(int*)malloc((days+1)*sizeof(int));
out[ 0 ] = 0;
b  [ 0 ] = 0;

//kai pame kali mas tihi//  
      
      
      
for ( i = 1; i <= days; ++i ) {  
scanf( "%d", &a[i] );  
sum = sum-(a[i] - m_o);  
if ( sum > megisto_sum ) { 
eftase=eftase+1; 
megisto_sum = sum;  
out[ eftase ] = sum;
b[eftase]=i;      
          
        }  
          
else {  


last=eftase;
begin=0;


while (begin<=last){
mid=(begin+last)/2;
if (out[mid]>=sum)
last=mid-1;
else
begin=mid+1;
}

mikos = i-b[mid];// - to i tou protou stoiheiou tou out pou einai >= sum //
if ( mikos > megisto ) {  
megisto = mikos;  
                }  
            } 		
        }  
        // teliosame//  
printf( "%d\n", megisto);  
system("pause");
  
return 0;  
}  
