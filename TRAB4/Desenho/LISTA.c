/***************************************************************************
*  $MCI Módulo de implementação: Módulo Lista Genérica
*
*  Arquivo gerado:              ListaGenerica.c
*  Letras identificadoras:      LST
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mbv- Maria Beatriz Vaz
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data        Observações
*		4.00   mbv,ps 01/jun/2014 Instrumentação incluída
*		3.00   mbv    14/abr/2014 Revisão geral do código e dos comentários
*       2.00   mbv    12/abr/2014 Revisão e adaptação do código
*       1.00   mbv    19/mar/2014 Início do desenvolvimento
*
****************************************************************************/

#include   <stdlib.h>
#include   <stdio.h>
#include   <string.h>

#include "LISTA.h"

#ifdef _DEBUG

#include "CONTA.H"
#include "CESPDIN.H"

#endif


/***********************************************************************
*
*  $TC Tipo de dados: LST Nó da Lista.
*
*
*  $ED Descrição do tipo
*	
*	Estrutura que define um nó (elemento) de uma Lista Genérica.
*	Nele está contido um ponteiro para o valor que o nó armazena 
*	(do tipo void), um ponteiro para o nó sucessor e um ponteiro
*	para o nó anterior.
*
***********************************************************************/

struct tpNoLista {

	void * pValor ;
	/* Ponteiro para o valor contido no elemento. */

	struct tpNoLista * pAnt ;
	/* Ponteiro para o elemento anterior. */

	struct tpNoLista * pProx ;
	/* Ponteiro para o próximo elemento. */
#ifdef _DEBUG
	char tipoElemento;
#endif
} ;


typedef struct tpNoLista TpNoLista;

/***********************************************************************
*
*  $TC Tipo de dados: LST Cabeça da Lista.
*
*
*  $ED Descrição do tipo
*	
*	Estrutura que define a cabeça de uma lista.
*	Possui um ponteiro para o nó do início da lista,
*	um ponteiro para o nó do fim da lista e um ponteiro
*	para o elemento corrente. Além disso, possui o número
*	de elementos que a lista contém.
*
***********************************************************************/

struct tpLista {

	TpNoLista * pOrigemLista ;
	/* Ponteiro para a origem da lista. */

	TpNoLista * pFimLista ;
	/* Ponteiro para o fim da lista. */

	TpNoLista * pNoCorrente ;
	/* Ponteiro para o nó corrente. */

	int numElementos;
	/* Indica a quantidade de elementos na lista. */

#ifdef _DEBUG
	char tipoElemento;
#endif
} ;

/***** Protótipos das funções encapuladas no módulo *****/

static void LiberarNo( TpLista * pLista , TpNoLista * pElem,  void ( * ExcluirValor) ( void * pDado)  ) ;

static  TpNoLista * CriarElemento( TpLista * pLista , void * pValor 
#ifdef _DEBUG
	, char tipoElemento
#endif 
	);

static void LimparCabeca( TpLista * pLista 
#ifdef _DEBUG
	, char tipoElem
#endif
	);

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LST Criar lista genérica duplamente encadeada.
*
****************************************************************************/

TpLista * LST_CriarLista ( 
#ifdef _DEBUG
	char tipoElem
#endif
	)
{
	TpLista * pLista;

	pLista = ( TpLista * )malloc( sizeof( TpLista )) ;
	/* alocar espaço para lista */

	if ( pLista== NULL )
	{
		printf ( " Espaço na memória insuficiente " ) ;
		return NULL ;
	} /* if */

#ifdef _DEBUG
	CED_MarcarEspacoAtivo( pLista );
#endif

	LimparCabeca( pLista 
#ifdef _DEBUG
		, tipoElem
#endif
		) ; 
	/*zerar todos os campos da estrutura.*/

	return pLista ;

} /* Fim função: LST Criar lista genérica duplamente encadeada*/

/***************************************************************************
*
*  Função: LST Esvaziar lista duplamente encadeada.
*  ****/

