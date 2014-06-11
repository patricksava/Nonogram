/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TestDesenho.c
*  Letras identificadoras:      TDES
*
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: ps - Patrick Sava
* 
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		2.00    ps	 01/06/2014 Instrumentação incluída
*       1.00    ps   01/04/2014 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo desenho. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo árvore:
*
*     =iniciardesenho <int linhas> <int colunas> 
*                   - chama a função DES_IniciaDesenho( int, int )
*
      "=iniciardesenhovazio" 
                    - chama a função DES_IniciaDesenhoVazio( int, int )

      "=iniciardesenhoprojeto"
                    - chama a função DES_IniciaDesenhoProjetado( char* )

      "=iniciardesenhoultimojogo"
                    - chama a função DES_RetomaUltimoJogoSalvo( )

*     =destroidesenho - chama a função DES_DestroiDesenho( )
*                    
*     =alterarmarcacao <int x> <int y>  (x,y) é uma coordenada no tabuleiro
*                   - chama a função DES_AlteraMarcacaoCoordenada( int, int );
* 
*     =ativardica - chama a função DES_AtivaDica( )
*
*     =imprimirjogo - chama a função DES_ImprimeMatrizJogo( )  
*
*     "=gravarjogo" - chama a função DES_GravaJogoAtual( )
*
*     "=gravarprojeto" - chama a função DES_GravaMatrizProjetada( char* )
*
*     "=jogofinalizado" - chama a função DES_JogoFinalizado( )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "GENERICO.h"
#include    "LERPARM.h"

