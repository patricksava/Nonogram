/***************************************************************************
 *  $MCI Módulo de implementação: Módulo Matriz
 *
 *  Arquivo gerado:              Matriz.c
 *  Letras identificadoras:      MAT
 *
 *  Projeto: Disciplinas INF 1301
 *  Gestor:  DI/PUC-Rio
 *  Autores: lm- Leandro Morgado
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data         Observações
 *       2.00   lm      12/abr/2014  Revisão e conclusão do código
 *       1.00   lm      11/abr/2014  Início do desenvolvimento
 *
 *************************************************************************
 * ***/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MATRIZ.h"
#include "LISTA.h"



/***********************************************************************
 *
 *  $TC Tipo de dados: MAT Matriz.
 *
 *
 *  $ED Descrição do tipo
 *	
 *	Estrutura que define um vetor de ponteiros para listas genéricas e 
 *  guarda informação sobre a ordem da matriz nos valores inteiros 'm'
 *  e 'n'. Ordem da matriz m x n.
 *	 
 ***********************************************************************/


struct tpMatriz {          
	
	int m;
	/* Numero de linhas da matriz. */ 
	
	int n;               
	/*  Numero de colunas da matriz. */ 
	
	TpLista** mat;
	/* Vetor de ponteiro para lista. */ 
	
};


/***** Protótipo das função encapulada no módulo *****/

	 static MAT_tpCondRet AjusteNoCorrente( TpMatriz* matriz );


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: MAT Criar Matriz.
 *  ****/

TpMatriz* MAT_CriarMatriz( int linhas, int colunas )
{
    
	int i, j;  
	/* elemento qualquer A(ij) : linha "i" coluna "j". */
	
	TpLista** vector;
	
	TpMatriz* matriz; 
	
	
    matriz = (TpMatriz*)malloc(sizeof(TpMatriz)); 
	/* Aloca espaço para a matriz */
	
	
	if( matriz == NULL)
    {    
		printf ( " Espaço na memória insuficiente " ) ;
		
		return NULL;
	
	} /* if */
	
	
    vector = (TpLista**)malloc(sizeof(TpLista*)*colunas);
 	/* Aloca espaço para o vetor de ponteiros */
    	
	
	if( vector == NULL) {
        
		printf ( " Espaço na memória insuficiente " ) ;
		
		return NULL;
	
    } /* if */
	
	
	for( j = 0; j < colunas; j++ )
	/* Percorrendo o vetor de ponteiros */ 
		
        vector[j] = LST_CriarLista (); 
		/* Criando as colunas da matriz */
	
	for( i = 0; i < linhas; i++)
	/* Criando as linhas da matriz */
		
		if( LST_InserirNovoNoFim( vector[j] , NULL ) != LST_CondRetOK)
			
			return NULL;


	matriz -> m = linhas;
	matriz -> n = colunas;
	matriz -> mat = vector;


	return matriz;

}/* Fim função: MAT Criar Matriz*/


/***************************************************************************
 *
 *  Função: MAT Inserir novo elemento na matriz.
 *  ****/


MAT_tpCondRet MAT_InserirNovoElemento(TpMatriz* matriz, void* novo) 
{
	
	int i, j;
	/* elemento qualquer A(ij) : linha "i" coluna "j". */
	
	
	if( matriz == NULL)
    {    
		printf ( " Matriz vazia " ) ;
		
		return MAT_CondRetMatrizInexistente;
		
	} /* if */
	
	
		
	if( AjusteNoCorrente( matriz ) != MAT_CondRetOK) {
		
		return MAT_CondRetValorNaoInserido;
	
	} /*if*/	
		
	
	for( i = 0 ; i < matriz -> m; i++) 
	/* Fixando a linha */ 	
				
		for( j = 0; j < matriz -> n; j++)
		/* Percorrendo as colunas */
			
			if( LST_AlterarValor(matriz -> mat[j], NULL) != LST_CondRetOK) { 
				
				return MAT_CondRetValorNaoInserido;
			} /*if*/
				
			else if( LST_Avancar( matriz -> mat[j], 1 ) !=  LST_CondRetOK) {
				
				return MAT_CondRetValorNaoInserido;
			} /*if*/
				
	return MAT_CondRetOK;

} /* Fim função: Inserir novo elemento na matriz*/


