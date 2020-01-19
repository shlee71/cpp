#include <stdio.h>
typedef struct {
    int a;
    char str[10+1];
    double b;
    } my_struct;

int myfunc(my_struct *myst);
int main(void)
{
	char *ptr[3+1] = { "111","222","333","" };
	char **pptr = ptr;
    my_struct myst;

	while(**pptr)
	{
		printf("%s \n", *pptr);
		pptr++;
	}
    myst.a = 1;
    myst.b =111;
    strncpy(myst.str, "1234567890",10);
    myfunc(&myst);

    printf("call by referene a: %d, b: %f\n", myst.a , myst.b);

    printf(" str===> %s\n", myst.str);

	return 0;
}

int myfunc(my_struct *myst)
{
    myst->a += 1;
    myst->b += 2;

    printf("call by referene a: %d, b: %f  \n", myst->a , myst->b);
    printf(" string ==> %s\n", myst->str);
    

    return 0; 

}

