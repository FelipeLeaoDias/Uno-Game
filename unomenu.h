int quantdig(int nume){
	int dig;
	if (nume == 0){
		dig = 1;
	}else{
		while (nume != 0){
			dig++;
			nume = nume/10;
		}
	}
	return dig;
}

void mpprint(){
	SetConsoleTextAttribute(h,15);
	system("cls");
	printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	printf ("X                                                X\n");
	printf ("X                                                X\n");
	printf ("X                     ");
	SetConsoleTextAttribute(h,4);
	printf ("U N O");
	SetConsoleTextAttribute(h,15);
	printf ("                      X\n");
	printf ("X                                                X\n");
	printf ("X                                                X\n");
	printf ("X                  1-> Jogar                     X\n");
	printf ("X                  2-> Estat�sticas              X\n");
	printf ("X                  3-> Tutorial                  X\n");
	printf ("X                  4-> Sair do jogo              X\n");
	printf ("X                                                X\n");
	printf ("X                                                X\n");
	printf ("X                                                X\n");
	printf ("X                                                X\n");
	printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");

}

void menuprincipal(){
	

	mpprint();
	switch(getch()){
		
		case 49:	//op��o 1 JOGAR
			SetConsoleTextAttribute(h,4);
			printf("\n\t    Deseja come�ar o jogo? (S/N)\n");
			SetConsoleTextAttribute(h,15);
			switch(tolower(getch())){
				case 115:
					gameaction();
				break;
				
				default:
					menuprincipal();
			}
		break;
		
		case 50:	//op��o 2 ESTATISTICA
			menuest();
		break;
		
		case 51:	//op��o 3 TUTORIAL
			paginastutorial = 1;
			menututo();
		break;
		
		case 52:
		SetConsoleTextAttribute(h,4);
			printf("\n\t    Deseja sair do jogo? (S/N)\n");
			SetConsoleTextAttribute(h,15);
			switch(tolower(getch())){
				case 115:
					exit(0);
				break;
				
				default:
					menuprincipal();
			}
		break;
		
		default:
			menuprincipal();
			
	}
	
	
}

void menuest(){
	int totalpartidas;
	char ret;
	leituraest();
	totalpartidas = quantvitorias + quantderrotas;
	
	SetConsoleTextAttribute(h,15);
	system("cls");
	printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	printf ("X                                                X\n");
	printf ("X                                                X\n");
	printf ("X                  ESTAT�STICAS                  X\n");
	printf ("X                                                X\n");
	printf("X");
	SetConsoleTextAttribute(h,4);
	printf ("              Turnos jogados - %d", quantturnos);
	quantturnos = quantdig(quantturnos);
	for(i = 0; (17 - quantturnos) != i; i++){
		printf(" ");
	}
	SetConsoleTextAttribute(h,15);
	printf("X\n");
	printf("X");
	SetConsoleTextAttribute(h,4);
	printf ("              Cartas jogadas - %d", quantcartas);
	quantcartas = quantdig(quantcartas);
	for(i = 0; (17 - quantcartas) != i; i++){
		printf(" ");
	}
	SetConsoleTextAttribute(h,15);
	printf("X\n");
	printf("X");
	SetConsoleTextAttribute(h,4);
	printf ("              Vit�rias - %d", quantvitorias);
	quantvitorias = quantdig(quantvitorias);
	for(i = 0; (23 - quantvitorias) != i; i++){
		printf(" ");
	}
	SetConsoleTextAttribute(h,15);
	printf("X\n");
	printf("X");
	SetConsoleTextAttribute(h,4);
	printf ("              Derrotas - %d", quantderrotas);
	quantderrotas = quantdig(quantderrotas);
	for(i = 0; (23 - quantderrotas) != i; i++){
		printf(" ");
	}
	SetConsoleTextAttribute(h,15);
	printf("X\n");
	printf("X");
	SetConsoleTextAttribute(h,4);
	printf ("              Jogos totais - %d", totalpartidas);
	totalpartidas = quantdig(totalpartidas);
	for(i = 0; (19 - totalpartidas) != i; i++){
		printf(" ");
	}
	SetConsoleTextAttribute(h,15);
	printf("X\n");
	printf("X");
	SetConsoleTextAttribute(h,4);
	printf ("              Vezes em UNO - %d", quantuno);
	quantuno = quantdig(quantuno);
	for(i = 0; (19 - quantuno) != i; i++){
		printf(" ");
	}
	SetConsoleTextAttribute(h,15);
	printf("X\n");
	printf ("X                                                X\n");
	printf ("X                    0-Voltar                    X\n");
	printf ("X                                                X\n");
	printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	
	switch(tolower(getch())){
		
		case 48:
			menuprincipal();
		break;
		
		default:
			menuest();
		
	}

	
	
}