/***************************************************************************
 *
 *  Função: MAT Alterar valor de um elemento da matriz.
 *  ****/


MAT_tpCondRet MAT_AlterarValor( TpMatriz* matriz, void* elem_subst, int linha, int coluna) 
{
	
	
	if( matriz == NULL)
    {    
		printf ( " Matriz vazia " ) ;
		
		return MAT_CondRetMatrizInexistente;
		
	} /* if */
	
	
	
	if( AjusteNoCorrente( matriz ) != MAT_CondRetOK) {
		
		return MAT_CondRetValorInalterado;
	}/*if*/
		
	if(LST_Avancar( matriz -> mat[coluna], linha)  != LST_CondRetOK) {
		
		return MAT_CondRetValorInalterado;
	}/*if*/
	
	if (LST_AlterarValor( matriz -> mat[coluna] , elem_subst ) != LST_CondRetOK) {
		
		return MAT_CondRetValorInalterado;
	}/*if*/
	
	return MAT_CondRetOK;		
		
} /* Fim função: MAT Alterar valor de um elemento da matriz*/


/***************************************************************************
 *
 *  Função: MAT Mapear elemento na matriz.
 *  ****/

void* MAT_ObterElemento( TpMatriz* matriz, int linha, int coluna) 
{ 
		
	if( matriz == NULL) {
       
		return NULL;
		
	} /* if */
		
	
	if( AjusteNoCorrente( matriz ) != MAT_CondRetOK) {
		
		return NULL;
	}/*if*/
	
	if( (LST_Avancar( matriz -> mat[coluna], linha) ) != LST_CondRetOK) {
		
		return NULL;
	}/*if*/
				
	return LST_ObterValor( matriz -> mat[coluna] );			
} /* Fim função: MAT Mapear elemento na matriz.*/

/***************************************************************************
 *
 *  Função: MAT Esvaziar matriz.
 *  ****/


MAT_tpCondRet MAT_EsvaziarMatriz( TpMatriz* matriz, void ( * ExcluirValor) ( void * pDado)  ) 
{
	
	int j;
	/* elemento qualquer A(ij) : linha "i" coluna "j". */
	
	
	if( matriz == NULL)
    {    
		printf ( " Matriz vazia " ) ;
		
		return MAT_CondRetMatrizInexistente;
		
	} /* if */ 
	
	
	for( j = 0; j < matriz -> m; j++)
		
		LST_EsvaziarLista( matriz -> mat[j],  ExcluirValor );
	
	return MAT_CondRetOK;

} /* Fim função: MAT Mapear elemento na matriz.*/



/***************************************************************************
 *
 *  Função: MAT Destruir Matriz
 *  ****/


MAT_tpCondRet MAT_DestruirMatriz( TpMatriz* matriz, void ( * ExcluirValor) ( void * pDado) ) 
{
	
	int j;
	/* coluna da matriz. */
	
	for( j = 0; j < matriz -> n; j++)
		
		if ( LST_DestruirLista( matriz -> mat[j], ExcluirValor ) != LST_CondRetOK) {
			
			return MAT_CondRetMatrizIntacta;
		
		}/*if*/
	
	return MAT_CondRetOK;
	
} /* Fim função: MAT Destruir Matriz.*/


/***************************************************************************
 
 
 
 /*****  Código das função encapsulada no módulo  *****/


/***********************************************************************
 *
 *  $FC Função: MAT Ajustar nó corrente das colunas
 *
 *  $ED Descrição da função
 *    Ajusta o nó corrente de todas as colunas da matriz
 *	  para a primeira linha.
 *
 ***********************************************************************/


static MAT_tpCondRet AjusteNoCorrente( TpMatriz* matriz ) {
	
	int j;
	
	if( matriz == NULL) {
		
		return MAT_CondRetMatrizInexistente;
	
	} else 
	{	
		for( j = 0; j < matriz -> n; j++)  
			
			if ( LST_IrInicio( matriz -> mat[j] ) != LST_CondRetOK) {
				
				return MAT_CondRetFalhou;
			
			}/*if*/
	
	}/*if/				
	
	 return MAT_CondRetOK;	

} /* Fim função: Ajustar nó corrente das colunas


/********** Fim do módulo de implementação: Módulo MATRIZ **********/

