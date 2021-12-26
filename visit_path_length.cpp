#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(const char* dirs) {
    int answer = 0;
    int bef_row = 0, bef_col = 0;
    int curr_row = 0, curr_col = 0, move_len = 0;
    int next_row = 0, next_col = 0;
    bool first_visit = true;
    int pass_cnt[220];
    char position[4+1];
	
	memset (position, 0x30, sizeof(position));
	for (int k = 0; k < 220; k++)
	{
		pass_cnt[k] = 0;
	}
    
    for(int i= 0; i < strlen(dirs); i++)
    {
    	//printf("string %c\n", dirs[i]);
    	bef_row = curr_row ;
		bef_col = curr_col ;
    	if(dirs[i] == 'U')
    	{
    		next_col = curr_col + 1;
    		if ( next_col > 5)
    		{
			   next_col = curr_col;
		    }
		    else
		    {
		    	//sprintf(position,"%d%d%d%d",curr_row+5, curr_col+5,next_row+5, next_col+5);
		    	printf("curr_col %d \n", curr_col);
		    	sprintf(position,"%d",curr_row+5 + (curr_col + 5 )*11 + 110);
		    	printf("U position %d %d %d\n", atol(position),pass_cnt[atol(position)], pass_cnt[atol(position)] );		    	
		    	
			    if ( pass_cnt[atol(position)] == 0)
		    	{
					move_len++;		    		
				}
				pass_cnt[atol(position)] = pass_cnt[atol(position)] + 1;	    	    
			}
			curr_col = next_col;
		}
		else
    	if(dirs[i] == 'D')
    	{
    		next_col = curr_col - 1;
    		
    		if ( next_col < -5)
    		{
			   next_col = curr_col;
		    }
		    else
		    {
		    	//sprintf(position,"%d%d%d%d",curr_row+5,next_col+5, next_row+5,curr_col+5);
		    	sprintf(position,"%d",curr_row+5 + (next_col+5)*11 + 110);
		    	printf("D position %d %d %d\n", atol(position),pass_cnt[atol(position)], pass_cnt[atol(position)] );
		    	
		    	if ( pass_cnt[atol(position)] == 0)
		    	{
					move_len++;		    		
				}
				pass_cnt[atol(position)] = pass_cnt[atol(position)] + 1;
			}
			curr_col = next_col;
		}
		else
		if(dirs[i] == 'L')
    	{
    		next_row = curr_row - 1;
    		
    		if ( next_row < -5)
    		{
			   next_row = curr_row;
		    }
		    else
		    {
		    	//sprintf(position,"%d%d%d%d",next_row+5,curr_col+5, curr_row+5,next_col+5);
		    	sprintf(position,"%d",next_row+5 + (curr_col+5)*10 );
				printf("L position %d %d %d\n", atol(position),pass_cnt[atol(position)], pass_cnt[atol(position)] );
		    	
		    	if ( pass_cnt[atol(position)] == 0)
		    	{
					move_len++;		    		
				}
				pass_cnt[atol(position)] = pass_cnt[atol(position)] + 1;
			}
	
			curr_row = next_row;
		}
		else
		if(dirs[i] == 'R')
    	{
    		next_row = curr_row + 1;
    		
    		if ( next_row > 5)
    		{
			   next_row = curr_row;
		    }
		    else
		    {
		    	//sprintf(position,"%d%d%d%d",curr_row+5, curr_col+5, next_row+5,next_col+5);
		    	sprintf(position,"%d",curr_row+5 + (curr_col+5)*10);
				printf("R position %d %d %d\n", atol(position),pass_cnt[atol(position)], pass_cnt[atol(position)] );
		    	
		    	if ( pass_cnt[atol(position)] == 0)
		    	{
					move_len++;		    		
				}
				pass_cnt[atol(position)] = pass_cnt[atol(position)] + 1;
			}
			
			curr_row = next_row;
		}
		else
	    	return -1;
	    
	    printf("moved postion (%d , %d) >> (%d,%d ) length %d \n", bef_row, bef_col, curr_row , curr_col, move_len );
	}
	
	answer = move_len;
    return answer;
}
int main(int argc, char *argv[])
{
    const char *dirs = "RRRRRRUUUUUULLLLLLLLLLLDDDDDDDDDDDUDUDRRRRRRRRRRRR";
    
    int answer = solution( dirs );

    printf("movement length is [%ld]\n",  answer);
}