void LST_EsvaziarLista( TpLista * pLista , void ( * ExcluirValor) ( void * pDado)  )
{
	TpNoLista * pElem ;
	TpNoLista * pProx ;

	if ( pLista == NULL)
	{
		return;
	} /* if */

	pLista->pNoCorrente = pLista->pOrigemLista ;
	while ( pLista->pNoCorrente != NULL )
	{
		pElem = pLista->pNoCorrente;
		pLista ->pNoCorrente = pLista->pNoCorrente->pProx;

		LiberarNo( pLista , pElem, ExcluirValor ) ;
	} /* while */


	LimparCabeca ( pLista 
#ifdef _DEBUG
		, ' '
#endif
		);
	pLista->pNoCorrente=NULL;

} /* Fim função: LST Esvaziar lista duplamente encadeada*/

/***************************************************************************
*
*  Função: LST Destruir lista duplamente encadeada.
*  ****/

LST_tpCondRet LST_DestruirLista( TpLista * pLista, void ( * ExcluirValor) ( void * pDado)  )
{

	if ( pLista == NULL)
	{
		return LST_CondRetListaInexistente;
	} /* if */

	LST_EsvaziarLista ( pLista , ExcluirValor );

#ifdef _DEBUG
	CED_MarcarEspacoNaoAtivo( pLista );
#endif
	free ( pLista );
	return LST_CondRetOK;

} /* Fim função: LST Destruir lista duplamente encadeada*/

/***************************************************************************
*
*  Função: LST Adicionar novo nó no inicio da lista duplamente encadeada.
*  ****/

LST_tpCondRet LST_InserirNovoNoInicio( TpLista * pLista , void * informacao
#ifdef _DEBUG
	, char tipoElemento
#endif
	)
{
	LST_tpCondRet CondRet;

	if ( pLista->pNoCorrente != NULL )
	{
		CondRet = LST_IrInicio ( pLista );
	} /* if */

	return LST_InserirNoAntes ( pLista, informacao 
#ifdef _DEBUG
		, tipoElemento
#endif
		);
}


/* Fim função: LST Adicionar novo nó no inicio da lista duplamente encadeada*/

/***********************************************************************************
*
*  Função: LST Adicionar novo nó no fim da lista duplamente encadeada.
*  ****/

LST_tpCondRet LST_InserirNovoNoFim( TpLista * pLista , void * informacao 
#ifdef _DEBUG
	, char tipoElemento
#endif
	)
{

	LST_tpCondRet CondRet;

	if ( pLista->pNoCorrente != NULL )
	{
		CondRet = LST_IrFim ( pLista );
	} /* if */

	return LST_InserirNoApos ( pLista, informacao 
#ifdef _DEBUG
		, tipoElemento
#endif
		);
}

/* Fim função: LST Adicionar novo nó no fim da lista duplamente encadeada. */

/***************************************************************************
*
*  Função: LST Inserir elemento antes do nó corrente.
*  ****/

LST_tpCondRet LST_InserirNoAntes( TpLista * pLista , void * informacao 
#ifdef _DEBUG
	, char tipoElemento
#endif
	)
{

	TpNoLista * pElem ;

	if ( pLista == NULL )
	{
		return LST_CondRetListaInexistente;
	} /* if */

	/* Criar elemento a inerir antes */

	pElem = CriarElemento( pLista , informacao 
#ifdef _DEBUG
		, tipoElemento
#endif
		) ;
	if ( pElem == NULL )
	{
		return LST_CondRetFaltouMemoria ;
	} /* if */

	/* Encadear o elemento antes do elemento corrente */

	/*Se a lista está vazia*/
	if ( pLista->pNoCorrente == NULL )
	{
		pLista->pOrigemLista = pElem ;
		pLista->pFimLista = pElem ;
	} else
	{
		/* Se é o nó corrente é o nó origem */
		if ( pLista->pNoCorrente->pAnt != NULL )
		{
			pElem->pAnt  = pLista->pNoCorrente->pAnt ;
			pLista->pNoCorrente->pAnt->pProx= pElem ;
		} else
		{
			pLista->pOrigemLista = pElem ;
		} /* if */

		pElem->pProx = pLista->pNoCorrente ;
		pLista->pNoCorrente->pAnt = pElem ;
	} /* if */

	pLista->pNoCorrente = pElem ;

	return LST_CondRetOK ;

} /* Fim função: LST  Inserir elemento antes */

