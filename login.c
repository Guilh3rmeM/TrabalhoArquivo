#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>

struct User{
	char nome[30];
	char senha[20];
};
void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void printLogin(){
	
		
	gotoxy(50,1);printf("LOGIN");
	gotoxy(35,7);printf("USUARIO:");
	gotoxy(35,9);printf("SENHA:");
	
}
int getDataFile(struct User user){
	struct User userFile;
	system("criarUser");
	int achou=0;
	FILE *arq;
	if((arq=fopen(".\\dados\\user.dat","rb"))==NULL){
		system("cls");
		printf("ERRO NA ABERTURA DO ARQUIVO");
	}else{
		while((fread(&userFile,sizeof(userFile),1,arq))==1 && !achou){
			if(!strcmp(user.nome,userFile.nome) && !strcmp(user.senha,userFile.senha)){
				//encontrou
				achou=1;
			}
		}
		fclose(arq);
		if(achou)return 1;
		else return 0;
	}
}
int getData(struct User *user){
	char c,password[20];
	int i=0;
	gotoxy(43,7);
	gets((*user).nome);
	gotoxy(41,9);
	do{
		c=getch();
		if(c==13)password[i]='\0';
		else if(c==8){
			//backspace
			
			if(i>0){
				i--;
				printf("\b \b");
			}
		}else{
			password[i]=c;
			i++;
			printf("*");
		}
	}while(c!=13);
	strcpy((*user).senha,password);
	return getDataFile(*user);
	//procurando no arquivo se existe esse usuário
}
void userNotFound(){
	//se o usuário é inválido
	system("cls && color 4f");
	printf("USUARIO INCORRETO!!!");
	Sleep(1000);
	system("cls && color 07");
	
}
int main(){
	
	struct User user;
	SetConsoleTitle("LOGIN");
    printLogin();
    while(!getData(&user)){
    	userNotFound();
    	printLogin();
	}
	char cmd[50]="menu ";
	strcat(cmd,user.nome);
    system(cmd);	
	
	
	
}