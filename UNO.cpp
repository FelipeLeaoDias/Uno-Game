#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <locale.h>
#include <math.h>
#include <dos.h>
#include <list>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

//ADICIONAR FUNÇÕES AQUI:
void embaralhar(), add(),cor(int i), desmao(), efftable(int eff), escolher(), guardarest(), leituraest(), nome(), checkvit();
void gameaction(), printmao(), visualgame(), playeract(), botact(), game(), menututo(), menuest(), menuprincipal(), mpprint(); 
int comprar(int carta), descartar(int carta), descartar2(int carta), descartarale(int carta);

typedef struct {

    int cor; 		//1-preto; 2-azul; 3-vermelho; 4-amarelo; 5-verde
    int num; 		//se a carta eh 0,1,2,3
    int ID;  		//contagem de cartas (para o sistema unicamente, não mexer)
    int effect;   	//efeito da carta
    string efdesc; 	//descrição de cada efeito para usuario
    string efname; 	//Demonstração da carta efeito : (+2)
    
} CARTA;
stack<CARTA> deck;
stack<CARTA> descarte;
stack<CARTA> compra;
vector<CARTA>shuffle;
CARTA criarcarta(int cor, int num, int ID, int effect);

typedef struct {

    vector<CARTA> mao;  //numero devera ser o maximo de cartas num jogo menos 4S
    int quantcard;		//numero de cartas na mão do jogador
    char nome[17];		//nome dos bots (player[1];player[2];player[3])
    bool uno = false;

} PLAYERS;
PLAYERS player[4]; //jogador 0 é o usuário

int i, j, k, x, pnt, paginastutorial, bomba, ief, rando, turno=0, carta;
int turnoest, cartasjogadasest, vitoriasest, derrotasest, quantunoest; 	//dados estatisticas durante o jogo
int quantturnos, quantcartas, quantvitorias, quantderrotas, quantuno; 	//dados estatisticas do FILE
int globef = 0, turntype = 1, turnat;
bool jogo = false, cartusada = false, skip = false, checkuno = false, cortauno = false;
FILE *arq;

#include "jogo.h"
#include "carregamento.h"
#include "file.h"
#include "unomenu.h"
#include "botnome.h"

int main() {

	time_t t;
	srand((unsigned) time(&t));
	setlocale(LC_ALL, "Portuguese");
	
	//Nome da janela, e tamanho da janela
	SetConsoleTitle("U N O v1.3 - By Devs: DrT | Miguez | Leaun | Pototo | Haya");
    HWND wh = GetConsoleWindow();
    
    DWORD dwWidth = GetSystemMetrics(SM_CXSCREEN);	//checando resolução do monitor
	DWORD dwHeight = GetSystemMetrics(SM_CYSCREEN);	//            :)
	
	//printf("%hd x %hd\n", dwWidth, dwHeight);	//printando resolução se quiserem testar :)
	//system("pause");
	
	//se tiverem outra resolução, so adicionar e mudar pra a janela aparecer no meio da tela
	if(dwWidth == 1920 && dwHeight == 1080){	//1920x1080
		MoveWindow(wh, 620, 210, 681, 610, TRUE);
	} else if(dwWidth == 1400 && dwHeight == 1050) { //1400x1050
		MoveWindow(wh, 320, 100, 681, 610, TRUE); //AJUSTEM OS DOIS PRIMEIROS NUMEROS PRA APARECER NO MEIO DA TELA!!
	}else if(dwWidth == 1366 && dwHeight == 768) { //1366x768
		MoveWindow(wh, 320, 80, 681, 610, TRUE); 
	} else {
		MoveWindow(wh, 100, 100, 681, 610, TRUE);
	}
	
	//primeiros dois numeros são coordenadas X e Y da janela na tela, os outros dois numeros são o tamanho da janela
	//testar se janela aparece no meio da tela mesmo estando em outras resoluçoes de monitor
	
	SetConsoleTextAttribute(h,15);
	add(); 			//IMPORTANTE: SO USAR UMA VEZ AO INICIAR PROGRAMA!!!
	lapagod(); 		//carregamento tela lapagod
	Sleep(1200); 	//tempinho pra ver a cara linda de lapinha :D
	loading(); 		//tela de loading
	while(1){
		menuprincipal();
	}
    return 0;
}

void embaralhar() {				//embaralha a pilha de descarte na de compras
	CARTA A;
	bool var = false;
	if(!descarte.empty()){
		A = descarte.top();
		descarte.pop();
		var = true;
	}

	while(!descarte.empty()){
		if(descarte.top().effect == 4 || descarte.top().effect == 5 || descarte.top().effect == 6 || descarte.top().effect == 7 ) descarte.top().cor = 1;
		shuffle.push_back(descarte.top());
		descarte.pop();
	}
	
	while(!compra.empty()){
		shuffle.push_back(compra.top());
		compra.pop();
	}
	
	random_shuffle(shuffle.begin(),shuffle.end());

	while(!shuffle.empty()){
		compra.push(shuffle.back());
		shuffle.pop_back();
	}

	if(var){
    	descarte.push(A);
	} else {
		descarte.push(compra.top());
		compra.pop();
	}
	
	if(descarte.top().cor == 1) descarte.top().cor = 2 + rand()%4;
	
}

