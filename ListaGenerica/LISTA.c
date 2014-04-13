/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo Lista Gen�rica
*
*  Arquivo gerado:              ListaGenerica.c
*  Letras identificadoras:      LST
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mbv- Maria Beatriz Vaz
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       2.00   mbv   12/abr/2014 Revis�o e adapta��o do c�digo
*       1.00   mbv   19/mar/2014 In�cio do desenvolvimento
*
*************************************************************************
* ***/

#include   <stdlib.h>
#include   <stdio.h>
#include   <string.h>

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
  
struct tpNoLista {

         void * pValor ;
               /* Ponteiro para o valor contido no elemento. */

         struct tpNoLista * pAnt ;
               /* Ponteiro para o elemento anterior. */

         struct tpNoLista * pProx ;
               /* Ponteiro para o pr�ximo elemento. */

   } ;


   typedef struct tpNoLista TpNoLista;

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

    struct tpLista {

         TpNoLista * pOrigemLista ;
               /* Ponteiro para o pr�ximo n� da lista. */

         TpNoLista * pFimLista ;
               /* Ponteiro para o n� anterior da lista. */

		 TpNoLista * pNoCorrente ;
			   /* Ponteiro para o n� corrente. */
		 
		 int numElementos;
			   /* Indica a quantidade de elementos na lista. */

   } ;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void LiberarNo( TpLista * pLista , TpNoLista * pElem ) ;

   static TpNoLista * CriarElemento( TpLista * pLista , void * pValor ) ;

   static void LimparCabeca( TpLista * pLista ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: LST Criar lista gen�rica duplamente encadeada.
*  ****/

   TpLista * LST_CriarLista ( void )
   {
	   TpLista * pLista;

	  pLista = ( TpLista * )malloc( sizeof( TpLista )) ;
	   /* alocar espa�o para lista */

      if ( pLista== NULL )
      {
		  printf ( " Espa�o na mem�ria insuficiente " ) ;
         return NULL ;
      } /* if */

	  LimparCabeca( pLista ) ; 
	  /*zerar todos os campos da estrutura.*/
	  
      return pLista ;

   } /* Fim fun��o: LST Criar lista gen�rica duplamente encadeada*/

/***************************************************************************
*
*  Fun��o: LST Esvaziar lista duplamente encadeada.
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


	  LimparCabeca ( pLista );
	  pLista->pNoCorrente==NULL;

   } /* Fim fun��o: LST Esvaziar lista duplamente encadeada*/

/***************************************************************************
*
*  Fun��o: LST Destruir lista duplamente encadeada.
*  ****/

   LST_tpCondRet LST_DestruirLista( TpLista * pLista, void ( * ExcluirValor) ( void * pDado)  )
   {

	  if ( pLista == NULL)
	  {
		  return LST_CondRetListaInexistente;
	  } /* if */
	  
	  LST_EsvaziarLista ( pLista , ExcluirValor );
	  free ( pLista );

	   return LST_CondRetOK;

   } /* Fim fun��o: LST Destruir lista duplamente encadeada*/

/***************************************************************************
*
*  Fun��o: LST Adicionar novo n� no inicio da lista duplamente encadeada.
*  ****/

   LST_tpCondRet LST_InserirNovoNoInicio( TpLista * pLista , void * informacao )
   {
	 LST_tpCondRet CondRet;

	 if ( pLista->pNoCorrente != NULL )
	 {
		 CondRet = LST_IrInicio ( pLista );
	 } /* if */

	 return LST_InserirNoAntes ( pLista, informacao );
   }


  /* Fim fun��o: LST Adicionar novo n� no inicio da lista duplamente encadeada*/

   
/***********************************************************************************
*
*  Fun��o: LST Adicionar novo n� no fim da lista duplamente encadeada.
*  ****/

   LST_tpCondRet LST_InserirNovoNoFim( TpLista * pLista , void * informacao )
     {

	 LST_tpCondRet CondRet;

	 if ( pLista->pNoCorrente != NULL )
	 {
		 CondRet = LST_IrFim ( pLista );
	 } /* if */

	 return LST_InserirNoApos ( pLista, informacao );
   }
 



   /* Fim fun��o: LST Adicionar novo n� no fim da lista duplamente encadeada. */

/***************************************************************************
*
*  Fun��o: LST Inserir elemento antes do n� corrente.
*  ****/

   LST_tpCondRet LST_InserirNoAntes( TpLista * pLista , void * informacao )
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

   LST_tpCondRet LST_LiberarNoCorrente( TpLista * pLista , void ( * ExcluirValor) ( void * pDado)  )
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
            pElem->pAnt->pProx  = pElem->pProx ;
            pLista->pNoCorrente = pElem->pAnt ;
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

      LiberarNo( pLista , pElem, ExcluirValor ) ;
	  pLista->numElementos--;

      return LST_CondRetOK ;

   } 
   
   /* Fim fun��o: LST Liberar n� corrente*/

/**********************************************************************************

*
*  Fun��o: LST obter a informa��o contida no n� corrente.
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

/**********************************************************************************
*
*  Fun��o: LST Ir para o fim da lista duplamente encadeada.
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
	
 /* Fim fun��o: LST Ir para o fim da lista duplamente encadeada.    */


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

   /**********************************************************************************
*
*  Fun��o: LST Busca informa��o.
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

	   
	  while ( CondRet != LST_CondRetOK  )
	  {
		  
		  if (  Compara ( pLista->pNoCorrente->pValor , informacao ) == 0) 
         {
            return LST_CondRetOK ;
         } /* if */

		 CondRet = LST_Avancar ( pLista, 1 ) ;

      } /* While */

      return LST_CondRetInfoNaoEncontrada ;
	}

 /* Fim fun��o: LST Busca informa��o.    */


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

   void LiberarNo( TpLista * pLista , TpNoLista * pElem, void ( * ExcluirValor) ( void * pDado) )
   {

	   if (( pElem->pValor != NULL ))
      {
		  pElem->pAnt = pElem->pProx;
      } /* if */

      ExcluirValor ( pElem ) ;

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

   } /* Fim fun��o: LST  -Limpar a cabe�a da lista */



/********** Fim do m�dulo de implementa��o: M�dulo LISTA **********/
