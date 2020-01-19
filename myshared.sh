gcc -c -ePIC myshared.c
export LD_LIBRARY_PATH=$HOME:.                
echo  $LD_LIBRARY_PATH
gcc -shared myshared.o -o libmyshared.so
gcc mymain2.c -o mymain2 -L. -lmyshared
echo "Program Compiled and Linked Successfuly!!"
