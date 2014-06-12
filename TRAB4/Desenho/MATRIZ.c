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
*		4.00   ps      01/jun/2014  Instrumentação incluída
*		3.00  ps/mbv   28/mai/2014  Deturpação e mudança para auto-verificável
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

#ifdef _DEBUG
#include "CONTA.H"
#include "CESPDIN.H"
#endif


/***********************************************************************
*
*  $TC Tipo de dados: MAT Matriz.
*
*
*  $ED Descrição do tipo
*  
*   Estrutura que define um vetor de ponteiros para listas genéricas
*  duplamente encadeadas e guarda informação sobre a ordem da matriz
*  nos valores inteiros 'm'e 'n'. Ordem da matriz m x n.
*   
***********************************************************************/


struct tpMatriz {         

	int m;
	/* Numero de linhas da matriz. */

	int n;              
	/*  Numero de colunas da matriz. */

	TpLista** mat;
	/* Vetor de ponteiro para lista. */

#ifdef _DEBUG
	char tipoElemento;
#endif

};


/***** Protótipo das função encapulada no módulo *****/

static MAT_tpCondRet AjusteNoCorrente( TpMatriz* matriz );


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MAT Criar Matriz.
*  ****/

TpMatriz* MAT_CriarMatriz( int linhas, int colunas
#ifdef _DEBUG
	,char tipoElemento
#endif
	)
{

	int i, j; 
	/* elemento qualquer A(ij) : linha "i" coluna "j". */

	TpLista** vector;

	TpMatriz* matriz;


	matriz = (TpMatriz*)malloc(sizeof(TpMatriz));
#ifdef _DEBUG
	CED_MarcarEspacoAtivo(matriz);
#endif
	/* Aloca espaço para a matriz */


	if ( linhas <=0 || colunas <= 0)
	{
		return NULL;
	} /* if */

	if( matriz == NULL)
	{   
		printf ( " Espaço na memória insuficiente " ) ;

		return NULL;

	} /* if */


	vector = ( TpLista** )malloc(sizeof( TpLista* )*colunas );
	/* Aloca espaço para o vetor de ponteiros */


	if( vector == NULL) {

		printf ( " Espaço na memória insuficiente " ) ;

		return NULL;

	} /* if */
#ifdef _DEBUG
	CED_MarcarEspacoAtivo(vector);
#endif

	for( j = 0; j < colunas; j++ ){
		/* Percorrendo o vetor de ponteiros */

		vector[j] = LST_CriarLista ( 
#ifdef _DEBUG
			tipoElemento
#endif
			);
		/* Criando as colunas da matriz */

		for( i = 0; i < linhas; i++){
			/* Criando as linhas da matriz */

			if( LST_InserirNovoNoFim( vector[j] , NULL
#ifdef _DEBUG
				,tipoElemento
#endif
				) != LST_CondRetOK)

			{
				return NULL;
			}/* if */
		} /*for*/
	}/* for */

	matriz -> m = linhas;
	matriz -> n = colunas;
	matriz -> mat = vector;


	return matriz;

}/* Fim função: MAT Criar Matriz*/


/***************************************************************************
*
*  Função: MAT Inserir novo elemento na matriz.
*  ****/



MAT_tpCondRet MAT_InserirNovoElemento(TpMatriz* matriz, void* novo 
#ifdef _DEBUG
	,char tipoElemento
#endif
	)
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


	for( i = 0 ; i < matriz -> m ; i++) {
		/* Fixando a linha */  

		for( j = 0; j < matriz -> n ; j++){
			/* Percorrendo as colunas */

			if(  LST_ObterValor( matriz-> mat[j]) == NULL ) {

				if( LST_AlterarValor( matriz -> mat[j] , novo
#ifdef _DEBUG
					,tipoElemento
#endif
					) != LST_CondRetOK ) {

						return MAT_CondRetValorNaoInserido;

				}/*if*/

				return MAT_CondRetOK;

			} /*if*/

			else if( LST_Avancar( matriz -> mat[j], 1 ) !=  LST_CondRetOK) {

				return MAT_CondRetValorNaoInserido;

			} /*if*/
		}
	}

	return MAT_CondRetValorNaoInserido;

} /* Fim função: Inserir novo elemento na matriz*/