/***************************************************************************
*
*  Função: LST  Inserir elemento após
*  ****/

LST_tpCondRet LST_InserirNoApos( TpLista * pLista , void * informacao 
#ifdef _DEBUG
	, char tipoElemento
#endif
	)
{

	TpNoLista * pElem ;

	if ( pLista == NULL)
	{
		return LST_CondRetListaInexistente;
	} /* if */

	/* Criar elemento a inerir após */

	pElem = CriarElemento( pLista , informacao 
#ifdef _DEBUG
		, tipoElemento
#endif
		) ;
	if ( pElem == NULL )
	{
		return LST_CondRetFaltouMemoria ;
	} /* if */

	/* Encadear o elemento após o elemento */

	/*Se a lista está vazia */
	if ( pLista->pNoCorrente == NULL )
	{
		pLista->pOrigemLista = pElem ;
		pLista->pFimLista = pElem ;
	} else
	{
		/* Se o nó corrente é o nó fim */
		if ( pLista->pNoCorrente->pProx != NULL )
		{
			pElem->pProx  = pLista->pNoCorrente->pProx ;
			pLista->pNoCorrente->pProx->pAnt = pElem ;
		} else
		{
			pLista->pFimLista = pElem ;
		} /* if */

		pElem->pAnt = pLista->pNoCorrente ;
		pLista->pNoCorrente->pProx = pElem ;

	} /* if */

	pLista->pNoCorrente = pElem ;

	return LST_CondRetOK ;

} /* Fim função: LST  Inserir elemento após */

/**********************************************************************************
*
*  Função: LST Liberar nó corrente.
*  ****/

LST_tpCondRet LST_LiberarNoCorrente( TpLista * pLista , void ( * ExcluirValor) ( void * pDado)  
#ifdef _DEBUG
	, int liberar
#endif
	)
{

	TpNoLista * pElem ;

	if ( pLista == NULL )
	{
		return LST_CondRetListaInexistente;
	}

	if ( pLista->pNoCorrente == NULL )
	{
		return LST_CondRetListaVazia ;
	} /* if */

	pElem = pLista->pNoCorrente ;

	/* Desencadeia à esquerda */

	if ( pElem->pAnt != NULL )
	{
		pElem->pAnt->pProx  = pElem->pProx ;
		pLista->pNoCorrente = pElem->pAnt ;
	} else {
		pLista->pNoCorrente    = pElem->pProx ;
		pLista->pOrigemLista = pLista->pNoCorrente ;
	} /* if */

	/* Desencadeia à direita */

	if ( pElem->pProx != NULL )
	{
		pElem->pProx->pAnt = pElem->pAnt ;
	} else
	{
		pLista->pFimLista = pElem->pAnt ;
	} /* if */


#ifdef _DEBUG
	if(liberar)
#endif
		LiberarNo( pLista , pElem, ExcluirValor ) ;


	return LST_CondRetOK ;

} 

/* Fim função: LST Liberar nó corrente*/

/**********************************************************************************

*
*  Função: LST obter a informação contida no nó corrente.
*  ****/

void * LST_ObterValor( TpLista * pLista ) 
{

	if ( pLista == NULL)
	{
		return NULL;

	} /* if */

	if ( pLista->pNoCorrente == NULL )
	{
		return NULL ;
	} /* if */

	if ( pLista->pNoCorrente->pValor == NULL )
	{
		return NULL;
	} /* if */

	return pLista->pNoCorrente->pValor;

} /* Fim função: LST obter a informação contida no nó corrente. */

/**********************************************************************************
*
*  Função: LST alterar a informação contida no nó corrente.
*  ****/

