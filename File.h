void guardarest(){
		
	arq = fopen("Estatistica.txt", "r");
	fclose(arq);
	if(arq == NULL){
	arq = fopen("Estatistica.txt", "w");
	fprintf(arq,"0 0 0 0 0");
	fclose(arq);
	}
	arq = fopen("Estatistica.txt", "r");
	fscanf(arq,"%d %d %d %d %d", &quantturnos, &quantcartas, &quantvitorias, &quantderrotas, &quantuno);
	fclose(arq);
	arq = fopen("Estatistica.txt", "w");
	quantturnos = turnoest + quantturnos;
	quantcartas = cartasjogadasest + quantcartas;
	quantvitorias = vitoriasest + quantvitorias;
	quantderrotas = derrotasest + quantderrotas;
	quantuno = quantunoest + quantuno;
	fprintf(arq,"%d %d %d %d %d", quantturnos, quantcartas, quantvitorias, quantderrotas, quantuno);
	fclose(arq);
	
}

void leituraest(){
	
	arq = fopen("Estatistica.txt", "r");
	fscanf(arq,"%d %d %d %d %d", &quantturnos, &quantcartas, &quantvitorias, &quantderrotas, &quantuno);
	fclose(arq);	
	
}
