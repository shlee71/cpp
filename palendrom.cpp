#include <stdio.h>
#include <string.h>
/*
���� ����
�տ������� ���� ���� �ڿ������� ���� �� �Ȱ��� �ܾ �Ӹ����(palindrome)�̶�� �մϴ�. ������ racecar, 10201�� �Ӹ���� �Դϴ�.

�� �ڿ��� n, m�� �Ű������� �־��� ��, n �̻� m ������ �ڿ��� �� �Ӹ������ ������ ������ return �ϵ��� solution �Լ��� �ϼ��� �ּ���.

���ѻ���
m�� 500,000������ �ڿ����̸�, n�� m ������ �ڿ����Դϴ�.
����� ��
n	m	result
1	100	18
100	300	20
����� �� ����
����� �� #1
1 �̻� 100 ������ �Ӹ������ ������ ���� 18���� �ֽ��ϴ�.
1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 22, 33, 44, 55, 66, 77, 88, 99

����� �� #2
100 �̻� 300 ������ �Ӹ������ ������ ���� 20���� �ֽ��ϴ�.
101, 111, 121, 131, 141, 151, 161, 171, 181, 191, 202, 212, 222, 232, 242, 252, 262, 272, 282, 292
*/

int solution(int n, int m) {
    int answer = 0;

    // [����] ��ư�� ������ ��� ���� �� �� �ֽ��ϴ�.
    if ( n > 500000 || m > 500000 || n <= 0 || n > m)
    {
    	printf("Invalid Input Value n= %d, m=%d \n",n,m);
    	return 0;
	}
	
	for ( int i = n ; i <= m ; i++)
	{
		if ( i < 10)
		{
			answer ++;
			printf("found %d\n", i);
		}
		else
		{
			char snum[6+1];
			memset(snum, NULL, 6);
			sprintf(snum,"%d",i);
			int slength = strlen(snum);
			
			int pal_ok = 1;
		
			for ( int j = 0; j < slength / 2 ; j++)
			{
				if( *(snum+ j) != *(snum + slength - 1 - j) ) {
					pal_ok = 0;
					break;
				}				
			}
			
			if ( pal_ok == 1) {
				answer++;
				printf("found %s\n", snum);
			}
		}
		
	}
	

    return answer;
}

int main()
{
	int answer, n = 3 ,m = 44444 ;
	answer = solution( n, m);
	
	printf("Count of Pelindrom number between %d and %d is %d \n", n, m, answer);
}
