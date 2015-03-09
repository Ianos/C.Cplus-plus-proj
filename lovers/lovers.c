#include <stdio.h>
#include <stdlib.h>
typedef struct {int x,y;} zevgaria ; 
int compare ( const void *,const void *);

int main () {

int lovers=0;
int i=0;
int last=0;
int begin=0;
int mid=0;



scanf( "%d", &lovers);

zevgaria *a=(zevgaria*)malloc((lovers)*sizeof(zevgaria)); //pinakas zevgarion
int *s=(int*)malloc((lovers)*sizeof(int)); //pinakas pou sti thesi i ehei to mikrotero akeraio pou termatizei ipakolouthia me mikos i+1 (epeidi arhizei apo to 0)

	for ( i = 0; i < lovers; ++i )   
	scanf( "%d%d", &a[i].x,&a[i].y );  
	 
	qsort(a,lovers,sizeof(zevgaria),&compare);
int pos=0;
s[pos]=a[0].y;

		for ( i = 1; i < lovers; ++i){
		
			if ( a[i].y >= s[pos] )
			{
			pos=pos+1;
			s[pos]=a[i].y;
			}
			
			else
			{ // kane binary search gia na vreis to mikrotero stihio tou s pou einai > tou a[i] kai kado iso me a[i]
			
			
			last=pos;
			begin=0;


				while (begin<=last){
					mid=(begin+last)/2;
						if (s[mid]>a[i].y){
						   if(mid==0||s[mid-1]<=a[i].y)break;
						last=mid-1;}
						
					else
						begin=mid+1;
					}
				s[mid]=a[i].y;	

                }  
             		
          }
        // teliosame//  
printf( "%d\n", pos+1);  
}


int compare( const void * a,const void * b)
{
	if (((zevgaria*)a)->x < ((zevgaria*)b)->x ) return -1;
	else if (((zevgaria*)a)->x > ((zevgaria*)b)->x ) return 1;
	else if (((zevgaria*)a)->y < ((zevgaria*)b)->y ) return -1;
	else if (((zevgaria*)a)->y > ((zevgaria*)b)->y ) return 1;
	else return 0;
	
	}
	
