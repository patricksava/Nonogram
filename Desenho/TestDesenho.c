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
*     =alterarmarcacao <int x> <int y>  (x,y) é uma coordenada no tabuleiro
*                   - chama a função DES_AlteraMarcacaoCoordenada( int, int );
* 
*     =ativardica - chama a função DES_AtivaDica( )
*
*     =imprimirjogo - chama a função DES_ImprimeMatrizJogo( )  
*
*     =destroidesenho - chama a função DES_DestroiDesenho( )
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
#define     ALT_MARC_CMD          "=alterarmarcacao"
#define     ATIV_DICA_CMD         "=ativardica"
#define     IMPRIME_JOGO_CMD      "=imprimirjogo"
#define     DESTROI_DES_CMD       "=destroidesenho"

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

            CondRetObtido = DES_IniciaDesenho( ) ;

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

            CondRetObtido = DES_IniciaDesenhoVazio( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar desenho vazio." );

         } /* fim ativa: Testar DES Iniciar desenho vazio */

      /* Testar DES Inicia desenho projetado */

         else if ( strcmp( ComandoTeste , INI_DES_PROJ_CMD ) == 0 )
         {
            char NomeJogo[41];

            NumLidos = LER_LerParametros( "is" ,
                               &CondRetEsperada, NomeJogo) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DES_IniciaDesenhoProjetado( NomeJogo ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar desenho vazio." );

         } /* fim ativa: Testar DES Iniciar desenho projetado */

      /* Testar DES Inicia desenho último jogo salvo */

         else if ( strcmp( ComandoTeste , INI_DES_ULT_JOGO_CMD ) == 0 )
         {
            int linhas, colunas;

            NumLidos = LER_LerParametros( "iii" ,
                               &CondRetEsperada, &linhas, &colunas) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DES_RetomaUltimoJogoSalvo( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar desenho vazio." );

         } /* fim ativa: Testar DES Iniciar desenho último jogo salvo */

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

      /* Testar DES Imprime Matriz de Jogo */

         else if ( strcmp( ComandoTeste , IMPRIME_JOGO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" , &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DES_ImprimeMatrizJogo( ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao imprimir matriz de jogo." );

         } /* fim ativa: Testar DES Imprime Matriz de Jogo */

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

      

      return TST_CondRetNaoConhec ;

   } /* Fim função: TDES Efetuar operações de teste específicas para desenho */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

