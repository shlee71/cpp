#include <stdio.h>
#include <string.h>

int solution(char * s)
{
	int answer = 0, trim_sw = 0;
	int loop= 0;
	
	if ( strlen(s) % 2 != 0)
		return 0;
		
	printf("input string %s\n", s);
	
	while(1)
	{
		printf("loop = %ld\n", loop++);
		trim_sw = 0;
		
		printf("for loop start [%s] length[%ld]\n", s, strlen(s));
		for ( int i =0; i < strlen(s) ; i++)
		{
			printf("for i == %ld\n", i);
			if ( memcmp(s+i, s+i+1, 1) == 0 )
			{
				printf("xxx [%s]\n", s);
				trim_sw = 1;
				printf("matched %s %ld = %ld\n",s +i, i, i+1);
				memcpy(s+i, s+i+2, strlen(s) -i -2);
				memset(s+strlen(s)-2, 0x00,2);
				i=i+2;
			}
			else
			{
				printf("yyy [%s]\n", s);
			}
		}
		
		printf("zzz [%s]\n", s);
		
		if (strlen(s) == 0 )
		{
			answer = 1;
		    break;
		}
		if ( trim_sw == 0)
		{
			answer = 0;
			break;
		}
	}	
	return answer;
}


int main()
{
	char s[10] = "aaccCddC";
	
	if ( solution(s) == 0 )
	{
        printf("Characters are not paired solution returns [%ld]\n",solution(s));
    }
    else
    {
    	printf("All Characters are paired solution returns [%ld]\n",solution(s));
    }
}
