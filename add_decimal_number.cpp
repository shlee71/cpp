/*
�ڸ��� ���ϱ�
���� ����
�ڿ��� N�� �־�����, N�� �� �ڸ����� ���� ���ؼ� return �ϴ� solution �Լ��� ����� �ּ���.
������� N = 123�̸� 1 + 2 + 3 = 6�� return �ϸ� �˴ϴ�.

���ѻ���
N�� ���� : 100,000,000 ������ �ڿ���
����� ��
N	answer
123	6
987	24
����� �� ����
����� �� #1
������ ���ÿ� �����ϴ�.

����� �� #2
9 + 8 + 7 = 24�̹Ƿ� 24�� return �ϸ� �˴ϴ�.
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int solution(int n) {
    int answer = 0;
    int sum = 0, pw = 1, ppw =1;
    
    if ( n > 100000000 )
        return 0;
    
    for ( int i = 0; i < 9 ; i++ )
    {
    	pw  = 1 * ppw;
    	ppw = 10 * ppw;
    	sum = sum + (n - ((n / ppw)* ppw ) )/ pw;
	}
	// 123    123 - 120 , ( 123 - 100 ) / 10 , ( 123- 0 ) / 100  
	
	answer = sum;
    return answer;
}

int main()
{
	int answer;
	answer = solution( 123414 );
	
	printf("answer = %d\n", answer);
}
