void gameaction(){

	embaralhar();	//embaralha a pilha de descartes na pilha de compras
	nome();
	
	cartusada = false, jogo = false;
	
	turno = 0;
	comprar(7); //mao jogador
	//player[turno].mao.push_back(criarcarta(1, -6, 999, 6));
    //player[turno].quantcard++;
	turno = 1;
	comprar(7); //mao bot 1         //compra todas as cartas iniciais
	turno = 2;
	comprar(7); //mao bot 2
	turno = 3;
	comprar(7); //mao bot 3

	jogo = true;
	
	turno = (rand() % 4);	//aleatoriza primeiro jogador
	turnoest=0; 			//estatistica rounds passados na partida
	cartasjogadasest=0;		//estatistica cartas jogadas na partida
	vitoriasest=0;			//estatistica vitoria na partida
	derrotasest=0;			//estatistica derrota na partida
	quantunoest=0;			//estatistica UNOs gritados na partida
	
	//IMPLEMENTAR CONTABILIZAÇÃO DE CADA UMA DAS ESTATISTICAS!

	visualgame();
	if(turno != 0){
		Sleep(3000);
	}
	game();
	
}

void game() {
	
	while(jogo){
		skip = false;
	
		if(globef == 3) turntype++;
		if(turntype%2) {
			turno++;
			if(turno >= 4){
				turno=0;
				turnoest++;
			}
		} else {
			turno--;
			if(turno <= -1){
				turno = 3;
				turnoest++;
			}
		}
	
		if(globef){
			efftable(globef);
			globef = 0;
		}
		
		if(!skip){
	
			if(descarte.top().cor == 1) escolher();
			
			turnat = turno;
			if(turno==0){
				pnt=1;
				playeract();
				checkvit();
			} else {
				botact();
				checkvit();
			}
			
		} else {
			Sleep(1000); //dar tempo na tela para ver efeito da carta de bloqueio
		}
		
		if(!skip) {
			visualgame();
		}
		
	}
	guardarest();
	
	for(k=0;k<4;k++){
		turno = k;
		desmao(); 
	}
	
	menuprincipal();
	
}

void playeract(){
	
	cartusada = false;
	while(cartusada == false){

		visualgame();
		carta = 0;

		switch(tolower(getch())){  //para funcionar com maiÃºscula

			case 119: //w

				pnt -= 10;

				if(pnt < 1) {
					pnt = 1;
				}

				playeract();
			break;

			case 97: //a

				if(pnt != 1){
					pnt -= 1;
				}

				playeract();
			break;

			case 115: //s

				pnt += 10;

				if(pnt > player[0].quantcard) {
					pnt = player[0].quantcard;
				}

				playeract();
			break;

			case 100: //d

				if(player[0].quantcard != pnt) {
					pnt += 1;
				}

				playeract();
			break;

			case 101: //e
				cartusada = true;
			break;
			
			case 102: //f
				if(player[0].quantcard == 2){
					checkuno = true;
					playeract();
				} else {
					playeract();
				}
			break;

			case 113:  //q
				
				int z;
				for(z=0;z<player[turno].mao.size()-1;z++){
					if(player[turno].mao[z].cor == descarte.top().cor)break;
					if(player[turno].mao[z].num == descarte.top().num)break;
					if(player[turno].mao[z].cor == 1)break;
				}
				
				while(player[turno].mao[z].cor != descarte.top().cor && player[turno].mao[z].num != descarte.top().num && player[turno].mao[z].cor != 1){
					comprar(1);
					for(z=0;z<player[turno].mao.size()-1;z++){
						if(player[turno].mao[z].cor == descarte.top().cor)break;
						if(player[turno].mao[z].num == descarte.top().num)break;
						if(player[turno].mao[z].cor == 1)break;
					}
				}
				
			break;

			default:
				playeract();

		}
		
		if(cartusada && (player[turno].mao[pnt-1].cor == descarte.top().cor || player[turno].mao[pnt-1].num == descarte.top().num || player[turno].mao[pnt-1].cor == 1)) {
			descartar(pnt);
			checkvit();
			
			if(checkuno && player[0].quantcard == 1) {
				player[0].uno = true;
				quantunoest++;
				checkuno = false;
			} else if(player[0].quantcard == 1 && player[0].uno == false) {
				
				cortauno = true;
				visualgame();
				Sleep(5000);
				comprar(2);
				checkuno = false;
				
			} else {
				checkuno = false;
			}
			
			pnt = -1;
			visualgame();
			Sleep(1500);
			game();
		} else {
			playeract();
		}

	}

}

