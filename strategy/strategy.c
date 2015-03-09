#include <stdio.h>
#include <stdlib.h>

int sumf(int*,int,int);

int main () {

int k,n,s,l,j,i,thesi,max,t,temp;

scanf( "%d",&n);

int *a=(int*)malloc(n*sizeof(int));
int *sum=(int*)malloc(n*sizeof(int));
int **S=(int**)malloc(n*sizeof(int*));
for (l=0; l<n; l++)
    S[l]=(int *)malloc(n*sizeof(int));

for (s=0; s < n; s++) scanf( "%d",&a[s]);

s=0;
for (thesi=0; thesi < n; thesi++)
{
sum[thesi]=s+a[thesi];
s=s+a[thesi];
}

for (k=0; k<n; k++) {

	for(i=0; i<n-k; i++){

		j= i+k;
		
		max=0;
		for(t=i; t<j; t++){
                 
                 if ( S[i][t] + sumf(sum,i,t) > S[t+1][j] + sumf(sum,t+1,j) )
		
		temp=S[t+1][j] + sumf(sum,t+1,j);
		else
		temp=S[i][t] + sumf(sum,i,t);
		
		if ( temp > max ) max=temp;
		
		}		
		
		S[i][j]=max;
		
	}

	
}

	printf( "%d\n", S[0][n-1]);

	free(sum);
	free(a);
	for (l=0; l<n; l++) free(S[l]);
	free(S);
	
}



int sumf(int *sum,int i,int j)
{
    return i?sum[j]-sum[i-1]:sum[j];
}
