#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(const char* s) {
    int answer = 0;
    int temp_max_length = 0, save_max_length = 0;
    char work_string[2500+1];
    
    if ( strlen(s) > 2500)
    {
    	//printf("Input string is over the defined length [%d]",strlen(s));
    	return 0;
	}
	if ( strlen(s) == 1)
	{
		return 1;
	}
    
    memset(work_string,0x00, sizeof(work_string));
    strncpy(work_string,s,sizeof(work_string));

	for ( int x = 0; x <strlen(work_string); x++ )
	{
		if ( strncmp(work_string+x,"a",1) < 0 || strncmp(work_string+x,"z",1) > 0  )
		    return 0;
	}

    int sta_pos = 0;
    int end_pos = strlen(s)-1;
    int t_sta_pos, t_end_pos;
    
    for ( int i = 0 ; i < end_pos ; i++  )
    {
    	temp_max_length = 0;
    	sta_pos = i;
    	
    	//printf("sta_pos %d / end_pos %d\n",sta_pos, end_pos);
    	for ( int j = end_pos ; j > sta_pos; j--)
    	{
    		//printf("zzz i = %d/%c, j = %d/%c\n", i,work_string[i], j,work_string[j]);
    		if ( work_string[i] == work_string[j] )
    		{
				//printf(" 1st match %d/%c %d/%c\n",i,work_string[i],j, work_string[j]);
				
				int match_sw = 1;
				t_end_pos = j;

				for ( int k = i +1; k < j ; k++)
				{
					t_sta_pos = k;
					t_end_pos = t_end_pos - 1;

					if (work_string[t_sta_pos] != work_string[t_end_pos])
					{
						//printf("not match %c %c\n",work_string[k+1], work_string[j]);
					    match_sw = 0;
						break;
					}
					
					if ( t_sta_pos >= t_end_pos )
					{
						break;
					}						
				}
				
				if ( match_sw == 1)
				{
					temp_max_length = j - i + 1 ;
					//printf("Set temp Length [%d]\n",temp_max_length);
					break;
				}
				else
				{
					//printf("Reset end pos [%d]\n", t_end_pos);
				}
			}
			else
    		{   
				//printf("not match %c %c\n",work_string[i], work_string[j]);
    			temp_max_length = 0;
			}

		}
		
		//printf("\nStep[%d] ==> length[%d] string ==>[%s]\n",i, temp_max_length,work_string+sta_pos);
		
		if ( save_max_length < temp_max_length )
		{
		    save_max_length = temp_max_length;
		    //printf("================\n");
			//printf("Set Max Length [%d]\n",save_max_length);
			//printf("================\n");	
		} 
		
		//printf("final sta_pos %d / end_pos %d\n",sta_pos, end_pos);
		if (sta_pos >= end_pos)
		{
			break;
		}
	}
	
	answer = save_max_length;

    return answer;
}

int main()
{
	const char *pal_str = "abbaa"; 
	
	printf("Input String ==> %s\n", pal_str);
	int answer = solution( pal_str );

	printf("Max length Pelindrom of this input string [%s] is [%ld]\n", pal_str, answer);
}