LST_tpCondRet LST_AlterarValor( TpLista * pLista , void * informacao 
#ifdef _DEBUG
	,char tipoElemento
#endif
	) 
{

	if ( pLista == NULL)
	{
		return LST_CondRetListaInexistente;

	} /* if */

	pLista->pNoCorrente->pValor = informacao;
#ifdef _DEBUG
	pLista->pNoCorrente->tipoElemento = tipoElemento;
#endif
	return LST_CondRetOK;
}

/* Fim função: LST alterar a informação contida no nó corrente*/

/**********************************************************************************
*
*  Função: LST Ir para o inicio da lista duplamente encadeada.
*  ****/

LST_tpCondRet LST_IrInicio( TpLista * pLista )
{
	if ( pLista == NULL )
	{
		return LST_CondRetListaInexistente;
	} /* if */

	pLista->pNoCorrente = pLista->pOrigemLista;

	return LST_CondRetOK;
}

/* Fim função: LST Ir para o inicio da lista duplamente encadeada.    */

/**********************************************************************************
*
*  Função: LST Ir para o fim da lista duplamente encadeada.
*  ****/

LST_tpCondRet LST_IrFim( TpLista * pLista )
{
	if ( pLista == NULL )
	{
		return LST_CondRetListaInexistente;
	} /* if */

	pLista->pNoCorrente = pLista->pFimLista;

	return LST_CondRetOK;
}

/* Fim função: LST Ir para o fim da lista duplamente encadeada.    */


/***************************************************************************
*
*  Função: LST  Avançar elemento
*  ****/

LST_tpCondRet LST_Avancar( TpLista * pLista , int numElem )
{

	int i ;

	TpNoLista * pElem ;

	if ( pLista == NULL)
	{
		return LST_CondRetListaInexistente;

	} /* if */

	/* Tratar lista vazia */

	if ( pLista->pNoCorrente == NULL )
	{

		return LST_CondRetListaVazia ;

	} /* fim ativa: Tratar lista vazia */

	/* Tratar avançar para frente */

	if ( numElem > 0 )
	{

		pElem = pLista->pNoCorrente ;
		for( i = numElem ; i > 0 ; i-- )
		{
			if ( pElem == NULL )
			{
				break ;
			} /* if */

			pElem    = pElem->pProx ;
		} /* for */

		if ( pElem != NULL )
		{
			pLista->pNoCorrente = pElem ;
			return LST_CondRetOK ;
		} /* if */

		pLista->pNoCorrente = pLista->pFimLista ;
		return LST_CondRetFimLista ;

	} /* fim ativa: Tratar avançar para frente */

	/* Tratar avançar para trás */

	else if ( numElem < 0 )
	{

		pElem = pLista->pNoCorrente ;
		for( i = numElem ; i < 0 ; i++ )
		{
			if ( pElem == NULL )
			{
				break ;
			} /* if */
			pElem    = pElem->pAnt ;
		} /* for */

		if ( pElem != NULL )
		{
			pLista->pNoCorrente = pElem ;
			return LST_CondRetOK ;
		} /* if */

		pLista->pNoCorrente = pLista->pOrigemLista ;
		return LST_CondRetFimLista ;

	} /* fim ativa: Tratar avançar para trás */

	/* Tratar não avançar */

	return LST_CondRetOK ;

} /* Fim função: LST Avançar elemento */

/**********************************************************************************
*
*  Função: LST Busca informação.
*  ****/

LST_tpCondRet LST_Busca( TpLista * pLista , void * informacao, int ( Compara ) ( void * pDado, void * pDado2) )
{

	LST_tpCondRet CondRet = LST_CondRetOK ;

	if ( pLista == NULL)
	{
		return LST_CondRetListaInexistente;
	} /* if */

	if ( pLista->pNoCorrente == NULL )
	{
		return LST_CondRetListaVazia ;
	} /* if */

	CondRet = LST_IrInicio ( pLista );


	while ( CondRet == LST_CondRetOK  )
	{

		if (  Compara ( pLista->pNoCorrente->pValor , informacao ) == 0) 
		{
			return LST_CondRetOK ;
		} /* if */

		CondRet = LST_Avancar ( pLista, 1 ) ;

	} /* While */

	return LST_CondRetInfoNaoEncontrada ;
}

