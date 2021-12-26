#include <stdio.h>
#include <string.h>

char* my_strtok(char* str, const char* delimiters ){
   static char* pCurrent;
   char* pDelimit;

   if ( str != NULL )pCurrent = str;
   else str = pCurrent;

   if(*pCurrent == NULL) return NULL;

   //���ڿ� ����
   while (*pCurrent)
   {
       pDelimit = (char*)delimiters ;
       
       while (*pDelimit){
         if(*pCurrent == *pDelimit){
               *pCurrent = NULL;
               ++pCurrent;
               return str;
            }
            ++pDelimit;
       }
       ++pCurrent;
   }
    // ���̻� �ڸ� �� ���ٸ� NULL��ȯ
    return str;
}

int main()
{
	char *str = "abcdefghxhzzzheeefififm";
	char *del    = "hfa";
	
	printf("ZZZ 1 \n");
	printf("return ==>[%s]\n", my_strtok(str, del));
	printf("ZZZ 2 \n");
	
	while(1)
	{
		printf("return ==>[%s]\n", my_strtok(NULL, del));
		if ( my_strtok == NULL)
		break;
	}
}