#include    "Desenho.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define     INICIAR_DES_CMD       "=iniciardesenho"
#define     INI_DES_VAZIO_CMD     "=iniciardesenhovazio"
#define     INI_DES_PROJ_CMD      "=iniciardesenhoprojeto"
#define     INI_DES_ULT_JOGO_CMD  "=iniciardesenhoultimojogo"
#define     DESTROI_DES_CMD       "=destroidesenho"
#define     ALT_MARC_CMD          "=alterarmarcacao"
#define     ATIV_DICA_CMD         "=ativardica"
#define     IMPRIME_JOGO_CMD      "=imprimirjogo"
#define     GRAVA_JOGO_CMD        "=gravarjogo"
#define     GRAVA_MAT_PROJ_CMD    "=gravarprojeto"
#define     JOGO_FINAL_CMD        "=jogofinalizado"
#ifdef _DEBUG
#define		DETURPA_CMD			  "=deturpa"
#define		VERIFICA_CMD		  "=verifica"
#endif

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TDES Efetuar operações de teste específicas para desenho
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     desenho sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      DES_tpCondRet CondRetObtido;
      DES_tpCondRet CondRetEsperada;

      int  NumLidos;

      /* Testar DES Inicia desenho */

         if ( strcmp( ComandoTeste , INICIAR_DES_CMD ) == 0 )
         {
            int linhas, colunas;

            NumLidos = LER_LerParametros( "iii" ,
                               &CondRetEsperada, &linhas, &colunas) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DES_IniciaDesenho( linhas, colunas ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar desenho." );

         } /* fim ativa: Testar DES Iniciar desenho aleatório */

      /* Testar DES Inicia desenho */

         else if ( strcmp( ComandoTeste , INI_DES_VAZIO_CMD ) == 0 )
         {
            int linhas, colunas;

            NumLidos = LER_LerParametros( "iii" ,
                               &CondRetEsperada, &linhas, &colunas) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DES_IniciaDesenhoVazio( linhas, colunas ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar desenho vazio." );

         } /* fim ativa: Testar DES Iniciar desenho vazio */

      /* Testar DES Inicia desenho projetado */

         else if ( strcmp( ComandoTeste , INI_DES_PROJ_CMD ) == 0 )
         {
            char NomeJogo[41];
            FILE* ArquivoJogo;

            NumLidos = LER_LerParametros( "is" ,
                               &CondRetEsperada, NomeJogo ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            ArquivoJogo = fopen( NomeJogo, "r" );

            CondRetObtido = DES_IniciaDesenhoProjetado( ArquivoJogo ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar desenho projetado." );

         } /* fim ativa: Testar DES Iniciar desenho projetado */

      /* Testar DES Inicia desenho último jogo salvo */

         else if ( strcmp( ComandoTeste , INI_DES_ULT_JOGO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" , &CondRetEsperada) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DES_RetomaUltimoJogoSalvo( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao retomar ultimo jogo salvo." );

         } /* fim ativa: Testar DES Iniciar desenho último jogo salvo */


      /* Testar DES Destroi desenho */

         else if ( strcmp( ComandoTeste , DESTROI_DES_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DES_DestroiDesenho( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao destruir desenho." );

         } /* fim ativa: Testar DES Destroi desenho */

      /* Testar DES Alterar Marcação Coordenada */

         else if ( strcmp( ComandoTeste , ALT_MARC_CMD ) == 0 )
         {
            int coordX, coordY;

            NumLidos = LER_LerParametros( "iii" ,
                               &CondRetEsperada, &coordX, &coordY ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DES_AlteraMarcacaoCoordenada( coordX, coordY ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao alterar marcação." );

         } /* fim ativa: Testar DES Alterar Marcação Coordenada */

      /* Testar DES Ativar Dica */

         else if ( strcmp( ComandoTeste , ATIV_DICA_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DES_AtivaDica( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ativar dica." );

         } /* fim ativa: Testar DES Ativar Dica */

      /* Testar DES Grava Jogo Atual */

         else if ( strcmp( ComandoTeste , GRAVA_JOGO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DES_GravaJogoAtual( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao gravar jogo atual." );

         } /* fim ativa: Testar DES Grava Jogo Atual */

      /* Testar DES Grava Projeto Matriz */

         else if ( strcmp( ComandoTeste , GRAVA_MAT_PROJ_CMD ) == 0 )
         {
            char NomeJogo[41];

            NumLidos = LER_LerParametros( "is" , &CondRetEsperada, NomeJogo ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DES_GravaMatrizProjetada( NomeJogo ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao gravar projeto." );

         } /* fim ativa: Testar DES Grava Projeto Matriz */

      /* Testar DES Jogo Finalizado */

         else if ( strcmp( ComandoTeste , JOGO_FINAL_CMD ) == 0 )
         {
            int FinalEsperado, FinalRecebido;

            NumLidos = LER_LerParametros( "i" , &FinalEsperado) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            FinalRecebido = DES_DesenhoFinalizado( ) ;

            return TST_CompararInt( FinalEsperado , FinalRecebido ,
                                    "Retorno errado ao verificar se o jogo terminou." );

         } /* fim ativa: Testar DES Jogo Finalizado */

	  /* Testar DES Jogo Finalizado */

         else if ( strcmp( ComandoTeste , IMPRIME_JOGO_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "i" , &CondRetEsperada) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DES_ImprimeDesenho( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao verificar se o jogo terminou." );

         } /* fim ativa: Testar DES Jogo Finalizado */
#ifdef _DEBUG
		 /* Testar DES Deturpa */

         else if ( strcmp( ComandoTeste , DETURPA_CMD ) == 0 )
         {
			int AcaoDeturpadora;
            NumLidos = LER_LerParametros( "ii" , &CondRetEsperada, &AcaoDeturpadora) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DES_Deturpar( AcaoDeturpadora ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao verificar se o jogo terminou." );

         } /* fim ativa: Testar DES Deturpa */

		 /* Testar DES Verifica */

		 else if ( strcmp( ComandoTeste , VERIFICA_CMD ) == 0 )
         {
			int numErrosEsperados;
			int numErrosOcorridos;
            NumLidos = LER_LerParametros( "i" , &numErrosEsperados) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            DES_Verifica( &numErrosOcorridos ) ;

            return TST_CompararInt( numErrosEsperados , numErrosOcorridos ,
                                    "Contagem de erros errada." );

         } /* fim ativa: Testar DES Verifica */
#endif
      return TST_CondRetNaoConhec ;

   } /* Fim função: TDES Efetuar operações de teste específicas para desenho */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

