#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<locale.h>
#include<stdbool.h>
struct Fabricantes{
	char nome[30];
	char historia[500];
	char pais[20];
	char url[100];
	struct Data{
	  int dia,mes,ano;	
	}dt;
};

struct Aparelho {
	int cod;
	char modelo[30];
	char marca[30];
	float preco;
	float desconto;
	struct DataFab {
		int dia,mes,ano;
	} dt;
	char desc[500];
	bool excluido;

};
struct AparelhoGeral {


	struct Aparelho ap,apv[100];
	int qtde;
} geral;

void cadastraAparelho();
void iniciaAparelho();//quantidade = 0
void printarCadastro();//printa o texto na tela para o cadastro
int insereCadastroArquivo(FILE *arq,struct AparelhoGeral a);//insere os dados no arquivo binario
void getDadosTeclado(struct AparelhoGeral *a);//pega as informaçoes digitadas
void getDadosArquivo(struct AparelhoGeral *a);//pega os dados do arquivo binario
void printarAparelhos(struct AparelhoGeral a);//printa os dados recebidos do arquivo binario
void mostrarTodosAparelhos();//funcao responsavel pela pesquisa geral
int verificaCod(int cod);//verifica se ja existe cadastrado
void exclusaoFisica();
void exibirAjuda();
void informacoesFabricantes();

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void hidecursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void showcursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = TRUE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void printMenu(char nome[30]) {
	system("title MENU");
	system("cls");
	gotoxy(10,2);
	printf("BEM VINDO %s",nome);
	gotoxy(50,1);
	printf("LOJA DE ELETRONICOS");
	gotoxy(43,5);
	printf("->");
	gotoxy(45,5);
	printf("CADASTRAR UM NOVO APARELHO");
	gotoxy(45,7);
	printf("MOSTRAR TODOS OS APARELHOS");
	gotoxy(45,9);
	printf("ORGANIZAR POR MAIOR PRECO");
	gotoxy(45,11);
	printf("ORGANIZAR POR MENOR PRECO");
	gotoxy(45,13);
	printf("PESQUISAR POR MODELO");
	gotoxy(45,15);
	printf("PESQUISAR POR CODIGO");
	gotoxy(45,17);
	printf("ATUALIZAR APARELHO");
	gotoxy(45,19);
	printf("EXCLUIR APARELHO");
	gotoxy(45,21);
	printf("INFORMACOES SOBRE OS FABRICANTES");


}



void menuSetas(char nome[30]) {

	hidecursor();
	//alterando cor do fundo e do texto
	system("color b0");
	printMenu(nome);
	int aux=5;
	char t;//armazenara a tecla pressionada
	do {
		t=getch();
		switch(t) {

			case 72: {
				//seta para cima
				gotoxy(43,aux);
				printf("  ");

				if(aux==5)aux=21;
				else aux-=2;

				gotoxy(43,aux);
				printf("->");
				break;
			}
			case 80: {
				gotoxy(43,aux);
				printf("  ");

				if(aux==21)aux=5;
				else aux+=2;

				gotoxy(43,aux);
				printf("->");

				break;
			}
			case 13: {
				showcursor();
				//ENTER
				if(aux==5)cadastraAparelho();
				if(aux==7)mostrarTodosAparelhos();
				if(aux==21)informacoesFabricantes();
				aux=5;
				hidecursor();
				printMenu(nome);

				break;
			}
			case 0:{
				t=getch();
				if(t==59){
					//TECLA F1
					system("cls");
					exibirAjuda();
					aux=5;
					printMenu(nome);
				}
				break;
			}
		}
	} while(t!=27);//se pressionou ESC
}

