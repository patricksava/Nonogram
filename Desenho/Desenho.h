/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo desenho
*
*  Arquivo gerado:              Desenho.h
*  Letras identificadoras:      DES
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: ps - Patrick Sava
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       1.00   ps   24/03/2014 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto de fun�oes para tratar do
*	  gerenciamento do desenho a medida que o usu�rio vai preenchendo a
*	  matriz do Nonogram.
*     Ele integra os m�dulos de Matriz Gen�rica, Lista Duplamente Encadeada
*	  Gen�rica, C�lula e Valor para
*	  permitir ao m�dulo Jogo uma f�cil manipula��o do campo de jogo.
*
***************************************************************************/


/***********************************************************************
*
*  $TC Tipo de dados: DES Condi��es de retorno
*
***********************************************************************/

   typedef enum {

         DES_CondRetOK ,
               /* Executou correto */

         DES_CondRetFaltouMemoria ,
               /* Faltou mem�ria ao alocar dados */

		 DES_CondRetTamanhoInvalido ,
			   /* Tamanho de m�ximo ou m�nimo de matriz permitido violado */

		 DES_CondRetDesenhoNaoIniciado ,
			   /* Estrutura desenho ainda n�o foi instanciada */

		 DES_CondRetCoordenadaInvalida ,
			   /* Coordenada de marca��o inv�lida */

		 DES_CondRetSemDicas ,
			   /* O usu�rio n�o possui mais dicas sobrando */

		 DES_CondRetJogoFinalizado ,
			   /* Todas as c�lulas devidas j� foram pintadas */

   } DES_tpCondRet ;



/***********************************************************************
*
*  $FC Fun��o: DES Inicia Desenho
*
*  $ED Descri��o da fun��o
*     Cria um desenho de jogo sem nenhum preenchimento.
*     Caso j� exista um desenho preparado, ele ser� destruido e um
*     novo ser� feito.
*
*  $FV Valor retornado
*     DES_CondRetOK
*     DES_CondRetFaltouMemoria
*     DES_CondRetTamanhoInvalido
*
*  $AE Assertivas de Entrada
*	  - N�mero de Linhas e Colunas s�o inteiros entre 3 e 10
*
*  $AS Assertivas de Sa�da
*	  - O m�dulo desenho instanciou corretamente a estrutura desenho
*       de forma aleat�ria.
*	  - O tabuleiro possuir� pelo menos uma c�lula que ter� que ser
*	    marcada para acabar o jogo
*	  - Valem as assertivas estruturais da estrutura de desenho e sub-
*	    estruturas.
***********************************************************************/

   DES_tpCondRet DES_IniciaDesenho( unsigned int NumLinhas, unsigned int NumColunas ) ;


/***********************************************************************
*
*  $FC Fun��o: DES Altera Marca��o de Coordenada
*
*  $ED Descri��o da fun��o
*     Dada uma coordenada (X,Y), a fun��o busca pela c�lula referente e altera
*     sua marca��o atual. Se ela j� estava marcada passa a ficar em branco e
*     vice-versa. Essa fun��o automaticamente informa se o jogo terminou.
*
*  $FV Valor retornado
*     DES_CondRetOK
*     DES_CondRetDesenhoNaoIniciado
*     DES_CondRetCoordenadaInvalida
*
*  $AE Assertivas de Entrada
*	  - Coord_X e Coord_Y devem ser valores entre 0 e o m�ximo do tabuleiro
*	  - Valem as assertivas estruturais da estrutura de desenho e sub-
*	    estruturas.
*
*  $AS Assertivas de Sa�da
*	  - Sendo pCelula a c�lula referente a coordenada (X,Y) dada,
*	    //Depois CEL_ExibeMarca��o(pCelula) == !CEL_ExibeMarcacao(pCelula) //Antes
***********************************************************************/

   DES_tpCondRet DES_AlteraMarcacaoCoordenada( unsigned int Coord_X, unsigned int Coord_Y );


/***********************************************************************
*
*  $FC Fun��o: DES Ativa Dica
*
*  $ED Descri��o da fun��o
*     Marca uma c�lula do tabuleiro que deveria ser marcada mas ainda est�
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
*  $AS Assertivas de Sa�da
*	  - Uma nova c�lula ser� marcada
*
***********************************************************************/

   DES_tpCondRet DES_AtivaDica ( void );

/***********************************************************************
*
*  $FC Fun��o: DES Imprime Matriz Jogo
*
*  $ED Descri��o da fun��o
*     Imprime na tela a matriz de jogo com as marcações feitas até o
*     momento
*
*  $FV Valor retornado
*     DES_CondRetOK
*     DES_CondRetDesenhoNaoIniciado
*
*  $AE Assertivas de Entrada
*
*  $AS Assertivas de Sa�da
*
***********************************************************************/

   DES_tpCondRet DES_ImprimeMatrizJogo( void );


