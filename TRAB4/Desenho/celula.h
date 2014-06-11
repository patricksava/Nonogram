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
 *  $AE  Assertivas Estruturais
 *      Seja a celula um ponteiro para o tipo Celula: 
 *
 *	celula -> marcacao_esperada = 0 ou  celula -> marcacao_esperada = 1 e
 *	celula -> marcacao_atual = 0    ou  celula -> marcacao_atual = 1
 *	
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
	
	CEL_CondRetFaltouMemoria = 1,
	/* Faltou memória ao alocar dados */
	
	CEL_CondRetCelulaVazia = 2,
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
 *	$AE Assertivas de entrada
 *	- Valem as assertivas estruturais.
 *    
 *	$AS Assertivas de saida
 *  - Se não houver problema de memória, o retorno é um endereço válido
 *    para uma celula.
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
 *	$AE Assertivas de entrada
 *	- Valem as assertivas estruturais
 *  - A entrada não pode ser um valor NULL para uma celula
 *	
 *	$AS Assertivas de saida
 *	- O retorno da funçao só poder ser um valor inteiro
 *  - O valor devolvido pela função não pode ser um endereço para uma celula
 *  - Os valores inteiros de saida só podem ser 1 ou 0
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
 *   $AE Assertivas de entrada
 *    - Valem as assertivas estruturais
 *    - A entrada não pode ser um valor NULL para uma celula
 *   
 *    $AS Assertivas de saida
 *	  - O retorno da funçao só poder ser um valor inteiro
 *    - O valor devolvido pela função não pode ser um endereço para uma celula
 *    - Os valores inteiros de saida só podem ser 1 ou 0
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
 *	$AE Assertivas de entrada
 *     - Valem as assertivas estruturais.
 *
 *	$AS Assertivas de saida
 *	    - O retorno da funçao só poder ser do tipo CEL_tpCondRet
 *      - O valor devolvido pela função não pode ser um endereço para uma celula
 *      - Os valores atuais da celula só podem ser transformados para 0 ou 1.
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
 *   $AE Assertivas de entrada
 *	 - Valem as assertivas estruturais
 *
 *	$AE Assertivas de saida
 *	  - O retorno da funçao só poder ser do tipo CEL_tpCondRet
 *    - O valor devolvido pela função não pode ser um endereço para uma celula
 *	  - Se não o endereço de entrada é válido, a estrutura da celula será 
 *      liberada da memória 
 *
 ***********************************************************************/


	CEL_tpCondRet CEL_DestruirCelula( Celula* cell);

/****************************************************************/

#undef	CELULA_EXT

/********** Fim do módulo de definição: Módulo Célula **********/

#else
#endif
