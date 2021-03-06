#if ! defined( VALOR_ )
#define VALOR_

/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo Valor
*
*  Arquivo gerado:              VALOR.H
*  Letras identificadoras:      VAL
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mbv - Maria Beatriz Vaz
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	   3.00   mbv   14/abr/2014 Revis�o do c�digo e dos coment�rios
*	   2.00   mbv   11/abr/2014 T�rmino do desenvolvimento
*      1.00   mbv   19/mar/2014 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     explorar uma estrutura de dados que se refere ao valor do jogo
*	  Nonogram. 
*	  Cada estrutura possui uma quantidade referente ao n�mero de quadrados
*	  marcados em sequencia a cada linha e o n�mero de quadrados pintados. 
*
***************************************************************************/
 
#if defined( VALOR_OWN )
   #define VALOR_EXT
#else
   #define VALOR_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: VAL Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         VAL_CondRetOk = 0 ,
               /* Executou correto */

         VAL_CondRetValorInexistente= 1 ,
               /* Estrutura n�o existe. */

		 VAL_CondRetFaltouMemoria = 3 ,
               /* Faltou mem�ria ao alocar dados */

   } VAL_tpCondRet ;

/***********************************************************************
* 
*   $ED Descri��o
*	Especifica a estrutura de dados utilizada no m�dulo.
*
***********************************************************************/

	typedef struct tpvalor TpValor;

/***********************************************************************
*
*  $FC Fun��o: VAL Criar tipo de dados.
*
*  $ED Descri��o da fun��o
*     Cria uma nova estrutura do tipo Valor e retorna um ponteiro
*	  para esta.
*
*  $FV Valor retornado
*     TpValor  * - ponteiro para a estrutura valor.
*
***********************************************************************/

	TpValor * VAL_CriarValor ( void );

/***********************************************************************
*
*  $FC Fun��o: VAL Alterar quantidade marcados.
*
*  $ED Descri��o da fun��o
*     Fun��o b�sica para criar o desenho do jogo. Altera
*	  a quantidade dos quadrados marcados em sequ�ncia para
*	  a desejada.
*
*  $EP Par�metros
*     TpValor * - Ponteiro para a estrutura que deseja alterar.
*	  int - quantidade de quadrados que deseja marcar.
*
*  $FV Valor retornado
*     VAL_tpCondRet
*
***********************************************************************/

	VAL_tpCondRet VAL_AlterarQntdMarcados ( TpValor * Valor , int quantidade );

/***********************************************************************
*
*  $FC Fun��o: VAL Incrementar a quantidade de pintados.
*
*  $ED Descri��o da fun��o
*     Cada vez que o usu�rio do jogo pintar um quadrado da figura
*	  devemos aumentar a quantidade de quadrados pintados em 1.
*
*  $EP Par�metros
*     TpValor * - Ponteiro para a estrutura que deseja alterar.
*
*  $FV Valor retornado
*     VAL_tpCondRet
*
***********************************************************************/

	VAL_tpCondRet VAL_IncrementarQntdPintados ( TpValor * Valor );

/***********************************************************************
*
*  $FC Fun��o: VAL Decrementar a quantidade de pintados.
*
*  $ED Descri��o da fun��o
*     Cada vez que o usu�rio do jogo desmarcar um quadrado da figura
*	  devemos diminuir a quantidade de quadrados pintados em 1.
*
*  $EP Par�metros
*     TpValor * - Ponteiro para a estrutura que deseja alterar.
*
*  $FV Valor retornado
*     VAL_tpCondRet
*
***********************************************************************/

	VAL_tpCondRet VAL_DecrementarQntdPintados ( TpValor * Valor );

/***********************************************************************
*
*  $FC Fun��o: VAL Obtem a quantidade de marcados.
*
*  $ED Descri��o da fun��o
*     Fun��o devolve a quantidade de quadrados do jogo
*	  marcados at� o momento.
*
*  $EP Par�metros
*     TpValor * - Ponteiro para a estrutura que deseja alterar.
*
*  $FV Valor retornado
*     int - receber a quantidade.
*
***********************************************************************/

	int VAL_ObterMarcados ( TpValor * Valor );

/***********************************************************************
*
*  $FC Fun��o: VAL Obtem a quantidade de pintados.
*
*  $ED Descri��o da fun��o
*     Fun�ao devolve a quantidade de atual de quadrados
*	  pintados na estrutura at� o momento.
*
*  $EP Par�metros
*     TpValor * - Ponteiro para a estrutura que deseja obter.
*
*  $FV Valor retornado
*     int - receber a quantidade.
*
***********************************************************************/

	int VAL_ObterPintados ( TpValor * Valor  );

/***********************************************************************
*
*  $FC Fun��o: VAL Resseta tipo de dados.
*
*  $ED Descri��o da fun��o
*     Fun�ao que resseta uma estruta de dados do tipo Valor
*
*  $EP Par�metros
*     TpValor * - Ponteiro para estrutura que deseja ressetar.
*
*  $FV Valor retornado
*     VAL_tpCondRet
*
***********************************************************************/

	VAL_tpCondRet VAL_RessetarValor ( TpValor * Valor );

/***********************************************************************
*
*  $FC Fun��o: VAL Destr�i tipo de dados.
*
*  $ED Descri��o da fun��o
*     Fun�ao que libera uma estruta de dados do tipo Valor
*
*  $EP Par�metros
*     TpValor * -Ponteiro para a estrutura que deseja liberar.
*
*  $FV Valor retornado
*     VAL_tpCondRet
*
***********************************************************************/

VAL_tpCondRet VAL_DestruirValor ( TpValor * Valor );

/****************************************************************/

#undef	LISTA_EXT

/********** Fim do m�dulo de defini��o: M�dulo Lista **********/

#else
#endif