typedef struct{
	int aa;
	int tipo;
}compdascartas;

bool comparacion(compdascartas a, compdascartas b){
	
	if(a.aa != b.aa) {
		return  a.aa > b.aa;
	} else {
		return a.tipo > b.tipo;
	}
}

compdascartas insere(int um , int dois){
	compdascartas seila;
	seila.aa = um;
	seila.tipo = dois;
	return seila;
}

void botact(){
	
	visualgame();
	Sleep(750);
	
	int azul=0, verm=0, amar=0, verd=0, z, z2, react;
	
	if((player[turno-1].mao.size() <= 4 || player[turno].mao.size()/2 >= player[turno-1].mao.size()) && turntype%2 == 0) {
		
		for(z=0;z<player[turno].mao.size()-1;z++){
			if((player[turno].mao[z].effect == 1 || player[turno].mao[z].effect == 2 || player[turno].mao[z].effect == 3 || player[turno].mao[z].effect == 5) && player[turno].mao[z].cor == descarte.top().cor)break;
			if((player[turno].mao[z].effect == 1 || player[turno].mao[z].effect == 2 || player[turno].mao[z].effect == 3 || player[turno].mao[z].effect == 5) && player[turno].mao[z].effect == descarte.top().effect)break;
			if(player[turno].mao[z].cor == descarte.top().cor)break;
			if(player[turno].mao[z].num == descarte.top().num)break;
			if(player[turno].mao[z].cor == 1)break;
		}
		
	} else if((player[turno+1].mao.size() <= 4 || player[turno].mao.size()/2 >= player[turno+1].mao.size()) && turntype%2 == 1) {
		
		for(z=0;z<player[turno].mao.size()-1;z++){
			if((player[turno].mao[z].effect == 1 || player[turno].mao[z].effect == 2 || player[turno].mao[z].effect == 3 || player[turno].mao[z].effect == 5) && player[turno].mao[z].cor == descarte.top().cor)break;
			if((player[turno].mao[z].effect == 1 || player[turno].mao[z].effect == 2 || player[turno].mao[z].effect == 3 || player[turno].mao[z].effect == 5) && player[turno].mao[z].effect == descarte.top().effect)break;
			if(player[turno].mao[z].cor == descarte.top().cor)break;
			if(player[turno].mao[z].num == descarte.top().num)break;
			if(player[turno].mao[z].cor == 1)break;
		}
		
	} else {
		
		for(z=0;z<player[turno].mao.size()-1;z++){
			if(player[turno].mao[z].cor == descarte.top().cor)break;
			if(player[turno].mao[z].num == descarte.top().num)break;
			if(player[turno].mao[z].cor == 1)break;
		}
		
	}
	
	while(player[turno].mao[z].cor !=  descarte.top().cor && player[turno].mao[z].num !=  descarte.top().num && player[turno].mao[z].cor != 1){
		comprar(1);
		for(z=0;z<player[turno].mao.size()-1;z++){
			if(player[turno].mao[z].cor == descarte.top().cor)break;
			if(player[turno].mao[z].num == descarte.top().num)break;
			if(player[turno].mao[z].cor == 1)break;
		}
	}

	descartar(z+1);
	
	if(player[turno].quantcard == 1 && player[turno].uno == false){
		
		react = (rand() % 3);
		
		if(react == 0) {
			cortauno = true;
			visualgame();
			Sleep(5000);
			comprar(2);
			
		} else {
			player[turno].uno == true;
		}
		
	}
	
	if(descarte.top().cor == 1 && descarte.top().effect != 6 && descarte.top().effect != 7) {
		
		azul=0;
		verm=0;
		amar=0;
		verd=0;
		
		for(z=0;z<player[turno].mao.size()-1;z++){	//1-preto; 2-azul; 3-vermelho; 4-amarelo; 5-verde
		
			if(player[turno].mao[z].cor == 2){
				azul++;
			} else if(player[turno].mao[z].cor == 3){
				verm++;
			} else if(player[turno].mao[z].cor == 4){
				amar++;
			} else if(player[turno].mao[z].cor == 5){
				verd++;
			}
		
		}

		list<compdascartas> lista;
		lista.push_back(insere(azul,2));
		lista.push_back(insere(verm,3));
		lista.push_back(insere(amar,4));
		lista.push_back(insere(verd,5));

		lista.sort(comparacion);

		int maior = lista.front().tipo;
		
		visualgame();
		Sleep(1000);
		
		descarte.top().cor = maior;
		
	}

	visualgame();
	checkvit();
	Sleep(2000);

}

