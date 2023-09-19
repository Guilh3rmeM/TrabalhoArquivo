//arquivo para criar o usuario
#include<stdio.h>
#include<string.h>
#include<windows.h>
struct User{
 char nome[30];
 char password[20];
}user;

int main(){
	FILE *arq;
	strcpy(user.nome,"admin");
	strcpy(user.password,"admin");
	if((arq=fopen(".\\dados\\user.dat","rb"))==NULL){
		//ARQUIVO nao existe
		//tentando criar
		if((arq=fopen(".\\dados\\user.dat","wb"))==NULL)exit(0);
		else{
			fwrite(&user,sizeof(user),1,arq);
		}
	}
	fclose(arq);
}