/* Fim função: LST Busca informação.    */

/**********************************************************************************
*
*  Função: LST Retorna Numero de Elementos.
*  ****/

int LST_RetornaNumElementos( TpLista * pLista )
{

	if ( pLista == NULL)
	{
		return 0;
	} /* if */

	return pLista->numElementos;
}

/* Fim função: LST Retorna Numero de Elementos.    */

/***************************************************************************



/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: LST  Liberar nó da lista
*
*  $ED Descrição da função
*     Elimina os espaços apontados pelo valor do nó e o
*     próprio nó.
*
***********************************************************************/

void LiberarNo( TpLista * pLista , TpNoLista * pElem, void ( * ExcluirValor) ( void * pDado) )
{

	if (( pElem != NULL ))
	{
		pElem->pAnt = pElem->pProx;
		ExcluirValor ( pElem->pValor ) ;

		pLista->numElementos = pLista->numElementos - 1;
#ifdef _DEBUG
		CED_MarcarEspacoNaoAtivo(pElem);
#endif
		free(pElem);
	} /* if */



} /* Fim função: LST Liberar No da lista */


/***********************************************************************
*
*  $FC Função: LST Criar o elemento
*
***********************************************************************/

TpNoLista * CriarElemento( TpLista * pLista , void * pValor 
#ifdef _DEBUG
	, char tipoElemento
#endif
	)
{

	TpNoLista * pElem ;

	pElem = ( TpNoLista * ) malloc( sizeof( TpNoLista )) ;
	if ( pElem == NULL )
	{
		return NULL ;
	} /* if */
#ifdef _DEBUG
	CED_MarcarEspacoAtivo( pElem );
#endif
	pElem->pValor = pValor ;
	pElem->pAnt   = NULL  ;
	pElem->pProx  = NULL  ;
#ifdef _DEBUG
	pElem->tipoElemento = tipoElemento;
#endif

	pLista->numElementos = pLista->numElementos + 1;

	return pElem ;

} /* Fim função: LST Criar o elemento */


/***********************************************************************
*
*  $FC Função: LST Limpar a cabeça da lista
*
***********************************************************************/

void LimparCabeca( TpLista * pLista 
#ifdef _DEBUG
	, char tipoElem
#endif
	)
{

	pLista->pOrigemLista = NULL ;
	pLista->pFimLista = NULL ;
	pLista->pNoCorrente = NULL ;
	pLista->numElementos   = 0 ;

#ifdef _DEBUG
	pLista->tipoElemento = tipoElem ;
#endif

} /* Fim função: LST  -Limpar a cabeça da lista */


#ifdef _DEBUG

/***********************************************************************
*
*  $FC Função: LST Alterar Ponteiro Sucessor
*
***********************************************************************/


void LST_AlteraPonteiroSucessor ( TpLista *pLista , void *ponteiro )
{
	pLista ->pNoCorrente ->pProx = (TpNoLista *) ponteiro;
} /* Fim função: LST  Altera Ponteiro Sucessor*/

/***********************************************************************
*
*  $FC Função: LST Altera Ponteiro Predecessor
*
***********************************************************************/

void LST_AlteraPonteiroPredecessor ( TpLista *pLista , void *ponteiro )
{
	pLista ->pNoCorrente ->pAnt = (TpNoLista * ) ponteiro;
}
/* Fim função: LST  Altera Ponteiro Predecessor*/

/***********************************************************************
*
*  $FC Função: LST Nulo Corrente
*
***********************************************************************/

void LST_NuloCorrente ( TpLista* pLista )
{
	pLista ->pNoCorrente = NULL;
}
/* Fim função: LST  Nulo Corrente */
/***********************************************************************
*
*  $FC Função: LST Nulo Origem
*
***********************************************************************/