void printmao(){
	
	int numiro;
	
	if(checkuno){
		printf("\tMÃO DO JOGADOR (%d):", player[0].quantcard);
		cor(1);
		printf("       -uno-    ");
		cor(0);
		if(bomba > 0){
			SetConsoleTextAttribute(h,4);
			printf("!!! PILHA DE COMPRAS: (%d) !!!\n", compra.size());
			cor(0);
		} else {
			printf("    PILHA DE COMPRAS: (%d)\n", compra.size());
		}
	} else if(player[0].uno){
		printf("\tMÃO DO JOGADOR (%d):", player[0].quantcard);
		SetConsoleTextAttribute(h,4);
		printf("       U N O    ");
		cor(0);
		if(bomba > 0){
			SetConsoleTextAttribute(h,4);
			printf("!!! PILHA DE COMPRAS: (%d) !!!\n", compra.size());
			cor(0);
		} else {
			printf("    PILHA DE COMPRAS: (%d)\n", compra.size());
		}
	} else {
		if(bomba > 0){
			printf("\tMÃO DO JOGADOR (%d):", player[0].quantcard);
			SetConsoleTextAttribute(h,4);
			printf("                !!! PILHA DE COMPRAS: (%d) !!!\n", compra.size());
			cor(0);
		} else {
			printf("\tMÃO DO JOGADOR (%d):                    PILHA DE COMPRAS: (%d)\n", player[0].quantcard, compra.size());
		}
		
	}

	for(i=0;i<=ceil(player[0].quantcard/10);i++){
	
		if(pnt > i*10 && pnt <= (i+1)*10 ){

			printf("\t\t");
			for(k = 0; numiro < player[0].mao.size() && k < 10 ;k++ ){
				if(player[0].mao[numiro].cor == 1){
					cor(1);
				} else if(player[0].mao[numiro].cor == 2){
					cor(2);
				} else if(player[0].mao[numiro].cor == 3){
					cor(3);
				} else if(player[0].mao[numiro].cor == 4){
					cor(4);
				} else if(player[0].mao[numiro].cor == 5){
					cor(5);
				}

				if(player[0].mao[numiro].num < 10 && player[0].mao[numiro].num >= 0){
					printf("(0%d)", player[0].mao[numiro].num);
				} else {
					printf("(%s)", player[0].mao[numiro].efname.c_str());
				}
				cor(0);
				numiro++;
			}
			printf("\n");

			if(turno == 0){
				printf("\t\t");
				for(k=0;k<10;k++){
					if(pnt- i*10 == k + 1) {
						printf(" /\\ ");
					} else {
						printf("    ");
					}
				}
				printf("\n");
			}


		} else {
			printf("\t\t");
			for(k = 0; numiro < player[0].mao.size() && k < 10 ;k++ ){
				if(player[0].mao[numiro].cor == 1){
					cor(1);
				} else if(player[0].mao[numiro].cor == 2){
					cor(2);
				} else if(player[0].mao[numiro].cor == 3){
					cor(3);
				} else if(player[0].mao[numiro].cor == 4){
					cor(4);
				} else if(player[0].mao[numiro].cor == 5){
					cor(5);
				}

				if(player[0].mao[numiro].num < 10 && player[0].mao[numiro].num >= 0){
					printf("(0%d)", player[0].mao[numiro].num);
				} else {
					printf("(%s)", player[0].mao[numiro].efname.c_str());
				}
				cor(0);
				numiro++;
			}
			
			printf("\n");
			
		}
	}
	
	if(player[0].mao[pnt-1].effect) printf("\n\tEfeito:");
	if(player[0].mao[pnt-1].effect) printf("\t%s",player[0].mao[pnt-1].efdesc.c_str());
	printf("\n");
	if(ief > 0){
		SetConsoleTextAttribute(h,4);
		printf("\t\t\tCARTAS DISTRIBUIDAS %d/6\n", ief);
		SetConsoleTextAttribute(h,15);
	}
}

