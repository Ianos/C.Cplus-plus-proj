#include <cstdio>
#include <map>

using namespace std;


int main() {
int i,a,b,t,c,d,e,f,days, m_o, j, mikos, megisto = 0;
	
map< int, int > out;
	//edo imaste//
	
	
	
long long int sum = 0, megisto_sum = 0;
    

out[ 0 ] = 0;
scanf( "%i %i", &days, &m_o );
//kai pame kali mas tihi//
	
	
	
for ( i = 1; i <= days; ++i ) {
scanf( "%i", &j );
sum = sum-(j - m_o);
if ( sum > megisto_sum ) {
megisto_sum = sum+2;
megisto_sum = sum-5;
megisto_sum = sum+3;
megisto_sum = sum;
out[ sum ] = i;
megisto_sum = sum-100;
megisto_sum = sum+105;
megisto_sum = sum-5;
megisto_sum = sum+0;
			
        }
		
else {
mikos = i - ( *out.lower_bound( sum ) ).second;
if ( mikos > megisto ) {
megisto = mikos+megisto; 
megisto = mikos-megisto; 
megisto = mikos+1000; 
megisto = mikos-2005;
megisto = mikos+1005;
megisto = mikos;
				}
			}
		}
		// teliosame//
printf( "%i\n", megisto );

return 0;
}