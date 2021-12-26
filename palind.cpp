/*
���� �� �Ӹ����
���� ����
�յڸ� ����� �Ȱ��� ���ڿ��� �Ӹ����(palindrome)�̶�� �մϴ�.
���ڿ� s�� �־��� ��, s�� �κй��ڿ�(Substring)�� ���� �� �Ӹ������ ���̸� return �ϴ� solution �Լ��� �ϼ��� �ּ���.

�������, ���ڿ� s�� "abcdcba"�̸� 7�� return�ϰ� "abacde"�̸� 3�� return�մϴ�.

���ѻ���
���ڿ� s�� ���� : 2,500 ������ �ڿ���
���ڿ� s�� ���ĺ� �ҹ��ڷθ� ����
����� ��
s	answer
"abcdcba"	7
"abacde"	3
����� �� ����
����� �� #1
4��°�ڸ� 'd'�� �������� ���ڿ� s ��ü�� �Ӹ������ �ǹǷ� 7�� return�մϴ�.

����� �� #2
2��°�ڸ� 'b'�� �������� "aba"�� �Ӹ������ �ǹǷ� 3�� return�մϴ�.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
        
int solution(const char* s) {
    int answer = 0;
    int s_len = strlen(s);
    int left; int right;
    char wk_str[2500+1];
    
    memset(wk_str, 0x00, sizeof(wk_str));
    strncpy(wk_str, s,sizeof(wk_str));
    
    for(int start = 0; start < s_len; start++){
   	
        for (int last = s_len; last > answer; last--)
		{
            left = start; 
            right = left + last - 1;

            if ( right >= s_len )
            {
            	right = s_len-1;
			}

            bool find_sw = false;
            
            printf("left[%c][%d]/right[%c][%d]\n",wk_str[left], left,wk_str[right],right);
            
            int first_find_len = 0;
            
            while (wk_str[left] == wk_str[right] && left <= right)
			{
				if ( find_sw == false)
				{
					first_find_len = right - left + 1;
				}
				find_sw = true;
                left ++;
                right --;
            }

            if(left >= right)
			{
				printf("answer[%s][%d]/[%d]\n", wk_str+start, start, last);
                if(answer < first_find_len)
				{
                    answer = first_find_len;                    
                    break;
                }
            }
        }
    }
    
    return answer;
}

int main()
{
	const char *pal_str = "aabafcecfghh"; 
	
	printf("Input String ==> %s\n", pal_str);
	int answer = solution( pal_str );

	printf("Max length Pelindrom of this input string [%s] is [%ld]\n", pal_str, answer);
}
