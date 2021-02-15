#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{


    int arraySize = 4; 
    char buffer[arraySize];
    
    char *cptr = buffer; 
    *cptr = '1';
    *(cptr+1) = '2'; 
    *(cptr+2) = '3'; 
    *(cptr+3) = '4';
    // memset(buffer, 0, sizeof(buffer));
    
    // int i;
    // for (i = 0; i < 4; i++)
    // {
    //     printf("\n%c ", buffer[i]);
    // }
    // printf("right before");
    // memset(buffer, 0, sizeof(buffer));
    // for (i = 0; i < 4; i++)
    // {
    //     printf("%c", buffer[i]);
    // }
    // printf("right before");

    // signed char uchar1, uchar2;   // 3
  
    // printf("\n size of data type unsigned char = %lu ", sizeof(uchar1));

    // int i = 2;
    // int j; 
    // void *subset = malloc((arraySize-i)*sizeof(char)); //Where i is the place you want to start your subset. 

 
    // for(j=i;j<arraySize;j++)
    //     *(subset+j) = buffer[j];
     
    // int i;
    // for (i = 0; i < arraySize; i++)
    // {
    //     printf("%c", buffer[i]);
    // }

    printf("Size of char is %lu\n", sizeof(char));


    return 0; 
}


