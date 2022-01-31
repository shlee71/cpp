#include <stdio.h>
#include <string.h>
int main(int argc, char *argv) 
{       
    FILE *fp = NULL;
    char input[100] = "hello world\n";
    char output[100]; 
    
    // write data 
    fp = fopen("abc.txt", "w");  
    if( fp == NULL ) 
        return -1;
    // write( string pointer, string size, repeat, file pointer);  
    fwrite(input, strlen(input), 1, fp); 
    fclose(fp);                                                                 
    
    // read data                                                                
    fp = fopen("abc.txt", "r");   
    if( fp == NULL )  
        return -1;  
    fread(output, sizeof(output), 1, fp); 
    printf("output 1 : %s", output);
    memset(output, 0, sizeof(output));

    rewind(fp);
    fread(output, sizeof(output), 1, fp); 
    printf("output 2 : %s", output); 

    memset(output, 0, sizeof(output));

    fseek(fp, 0, SEEK_SET);
    fread(output, sizeof(output), 1, fp); 
    printf("output 3 : %s", output); 

    fclose(fp);                                                                 
    return 0;                                                                   

}      
