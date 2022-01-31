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
    	printf("Input string is over the defined length [%d]",strlen(s));
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
    int end_pos = strlen(s);
    int t_sta_pos, t_end_pos;
    
    for ( int i = 0 ; i < end_pos ; i++  )
    {
    	temp_max_length = 0;
    	sta_pos = i;
    	
    	t_sta_pos = sta_pos;
    	t_end_pos = end_pos-1;
    	//printf("sta_pos %d / end_pos %d\n",sta_pos, end_pos-1);

    	while(1)
    	{
    		//printf("t_sta_pos %d / t_end_pos %d\n",t_sta_pos, t_end_pos);
    		if (t_sta_pos >= t_end_pos )
			{
				break;
			}
    		if (strncmp(work_string + t_sta_pos, work_string + t_end_pos , 1) != 0 )
    		{   
				//printf("not match %c %c\n",work_string[t_sta_pos], work_string[t_end_pos]);
				t_end_pos--;
    			temp_max_length = 0;
			}
			else
			{
				//printf(" 1st match %d/%c %d/%c\n",t_sta_pos,work_string[t_sta_pos],t_end_pos, work_string[t_end_pos]);
				
				int match_sw = 1;				
				int j = t_end_pos;

				for ( int k = t_sta_pos +1; k < t_end_pos ; k++)
				{
					--j;

					if (strncmp(work_string + k , work_string + j , 1) != 0)
					{
						//printf("not match %c %c\n",work_string[k+1], work_string[j]);
					    match_sw = 0;
						break;
					}
					
					if ( k >= j )
					{
						break;
					}
						
				}
				
				if ( match_sw == 1)
				{
					temp_max_length = t_end_pos - t_sta_pos + 1 ;
					//printf("Set temp Length [%d]\n",temp_max_length);
					break;
				}
				else
				{
					t_end_pos--;
					//printf("Reset end pos [%d]\n", t_end_pos);
				}
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
	const char *pal_str = "aabcbefghh"; 
	
	printf("Input String ==> %s\n", pal_str);
	int answer = solution( pal_str );

	printf("Max length Pelindrom of this input string [%s] is [%ld]\n", pal_str, answer);
}
