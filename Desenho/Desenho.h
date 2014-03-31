/***************************************************************************
*
*  $MCD Módulo de definição: Módulo desenho
*
*  Arquivo gerado:              Desenho.h
*  Letras identificadoras:      DES
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: ps - Patrick Sava
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   ps   24/03/2014 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto de funçoes para tratar do 
*	  gerenciamento do desenho a medida que o usuário vai preenchendo a 
*	  matriz do Nonogram.
*     Ele integra os módulos de Matriz Genérica, Lista Duplamente Encadeada
*	  Genérica, Célula e Valor para 
*	  permitir ao módulo Jogo uma fácil manipulação do campo de jogo.
*
***************************************************************************/


/***********************************************************************
*
*  $TC Tipo de dados: DES Condições de retorno
*
***********************************************************************/

   typedef enum {

         DES_CondRetOK ,
               /* Executou correto */

         DES_CondRetFaltouMemoria ,
               /* Faltou memória ao alocar dados */

		 DES_CondRetTamanhoInvalido ,
			   /* Tamanho de máximo ou mínimo de matriz permitido violado */

		 DES_CondRetDesenhoNaoIniciado ,
			   /* Estrutura desenho ainda não foi instanciada */

		 DES_CondRetCoordenadaInvalida ,
			   /* Coordenada de marcação inválida */

		 DES_CondRetSemDicas ,
			   /* O usuário não possui mais dicas sobrando */

		 DES_CondRetJogoFinalizado ,
			   /* Todas as células devidas já foram pintadas */

   } DES_tpCondRet ;



/***********************************************************************
*
*  $FC Função: DES Inicia Desenho
*
*  $ED Descrição da função
*     Cria um desenho de jogo sem nenhum preenchimento.
*     Caso já exista um desenho preparado, ele será destruido e um 
*     novo será feito.
*
*  $FV Valor retornado
*     DES_CondRetOK
*     DES_CondRetFaltouMemoria
*     DES_CondRetTamanhoInvalido
*
*  $AE Assertivas de Entrada
*	  - Número de Linhas e Colunas são inteiros entre 3 e 10
*
*  $AS Assertivas de Saída
*	  - O módulo desenho instanciou corretamente a estrutura desenho
*       de forma aleatória.
*	  - O tabuleiro possuirá pelo menos uma célula que terá que ser 
*	    marcada para acabar o jogo
*	  - Valem as assertivas estruturais da estrutura de desenho e sub-
*	    estruturas.
***********************************************************************/

   DES_tpCondRet DES_IniciaDesenho( unsigned int NumLinhas, unsigned int NumColunas ) ;


/***********************************************************************
*
*  $FC Função: DES Altera Marcação de Coordenada
*
*  $ED Descrição da função
*     Dada uma coordenada (X,Y), a função busca pela célula referente e altera
*     sua marcação atual. Se ela já estava marcada passa a ficar em branco e 
*     vice-versa. Essa função automaticamente informa se o jogo terminou.
*
*  $FV Valor retornado
*     DES_CondRetOK
*     DES_CondRetDesenhoNaoIniciado
*     DES_CondRetCoordenadaInvalida
*
*  $AE Assertivas de Entrada
*	  - Coord_X e Coord_Y devem ser valores entre 0 e o máximo do tabuleiro
*	  - Valem as assertivas estruturais da estrutura de desenho e sub-
*	    estruturas.
*
*  $AS Assertivas de Saída
*	  - Sendo pCelula a célula referente a coordenada (X,Y) dada,
*	    //Depois CEL_ExibeMarcação(pCelula) == !CEL_ExibeMarcacao(pCelula) //Antes
***********************************************************************/

   DES_tpCondRet DES_AlteraMarcacaoCoordenada( unsigned int Coord_X, unsigned int Coord_Y );


/***********************************************************************
*
*  $FC Função: DES Ativa Dica
*
*  $ED Descrição da função
*     Marca uma célula do tabuleiro que deveria ser marcada mas ainda está 
*     em branco
*
*  $FV Valor retornado
*     DES_CondRetOK
*     DES_CondRetSemDicas
*     DES_CondRetDesenhoNaoIniciado
*     DES_CondRetJogoFinalizado
*
*  $AE Assertivas de Entrada
*	  - Valem as assertivas estruturais da estrutura de desenho e sub-
*	    estruturas.
*
*  $AS Assertivas de Saída
*	  - Uma nova célula será marcada
*
***********************************************************************/

   DES_tpCondRet DES_AtivaDica ( void );