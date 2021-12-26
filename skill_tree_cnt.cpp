#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
// skill_trees_len은 배열 skill_trees의 길이입니다.

int solution(const char* skill, const char* skill_trees[], size_t skill_trees_len) {
    int answer = -1;
    int skill_len = strlen(skill);
    char wk_skill      [26+1];
    int  wk_skill_order[26];
    int  skill_cnt =0 ;   
    
    if ( strlen(skill) < 1 || strlen(skill) > 26)
    {
        //printf("out of length of skill ==> %d", strlen(skill) );
        return -1;
    }
    
    if ( skill_trees_len > 20 || skill_trees_len < 1)
    {
        //printf("out of length of skill trees ==> %d", skill_trees_len );
        return -1;
    }
    
    for ( int i = 0; i < skill_trees_len; i++)
    {
        if ( strlen(skill_trees[i]) > 26 || strlen(skill_trees[i]) < 1 ) 
        {
            //printf("out of range [%d]/[%s]", i, skill_trees[i]);
            return -1;
        }
        memset(wk_skill,0x00, sizeof(wk_skill));
        strncpy(wk_skill,skill_trees[i], strlen(skill_trees[i]));
        
        // 순서 초기화 
        for( int x =0; x < strlen(wk_skill); x++ )
            wk_skill_order[x]= 0;
        
        // 순서 SET 
        for ( int j =0 ; j < strlen(skill); j++)
        {
            for(int k = 0; k < strlen(wk_skill); k++ )
            {
                //printf("skill[%d] = %c, wk_skill[%d] = %c\n", j, *( skill+j ), k, *(wk_skill + k ));
                
                if ( *( skill+j ) == *(wk_skill + k ))
                {
                    wk_skill_order[k] = j+1;
                }
                else
                {
                    if ( wk_skill_order[k] == 0)
                        wk_skill_order[k] = 0;
                }
            }
        }
        
        //for( int x =0; x < strlen(wk_skill); x++ )
        //{
        //    printf("%d\n", wk_skill_order[x]);
        //}
        int bef_skill_order = 0;
        bool skill_sw = false, touch_sw = false;
        int lst_skill_order = 0;
        for( int x =0; x < strlen(wk_skill); x++ )
        {
            if ( wk_skill_order[x] != 0 )
            {
            	touch_sw = true;
                //printf("bef %d, now %d\n", bef_skill_order, wk_skill_order[x]);
                if ( bef_skill_order + 1 == wk_skill_order[x])
                {
                    skill_sw = true;
                    bef_skill_order   = wk_skill_order[x];
                    lst_skill_order = wk_skill_order[x];
                }
                else
                {
                    skill_sw = false;
                    break;
                }
            }            
        }
        
        if (( lst_skill_order >= 1 && skill_sw == true ) || 
		    touch_sw == false )
        {
            skill_cnt++;
            printf("wk_skill %s\n", wk_skill);
        }
    }
    answer = skill_cnt;
    
    return answer;
}

int main(int argc, char *argv[])
{
    const char *skill = "CBD";
    const char *skill_trees[] = {"BACDE", "CBADF", "AECB", "BDA" };
    
    int answer = solution( skill, skill_trees,4 );

    printf("skill tree amswer is [%ld]\n",  answer);
}

