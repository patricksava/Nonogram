/***************************************************************************
*  $MCI Módulo de implementação: TVAL Teste Estrutura Valor
*
*  Arquivo gerado:              TESTVAL.c
*  Letras identificadoras:      TVAL
*
*  Projeto: INF 1301 
*  Gestor:  LES/DI/PUC-Rio
*  Autores: mbv
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  2       mbv   11/abr/2014 Término do desenvolvimento
*     1       mbv   10/abr/2014 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "GENERICO.h"
#include    "LERPARM.h"

#include    "VALOR.h"

/* Tabela dos nomes dos comandos de teste específicos */

static const char RESET_VAL_CMD           [ ] = "=resetteste"     ;
static const char CRIAR_VAL_CMD           [ ] = "=criarvalor"     ;
static const char DESTRUIR_VAL_CMD        [ ] = "=destruirvalor"  ;
static const char ESVAZIAR_VAL_CMD        [ ] = "=esvaziarvalor"  ;
static const char INCRPIN_VAL_CMD         [ ] = "=incrpintados"   ;
static const char DECRPIN_VAL_CMD         [ ] = "=decrpintados"   ;
static const char ALTERAR_VAL_CMD         [ ] = "=alterarvalor"   ;
static const char OBTERPIN_VAL_CMD        [ ] = "=obterpintados"  ;
static const char OBTERMARC_VAL_CMD       [ ] = "=obtermarcados"  ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_VALOR  10
#define DIM_VALOR 100

TpValor  *vetValor[ DIM_VT_VALOR];

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxValor( int inxValor , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TVAL &Testar valor
*
*  $ED Descrição da função
*     Podem ser criadas até 10 estruturas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de valores. Provoca vazamento de memória
*     =criarvalor                   inxValor
*     =destruirvalor                inxValor
*	  =esvaziarvalor                inxValor
*     =incrpintados                 inxValor
*     =decrpintados                 inxValor
*     =alterarvalor                 inxValor
*	  =obterpintados                inxValor  string  CondretPonteiro
*	  =obtermarcados                inxValor  string  CondretPonteiro
*
***********************************************************************/


   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxValor  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      VAL_tpCondRet CondRet ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;
	  int numElemEsp = -1 ;

      /* Efetuar reset de teste de valor */

         if ( strcmp( ComandoTeste , RESET_VAL_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_VALOR ; i++ )
            {
               vetValor [ i ] = NULL ;

            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de valor */

      /* Testar CriarValor */

         else if ( strcmp( ComandoTeste , CRIAR_VAL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxValor ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxValor( inxValor , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */


            vetValor[ inxValor ] =
                 VAL_CriarValor() ;


            return TST_CompararPonteiroNulo( 1 , vetValor[ inxValor ] ,
               "Erro em ponteiro de novo valor."  ) ;

         } /* fim ativa: Testar CriarValor */

      /* Testar IncrementarQntdPintados */

         else if ( strcmp( ComandoTeste , INCRPIN_VAL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxValor, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxValor( inxValor , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = VAL_IncrementarQntdPintados( vetValor[ inxValor ] ) ;

            if ( CondRet != VAL_CondRetOk )
            {
                return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao incrementar pintados."); 
            } /* if */

            return TST_CondRetOK ;

         } /* fim ativa: IncrementarQntdPintados*/

      /* Testar DecrementarQntdPintados*/

         else if ( strcmp( ComandoTeste , DECRPIN_VAL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                               &inxValor, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxValor( inxValor , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = VAL_DecrementarQntdPintados( vetValor[ inxValor ] ) ;

			if ( CondRet != VAL_CondRetOk )
            {
                return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao decrementar pintados."); 
            } /* if */


            return TST_CondRetOK ;

         } /* fim ativa: Testar DecrementarQntdPintados */


     /* Testar DestruirValor */

         else if ( strcmp( ComandoTeste , DESTRUIR_VAL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                       &inxValor, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxValor( inxValor , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            
            CondRet = VAL_DestruirValor( vetValor[ inxValor ] ) ;

			if (CondRet != CondRetEsp)
			{
            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao excluir."                   ) ;
			} /* if */

			vetValor[ inxValor ] = NULL ;

			return TST_CondRetOK ; 

         } /* fim ativa: Testar DestruirValor */


      /* Testar RessetarValor */

         else if ( strcmp( ComandoTeste , ESVAZIAR_VAL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                       &inxValor, &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxValor( inxValor , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

		    CondRet = VAL_RessetarValor( vetValor[ inxValor ] ) ;

			if ( CondRet != VAL_CondRetOk )
            {
                return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao esvaziar valor."); 
            } /* if */

            return TST_CondRetOK ;


         } /* fim ativa: Testar RessetarValor */

		       /* VAL AlterarQntdMarcados */

         else if ( strcmp( ComandoTeste , ALTERAR_VAL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &inxValor , &numElem ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxValor( inxValor , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      VAL_AlterarQntdMarcados( vetValor[ inxValor ] , numElem ) ,
                      "Condicao de retorno errada ao alterar" ) ;

         } /* fim ativa: VAL  AlterarQntdMarcados */

    /* VAL ObterMarcados */

         else if ( strcmp( ComandoTeste , OBTERMARC_VAL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxValor, &numElem ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxValor( inxValor , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( numElem ,
                      VAL_ObterMarcados( vetValor[ inxValor ]) ,
                      "Condicao de retorno errada ao obter valor marcados" ) ;

         } /* fim ativa: VAL  ObterMarcados */
  
		 /* VAL ObterPintados */

         else if ( strcmp( ComandoTeste , OBTERPIN_VAL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxValor, &numElem ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxValor( inxValor , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( numElem ,
                      VAL_ObterPintados( vetValor[ inxValor ]) ,
                      "Condicao de retorno errada ao obter valor pintados" ) ;

         } /* fim ativa: VAL  ObterMarcados */
      return TST_CondRetNaoConhec ;

}
/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************


/***********************************************************************
*
*  $FC Função: TVAL -Validar indice de valor
*
***********************************************************************/

   int ValidarInxValor( int inxValor , int Modo )
   {

      if ( ( inxValor <  0 )
        || ( inxValor >= DIM_VT_VALOR ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vetValor[ inxValor ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vetValor[ inxValor ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TVAL -Validar indice de VALOR */

/********** Fim do módulo de implementação: TVAL Teste de Estrutura do tipo valor **********/

