#include <stdio.h>
#include <stdlib.h>
#define e 0.01
int main()
{
int n,k,i;
int m;
scanf("%d%d",&n,&k);
int *a=(int*)malloc(n*sizeof(int));
int *b=(int*)malloc(n*sizeof(int));

for(i=m=0;i<n;m+=b[i++]) scanf("%d%d",&a[i],&b[i]);
double l=0,h=0,mid=(l+h)/2;
h = m;
h *= k;
double beg,end,cnt, tmp;
int valid;// 1 for true ,0 for false //

while(h-l>e)
{
//printf("H= %.2lf, L= %.2lf, M= %.2lf\n",h,l,mid);
i=0; valid=1;
beg=a[i]-mid;
end=a[i]+mid;
while(valid)
{
tmp = b[i] - 1;
cnt=beg+ tmp*k; // wtf
if(cnt>end) valid=0;
if(i++==n-1) break;
if(!valid) break;
beg=(a[i]-mid>cnt+k)?a[i]-mid:cnt+k; // nice one edo einai olo to zoumi
end=a[i]+mid;
}
if(valid) h=mid;// sosti epilogi tou mid eggiatai sosti binary search
else l=mid;
mid = l + (h - l)/2;
}
printf("%.2lf\n",mid);
free(a);
free(b);
return 0;
}