void menututo(){

	system("cls");	
	switch(paginastutorial){
		
	case 1:
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
		printf ("X  USE        *Aperte 0 para voltar*             X\n");
		printf ("X  A-D                                      (1)  X\n");
		printf ("X                T U T O R I A L                 X\n");
		printf ("X                     U N O                      X\n");
		printf ("X                                                X\n");
		printf ("X      1- O UNO � um jogo de cartas que          X\n");
		printf ("X      possui como objetivo ficar com nenhuma    X\n");
		printf ("X      carta em sua m�o. Para isso, o jogador    X\n");
		printf ("X      dever� utilizar cartas especiais de       X\n");
		printf ("X      a��o para evitar que os advers�rios       X\n");
		printf ("X      fa�am o mesmo primeiro.                   X\n");
		printf ("X                                                X\n");
		printf ("X                                                X\n");
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	break;
	
	case 2:
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
		printf ("X  USE        *Aperte 0 para voltar*             X\n");
		printf ("X  A-D                                      (2)  X\n");
		printf ("X                T U T O R I A L                 X\n");
		printf ("X                     U N O                      X\n");
		printf ("X                                                X\n");
		printf ("X      2- As cartas de a��o s�o cartas que       X\n");
		printf ("X      possuem efeitos especiais para atra-      X\n");
		printf ("X      palhar o advers�rio de conseguir a        X\n");
		printf ("X      vit�ria. As cartas e seus efeitos         X\n");            
		printf ("X      apareceram durante o jogo. A seguir       X\n");            
		printf ("X      algumas dessas cartas:                    X\n");
		printf ("X                                                X\n");
		printf ("X                                                X\n");
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	break;
	
	case 3:
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
		printf ("X  USE        *Aperte 0 para voltar*             X\n");
		printf ("X  A-D                                      (3)  X\n");
		printf ("X                T U T O R I A L                 X\n");
		printf ("X                     U N O                      X\n");
		printf ("X                                                X\n");
		printf ("X      - Bloqueio (XX) - Impede o pr�ximo        X\n");
		printf ("X      jogador de jogar uma carta.               X\n");
		printf ("X                                                X\n");
		printf ("X      - Inverter (<>) - Inverte a ordem de      X\n");            
		printf ("X      jogada dos jogadores. A ordem pode ser    X\n");            
		printf ("X      vista pelas setas entre os nomes dos      X\n");
		printf ("X      jogadores.                                X\n");
		printf ("X                                                X\n");
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	break;
	
	case 4:
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
		printf ("X  USE        *Aperte 0 para voltar*             X\n");
		printf ("X  A-D                                      (4)  X\n");
		printf ("X                T U T O R I A L                 X\n");
		printf ("X                     U N O                      X\n");
		printf ("X                                                X\n");
		printf ("X     - Muda de cor (##) - Carta que pode        X\n");
		printf ("X     ser jogada a qualquer momento para         X\n");
		printf ("X     mudar a cor da proxima carta jogada.       X\n");
		printf ("X                                                X\n");            
		printf ("X     - Muda de cor e compra 4 (#4) - igual      X\n");            
		printf ("X     a carta muda de cor normal por�m tamb�m    X\n");
		printf ("X     faz o advers�rio seguinte cavar 4.         X\n");
		printf ("X                                                X\n");
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	break;
	
	case 5:		//ATEN��O A PONTUA��O, ALINHAMENTO, N�MERO DA P�GINA, N�MERO DO 'case' E PONTO FINAL!
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
		printf ("X  USE        *Aperte 0 para voltar*             X\n");
		printf ("X  A-D                                      (5)  X\n");
		printf ("X                T U T O R I A L                 X\n");
		printf ("X                     U N O                      X\n");
		printf ("X                                                X\n");
		printf ("X     - Bomba (++) - Ao ser jogada, uma bomba    X\n");
		printf ("X     ser� posta na pilha de compras, o pr�xi-   X\n");
		printf ("X     mo jogador a comprar ou cavar cartas ir�   X\n");
		printf ("X     cavar duas a mais do que deveria.          X\n");       
		printf ("X                                                X\n");           
		printf ("X     - Random 6 (R6) - Distribui 6 cartas para  X\n");
		printf ("X     seus oponentes de forma aleat�ria.         X\n");
		printf ("X                                                X\n");
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	break;
	
	case 6:		//ATEN��O A PONTUA��O, ALINHAMENTO, N�MERO DA P�GINA, N�MERO DO 'case' E PONTO FINAL!
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
		printf ("X  USE        *Aperte 0 para voltar*             X\n");
		printf ("X  A-D                                      (6)  X\n");
		printf ("X                T U T O R I A L                 X\n");
		printf ("X                     U N O                      X\n");
		printf ("X                                                X\n");
		printf ("X     3- Durante o seu turno, use as teclas      X\n");
		printf ("X     'WASD' para mover o cursor de sele��o      X\n");
		printf ("X     de cartas, e pressione a tecla 'E'         X\n");
		printf ("X     para confirmar a jogada da carta           X\n");       
		printf ("X     selecionada na m�o.                        X\n");           
		printf ("X                                                X\n");
		printf ("X                                                X\n");
		printf ("X                                                X\n");
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	break;
	
	case 7:
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
		printf ("X  USE        *Aperte 0 para voltar*             X\n");
		printf ("X  A-D                                      (7)  X\n");
		printf ("X                T U T O R I A L                 X\n");
		printf ("X                     U N O                      X\n");
		printf ("X                                                X\n");
		printf ("X     4- Se o jogador n�o tiver cartas que       X\n");
		printf ("X     possam ser jogadas, ele dever� cavar       X\n");
		printf ("X     mais cartas apertando a tecla 'Q'.         X\n");
		printf ("X     O jogador ir� cavar automaticamente        X\n");            
		printf ("X     at� conseguir uma carta que possa ser      X\n");            
		printf ("X     jogada naquele turno.                      X\n");
		printf ("X                                                X\n");
		printf ("X                                                X\n");
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	break;
	
	case 8:
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
		printf ("X  USE        *Aperte 0 para voltar*             X\n");
		printf ("X  A-D                                      (8)  X\n");
		printf ("X                T U T O R I A L                 X\n");
		printf ("X                     U N O                      X\n");
		printf ("X                                                X\n");
		printf ("X    5- Ao ficar com uma carta sem gritar UNO    X\n");
		printf ("X    o jogador ser� penalizado com a compra      X\n");
		printf ("X    de +2 cartas. Para evitar isso, ao ter      X\n");
		printf ("X    2 cartas na m�o (logo antes de descartar    X\n");            
		printf ("X    a pr�xima carta), o jogador dever� apertar  X\n");            
		printf ("X    'F' para chamar UNO. Ao jogar a pen�ltima   X\n");
		printf ("X    carta ser� gritado UNO automaticamente.     X\n");
		printf ("X                                                X\n");
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	break;  
	
	case 9:
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
		printf ("X  USE        *Aperte 0 para voltar*             X\n");
		printf ("X  A-D                                      (9)  X\n");
		printf ("X                T U T O R I A L                 X\n");
		printf ("X                     U N O                      X\n");
		printf ("X                                                X\n");
		printf ("X    6- Bots ir�o ocasionalmente esquecer de     X\n");
		printf ("X    gritar UNO tamb�m e tentar�o jogar cartas   X\n");
		printf ("X    para te impedir de vencer. Al�m disso,      X\n");
		printf ("X    fique atento a cor que eles escolherem      X\n");       
		printf ("X    quando trocarem de cor! � um indicativo     X\n");           
		printf ("X    da cor que eles mais tem na m�o! Lembre-    X\n");
		printf ("X    se que eles tamb�m est�o tentando vencer.   X\n");
		printf ("X                                                X\n");
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	break;
	
}
	fflush(stdin);
	switch(tolower(getch())){
		
		case 48:
			menuprincipal();
		break;
		
		case 97:
			paginastutorial--;
			if(paginastutorial < 1){
				paginastutorial = 9;
			}
		break;
		
		case 100:
			paginastutorial++;	
			if(paginastutorial > 9){
				paginastutorial = 1;
			}
		break;	
		
		default:
			menututo();
	}
	menututo();
}



/* TEMPLATE

	case 0:		//ATEN��O A PONTUA��O, ALINHAMENTO, N�MERO DA P�GINA, N�MERO DO 'case' E PONTO FINAL!
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
		printf ("X  USE        *Aperte 0 para voltar*             X\n");
		printf ("X  A-D                                      (1)  X\n");
		printf ("X                T U T O R I A L                 X\n");
		printf ("X                     U N O                      X\n");
		printf ("X                                                X\n");
		printf ("X                                                X\n");
		printf ("X                                                X\n");
		printf ("X                                                X\n");
		printf ("X                                                X\n");       
		printf ("X                                                X\n");           
		printf ("X                                                X\n");
		printf ("X                                                X\n");
		printf ("X                                                X\n");
		printf ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	break;

*/











