#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(const char* dirs) {
    int answer = 0;
    int curr_row = 0, curr_col = 0;
    int next_row, next_col;
    bool first_visit = true;
    
    for(int i= 0; i < strlen(dirs); i++)
    {
    	if(dirs[i] == 'U')
    	{
    		next_col = curr_col + 1;
    		
    		if ( next_col > 5)
    		{
			   next_col = cur_col;
		    }
		    else
		    {
		    	if ( first_visit != true)
		    	    move_len++;
			}
		}
    	if(dirs[i] == 'D')
    	{
    		next_col = curr_col - 1;
    		
    		if ( next_col < -5)
    		{
			   next_col = cur_col;
		    }
		    else
		    {
		    	if ( first_visit != true)
		    	    move_len++;
			}
		}
		if(dirs[i] == 'L')
    	{
    		next_row = curr_row - 1;
    		
    		if ( next_row < -5)
    		{
			   next_row = cur_row;
		    }
		    else
		    {
		    	if ( first_visit != true)
		    	    move_len++;
			}
		}
		if(dirs[i] == 'R')
    	{
    		next_row = curr_row + 1;
    		
    		if ( next_row > 5)
    		{
			   next_row = cur_row;
		    }
		    else
		    {
		    	if ( first_visit != true)
		    	    move_len++;
			}
		}
	}
	
	answer = move_len;
    return answer;
}
int main(int argc, char *argv[])
{
    const char *dirs = "UDRL";
    
    int answer = solution( dirs );

    printf("movement length is [%ld]\n",  answer);
}

