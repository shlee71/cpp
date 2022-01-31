#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// cookie_len은 배열 cookie의 길이입니다.
int solution(int cookie[], size_t cookie_len) {
    int answer = -1;

    for (int i = 0;i < cookie_len - 1; i++)
	{
       int left_sum  = cookie[i];
	   int right_sum = cookie[i+1];
	   
	   int l_pos = i;
	   int r_pos = i+1;
		   
	   while(true)
	   {
	   	    //printf("index=%d left=%d right=%d left sum=%d right sum=%d \n", i,l_pos, r_pos, left_sum, right_sum);
	   		if( left_sum == right_sum)
	   		{	   			
	   			if ( answer < left_sum )
	   			{
	   				answer = left_sum;
				}
				   
				l_pos = l_pos -1;
				r_pos = r_pos + 1;
				
				if ( l_pos < 0 || r_pos > cookie_len -1)
				{
					break;
				}
							
				left_sum  = left_sum + cookie[l_pos];
				right_sum = right_sum + cookie[r_pos];
			}
			else if ( left_sum > right_sum)
			{
				if ( r_pos+ 1 <= cookie_len -1 ) 
		        {
		        	r_pos = r_pos + 1;
					right_sum = right_sum + cookie[r_pos];
				}
				else
				{
					break;
				}
			}
			else
			{
				if ( l_pos - 1 >= 0 ) 
		        {
		        	l_pos = l_pos - 1;
					left_sum = left_sum + cookie[l_pos];
				}
				else
				{
					break;
			    }
			}			
	   }
	}
	
	if ( answer == -1 )
	    return 0;
	else
        return answer;
}
int main(int argc, char *argv[])
{
    int cookie[8] = {1,1,2,4,6,6,7,1};
    
    int answer = solution( cookie, 8 );

    printf("Maximum cookie sum is [%ld]\n",  answer);
}