void LST_NuloOrigem ( TpLista* pLista )
{
	pLista ->pOrigemLista = NULL;
}/* Fim função: LST  Nulo Origem */

/***********************************************************************
*
*  $FC Função: LST Verifica Assertiva Prox
*
***********************************************************************/

int LST_VerificaAssertivaProx ( TpLista *pLista )
{
	TpNoLista *aux;
	int i = 1;
	aux = pLista->pOrigemLista;
	if ( aux != NULL )
	{

		while ( aux->pProx != NULL && CED_ObterTipoEspaco(aux->pProx) == CED_ObterTipoEspaco(aux) )
		{
			CNT_CONTAR("LST_AssertivaProx_While1");
			if ( aux != aux->pProx->pAnt ){
				printf("\nErro: pNoCorrente != pNoCorrente->pProx->pAnt\n");
				CNT_CONTAR("LST_AssertivaProx_Erro");
				return 1;
			} else {
				CNT_CONTAR("LST_AssertivaProx_No_Ok");
			}

			i++;
			aux = aux -> pProx;
		}
		CNT_CONTAR("LST_AssertivaProx_if1");
	} else {
		CNT_CONTAR("LST_AssertivaProx_else1");
	}

	if(i == LST_RetornaNumElementos( pLista ))
	{
		CNT_CONTAR("LST_AssertivaProx_if2");
		return 0;
	} /* if*/
	else
	{
		printf("\nErro: nao foi possivel percorrer toda a lista, significa que algum no foi desencadeado\n");
		CNT_CONTAR("LST_AssertivaProx_else2");
		return 1;
	} /* if*/

}/* Fim função: LST  Verifica Assertiva Prox  */

/***********************************************************************
*
*  $FC Função: LST Verifica Assertiva Ant
*
***********************************************************************/

int LST_VerificaAssertivaAnt ( TpLista *pLista )
{
	TpNoLista *aux;
	int i = 1;
	aux = pLista->pFimLista;

	if ( aux != NULL )
	{
		CNT_CONTAR("LST_AssertivaAnt_if1");
		while ( aux->pAnt != NULL && CED_ObterTipoEspaco(aux->pAnt) == CED_ObterTipoEspaco(aux) )
		{
			CNT_CONTAR("LST_AssertivaAnt_while1");
			if ( aux != aux->pAnt->pProx ){
				printf("\nErro: pNoCorrente != pNoCorrente->pAnt->pProx\n");
				CNT_CONTAR("LST_AssertivaAnt_Erro");
				return 1;
			} else {
				CNT_CONTAR("LST_AssertivaAnt_No_ok");
			}

			i++;
			aux = aux -> pAnt;
		}
	} else {
		CNT_CONTAR("LST_AssertivaAnt_else1");
	}/* if*/

	if(i == LST_RetornaNumElementos( pLista ))
	{
		CNT_CONTAR("LST_AssertivaAnt_if2");
		return 0;
	} /* if*/
	else
	{
		printf("\nErro: nao foi possivel percorrer toda a lista, significa que algum no foi desencadeado\n");
		CNT_CONTAR("LST_AssertivaAnt_else2");
		return 1;
	} /* if*/

}/* Fim função: LST  Verifica Assertiva Ant  */

/***********************************************************************
*
*  $FC Função: LST Verifica Assertiva Lista Vazia
*
***********************************************************************/

int LST_VerificaAssertivaListaVazia ( TpLista *pLista )
{

	if ( LST_RetornaNumElementos (pLista) == 0 )
	{
		CNT_CONTAR("LST_AssertivaListaVazia_if1");
		if ( pLista -> pNoCorrente != NULL || pLista -> pOrigemLista != NULL || pLista -> pFimLista != NULL )
		{
			CNT_CONTAR("LST_AssertivaListaVazia_Erro");
			return 1;
		} else {
			CNT_CONTAR("LST_AssertivaListaVazia_Ok");
		} /* if */
		return 0;
	} else {
		CNT_CONTAR("LST_AssertivaListaVazia_else1");
	}
	return 0;
}/* Fim função: LST  Verifica Assertiva Lista Vazia  */