void visualgame(){

	system("cls");
	
	if(cortauno){
		SetConsoleTextAttribute(h,4);
		printf("\n\t                      !!! CORTA UNO !!!                      \n");
		cor(0);
		cortauno = false;
	}
	
	
	printf("\n");

	printf("\t __________________   __________________   __________________ \n");
	
	if(turntype%2) {
		printf("       >|                  |>|                  |>|                  |>\n");
	} else {
		printf("       <|                  |<|                  |<|                  |<\n");
	}

	if(turno == 1){
		printf("\t| ");
		cor(4);
		printf("%s", player[1].nome);
		cor(0);
		printf(" | ");
		printf("| %s | | %s |\n", player[2].nome, player[3].nome);
	} else if(turno == 2){
		printf("\t| %s | ", player[1].nome);
		printf("| ");
		cor(4);
		printf("%s", player[2].nome);
		cor(0);
		printf(" | ");
		printf("| %s |\n", player[3].nome);
	} else if(turno == 3){
		printf("\t| %s | | %s | ", player[1].nome, player[2].nome);
		printf("| ");
		cor(4);
		printf("%s", player[3].nome);
		cor(0);
		printf(" |\n");
	} else {
		printf("\t| %s | | %s | | %s |\n", player[1].nome, player[2].nome, player[3].nome);
	}

	if(player[1].quantcard > 9){
		printf("\t|       (%d)       |", player[1].quantcard);
	} else {
		printf("\t|       (0%d)       |", player[1].quantcard);
	}

	if(player[2].quantcard > 9){
		printf(" |       (%d)       |", player[2].quantcard);
	} else {
		printf(" |       (0%d)       |", player[2].quantcard);
	}

	if(player[3].quantcard > 9){
		printf(" |       (%d)       |", player[3].quantcard);
	} else {
		printf(" |       (0%d)       |", player[3].quantcard);
	}

	printf("\n");
	if(turntype%2) {
		printf("       >|__________________|>|__________________|>|__________________|>\n");
	} else {
		printf("       <|__________________|<|__________________|<|__________________|<\n");
	}

	printf("\t");
	for(k=1;k<4;k++){
		if(player[k].quantcard == 1){
			SetConsoleTextAttribute(h,4);
			printf("        U N O        ");
			cor(0);
		} else {
			printf("                     ");
		}
	}
	printf("\n");

	if(descarte.top().cor == 1){
		cor(1);
	} else if(descarte.top().cor == 2){
		cor(2);
	} else if(descarte.top().cor == 3){
		cor(3);
	} else if(descarte.top().cor == 4){
		cor(4);
	} else if(descarte.top().cor == 5){
		cor(5);
	}

	printf("\t\t\t\t   _________\n");
	printf("\t\t\t\t  |         |\n");
	if(descarte.top().num < 10 && descarte.top().num >= 0){
		printf("\t\t\t\t  |    %d    |\n", descarte.top().num);
	} else if(descarte.top().effect >= 1){
		printf("\t\t\t\t  |   %s    |\n", descarte.top().efname.c_str());
	}

	if(descarte.top().cor == 1){
		printf("\t\t\t\t  |  Preto  |  (%d)\n", descarte.size());
	} else if(descarte.top().cor == 2){
		printf("\t\t\t\t  |  Azul   |  (%d)\n", descarte.size());
	} else if(descarte.top().cor == 3){
		printf("\t\t\t\t  |  Verme  |  (%d)\n", descarte.size());
	} else if(descarte.top().cor == 4){
		printf("\t\t\t\t  |  Amare  |  (%d)\n", descarte.size());
	} else if(descarte.top().cor == 5){
		printf("\t\t\t\t  |  Verde  |  (%d)\n", descarte.size());
	}

	if(descarte.top().num < 10 && descarte.top().num >= 0){
		printf("\t\t\t\t  |    %d    |\n", descarte.top().num);
	} else if(descarte.top().effect >= 1){
		printf("\t\t\t\t  |    %s   |\n", descarte.top().efname.c_str());
	}
	
	printf("\t\t\t\t  |_________|\n\n");

	cor(0);

	if(turno == 0){
		cor(1);
		printf("\tWASD move o cursor | 'E' usa a carta\n");
		printf("\t 'Q' compra cartas | 'F' chama UNO\n");
		cor(0);
	} else if(turno != 0) {
		cor(1);
		printf("\tEspere sua vez...\n\n");
		cor(0);
	} else {
		printf("\n\n");
	}

	printmao();

}

void mantercor(){
	CARTA seila;
	seila = descarte.top();
	descarte.pop();
	seila.cor = descarte.top().cor;
	descarte.push(seila);
}

