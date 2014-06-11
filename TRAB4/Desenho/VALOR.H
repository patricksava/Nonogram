#if ! defined( VALOR_ )
#define VALOR_

/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Valor
*
*  Arquivo gerado:              VALOR.H
*  Letras identificadoras:      VAL
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mbv - Maria Beatriz Vaz
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	   3.00   mbv   14/abr/2014 Revisão do código e dos comentários
*	   2.00   mbv   11/abr/2014 Término do desenvolvimento
*      1.00   mbv   19/mar/2014 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar uma estrutura de dados que se refere ao valor do jogo
*	  Nonogram. 
*	  Cada estrutura possui uma quantidade referente ao número de quadrados
*	  marcados em sequencia a cada linha e o número de quadrados pintados. 
*
*  $AE Assertivas Estrturais
*  Seja pValor um ponteiro para uma estrtura TpValor.
*  pValor -> QntdMarcados >= 0 e pValor -> QntdPintados >= 0
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
               /* Estrutura não existe. */

		 VAL_CondRetFaltouMemoria = 3 ,
               /* Faltou memória ao alocar dados */

   } VAL_tpCondRet ;

/***********************************************************************
* 
*   $ED Descrição
*	Especifica a estrutura de dados utilizada no módulo.
*
***********************************************************************/

	typedef struct tpvalor TpValor;

/***********************************************************************
*
*  $FC Função: VAL Criar tipo de dados.
*
*  $ED Descrição da função
*     Cria uma nova estrutura do tipo Valor e retorna um ponteiro
*	  para esta.
*
*  $FV Valor retornado
*     TpValor  * - ponteiro para a estrutura valor.
*
*  $AE Assertivas de Entrada
*	O ponteiro para receber o valor deve ser NULL
*
*  $AS Assertivas de Saída
*	Caso o espaço na memória seja sufciente, o valor será criado.
*   TpValor -> QntdMarcados == TpValor -> QntdPintados == 0
*
***********************************************************************/

	TpValor * VAL_CriarValor ( void );

/***********************************************************************
*
*  $FC Função: VAL Alterar quantidade marcados.
*
*  $ED Descrição da função
*     Função básica para criar o desenho do jogo. Altera
*	  a quantidade dos quadrados marcados em sequência para
*	  a desejada.
*
*  $EP Parâmetros
*     TpValor * - Ponteiro para a estrutura que deseja alterar.
*	  int - quantidade de quadrados que deseja marcar.
*
*  $FV Valor retornado
*     VAL_tpCondRet
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais do valor.
*
*  $AS Assertivas de Saída
*	Caso a estrutura valor seja valída, o número de marcados será
*	alterado.
*   Valem as assertivas estrururais do valor.
*
***********************************************************************/

	VAL_tpCondRet VAL_AlterarQntdMarcados ( TpValor * Valor , int quantidade );

/***********************************************************************
*
*  $FC Função: VAL Incrementar a quantidade de pintados.
*
*  $ED Descrição da função
*     Cada vez que o usuário do jogo pintar um quadrado da figura
*	  devemos aumentar a quantidade de quadrados pintados em 1.
*
*  $EP Parâmetros
*     TpValor * - Ponteiro para a estrutura que deseja alterar.
*
*  $FV Valor retornado
*     VAL_tpCondRet
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais do valor.
*
*  $AS Assertivas de Saída
*	Caso a estrutura valor seja valída, o número de pintados será
*	acrescido em 1.
*   Valem as assertivas estrururais do valor.
*
***********************************************************************/

	VAL_tpCondRet VAL_IncrementarQntdPintados ( TpValor * Valor );

/***********************************************************************
*
*  $FC Função: VAL Decrementar a quantidade de pintados.
*
*  $ED Descrição da função
*     Cada vez que o usuário do jogo desmarcar um quadrado da figura
*	  devemos diminuir a quantidade de quadrados pintados em 1.
*
*  $EP Parâmetros
*     TpValor * - Ponteiro para a estrutura que deseja alterar.
*
*  $FV Valor retornado
*     VAL_tpCondRet
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais do valor.
*
*  $AS Assertivas de Saída
*	Caso a estrutura valor seja valída, o número de pintados será
*	diminuido em 1.
*   Valem as assertivas estrururais do valor.
*
***********************************************************************/

	VAL_tpCondRet VAL_DecrementarQntdPintados ( TpValor * Valor );

/***********************************************************************
*
*  $FC Função: VAL Obtem a quantidade de marcados.
*
*  $ED Descrição da função
*     Função devolve a quantidade de quadrados do jogo
*	  marcados até o momento.
*
*  $EP Parâmetros
*     TpValor * - Ponteiro para a estrutura que deseja alterar.
*
*  $FV Valor retornado
*     int - receber a quantidade.
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais do valor.
*
*  $AS Assertivas de Saída
*	Caso a estrutura valor seja valída, a quantidade de marcados
*	sera retornada.
*   Valem as assertivas estrururais do valor.
*
***********************************************************************/

	int VAL_ObterMarcados ( TpValor * Valor );

/***********************************************************************
*
*  $FC Função: VAL Obtem a quantidade de pintados.
*
*  $ED Descrição da função
*     Funçao devolve a quantidade de atual de quadrados
*	  pintados na estrutura até o momento.
*
*  $EP Parâmetros
*     TpValor * - Ponteiro para a estrutura que deseja obter.
*
*  $FV Valor retornado
*     int - receber a quantidade.
*
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais do valor.
*
*  $AS Assertivas de Saída
*	Caso a estrutura valor seja valída, o número de pintados será
*	retornado.
*   Valem as assertivas estrururais do valor.
*
***********************************************************************/

	int VAL_ObterPintados ( TpValor * Valor  );

/***********************************************************************
*
*  $FC Função: VAL Resseta tipo de dados.
*
*  $ED Descrição da função
*     Funçao que resseta uma estruta de dados do tipo Valor
*
*  $EP Parâmetros
*     TpValor * - Ponteiro para estrutura que deseja ressetar.
*
*  $FV Valor retornado
*     VAL_tpCondRet
*
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais do valor.
*
*  $AS Assertivas de Saída
*	Caso a estrutura valor seja valída,
*	TpValor -> QntdMarcados == TpValor -> QntdPintados == 0. 
*   Valem as assertivas estrururais do valor.
*
***********************************************************************/

	VAL_tpCondRet VAL_RessetarValor ( TpValor * Valor );

/***********************************************************************
*
*  $FC Função: VAL Destrói tipo de dados.
*
*  $ED Descrição da função
*     Funçao que libera uma estruta de dados do tipo Valor
*
*  $EP Parâmetros
*     TpValor * -Ponteiro para a estrutura que deseja liberar.
*
*  $FV Valor retornado
*     VAL_tpCondRet
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais do valor.
*
*  $AS Assertivas de Saída
*	Caso a estrutura valor seja valída, o espaço alocado para
*	a estrtura será liberado.
*
***********************************************************************/

	VAL_tpCondRet VAL_DestruirValor ( TpValor * Valor );

/****************************************************************/

#undef	LISTA_EXT

/********** Fim do módulo de definição: Módulo Lista **********/

#else
#endif
