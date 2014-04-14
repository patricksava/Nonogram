#if ! defined( CELULA_ )
#define CELULA_

/***************************************************************************
 *
 *  $MCD Módulo de definição: Módulo CELULA
 *
 *  Arquivo gerado:              CELULA.H
 *  Letras identificadoras:      CEL
 *
 *  Projeto: Disciplinas INF 1301
 *  Gestor:  DI/PUC-Rio
 *  Autores: lm - Leandro Morgado
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor  Data          Observações
 *	    2.00   lm     12/abr/2014   Término do desenvolvimento
 *      1.00   lm     11/abr/2014   Início do desenvolvimento
 *
 *  $ED Descrição do módulo
 *     Este módulo implementa um conjunto simples de funções para criar e
 *     explorar uma estrutura de dados que se refere à célula da matriz que
 *     constitui o jogo Nonogram. 
 *	   Cada estrutura possui uma quantidade referente aos valores atual	   
 *	   e esperado pela célula, com os numéros inteiros 0 significando 
 *	   valor não marcado e 1 marcado.
 *	    
 ***************************************************************************/


#if defined( VALOR_OWN )
#define VALOR_EXT
#else
#define VALOR_EXT extern
#endif

/***********************************************************************
 *
 *  $TC Tipo de dados: CEL Condicoes de retorno
 *
 *
 ***********************************************************************/


typedef enum {

		
	CEL_CondRetOK = 0,
	/* Executou correto */

	CEL_CondRetMesmaMarcacao = 1,
	/*Não alterou a marcação*/
	
	CEL_CondRetFaltouMemoria = 2,
	/* Faltou memória ao alocar dados */
	
	CEL_CondRetCelulaMorta = 3,
	/* Célula destruída corretamente */
	
	
}CEL_tpCondRet;


/***********************************************************************
 * 
 *   $ED Descrição
 *	     Especifica a estrutura de dados utilizada no módulo.
 *
 ***********************************************************************/

		typedef struct celula Celula;

/***********************************************************************
 *
 *  $FC Função: CEL Criar tipo de dados.
 *
 *  $ED Descrição da função
 *     Cria uma nova estrutura do tipo Celula e retorna um ponteiro
 *	   para esta.
 *
 *  $FV Valor retornado
 *     Celula* celula 
 *
 ***********************************************************************/

        Celula* CEL_CriaCelula( int marcacao_esperada, int marcacao_atual );


/***********************************************************************
 *
 *  $FC Função: CEL retorna marcação esperada.
 *
 *  $ED Descrição da função
 *     Função que devolve o valor da marcacão esperada, isto é, o valor 1 
 *     para marcado e 0 para não marcado.
 *
 *  $EP Parâmetros
 *     Celula* - ponteiro do tipo Celula para a estrutura que se deseja investigar.
 *
 *	$FV Valor retornado
 *     int
 *
 ***********************************************************************/

		int CEL_MarcacaoEsperada( Celula* cell);

/***********************************************************************
 *
 *  $FC Função: CEL retorna marcação atual.
 *
 *  $ED Descrição da função
 *     Função que devolve o valor da marcacão atual, isto é, o valor 1 
 *     para marcado e 0 para não marcado.
 *
 *  $EP Parâmetros
 *     Celula* - ponteiro do tipo Celula para a estrutura que se deseja investigar.
 *
 *	$FV Valor retornado
 *     int
 *
 ***********************************************************************/

		int CEL_MarcacaoAtual( Celula* cell);

/***********************************************************************
 *
 *  $FC Função: CEL altera marcação atual.
 *
 *  $ED Descrição da função
 *     Função que muda o status da marcacão atual. Alera de valor marcado (valor 1)
       para não marcado (valor 0), e vice-versa. 
 *
 *  $EP Parâmetros
 *     Celula* - ponteiro para a estrutura do tipo Celula em que se deseja
 *     alterar o campo relacionado a marcação atual 
 *
 *	$FV Valor retornado
 *     CEL_tpCondRet
 *
 ***********************************************************************/


	CEL_tpCondRet CEL_AlteraMarcacao( Celula* cell);


/***********************************************************************
 *
 *  $FC Função: CEL Destrói tipo de dados.
 *
 *  $ED Descrição da função
 *     Funçao que libera uma estruta de dados do tipo Celula
 *
 *  $EP Parâmetros
 *     Celula* - ponteiro para a estrutura que deseja liberar.
 *
 *  $FV Valor retornado
 *     CEL_tpCondRet
 *
 ***********************************************************************/


	CEL_tpCondRet CEL_DestruirCelula( Celula* cell);

/****************************************************************/

#undef	CELULA_EXT

/********** Fim do módulo de definição: Módulo Célula **********/

#else
#endif