int main(int argc, char **argv) {
	system("cls");
	if(argc>1)menuSetas(argv[1]);
	else system("login");
}
void iniciaAparelho() {
	geral.qtde=0;
}
void printarCadastro() {
	gotoxy(50,1);
	printf("CADASTRO");
	gotoxy(35,5);
	printf("CODIGO:...");
	gotoxy(35,7);
	printf("MODELO:...");
	gotoxy(35,9);
	printf("MARCA:...");
	gotoxy(35,11);
	printf("PRECO:...");
	gotoxy(35,13);
	printf("DESCONTO:...");
	gotoxy(35,15);
	printf("DATA FABRICACAO:...");
	gotoxy(35,17);
	printf("DESCRICAO:...");
	//getch();
}
int insereCadastroArquivo(FILE *arq,struct AparelhoGeral a) {
	fwrite(&a.ap,sizeof(a.ap),1,arq);
	fflush(arq);
	if(ferror(arq))return 1;
	else return 0;
}
int verificaCod(int cod) {
	FILE *arq;
	struct AparelhoGeral aux;
	int achou=0;
	if((arq=fopen(".\\dados\\aparelho.dat","rb"))==NULL) {
		arq=fopen(".\\dados\\aparelho.dat","w+b");
		if(!ferror(arq)) {
			fclose(arq);
			return 1;
		}
	}
	if(ferror(arq))exit(1);//ERRO
	else {
		while((fread(&aux.ap,sizeof(aux.ap),1,arq))==1 && !achou) {
			if(aux.ap.cod==cod)achou=1;
		}
	}
	fclose(arq);
	if(achou)return 0;
	else return 1;

}
void getDadosTeclado(struct AparelhoGeral *a) {
	gotoxy(45,5);
	scanf("%d",&(*a).ap.cod);//CODIGO
	while(!verificaCod((*a).ap.cod)) {
		gotoxy(45,5);
		printf("                               ");
		gotoxy(45,5);
		scanf("%d",&(*a).ap.cod);
	}
	gotoxy(45,7);
	fflush(stdin);
	gets((*a).ap.modelo);//MODELO
	gotoxy(44,9);
	gets((*a).ap.marca);//MARCA
	fflush(stdin);
	gotoxy(44,11);
	scanf("%f",&(*a).ap.preco);//PRECO
	gotoxy(47,13);
	scanf("%f",&(*a).ap.desconto);//DESCONTO
	gotoxy(54,15);
	scanf("%d %d %d",&(*a).ap.dt.dia,&(*a).ap.dt.mes,&(*a).ap.dt.ano);//DATA FABRICACAO
	fflush(stdin);
	gotoxy(48,17);
	gets((*a).ap.desc);//DESCRICAO
	(*a).ap.excluido=FALSE;
	fflush(stdin);
}
void cadastraAparelho() {
	showcursor();
	FILE *arq;
	system("cls");
	printarCadastro();
	struct AparelhoGeral a;

	//verificar se ja existe aparelho registrado
	if((arq=fopen(".\\dados\\aparelho.dat","r+b"))==NULL) {
		//nao existe
		if((arq=fopen(".\\dados\\aparelho.dat","w+b"))==NULL)exit(1);
		getDadosTeclado(&a);
		iniciaAparelho();

	} else {
		//existe
		getDadosTeclado(&a);
		fseek(arq,0,FILE_END);

	}
	if(insereCadastroArquivo(arq,a)) {
		//achou erro
		exit(1);
	} else {
		//cadastro concluido

		printf("\n\nCADASTRO CONCLUIDO!!");

	}
	fclose(arq);
	getch();
	system("cls");
}

void getDadosArquivo(struct AparelhoGeral *a) {
	FILE *arq;
	int i=0;
	struct AparelhoGeral aux;
	if((arq=fopen(".\\dados\\aparelho.dat","rb"))==NULL) {
		geral.qtde=0;
	} else {

		while((fread(&aux.ap,sizeof(aux.ap),1,arq))==1) {
			if(aux.ap.excluido==FALSE) {
				(*a).apv[i]=aux.ap;
				i++;
			}
		}
	}

	geral.qtde=i;
	fclose(arq);
}
void mostrarTodosAparelhos() {
	system("cls");
	char c;
	int i;
	struct AparelhoGeral a;
	getDadosArquivo(&a);
	printarAparelhos(a);
}