/***************************************************************************
*
*  Função: MAT Alterar valor de um elemento da matriz.
*  ****/


MAT_tpCondRet MAT_AlterarValor( TpMatriz* matriz, void* elem_subst, int linha, int coluna
#ifdef _DEBUG
	,char tipoElemento
#endif
	)
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

	if (LST_AlterarValor( matriz -> mat[coluna] , elem_subst
#ifdef _DEBUG
		, tipoElemento
#endif
		) != LST_CondRetOK) {

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
*  Função: MAT Destruir Matriz
*  ****/


MAT_tpCondRet MAT_DestruirMatriz( TpMatriz* matriz, void ( * ExcluirValor) ( void * pDado) )
{

	int j;
	/* coluna da matriz. */

	for( j = 0; j < matriz -> n; j++){

		if ( LST_DestruirLista( matriz -> mat[j], ExcluirValor ) != LST_CondRetOK) {

			return MAT_CondRetMatrizIntacta;

		}/*if*/
	}
#ifdef _DEBUG
	CED_MarcarEspacoNaoAtivo(matriz->mat);
#endif
	free ( matriz -> mat );

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
*     para a primeira linha.
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

	}/*if*/            

	return MAT_CondRetOK;  

} /* Fim função: Ajustar nó corrente das colunas*/

#ifdef _DEBUG


/***********************************************************************
*
*  $FC Função: MAT Altera Ponteiro Sucessor
*
***********************************************************************/

void MAT_AlteraPonteiroSucessor( TpMatriz* matriz, int linha, int coluna, void* elem )
{
	LST_IrInicio( matriz->mat[coluna] );
	LST_Avancar( matriz->mat[coluna], linha );
	LST_AlteraPonteiroSucessor( matriz->mat[coluna], elem );
} /* Fim função: MAT Altera Ponteiro Sucessor */


/***********************************************************************
*
*  $FC Função: MAT Altera Ponteiro Predecessor
*
***********************************************************************/

void MAT_AlteraPonteiroPredecessor( TpMatriz* matriz, int linha, int coluna, void* elem )
{
	LST_IrInicio( matriz->mat[coluna] );
	LST_Avancar( matriz->mat[coluna], linha );
	LST_AlteraPonteiroPredecessor( matriz->mat[coluna], elem );
} /* Fim função: MAT Altera Ponteiro Predecessor */


/***********************************************************************
*
*  $FC Função: MAT Free Incompleto
*
***********************************************************************/

void MAT_FreeIncompleto (TpMatriz* matriz)
{
	AjusteNoCorrente( matriz );

	LST_Avancar(matriz->mat[0], 2);//Coordenada (1,2)

	LST_LiberarNoCorrente( matriz->mat[0], NULL, 0 );

} /* Fim função: MAT Free Incompleto */



/***********************************************************************
*
*  $FC Função: MAT Verifica Assertiva Linhas e Colunas
*
***********************************************************************/

int MAT_VerificaAssertivaLinhaColuna (TpMatriz* matriz)
{
	
	if ( matriz -> m > 0 && matriz ->n > 0 )
	{
		CNT_CONTAR("MAT_AssertivaLinhaColuna_OK");
		return 0;
	} /* if */
	CNT_CONTAR("MAT_AssertivaLinhaColuna_Erro");
	return 1;

} /* Fim função: MAT Verifica Assertiva Linhas e Colunas */


/***********************************************************************
*
*  $FC Função: MAT Verifica Assertiva Ponteiro Lista
*
***********************************************************************/

