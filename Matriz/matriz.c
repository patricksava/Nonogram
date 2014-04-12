

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz.h"
#include "lista.h"


struct tpMatriz {          
	int m;                // NUMERO DE LINHAS 
	int n;               //  NUMERO DE COLUNAS 
	TpLista** mat; 	    //   TpLista* mat[n] 
	
};



// FUNCAO ENCAPSULADA
static MAT_tpCondRet AjusteNoCorrente( TpMatriz* matriz );




//CRIAR MATRIZ

MAT_tpCondRet MAT_CriarMatriz( TpMatriz* matriz, int linhas, int colunas )
{
    
	int i, j;  // elemento qualquer A(ij) : linha "i" coluna "j"
	
    TpLista** vector; 
	
	
    matriz = (TpMatriz*)malloc(sizeof(TpMatriz)); // MATRIZ QUE A FUNCAO DEVOLVE POR REFERENCIA
	
	if( matriz == NULL)
        return MAT_CondRetFaltouMemoria;
	
    vector = (TpLista**)malloc(sizeof(TpLista*)*colunas); // VETOR DE PONTEIROS ALOCADO
	
    if( vector == NULL)
        return MAT_CondRetFaltouMemoria;
	
    
	
	// ESTRUTURA DA MATRIZ:
	
    // CAMINH0 NO VETOR (ESQUERDA -> DIREITA)
	for( j = 0; j < colunas; j++ )        
		
		// CRIANDO COLUNAS NA MATRIZ
        vector[j] = LST_CriarLista ();  
	
	// DESCENDO COM A LISTA M-LINHAS ABAIXO
	for( i = 0; i < linhas; i++)    
		
		if( LST_InserirNovoNoFim( vector[j] , NULL ) != LST_CondRetOK)
			
			return MAT_CondRetMatrizInexistente;


matriz -> m = linhas;
matriz -> n = colunas;
matriz -> mat = vector;


return MAT_CondRetOK;

}



// INSERIR NOVO ELEMENTO NA 1ª POSICAO VAZIA DA MATRIZ QUE ENCONTRAR:

MAT_tpCondRet MAT_InserirNovoElemento(TpMatriz* matriz, void* novo) 
{
	
	int i, j; // ELEMENTO A(ij)
	
	
	// COLOQUEI O NO CORRENTE NA ORIGEM DA LISTA
	if( AjusteNoCorrente( matriz ) != MAT_CondRetOK)
		return MAT_CondRetValorNaoInserido;
	
	// FIXO A LINHA
	for( i = 0 ; i < matriz -> m; i++) 
		
		// PERCORRO PELAS COLUNAS		
		for( j = 0; j < matriz -> n; j++) 
			
			// ENCONTREI UM NO VAZIO
			if( LST_AlterarValor(matriz -> mat[j], NULL) != LST_CondRetOK) 
				return MAT_CondRetValorNaoInserido;
	
	// NAO ENCONTREI E AVANCEI UMA POSICAO DO NO CORRENTE NESSA COLUNA
			else if( LST_Avancar( matriz -> mat[j], 1 ) !=  LST_CondRetOK)
				return MAT_CondRetValorNaoInserido;
	
	return MAT_CondRetOK;
}




// ALTERAR VALOR DE UM ELEMENTO DA MATRIZ:
MAT_tpCondRet MAT_AlterarValor( TpMatriz* matriz, void* elem_subst, int linha, int coluna) 
{
	
	
	// COLOQUEI O NO CORRENTE NA ORIGEM DA LISTA
	if( AjusteNoCorrente( matriz ) != MAT_CondRetOK)
		return MAT_CondRetValorInalterado;
	
	if(LST_Avancar( matriz -> mat[coluna], linha - 1)  != 0 )
		return MAT_CondRetValorInalterado;
	
	
	if (LST_AlterarValor( matriz -> mat[coluna] , elem_subst ) != 0)
		return MAT_CondRetValorInalterado;
	
	
	return MAT_CondRetOK;		
	
	
}



// DESTRUIR MATRIZ
MAT_tpCondRet MAT_DestruirMatriz( TpMatriz* matriz) 
{
	
	int j;
	
	for( j = 0; j < matriz -> n; j++)
		if ( LST_DestruirLista( matriz -> mat[j] ) != LST_CondRetOK)
			return MAT_CondRetMatrizIntacta;
	
	
	return MAT_CondRetOK;
	
}




// ESVAZIAR MATRIZ
MAT_tpCondRet MAT_EsvaziarMatriz( TpMatriz* matriz ) 
{
	
	int i, j;
	
	// COLOQUEI O NO CORRENTE NA ORIGEM DA LISTA
	if( AjusteNoCorrente( matriz ) != MAT_CondRetOK)
		return MAT_CondRetFalhou;
	
	
	for( j = 0; j < matriz -> m; j++)
		
		for( i = 0; i < matriz ->n; i++) {
			
			if( LST_AlterarValor(matriz -> mat[j], NULL) != LST_CondRetOK)
				return MAT_CondRetMatrizCheia;
			
			else if ( LST_Avancar( matriz -> mat[j], 1)  != LST_CondRetOK)
					return MAT_CondRetMatrizCheia;
		}
	
	return MAT_CondRetOK;
}




// MAPEAR AS POSICOES (I E J) DO ELEMENTO DADO
MAT_tpCondRet MAT_ObterPosicaoElemento( TpMatriz* matriz, void* elem_dado, int* num_linha, int* num_coluna ) 
{
	
	int i , j; // elemento a(ij)
	
	for( j = 0; j < matriz -> n; j++) 
		
		for( i = 0; i < matriz -> m; i++)
			
			if( LST_Busca( matriz -> mat [j] , elem_dado) == LST_CondRetOK) {
				
				*num_linha = i + 1;
				
				*num_coluna = j + 1; 
				
				return MAT_CondRetOK;
				
			}
	
	
	return MAT_CondRetPosicaoInvalida;
	
}




// MAPEAR O ELEMENTO A PARTIR DE SUAS POSICOES I E J DADAS
MAT_tpCondRet MAT_ObterElemento( TpMatriz* matriz, void* elem_procurado, int linha, int coluna) 
{ 
	
	int i, j; 
	
	// AJUSTE DA POSICAO DO NO CORRENTE PARA A ORIGEM DAS COLUNAS/LISTAS
	if( AjusteNoCorrente( matriz ) != MAT_CondRetOK)
		return MAT_CondRetElementoInexistente;
	
	
	for( j = 0; j < matriz -> n; j++) 
		
		for( i = 0; i < matriz -> m; i++) 
			
			if( i == linha - 1 && j == coluna - 1 ) {
				
				 if (( matriz -> mat[j] , elem_procurado ) == LST_CondRetOK)
					 return MAT_CondRetOK;
				
			}
	
			else if( (LST_Avancar( matriz -> mat[j], 1) ) != LST_CondRetOK)
				return MAT_CondRetElementoInexistente;
	
	
	return MAT_CondRetElementoInexistente;
	
}




// AJUSTE DA POSICAO DO NO CORRENTE PARA A ORIGEM DAS COLUNAS/LISTAS:
static MAT_tpCondRet AjusteNoCorrente( TpMatriz* matriz ) {
	
	int j;
	
	if( matriz == NULL)
		return MAT_CondRetFaltouMemoria;
	else 
		for( j = 0; j < matriz -> n; j++)  
			if ( LST_IrInicio( matriz -> mat[j] ) != LST_CondRetOK)
				return MAT_CondRetFalhou;
	
	return MAT_CondRetOK;
	
}


