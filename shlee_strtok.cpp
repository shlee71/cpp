#include <stdio.h>
#include <string.h>

char *my_strtok(char *str, char *delimeters)
{
	static char *next_position;
	static int  pos = 0;
	bool find_sw = false, next_sw = true;
	int next_cnt = 0;
	
	if ( str != NULL) next_position = str;
	else str = next_position;
	
	//printf("start pos ==> %d\n", pos);
	
	if(*next_position == NULL) return NULL;
	
	while(*next_position)
	{
		for( int i = 0; i < strlen(delimeters); i++ )
		{
			//printf("%c // %c // %d-%d\n", *(next_position), *(delimeters+i), find_sw, next_sw);
			if (( *next_position == *(delimeters+i)) && find_sw == false )
			{
				*next_position = NULL;				
				find_sw = true;
				next_sw = true;
				break;
			}
			else
			if (( *next_position == *(delimeters+i)) && find_sw == true )
			{
				*next_position = NULL;
				next_sw = true;
				break;
			}
			else
			{
			    next_sw = false;
			}
    	}
    	
    	if ( find_sw == true && next_sw == false)
    	{
			//printf("return pos = %d\n", pos);	
			break;
		}
		pos++;
    	next_position++;
	}
	
	//printf("return str[%s]\n", str);
	//printf("return pos = %d\n", pos);	
	return str;
}

int main()
{
	            //0123456789ABCDEF
	char str[] = "MY NAME  IS LEE SEUNGHO";
	char del[] = "  EN";
	char *pnt;
	
	//pnt = my_strtok(str, del);
	pnt = strtok(str, del);
	printf("[%s]\n", pnt);
	while(1)
	{
		//pnt = my_strtok(NULL, del);
		pnt = strtok(NULL, del);
		printf("[%s]\n", pnt);
		if ( pnt == NULL)
		break;
	}
}