/***********************************************************************
*
*  $FC Função: LST Verifica Assertiva Lista Elemento Unico
*
***********************************************************************/

int LST_VerificaAssertivaListaElemUnico ( TpLista *pLista )
{  
	if ( LST_RetornaNumElementos (pLista) == 1 )
	{
		CNT_CONTAR("LST_AssertivaListaElemUnico_if1");
		if ( pLista -> pNoCorrente != pLista -> pOrigemLista || pLista -> pNoCorrente != pLista -> pFimLista )
		{
			printf("\n Lista com Um elemento e ponteiro corrente diferente do ponteiro origem ou do ponteiro fim\n");
			CNT_CONTAR("LST_AssertivaListaElemUnico_if2");
			return 1;
		} else {
			CNT_CONTAR("LST_AssertivaListaElemUnico_else2");
		}/* if */

		if ( pLista -> pNoCorrente-> pProx != NULL || pLista -> pNoCorrente-> pAnt != NULL )
		{
			printf("\n Lista com Um elemento e ponteiro proximo/anterior do no corrente nao eh nulo\n");
			CNT_CONTAR("LST_AssertivaListaElemUnico_if3");
			return 1;
		} else {
			CNT_CONTAR("LST_AssertivaListaElemUnico_else3");
		}/* if */

		return 0;
	} else {
		CNT_CONTAR("LST_AssertivaListaElemUnico_else1");
	}
	return 0;
}/* Fim função: LST  Verifica Assertiva Lista Elemento Unico  */

/***********************************************************************
*
*  $FC Função: LST Verifica Assertiva Lista Preenchida
*
***********************************************************************/

int LST_VerificaAssertivaListaPreenchida ( TpLista *pLista )
{
	if ( LST_RetornaNumElementos (pLista) > 1 )
	{
		CNT_CONTAR("LST_AssertivaListaPreenchida_if1");
		if ( pLista -> pNoCorrente == NULL || pLista -> pFimLista == NULL || pLista -> pOrigemLista == NULL )
		{
			printf("\nLista Preenchida: erro pNoCorrente ou pFimLista ou pOrigemLista nulo(s)\n");
			CNT_CONTAR("LST_AssertivaListaPreenchida_if2");
			return 1;
		} else {
			CNT_CONTAR("LST_AssertivaListaPreenchida_else2");
		}/* if */

		return 0;
	} else {
		CNT_CONTAR("LST_AssertivaListaPreenchida_else1");
	}
	return 0;
}/* Fim função: LST  Verifica Assertiva Lista Preenchida  */

/***********************************************************************
*
*  $FC Função: LST Verifica Assertiva Lista Preenchida
*
***********************************************************************/

int LST_VerificaAssertivaTipoListaElementos ( TpLista *pLista )
{
	TpNoLista* aux = pLista->pOrigemLista;

	while(aux != NULL)
	{
		CNT_CONTAR("LST_AssertivaTipoElemento_while");
		if(aux->pValor == NULL)
		{
			CNT_CONTAR("LST_AssertivaTipoElemento_Null_ComErro");
			printf("\nErro: Ponteiro para conteudo da celula nulo!\n");
			return 1;
		} else {
			CNT_CONTAR("LST_AssertivaTipoElemento_NotNull_Ok");
		}
		if(aux->tipoElemento != pLista->tipoElemento)
		{
			CNT_CONTAR("LST_AssertivaTipoElemento_ComErro");
			printf("\nErro: Tipo do conteudo da celula diferente do registrado na cabeca da lista!\n");
			return 1;
		} else {
			CNT_CONTAR("LST_AssertivaTipoElemento_Ok");
		}

		aux = aux->pProx;
	}
	CNT_CONTAR("LST_AssertivaTipoElemento_Fim");
	return 0;
}

#endif



/********** Fim do módulo de implementação: Módulo LISTA **********/
