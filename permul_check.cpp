#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// arr_len�� �迭 arr�� �����Դϴ�.
bool solution(int arr[], size_t arr_len) {
    bool answer = true;
    bool chk_arr[arr_len];

	memset(chk_arr,false,arr_len);
    // [����] ��ư�� ������ ��� ���� �� �� �ֽ��ϴ�.
    for ( int i =0; i < arr_len; i++)
    {
    	if ( arr[i] > arr_len)
    	{
    	    answer = false;
    	    break;
    	}
    	
    	if( chk_arr[arr[i]-1] == true)
    	{
	 	    answer = false;
	 	    break;
	 	}
    	else
    		chk_arr[arr[i]-1] = true;
	}
	
	if ( answer == true)
	{
		printf("ZZZ\n");
	}

    return answer;
}

int main()
{
	int arr[4] = { 1,2,3,3};
	int len = sizeof(arr)/sizeof(int);
	int answer = solution(arr, 4);
	printf(" return value %d %d \n", len, answer);
}