string effunc(int effect){
	
	string coisa;
	switch(effect){

	case 1:
		coisa = "Próximo jogador compra 2 cartas.";
	break;
	
	case 2:
		coisa = "Próximo jogador será impedido de jogar.";
	break;
	
	case 3:
		coisa = "Inverte o sentido do jogo.";
	break;
	
	case 4:
		coisa = "Escolha a cor da carta.";
	break;
	
	case 5:
		coisa = "Escolha a cor da carta | Próximo jogador compra 4 cartas.";
	break;
	
	case 6:
        coisa = "Próximo jogador a comprar, compra 2 a mais.";
    break;
	
	case 7:
		coisa = "Distribui 6 cartas entre todos os oponentes.";
	break;
	
	case 8:    
        coisa = "Descarta 3 cartas (máximo de cartas restantes: 2).";
    break;
    
    case 9:
        coisa = "Todos os adversários compram 1.";
    break;
	}

	return coisa;
}

string effname(int effect){
	
	string coisa;
	switch(effect){

	case 1:
		coisa = "+2";
	break;
	
	case 2:
		coisa = "XX";
	break;
	
	case 3:
		coisa = "<>";
	break;
	
	case 4:
		coisa = "##";
	break;
	
	case 5:
		coisa = "#4";
	break;
	
	case 6:
        coisa = "++";
    break;
	
	case 7:
		coisa = "R6";
	break;
	
	case 8:
        coisa = "-3";
    break;
    
    case 9:
        coisa = "T1";
    break;
    

	}
	
	return coisa;
}

CARTA criarcarta(int cor, int num, int ID, int effect){
	CARTA A;
	A.cor = cor;
	A.num = num;
	A.ID = ID;
	A.effect = effect;
	if(effect) A.efdesc = effunc(effect);
	if(effect) A.efname = effname(effect);
	return A;
}

void efftable(int eff){
	switch(eff){
		
		//ATENÇÃO!! se for usar mantercor() na sua carta, coloque como a primeira função do codigo!
		
		case 1:
			comprar(2);
			skip = true;
		break;
			
		case 2:
			skip = true;
		break;
			
		case 5:
			comprar(4);
			skip = true;
		break;
		
		case 6:
			mantercor();
            bomba += 2;
        break;
		
		case 7:
			mantercor();
			
			//turnat agora eh definido dentro de game() para corrigir bugs
			
			for(ief=1;ief<7;ief++){
				
				turno = rand()%4;
				while(turno == turnat){
					turno = rand()%4;
				}
				comprar(1);
				
			}
			ief = 0;
			
			if(turntype%2) { //corrigindo a variavel pois efeito ocorre no proximo turno
				turno = turnat + 1;
			} else {
				turno = turnat - 1;
			}
			
			if(turno <= -2){ //tinha algum bug q ele tava ultrapassando muito o turno q ele deveria ta, isso corrige
				turno = -1;
			} else if(turno >= 6) {
				turno = 5;
			}
			
		break;
	}
		
}

void escolher(){
	
	char a;
	system("cls");
	visualgame();
	SetConsoleTextAttribute(h,4);
	printf("\tEscolha a cor para sua carta:\n");
	cor(2);
	printf("\t 1 > Azul");
	cor(1);
	printf(" | ");
	cor(3);
	printf("2 > Vermelho");
	cor(1);
	printf(" | ");
	cor(4);
	printf("3 > Amarelo");
	cor(1);
	printf(" | ");
	cor(5);
	printf("4 > Verde\n\n");
	cor(0);
	a = getch();
	
	if(a > 48 && a < 53){
		descarte.top().cor = 2 + a-49;
	} else {
		escolher();
	}
}

void cor(int i){
	switch(i){
		
		case 0: //padrao branco
			SetConsoleTextAttribute(h,15);
		break;
		
		case 1: // Preto
			SetConsoleTextAttribute(h,8);
		break;
		
		case 2: //Azul
			SetConsoleTextAttribute(h,1);
		break;
		
		case 3: //Vermelho
			SetConsoleTextAttribute(h,12);
		break;
		
		case 4: //Amarelo
			SetConsoleTextAttribute(h,14);
		break;
		
		case 5: //Verde
			SetConsoleTextAttribute(h,10);
		break;
	}

}

void checkvit() {
	
	for(k=0;k<4;k++){
		if(player[k].quantcard <= 0){
			jogo = false;
			if(k == 0) {
				vitoriasest++;
			} else {
				derrotasest++;
			}
			guardarest();
	
			if(turno == 0) {
				printf("\tVOCÊ VENCEU!\n");
			} else {
				printf("\tJOGADOR '%s' VENCEU!\n", player[turno].nome);
			}
			
			printf("\t");
			system("pause");
	
			for(k=0;k<4;k++){
				turno = k;
				desmao(); 
			}
	
			menuprincipal();
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