int MAT_VerificaAssertivaPontLista (TpMatriz* matriz)
{
	int i=0;
	int numErros = 0;

	if( matriz -> mat != NULL )
	{
		CNT_CONTAR("MAT_AssertivaPonteiroLista_MatrizNaoNula");
		while ( i <= matriz -> m )
		{
			CNT_CONTAR("MAT_AssertivaPonteiroLista_While");
			if ( matriz -> mat[i] == NULL ){
				CNT_CONTAR("MAT_AssertivaPonteiroLista_Nulo");
				numErros++;
			} else {
				CNT_CONTAR("MAT_AssertivaPonteiroLista_OK");
			}

			i++;
		}
	} else {
		CNT_CONTAR("MAT_AssertivaPonteiroLista_MatrizNula");
	}
	return numErros;
} /* Fim função: MAT Verifica Assertiva Ponteiro Lista */

/***********************************************************************
*
*  $FC Função: MAT Verifica Assertiva Listas
*
***********************************************************************/

int MAT_VerificaAssertivaListas (TpMatriz* matriz)
{
	int i=0;
	int numErros = 0;

	if( matriz -> mat != NULL )
	{
		CNT_CONTAR("MAT_AssertivaListas_MatrizNaoNula");
		while ( i < matriz -> m )
		{
			int numElem = LST_RetornaNumElementos( matriz -> mat[i] );
			CNT_CONTAR("MAT_AssertivaListas_While");
			if(numElem == 0)
			{

				if( LST_VerificaAssertivaListaVazia( matriz->mat[i] ) )
				{
					printf("\nErro na assertiva Lista Vazia da coluna %d\n", i);
					CNT_CONTAR("MAT_AssertivaListas_ListaVazia_ComErros");
					numErros++;
				} else 
				{
					CNT_CONTAR("MAT_AssertivaListas_ListaVazia_Ok");
				}/* if */


			}
			else if( numElem == 1 )
			{

				if( LST_VerificaAssertivaListaElemUnico( matriz->mat[i] ))
				{
					printf("\nErro na assertiva Lista com 1 elemento da coluna %d\n", i);
					CNT_CONTAR("MAT_AssertivaListas_ListaUmElemento_ComErros");
					numErros++;
				} else 
				{
					CNT_CONTAR("MAT_AssertivaListas_ListaUmElemento_Ok");
				}/* if */


			} else 
			{

				if(LST_VerificaAssertivaProx( matriz->mat[i] ))
				{
					printf("\nErro na assertiva do ponteiro pProx da coluna %d\n", i);
					CNT_CONTAR("MAT_AssertivaListas_ListaVariosElementos_Prox_ComErros");
					numErros++;
				} else 
				{
					CNT_CONTAR("MAT_AssertivaListas_ListaVariosElementos_Prox_Ok");
				}/* if */



				if(LST_VerificaAssertivaAnt( matriz->mat[i] ))
				{
					printf("\nErro na assertiva do ponteiro pAnt da coluna %d\n", i);
					CNT_CONTAR("MAT_AssertivaListas_ListaVariosElementos_Ant_ComErros");
					numErros++;
				} else 
				{
					CNT_CONTAR("MAT_AssertivaListas_ListaVariosElementos_Ant_Ok");
				}/* if */



				if(LST_VerificaAssertivaTipoListaElementos( matriz->mat[i] ))
				{
					printf("\nErro na assertiva de tipos de conteudo da lista %d\n", i);
					CNT_CONTAR("MAT_AssertivaListas_ListaVariosElementos_Tipos_ComErros");
					numErros++;
				} else 
				{
					CNT_CONTAR("MAT_AssertivaListas_ListaVariosElementos_Tipos_Ok");
				}/* if */


			}/* if */
			i++;
		}/* while */

	} else 
	{
		CNT_CONTAR("MAT_AssertivaListas_MatrizNula");
	}
	return numErros;
} /* Fim função: MAT Verifica Assertiva Listas */



#endif




/********** Fim do módulo de implementação: Módulo MATRIZ **********/
