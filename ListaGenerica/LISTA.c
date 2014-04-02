/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo Lista Gen�rica
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
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       3.00   avs   28/02/2003 Uniformiza��o da interface das fun��es e
*                               de todas as condi��es de retorno.
*       2.00   avs   21/03/2014 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00   mbv   19/mar/2014 In�cio do desenvolvimento
*
*************************************************************************
* ***/

#include   <malloc.h>
#include   <stdio.h>

#include "LISTA.h"


/***********************************************************************
*
*  $TC Tipo de dados: LST N� da Lista.
*
*
*  $ED Descri��o do tipo
*	
*	Estrutura que define um n� (elemento) de uma Lista Gen�rica.
*	Nele est� contido um ponteiro para o valor que o n� armazena 
*	(do tipo void), um ponteiro para o n� sucessor e um ponteiro
*	para o n� anterior.
*
***********************************************************************/
  
typedef struct tpNoLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento. */

         struct tpNoLista * pAnt ;
               /* Ponteiro para o elemento anterior. */

         struct tpNoLista * pProx ;
               /* Ponteiro para o pr�ximo elemento. */

   } TpNoLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LST Cabe�a da Lista.
*
*
*  $ED Descri��o do tipo
*	
*	Estrutura que define a cabe�a de uma lista.
*	Possui um ponteiro para o n� do in�cio da lista,
*	um ponteiro para o n� do fim da lista e um ponteiro
*	para o elemento corrente. Al�m disso, possui o n�mero
*	de elementos que a lista cont�m.
*
***********************************************************************/

   typedef struct tpLista {

         TpNoLista * pOrigemLista ;
               /* Ponteiro para o pr�ximo n� da lista. */

         TpNoLista * pFimLista ;
               /* Ponteiro para o n� anterior da lista. */

		 TpNoLista * pNoCorrente ;
			   /* Ponteiro para o n� corrente. */
		 
		 int numElementos;
			   /* Indica a quantidade de elementos na lista. */

   } TpLista ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void LiberarNo( TpLista * pLista , TpNoLista * pElem ) ;

   static TpNoLista * CriarElemento( TpLista * pLista , void * pValor ) ;

   static void LimparCabeca( TpLista * pLista ) ;

   static void LST_EsvaziarLista( TpLista * pLista  );

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: LST Criar lista gen�rica duplamente encadeada.
*  ****/

   LST_tpCondRet LST_CriarLista( TpLista * pLista )
   {
	  pLista = ( TpLista * )malloc( sizeof( TpLista )) ;
      if ( pLista== NULL )
      {
         return LST_CondRetFaltouMemoria ;
      } /* if */

	  LimparCabeca( pLista ) ; 

      return LST_CondRetOK ;

   } /* Fim fun��o: LST Criar lista gen�rica duplamente encadeada*/

/***************************************************************************
*
*  Fun��o: LST Destruir lista duplamente encadeada.
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

   } /* Fim fun��o: LST Destruir lista duplamente encadeada*/

/***************************************************************************
*
*  Fun��o: LST Esvaziar lista duplamente encadeada.
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

   } /* Fim fun��o: LST Esvaziar lista duplamente encadeada*/
   
/***************************************************************************
*
*  Fun��o: LST Adicionar novo n� no inicio da lista duplamente encadeada.
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

   } /* Fim fun��o: LST Adicionar novo n� no inicio da lista duplamente encadeada*/

   
/***********************************************************************************
*
*  Fun��o: LST Adicionar novo n� no fim da lista duplamente encadeada.
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

   } /* Fim fun��o: LST Adicionar novo n� no fim da lista duplamente encadeada. */

/***************************************************************************
*
*  Fun��o: LST Inserir elemento antes do n� corrente.
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

   } /* Fim fun��o: LST  Inserir elemento antes */

/***************************************************************************
*
*  Fun��o: LST  Inserir elemento ap�s
*  ****/

   LST_tpCondRet LST_InserirNoApos( TpLista * pLista , void * informacao )      
   {

      TpNoLista * pElem ;

	  if ( pLista == NULL)
	  {
		  return LST_CondRetListaInexistente;
	  } /* if */

      /* Criar elemento a inerir ap�s */

         pElem = CriarElemento( pLista , informacao ) ;
         if ( pElem == NULL )
         {
            return LST_CondRetFaltouMemoria ;
         } /* if */

      /* Encadear o elemento ap�s o elemento */

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

   } /* Fim fun��o: LST  Inserir elemento ap�s */

  
   
/**********************************************************************************
*
*  Fun��o: LST Liberar n� corrente.
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

      /* Desencadeia � esquerda */

         if ( pElem->pAnt != NULL )
         {
            pElem->pAnt->pProx   = pElem->pProx ;
            pLista->pNoCorrente    = pElem->pAnt ;
         } else {
            pLista->pNoCorrente    = pElem->pProx ;
            pLista->pOrigemLista = pLista->pNoCorrente ;
         } /* if */

      /* Desencadeia � direita */

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
   
   /* Fim fun��o: LST Liberar n� no inicio da lista duplamente encadeada*/

/**********************************************************************************

*
*  Fun��o: LST obter a informa��o contida no n� corrente.
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

   } /* Fim fun��o: LST obter a informa��o contida no n� corrente. */

/**********************************************************************************
*
*  Fun��o: LST alterar a informa��o contida no n� corrente.
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

 /* Fim fun��o: LST alterar a informa��o contida no n� corrente*/

/**********************************************************************************
*
*  Fun��o: LST Busca informa��o.
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

 /* Fim fun��o: LST Busca informa��o.    */

/**********************************************************************************
*
*  Fun��o: LST Ir para o inicio da lista duplamente encadeada.
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
	
 /* Fim fun��o: LST Ir para o inicio da lista duplamente encadeada.    */


/***************************************************************************
*
*  Fun��o: LST  Avan�ar elemento
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

      /* Tratar avan�ar para frente */

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

         } /* fim ativa: Tratar avan�ar para frente */

      /* Tratar avan�ar para tr�s */

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

         } /* fim ativa: Tratar avan�ar para tr�s */

      /* Tratar n�o avan�ar */

         return LST_CondRetOK ;

   } /* Fim fun��o: LST Avan�ar elemento */

/***************************************************************************
	


	/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: LST  Liberar n� da lista
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do n� e o
*     pr�prio n�.
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

   } /* Fim fun��o: LST Liberar No da lista */


/***********************************************************************
*
*  $FC Fun��o: LST Criar o elemento
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

   } /* Fim fun��o: LST Criar o elemento */


/***********************************************************************
*
*  $FC Fun��o: LST Limpar a cabe�a da lista
*
***********************************************************************/

   void LimparCabeca( TpLista * pLista )
   {

      pLista->pOrigemLista = NULL ;
      pLista->pFimLista = NULL ;
      pLista->pNoCorrente = NULL ;
      pLista->numElementos   = 0 ;

   } /* Fim fun��o: LIS  -Limpar a cabe�a da lista */

/********** Fim do m�dulo de implementa��o: M�dulo LISTA **********/
