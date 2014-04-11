/***************************************************************************
*  $MCI Módulo de implementação: Módulo Lista Genérica
*
*  Arquivo gerado:              ListaGenerica.c
*  Letras identificadoras:      LST
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mbv- Maria Beatriz Vaz
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       2.00   mbv   10/abr/2014 Revisão e adaptação do código
*       1.00   mbv   19/mar/2014 Início do desenvolvimento
*
*************************************************************************
* ***/

#include   <malloc.h>
#include   <stdio.h>

#include "LISTA.h"


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
  
typedef struct tpNoLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento. */

         struct tpNoLista * pAnt ;
               /* Ponteiro para o elemento anterior. */

         struct tpNoLista * pProx ;
               /* Ponteiro para o próximo elemento. */

   } TpNoLista ;

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

   typedef struct tpLista {

         TpNoLista * pOrigemLista ;
               /* Ponteiro para o próximo nó da lista. */

         TpNoLista * pFimLista ;
               /* Ponteiro para o nó anterior da lista. */

		 TpNoLista * pNoCorrente ;
			   /* Ponteiro para o nó corrente. */
		 
		 int numElementos;
			   /* Indica a quantidade de elementos na lista. */

   } TpLista ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void LiberarNo( TpLista * pLista , TpNoLista * pElem ) ;

   static TpNoLista * CriarElemento( TpLista * pLista , void * pValor ) ;

   static void LimparCabeca( TpLista * pLista ) ;

   static void LST_EsvaziarLista( TpLista * pLista  );

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: LST Criar lista genérica duplamente encadeada.
*  ****/

   TpLista * LST_CriarLista( void )
   {
	   TpLista * pLista;

	  pLista = ( TpLista * )malloc( sizeof( TpLista )) ;
      if ( pLista== NULL )
      {
		  printf ( " Espaço na memória insuficiente " ) ;
         return NULL ;
      } /* if */

	  LimparCabeca( pLista ) ; 

      return pLista ;

   } /* Fim função: LST Criar lista genérica duplamente encadeada*/

/***************************************************************************
*
*  Função: LST Destruir lista duplamente encadeada.
*  ****/

   LST_tpCondRet LST_DestruirLista( TpLista * pLista  )
   {

	  if ( pLista == NULL)
	  {
		  return LST_CondRetListaInexistente;
	  } /* if */
	  
	  LST_EsvaziarLista ( pLista );
	  free ( pLista );

	   return LST_CondRetOK;

   } /* Fim função: LST Destruir lista duplamente encadeada*/

/***************************************************************************
*
*  Função: LST Esvaziar lista duplamente encadeada.
*  ****/

   void LST_EsvaziarLista( TpLista * pLista  )
   {
      TpNoLista * pElem ;
      TpNoLista * pProx ;

	  if ( pLista == NULL)
	  {
		  return;
	  } /* if */

      pElem = pLista->pOrigemLista ;
      while ( pElem != NULL )
      {
         pProx = pElem->pProx ;
         LiberarNo( pLista , pElem ) ;
         pElem = pProx ;
      } /* while */

   } /* Fim função: LST Esvaziar lista duplamente encadeada*/
   
/***************************************************************************
*
*  Função: LST Adicionar novo nó no inicio da lista duplamente encadeada.
*  ****/

   LST_tpCondRet LST_InserirNovoNoInicio( TpLista * pLista , void * informacao )
   {
	  TpNoLista * pElem;
     /* Criar o elemento a ser inserido. */
	  TpNoLista * NovoNo;
	  
	  NovoNo=( TpNoLista * )malloc( sizeof( TpNoLista )) ;
	  if ( NovoNo== NULL )
      {
         return LST_CondRetFaltouMemoria ;
      } /* if */
	  
	  if ( pLista == NULL )
	  {
		  NovoNo->pProx=NULL;
		  NovoNo->pAnt=NULL;
		  NovoNo->pValor=informacao;

		  pLista->pOrigemLista=NovoNo;
		  pLista->pFimLista=NovoNo;
		  pLista->pNoCorrente=NovoNo;
		  pLista->numElementos=1;

		  return LST_CondRetCriouLista;
	  } /* if */

	  pElem=pLista->pOrigemLista;
	  pLista->pOrigemLista=NovoNo;
	  NovoNo->pProx=pElem;
	  pElem->pAnt=NovoNo;

	  pLista->numElementos++;

	  return LST_CondRetOK ;

   } /* Fim função: LST Adicionar novo nó no inicio da lista duplamente encadeada*/

   
/***********************************************************************************
*
*  Função: LST Adicionar novo nó no fim da lista duplamente encadeada.
*  ****/

   LST_tpCondRet LST_InserirNovoNoFim( TpLista * pLista , void * informacao )
   {

      TpNoLista * pElem;
     /* Criar o elemento a ser inserido. */
	  TpNoLista * NovoNo;
	  
	  NovoNo=( TpNoLista * )malloc( sizeof( TpNoLista )) ;
	  if ( NovoNo== NULL )
      {
         return LST_CondRetFaltouMemoria ;
      } /* if */
	  
	  if ( pLista == NULL )
	  {
		  NovoNo->pProx=NULL;
		  NovoNo->pAnt=NULL;
		  NovoNo->pValor=informacao;

		  pLista->pOrigemLista=NovoNo;
		  pLista->pFimLista=NovoNo;
		  pLista->pNoCorrente=NovoNo;
		  pLista->numElementos=1;

		  return LST_CondRetCriouLista;
	  } /* if */

	  
	  
	  pElem=pLista->pFimLista;
	  pLista->pFimLista=NovoNo;
	  NovoNo->pAnt=pElem;
	  pElem->pProx=NovoNo;

	  pLista->numElementos++;

	  return LST_CondRetOK ;

   } /* Fim função: LST Adicionar novo nó no fim da lista duplamente encadeada. */

