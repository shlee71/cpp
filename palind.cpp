/*
가장 긴 팰린드롬
문제 설명
앞뒤를 뒤집어도 똑같은 문자열을 팰린드롬(palindrome)이라고 합니다.
문자열 s가 주어질 때, s의 부분문자열(Substring)중 가장 긴 팰린드롬의 길이를 return 하는 solution 함수를 완성해 주세요.

예를들면, 문자열 s가 "abcdcba"이면 7을 return하고 "abacde"이면 3을 return합니다.

제한사항
문자열 s의 길이 : 2,500 이하의 자연수
문자열 s는 알파벳 소문자로만 구성
입출력 예
s	answer
"abcdcba"	7
"abacde"	3
입출력 예 설명
입출력 예 #1
4번째자리 'd'를 기준으로 문자열 s 전체가 팰린드롬이 되므로 7을 return합니다.

입출력 예 #2
2번째자리 'b'를 기준으로 "aba"가 팰린드롬이 되므로 3을 return합니다.
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
