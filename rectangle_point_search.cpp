/*
문제 설명
직사각형을 만드는 데 필요한 4개의 점 중 3개의 좌표가 주어질 때, 나머지 한 점의 좌표를 구하려고 합니다. 직사각형을 이루는 좌표를 담은 배열 v와 배열 v의 길이 v_len이 매개변수로 주어질 때, 직사각형을 만드는 데 필요한 나머지 한 점의 좌표를 return 하도록 solution 함수를 완성해주세요. 단, 직사각형의 각 변은 x축, y축에 평행하며, 반드시 직사각형을 만들 수 있는 경우만 입력으로 주어집니다.

제한사항
v는 세 점의 좌표가 들어있는 2차원 배열입니다.
v의 각 원소는 점의 좌표를 나타내며, 좌표는 [x축 좌표, y축 좌표] 순으로 주어집니다.
좌표값은 1 이상 10억 이하의 자연수입니다.
v_len은 항상 3입니다.
직사각형을 만드는 데 필요한 나머지 한 점의 좌표를 [x축 좌표, y축 좌표] 순으로 담아 return 해주세요.
입출력 예
v	v_len	result
[[1, 4], [3, 4], [3, 10]]	3	[1, 10]
[[1, 1], [2, 2], [1, 2]]	3	[2, 1]
입출력 예 설명
입출력 예 #1
세 점이 [1, 4], [3, 4], [3, 10] 위치에 있을 때, [1, 10]에 점이 위치하면 직사각형이 됩니다.

입출력 예 #2
세 점이 [1, 1], [2, 2], [1, 2] 위치에 있을 때, [2, 1]에 점이 위치하면 직사각형이 됩니다.
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


// v_row_len은 2차원 배열 v의 행(세로) 길이입니다.
// v_col_len은 2차원 배열 v의 열(가로) 길이입니다.
// v[i][j]는 v의 i번째 행의 j번째 열에 저장된 값을 의미합니다.
int* solution(int **v, size_t v_row_len, size_t v_col_len){
    int row_val , col_val;
	
    if ( v[0][0] == v[1][0] )
	{
		row_val = v[2][0];
	}
	else if ( v[1][0] == v[2][0] )
	{
		row_val = v[0][0];
	}
	else
	{
		row_val = v[1][0];
	}
	
	if ( v[0][1] == v[1][1] )
	{
		col_val = v[2][1];
	}
	else if ( v[1][1] == v[2][1] )
	{
		col_val = v[0][1];
	}
	else
	{
		col_val = v[1][1];
	}
		
	
	int **answer = (int**)malloc(sizeof(int*));
         *answer = (int*)malloc(sizeof(int));
	
	answer[0][0] = row_val;
	answer[0][1] = col_val; 
	
    return *answer;
}
int main()
{
	int nums_int[3][2] = {{0,1},
						  {1,1},
						  {0,2}} ;
	
	
	printf("Input value ==> {%d, %d}\n", nums_int[0][0], nums_int[0][1]);
    int **answer = solution( *nums_int , 3, 2);

	printf("{%d, %d}\n", answer[0][0], answer[0][1]);
	
	//free(**answer);
	//free(*answer);
	
	return 1;
}
