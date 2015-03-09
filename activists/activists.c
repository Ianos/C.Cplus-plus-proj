#include <stdio.h>
#include <stdlib.h>

int** mul(int**,int**,int);


int main()
{

int k,n,m,s,t,l,i,j,x,y,exp;

scanf( "%d%d%d%d%d", &k, &n, &m, &s, &t );  

int **a=(int**)malloc(n*sizeof(int*));
int **power=(int**)malloc(n*sizeof(int*));

for (l=0; l<n; l++){
    a[l]=(int *)malloc(n*sizeof(int));
	power[l]=(int *)malloc(n*sizeof(int));
                                             }
	// arhikopoiisi pinaka me zero's
for (i=0; i<n; i++)
	{
		for (j=0; j<n; j++)
		{
		a[i][j]=0;
		power[i][j]=0;
		//kano ton power monadiaio
        if (i==j) power[i][i]=1;
        }
		
				}
	system("PAUSE");
			
			for (i=0; i<m; i++)
			{
				scanf( "%d%d", &x, &y);
				a[x-1][y-1]=1;
				}
				
exp=k-1;
			
while (exp>=1){
      if (exp%2==1)
      power=mul(power,a,n);
      exp=exp/2;
      a=mul(a,a,n);
      }
      


printf("%d\n",power[s-1][t-1]);       
system("PAUSE");

      
	
				
				
				
				
}

int** mul (int** array1,int** array2,int N) {
      
      int c,d,k,f,sum;
      int **pol=(int**)malloc(N*sizeof(int*));
      for (f=0; f<N; f++)
      pol[f]=(int *)malloc(N*sizeof(int));
      system("PAUSE");
      
for ( c = 0 ; c < N  ; c++ )
    {
      for ( d = 0 ; d < N ; d++ )
      {
          sum=0;
        for ( k = 0 ; k < N ; k++ )
        {
          sum = (sum + array1[c][k]*(long long)array2[k][d])%100000007;
        }
 
        pol[c][d] = sum;
        sum = 0;
      }
    }
    
  return  pol;
  
  // free array pol
  
  for (f=0; f<N; f++) free(pol[f]);
  free(pol);
} 
// telos mul


