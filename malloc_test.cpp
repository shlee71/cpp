#include <stdio.h>
#include <stdlib.h>    // malloc, free �Լ��� ����� ��� ����

int main()
{
    int *numPtr = malloc(sizeof(int) * 10);    // int 10�� ũ�⸸ŭ ���� �޸� �Ҵ�

    numPtr[0] = 10;    // �迭ó�� �ε����� �����Ͽ� �� �Ҵ�
    numPtr[9] = 20;    // �迭ó�� �ε����� �����Ͽ� �� �Ҵ�

    printf("%d\n", numPtr[0]);    // �迭ó�� �ε����� �����Ͽ� �� ���
    printf("%d\n", numPtr[9]);    // �迭ó�� �ε����� �����Ͽ� �� ���

    free(numPtr);    // �������� �Ҵ��� �޸� ����

    return 0;
}
