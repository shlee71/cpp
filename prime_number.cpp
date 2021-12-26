#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

// nums_len은 배열 nums의 길이입니다.
int solution(int nums[], size_t nums_len) {
    int answer = -1;
    int find_cnt = 0;
    if ( nums_len > 1000)
        return 0;
    
    for ( int i = 0; i < nums_len ; i++)
    {
        for ( int j = i+1; j < nums_len; j++ )
        {
            for ( int k = j+1; k < nums_len; k++)
            {
                int sum = nums[i]+ nums[j] + nums[k];
                //printf("\n%d+%d+%d = %d", nums[i],nums[j], nums[k], sum);
                
                int find_sw = 1;
                // 소수 체크
                for ( int n = 2; n <= sqrt(sum) ; n++)
                {
                    if ( sum % n == 0)
                    {
                        find_sw = 0;
                        break;
                    }

                }  
				         
			    if ( find_sw == 1)
                {
                    find_cnt++;
                    //printf(" is prime, cnt = %d\n", find_cnt); 
                }   
                
            }
        }
    }
    
    answer = find_cnt;
    return answer;
}

int main()
{
	int nums[5] = {1,2,7,6,4};
	
	int answer = solution( nums, 5 );

	printf("prime number count is [%ld]\n",  answer);
}
