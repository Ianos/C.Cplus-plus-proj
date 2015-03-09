#include <stdio.h>
#include <stdlib.h>

int comp(const void*,const void*);


int main () {

long long int i,n,a,b,w;
long long int teliko=0;

		scanf( "%lld", &n);
		
long long int sum_mst=0;
			
long long int *varos=(long long int*)malloc((n-1)*sizeof(long long int));
		
			for (i=0; i<n-1; i++)
				{
					scanf( "%lld%lld%lld", &a, &b, &w);
					sum_mst=sum_mst+w;
					varos[i]=w;
								}
								
								
								
			qsort(varos,n-1,sizeof(long long int),&comp);
			
			
			for (i=n-2; i>=0; i--)
			{
                system("PAUSE");
			 teliko=teliko+(i*(varos[i]+1))+varos[i];
                                               }
                   
                   printf( "%lld\n", teliko);
								system("PAUSE");
								
								
		
								
							
								
}


int comp(const void * e,const void * f) 
{
   long long int* c;
    long long int* d;
    c=(long long int*)e;
    d=(long long int*)f;
  if (*c==*d)
    return 0;
  else
    if (*c < *d)
        return -1;
     else
      return 1;
}
			
			
