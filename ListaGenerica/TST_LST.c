/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TST_LST.C
*  Letras identificadoras:      TLST
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mbv - Maria Beatriz Vaz
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       3.00   avs   28/02/2003 Uniformiza��o da interface das fun��es e
*                               de todas as condi��es de retorno.
*       2.00   avs   03/08/2002 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00   mbv   30/mar/2014 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este modulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo lista. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo lista:
*
*     =criar        - chama a fun��o LST_CriarLista( <TpLista> )
*                     Obs. nota��o: <TpLista>  � o valor do par�metro
*                     que se encontra no comando de	teste.			
*     =insinicio <Void>
*                   - chama a fun��o LST_InserirNovoNoInicio( <TpLista> , <Void> )
*                     Obs. nota��o: <Void>  � o valor do par�metro
*                     que se encontra no comando de teste.
*
*     "=insfim" <Void>
*                    - chama a fun��o LST_InserirNovoNoFim( <TpLista> , <Void> )
*     "=insapos"     - chama a fun��o LST_InserirNoApos( <TpLista> , <Void> )
*     "=insantes"    - chama a fun��o LST_InserirNoAntes( <TpLista> , <Void> )
*     "=libera"      - chama a fun��o LST_LiberarNoCorrente( <TpLista> )
*     "=obter" <Void>
*                    - chama a fun��o LST_ObterValor( <TpLista> , <Void> ) e compara
*                     o valor retornado com o valor <Void>
*     "=alterar"     - chama a fun��o LST_AlterarValor( <TpLista> , <Void> )
*     "=irinicio"    - chama a fun��o LST_IrInicio( <TpLista> )
*     "=irfim"       - chama a fun��o LST_IrFim( <TpLista> )
*     "=avancar"     - chama a fun��o LST_Avancar( <TpLista> , <int> )
*     "=destroi"     - chama a fun��o LST_DestruirLista( <TpLista> )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESP.H"

#include    "GENERICO.h"
#include    "LERPARM.h"

#include    "LISTA.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     CRIAR_LST_CMD       "=criar"
#define     INS_INICIO_CMD      "=insinicio"
#define     INS_FIM_CMD         "=insfim"
#define     INS_APOS_CMD        "=insapos"
#define     INS_ANTES_CMD       "=insantes"
#define     LIBERAR_CMD         "=liberar"
#define     OBTER_VAL_CMD       "=obter"
#define     ALTERAR_VAL_CMD     "=alterar"
#define     IR_INICIO_CMD       "=irinicio"
#define     IR_FIM_CMD          "=irfim"
#define     AVANCAR_CMD         "=avancar"
#define     DESTROI_CMD         "=destruir"

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TARV Efetuar opera��es de teste espec�ficas para lista
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     lista sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESP.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      LST_tpCondRet CondRetObtido   = LST_CondRetOK ;
      LST_tpCondRet CondRetEsperada = LST_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

      /* Testar ARV Criar �rvore */

         if ( strcmp( ComandoTeste , CRIAR_LST_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros("i", &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = LST_CriarLista( ValorDado  ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar �rvore." );

         } /* fim ativa: Testar ARV Criar �rvore */

      /* Testar ARV Adicionar filho � direita */

         else if ( strcmp( ComandoTeste , INS_DIR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ci" ,
                               &ValorDado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_InserirDireita( ValorDado ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado inserir �a direita." );

         } /* fim ativa: Testar ARV Adicionar filho � direita */

      /* Testar ARV Adicionar filho � esquerda */

         else if ( strcmp( ComandoTeste , INS_ESQ_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ci" ,
                               &ValorDado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_InserirEsquerda( ValorDado ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir � esquerda." );

         } /* fim ativa: Testar ARV Adicionar filho � esquerda */

      /* Testar ARV Ir para n� pai */

         else if ( strcmp( ComandoTeste , IR_PAI_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrPai( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para pai." );

         } /* fim ativa: Testar ARV Ir para n� pai */

      /* Testar ARV Ir para n� � esquerda */

         else if ( strcmp( ComandoTeste , IR_ESQ_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrNoEsquerda( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para esquerda." );

         } /* fim ativa: Testar ARV Ir para n� � esquerda */

      /* Testar ARV Ir para n� � direita */

         else if ( strcmp( ComandoTeste , IR_DIR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                               &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrNoDireita( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para direita." );

         } /* fim ativa: Testar ARV Ir para n� � direita */

      /* Testar ARV Obter valor corrente */

         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ci" ,
                               &ValorEsperado , &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_ObterValorCorr( &ValorObtido ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." );

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararChar( ValorEsperado , ValorObtido ,
                                     "Conte�do do n� est� errado." ) ;

         } /* fim ativa: Testar ARV Obter valor corrente */

      /* Testar ARV Destruir �rvore */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {

            ARV_DestruirArvore( ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ARV Destruir �rvore */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TARV Efetuar opera��es de teste espec�ficas para �rvore */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