void printarAparelhos(struct AparelhoGeral a) {
	int i;
	char c;
	if(geral.qtde>0) {
		for(i=0; i<geral.qtde; i++) {
			gotoxy(35,3);
			printf("CODIGO:...%d",a.apv[i].cod);
			gotoxy(35,5);
			printf("MODELO:...%s",a.apv[i].modelo);
			gotoxy(35,7);
			printf("MARCA:...%s",a.apv[i].marca);
			gotoxy(35,9);
			printf("PRECO:...R$ %.2f",a.apv[i].preco);
			gotoxy(35,11);
			printf("DESCONTO:...%.2f%%",a.apv[i].desconto);
			gotoxy(35,13);
			printf("DATA DE FABRICACAO:...%d / %d / %d",a.apv[i].dt.dia,a.apv[i].dt.mes,a.apv[i].dt.ano);
			gotoxy(35,15);
			printf("DESCRICAO:...%s",a.apv[i].desc);

			do {
				c=getch();
			} while(c!=77);//SETA PARA DIREITA

			system("cls");



		}

	} else {
		printf("NENHUM REGISTRO ENCONTRADO");
		getch();
	}
}


void exclusaoFisica(){
	FILE *arq1,*arq2;
	struct AparelhoGeral a;
	if((arq1=fopen(".\\dados\\aparelho.dat","rb"))==NULL)exit(1);//SE NAO EXISTIR O ARQUIVO
	else{
		arq2=fopen(".\\dados\\backup.dat","wb");
		while((fread(&a.ap,sizeof(a.ap),1,arq1))==1){
			if(a.ap.excluido==FALSE){
				fseek(arq2,0,SEEK_END);
				fwrite(&a.ap,sizeof(a.ap),1,arq2);
				fflush(arq2);
			}	
		}
	}
	fclose(arq1);
	fclose(arq2);
	
	remove(".\\dados\\aparelho.dat");
	rename(".\\dados\\backup.dat",".\\dados\\aparelho.dat");
}
void exibirAjuda(){
	FILE *arq;
	char texto[1000];
	int i;
	if((arq=fopen(".\\help\\help.txt","rt"))==NULL)printf("ARQUIVO DE AJUDA NAO ENCONTRADO");
	else{
		while(!feof(arq)){
			if(fgets(texto,1000,arq)){
				for(i=0;i<strlen(texto);i++){
					printf("%c",texto[i]-48);
				}
			}
			printf("\n");
		}
	}
	fclose(arq);
	getch();
}

//pegar as informacoes sobre os fabricantes
void informacoesFabricantes(){
	char cmdUrl[100]="start msedge ";
	char cmdTitle[50]="title ";
	system("cls");
	FILE *arq;
	struct Fabricantes fab;
	char c;
	if((arq=fopen(".\\dados\\fabricante.dat","rb"))==NULL){
		printf("ARQUIVO NAO ENCONTRADO!!!");
		getch();
	}else{
		while((fread(&fab,sizeof(fab),1,arq))==1){
			strcat(cmdTitle,fab.nome);
			system(cmdTitle);
			strcat(cmdUrl,fab.url);
			printf("EMPRESA:...%s\n",fab.nome);
			printf("DESCRICAO:...%s\n",fab.historia);
			printf("PAIS:..%s\n",fab.pais);
			printf("DATA DE FUNDACAO:... %d / %d / %d",fab.dt.dia,fab.dt.mes,fab.dt.ano);
			printf("\n\nPessione a tecla espaco para acessar o website da empresa");
			c=getch();
		    while(c!=77){
		    	if(c==32)system(cmdUrl);
		    	c=getch();
			}
			system("cls");
			strcpy(cmdUrl,"start msedge ");
			strcpy(cmdTitle,"title ");
		}
	}
	
}