/***************************************************************************
*
*  Função: LST Inserir elemento antes do nó corrente.
*  ****/

   LST_tpCondRet LIS_InserirNoAntes( TpLista * pLista , void * informacao )
   {

      TpNoLista * pElem ;
      
	  if ( pLista == NULL )
	  {
		  return LST_CondRetListaInexistente;
	  } /* if */

	  /* Criar elemento a inerir antes */

         pElem = CriarElemento( pLista , informacao ) ;
         if ( pElem == NULL )
         {
            return LST_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento antes do elemento corrente */

         if ( pLista->pNoCorrente == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
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
		 pLista->numElementos++;

         return LST_CondRetOK ;

   } /* Fim função: LST  Inserir elemento antes */

/***************************************************************************
*
*  Função: LST  Inserir elemento após
*  ****/

   LST_tpCondRet LST_InserirNoApos( TpLista * pLista , void * informacao )      
   {

      TpNoLista * pElem ;

	  if ( pLista == NULL)
	  {
		  return LST_CondRetListaInexistente;
	  } /* if */

      /* Criar elemento a inerir após */

         pElem = CriarElemento( pLista , informacao ) ;
         if ( pElem == NULL )
         {
            return LST_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento após o elemento */

         if ( pLista->pNoCorrente == NULL )
         {
            pLista->pOrigemLista = pElem ;
            pLista->pFimLista = pElem ;
         } else
         {
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
         pLista->numElementos++;

         return LST_CondRetOK ;

   } /* Fim função: LST  Inserir elemento após */

  
   
/**********************************************************************************
*
*  Função: LST Liberar nó corrente.
*  ****/

   LST_tpCondRet LST_LiberarNoCorrente( TpLista * pLista  )
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
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pNoCorrente    = pElem->pAnt ;
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

      LiberarNo( pLista , pElem ) ;
	  pLista->numElementos--;

      return LST_CondRetOK ;

   } 
   
   /* Fim função: LST Liberar nó no inicio da lista duplamente encadeada*/

/**********************************************************************************

*
*  Função: LST obter a informação contida no nó corrente.
*  ****/

	LST_tpCondRet LST_ObterValor( TpLista * pLista , void * informacao ) 
	{

	  if ( pLista == NULL)
	  {
		  return LST_CondRetListaInexistente;

	  } /* if */

      if ( pLista->pNoCorrente == NULL )
      {
        return LST_CondRetListaVazia ;
      } /* if */
	   
	  if ( pLista->pNoCorrente->pValor == NULL )
	  {
		  return LST_CondRetNoNaoPossuiInfo;
	  } /* if */

	  informacao=pLista->pNoCorrente->pValor;

	  return LST_CondRetOK;

   } /* Fim função: LST obter a informação contida no nó corrente. */

/**********************************************************************************
*
*  Função: LST alterar a informação contida no nó corrente.
*  ****/

	LST_tpCondRet LST_AlterarValor( TpLista * pLista , void * informacao ) 
	{

	  if ( pLista == NULL)
	  {
		  return LST_CondRetListaInexistente;

	  } /* if */

	  pLista->pNoCorrente->pValor = informacao;
	  
	  return LST_CondRetOK;
	}

 /* Fim função: LST alterar a informação contida no nó corrente*/

/**********************************************************************************
*
*  Função: LST Busca informação.
*  ****/

	LST_tpCondRet LST_Busca( TpLista * pLista , void * informacao )
	{

      TpNoLista * pElem ;

	  if ( pLista == NULL)
	  {
		  return LST_CondRetListaInexistente;
	  } /* if */

      if ( pLista->pNoCorrente == NULL )
      {
         return LST_CondRetListaVazia ;
      } /* if */

	  for ( pElem  = pLista->pNoCorrente ; pElem != NULL ; pElem = pElem->pProx ) 
	  {
         if ( pElem->pValor == informacao )
         {
            pLista->pNoCorrente = pElem ;
            return LST_CondRetOK ;
         } /* if */
      } /* for */

      return LST_CondRetInfoNaoEncontrada ;
	}

 /* Fim função: LST Busca informação.    */

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

   void LiberarNo( TpLista * pLista , TpNoLista * pElem )
   {

	   if (( pElem->pValor != NULL ))
      {
		  pElem->pAnt = pElem->pProx;
      } /* if */

      free( pElem ) ;

	  pLista->numElementos--;

   } /* Fim função: LST Liberar No da lista */


/***********************************************************************
*
*  $FC Função: LST Criar o elemento
*
***********************************************************************/

   TpNoLista * CriarElemento( TpLista * pLista , void * pValor )
   {

      TpNoLista * pElem ;

      pElem = ( TpNoLista * ) malloc( sizeof( TpNoLista )) ;
      if ( pElem == NULL )
      {
         return NULL ;
      } /* if */

      pElem->pValor = pValor ;
      pElem->pAnt   = NULL  ;
      pElem->pProx  = NULL  ;

      pLista->numElementos ++ ;

      return pElem ;

   } /* Fim função: LST Criar o elemento */


/***********************************************************************
*
*  $FC Função: LST Limpar a cabeça da lista
*
***********************************************************************/

   void LimparCabeca( TpLista * pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pNoCorrente = NULL ;
      pLista->numElementos   = 0 ;

   } /* Fim função: LIS  -Limpar a cabeça da lista */

/********** Fim do módulo de implementação: Módulo LISTA **********/