void add() {					//introduz todas as cartas ao jogo e as põe na pilha de descartes

	int id = 1;
	int intcor = 2;

	while(intcor < 6){
		while(j < 2){
			for(i = 1; i <= 9; i++){
				shuffle.push_back(criarcarta(intcor, i, id, 0));
				id++;
    		}
    		
			j++;
		}
		
		shuffle.push_back(criarcarta(intcor, 0, id, 0));
		id++;
		intcor++;
		j = 0;
	}


	for(j=0;j<2;j++){
		for(i=2;i<=5;i++) {
			shuffle.push_back(criarcarta(i, -1 , id, 1));
			id++;
		}
	}

	for(j=0;j<2;j++){
		for(i=2;i<=5;i++) {
			shuffle.push_back(criarcarta(i, -2, id, 2));
    		id++;
    		shuffle.push_back(criarcarta(i, -3, id, 3));
    		id++;
		}
	}


	for(i=0;i<4;i++) {
		shuffle.push_back(criarcarta(1, -4, id, 4));
		id++;
		shuffle.push_back(criarcarta(1, -5, id, 5));
		id++;
	}
	
	for(i=0;i<2;i++) { //criar bomba e chuva de carta
		shuffle.push_back(criarcarta(1, -6, id, 6));
		id++;
		shuffle.push_back(criarcarta(1, -7, id, 7));
		id++;
	}
	
	intcor = 2;
    while(intcor < 6){ //carta descartar 3
        
        shuffle.push_back(criarcarta(intcor, -8, id, 8));
        id++;
        intcor++;
    }

	random_shuffle(shuffle.begin(), shuffle.end());
	
	while(!shuffle.empty()){
		compra.push(shuffle.back());
		shuffle.pop_back();
	}
	
}

int comprar(int carta) { 		//compra uma quantidade X de cartas da pilha de compras e põe na mão do jogador
	
	if(descarte.size() == carta && compra.empty()) {
      printf("\t\tNão foi possível comprar uma carta\n");
      Sleep(1000);
      return 2;
    }

	if(compra.empty()) {      //verifica quantidade suficiente de carta na pilha de compra e embaralha
		embaralhar();
    } else if(compra.size() < carta){
		carta = compra.size();
	}      

	for(int i=0;i<carta;i++){
		player[turno].mao.push_back(compra.top());
    	compra.pop();
		player[turno].quantcard++;
		
		if(jogo == true){ //comprar cartas pausadamente
			visualgame();
			if(carta > 1){
				SetConsoleTextAttribute(h,4);
				printf("\t\t\tJOGADOR %d COMPRANDO CARTAS %d/%d\n", turno+1, i+1, carta);
				SetConsoleTextAttribute(h,15);
			} else {
				SetConsoleTextAttribute(h,4);
				printf("\t\t\tJOGADOR %d CAVANDO CARTAS...\n", turno+1);
				SetConsoleTextAttribute(h,15);
			}
			Sleep(750);
		}
		
	}
	
	if(player[turno].quantcard != 1 && player[turno].uno == true) {
		player[turno].uno = false;
	}
	
	if(bomba > 0){
		bomba=0;
		SetConsoleTextAttribute(h,4);
		printf("\t\t\tBOMBA EXPLODIU NO JOGADOR %d!!\n", turno+1);
		SetConsoleTextAttribute(h,15);
		Sleep(2000);
		comprar(2);
	}
	

}

void desmao() {					//descarta para a pilha de descarte TODAS as cartas na mão

	x = player[turno].quantcard;
	for(j=0;j<x;j++){
		descartar2(1);
	}

}

int descartar(int carta) {    	//descarta a carta de posição X da mão do jogador e põe ela na pilha de compras

    if(player[turno].quantcard > 0){
    	if(turno == 0){
    		cartasjogadasest++;
		}
        carta--;
        descarte.push(player[turno].mao[carta]);
        player[turno].mao.erase(player[turno].mao.begin() + carta);
        globef = descarte.top().effect;
        player[turno].quantcard--;
        
        if(descarte.top().effect == 8){ //funcionamento da carta (-3)
       		SetConsoleTextAttribute(h,4);
       		printf("\t\t\tJOGADOR %d DESCARTANDO CARTAS 0/3\n", turno+1);
       		SetConsoleTextAttribute(h,15);
        	Sleep(750);
            descartarale(3);
        }
    }

}

int descartar2(int carta) {    	//descarta a carta de posição X da mão do jogador e põe ela na pilha shuffle

    if(player[turno].quantcard > 0){
        shuffle.push_back(player[turno].mao[carta]);
        player[turno].mao.erase(player[turno].mao.begin() + carta);
        globef = shuffle.back().effect;
        player[turno].quantcard--;
    }

}

int descartarale(int carta) {  	//descarta X cartas aleatoriamente da mão jo jogador
    
    
    for(int i = 0; i < carta; i++){
        if(player[turno].mao.size() <= 2){
            break;
        } else {
            descartar2(rand() % player[turno].mao.size());
            visualgame();
            SetConsoleTextAttribute(h,4);
			printf("\t\t\tJOGADOR %d DESCARTANDO CARTAS %d/%d\n", turno+1, i+1, carta);
			SetConsoleTextAttribute(h,15);
            Sleep(750);
        }
    }
    

}

/*

	SetConsoleTextAttribute(h,15);

    0 = Black
    1 = Blue
    2 = Green
    3 = Aqua
    4 = Red
    5 = Purple
    6 = Yellow
    7 = White
    8 = Gray
    9 = Light Blue
    10 = Light Green
    11 = Light Aqua
    12 = Light Red
    13 = Light Purple
    14 = Light Yellow
    15 = Bright White

*/
