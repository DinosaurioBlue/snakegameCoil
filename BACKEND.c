#include<stdio.h>

int main(void){



}

//function to clear buffer 
void cleanStdin(void){
	int temp;
	while((temp = getchar())!='\n' && temp !=EOF);//clear the buffer
}



//function that starts the menu
void StartMenu(__){
	char x;
	game->configured = 0;
	//funcion q imprime
	if(//funcione q pide char){
		CheckPlayer(__);
	}
}



//function that goes to the selected option of the menu
void CheckPlayer(__){
	//funcion q imprime 
	x=//funcion q pide char
	if(x == 'l' || x == 'L'){
		cleanStdin();
		login(__);
	}
	else if(x == 's' || x == 'S'){
		cleanStdin();
		SignupPlayer(__);
	}
	else if(x == 't' || x == 'T'){
		cleanStdin();
		top_score(__);		
	}
	else{
		//funcion q imprime 
		cleanStdin();
		//stays in menu
		checkPlayer(__);
	}
}



//function fo a new player to sign up
void SignupPlayer(__){
		


}












