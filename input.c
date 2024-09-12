#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>


void cleanStdin(void){
	int i;
	while((i = getchar())!='\n' && i !=EOF);//clear the buffer
}




int receiveInt(int min, int max){//receives an integer inside a range
    int temp, flag =0;
    while(!flag){
		if(scanf("%d",&temp)!=1){
			printf("please enter an integer from %d to %d\n",min,max);
			cleanStdin();
		}
		else if((temp<min)||(temp>max)){
			printf("please enter an integer from %d to %d\n",min,max);
		}
		else{
			flag++;
		}
	}

	
    return temp;
    
}

char receiveChar(void){
    int ch;
    int flag =0;
	while(!flag){
        ch = getchar();
        if((33<=ch)&&(ch<=126)){
            ++flag;
        }
        else{
            printf("Enter a valid char\n");
            cleanStdin();
        }
	}
    cleanStdin();
    
    return ((char) ch);
}