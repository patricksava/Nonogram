#include <stdio.h>
#include <stdlib.h>
#include "celula.h"



struct celula {

	int atual;
	
	int esperado;

};



// CRIAR CELULA
Celula* Cel_CriaCelula(int marcacao_esperada, int marcacao_atual ) 
{


	Celula* cell = (Celula*)malloc(sizeof(Celula));
						   
	if (cell == NULL) {
	
			printf("Erro na alocacao de memoria\n");			   
			 
			return NULL;			   
	}

	cell -> esperado = marcacao_esperada;
	cell -> atual = marcacao_atual;
	

	return cell;

}


// MARCACAO ESPERADA NA CELULA
int Cel_MarcacaoEsperada( Celula* cell) {
						   
	if( cell == NULL )
		exit (1);
						   
	return cell -> esperado;					   
						   
												
} 


// MARCACAO ATUAL DA CELULA
int Cel_MarcacaoAtual( Celula* cell) {
						   
	if( cell == NULL )
		exit (1);
						   
	return  cell -> esperado;
						   
}

						   
// MUDA A MARCACAO ATUAL
CEL_tpCondRet Cel_AlteraMarcacao( Celula* cell) {

	if( cell == NULL )
		CEL_CondRetFaltouMemoria;
						   

	if( cell -> atual == 0)
		cell -> atual = 1;
	
	else if(cell -> atual == 1)
		cell -> atual = 0;
						   
	else
		return  CEL_CondRetMesmaMarcacao;
						   
	return 	CEL_CondRetOK;				   
						   
}

	
CEL_tpCondRet Cel_DestruirCelula( Celula* cell) {
						   
	if( cell == NULL)
		return CEL_CondRetCelulaMorta;
						   
	free(cell);
						   
	return CEL_CondRetOK;
						   
}	
	
	
	
	
	
	
	
	
	
	
	
