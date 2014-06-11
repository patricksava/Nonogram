#if ! defined( MATRIZ_ )
#define MATRIZ_
 
/***************************************************************************
 *
 *  $MCD Módulo de definição: Módulo MATRIZ
 *
 *  Arquivo gerado:              MATRIZ.H
 *  Letras identificadoras:      MAT
 *
 *  Projeto: Disciplinas INF 1301
 *  Gestor:  DI/PUC-Rio
 *  Autores: lm - Leandro Morgado
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data      Observações
 *       2.00   lm   12/abr/2014  Continuaçao do desenvolvimento e revisao
 *       1.00   lm   11/abr/2014  Início do desenvolvimento
 *
 *  $ED Descrição do módulo
 *     Este módulo implementa um conjunto simples de funções para criar e
 *     explorar matrizes. Uma matriz é formada por um vetor de ponteiros,
 *     que apontam para listas duplamente encadeadas, com tantas posições
 *     quanto forem o número de colunas da matriz.
 *     Os índices do vetor de ponteiros dão acesso as colunas da matriz com
 *     tantos elementos quanto forem o número de linhas da matriz.
 *    
 *     Este módulo permite a criação de mais de uma matriz.
 *     Ao iniciar a execução do programa não existe matriz.
 *
 *  $AE Assertivas Estrturais
 *   Matriz contém:
 *       - Número de Linhas
 *       - Número de Colunas
 *       - Ponteira para lista duplamente encadeada
 *   Seja pMatriz um ponteiro para uma matriz, então pMatriz-> numColunas > 0 e pMatriz-> numLinhas >0
 *   Se pMatriz não é nula, então pMatriz->pLista != NULL
 *   Para pMatriz-> pLista valem as assertivas da Lista Duplamente Encadeada
 *
 ***************************************************************************/
 
#if defined( MATRIZ_OWN )
#define MATRIZ_EXT
#else
#define MATRIZ_EXT extern
#endif
 
 
/***********************************************************************
 *
 *  $TC Tipo de dados: MAT Condicoes de retorno
 *
 *
 ***********************************************************************/
 
 
typedef enum {
     
    MAT_CondRetOK = 0, 
    /* Executou correto */
     
    MAT_CondRetFalhou = 1,
    /*Retorno falhou*/
     
    MAT_CondRetMatrizInexistente = 2,
    /*Matriz não existe*/
     
    MAT_CondRetValorNaoInserido = 3,
    /*Valor não inserido na matriz*/
     
    MAT_CondRetValorInalterado  = 4,
    /*Elemento da matriz não alterado*/
     
    MAT_CondRetMatrizIntacta = 5,
    /*Matriz não destruída*/
     
}MAT_tpCondRet;
 
 
/***********************************************************************
 *
 *   $ED Descrição
 *  Especifica a estrutura de dados utilizada no módulo.
 *
 ***********************************************************************/
 
 
    typedef struct tpMatriz TpMatriz;
 
 
/***********************************************************************
 *
 *  $FC Função: MAT Criar Matriz.
 *
 *  $ED Descrição da função
 *     Cria uma nova matriz, vazia, pronta para ser preenchida
 *
 *  $EP Parâmetros
 *     linhas - numero de linhas da matriz
 *	   colunas - numero de colunas da matriz
 *     No modo DEBUG, caracter que representa o tipo de elemento da matriz
 *
 *  $FV Valor retornado
 *     TpMatriz* matriz - ponteiro para a nova matriz
 *
  *	$AE Assertivas de entrada
 *  - Valem as assertivas estruturais de matriz
 *  
 *
 *  $AS Assertivas de saída
 *  - Se a função não devolve um endereco inválido de memória, então,
 *   devolve um endereço para o tipo matriz.
 *    
 ***********************************************************************/
   
     TpMatriz* MAT_CriarMatriz( int linhas, int colunas
	#ifdef _DEBUG
		,char tipoElemento
	 #endif
		);
 
/***********************************************************************
 *
 *  $FC Função: MAT inserir novo elemento na matriz.
 *
 *  $ED Descrição da função
 *     Insere um elemento na primeira posição vazia da matriz.
 *     A leitura da matriz é feita da esquerda para direita e  
 *     de cima para baixo até se encontrar uma célula vazia.
 *
 *  $EP Parâmetros
 *     matriz - matriz que se deseja realizar a inserção 
 *     novo - elemento que se deseja inserir.
 *     Compara - função responsável por comparar 2 elementos
 *               retornando 0 caso sejam iguais.
 *     No modo DEBUG, caracter que representa o tipo de elemento da matriz
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetMatrizInexistente
 *     MAT_CondRetValorNaoInserido
 *
  *   $AE Assertivas de entrada
 *   - Valem as assertivas estruturais de matriz
 *   - Se a entrada tpmatriz para o tipo matriz for um endereco valido, 
 *      um novo elemento sera inserido.
 *
 *   $AS Assertivas de saída
 *   - Se um novo elemento for inserido corretamente, a funcao devolve 
 *     condicao ok.

 ***********************************************************************/
 
     MAT_tpCondRet MAT_InserirNovoElemento(TpMatriz* matriz, void* novo 
	#ifdef _DEBUG
		,char tipoElemento
	 #endif
		);
     
/***********************************************************************
 *
 *  $FC Função: MAT Obter elemento.
 *
 *  $EP Parâmetros
 *     matriz - matriz que se deseja realizar a busca
 *     linha -  linha da matriz onde se procura o elemento.
 *     coluna - coluna da matriz onde se procura o elemento.
 *
 *  $ED Descrição da função
 *    Realiza-se a busca de uma informação dentro de uma matriz,
 *    apartir das coordenadas linha e coluna.
 *
 *  $FV Valor retornado
 *   void* informação - ponteiro para a informação retornada. 
 *
  *  $AE Assertivas de entrada
 *   - Valem as assertivas estruturais de matriz
 *   - Para se obter um elemento, a matriz para o tipo Matriz deve
       possuir um endereço válido.
 * 
 *	$AS Assertivas de saída
 *  - Dada a linha e coluna, a função retorna um endereço valido 
 *    para o tipo do elemento procurado ou endereço inválido
 *
 ***********************************************************************/  
 
    void* MAT_ObterElemento( TpMatriz* matriz, int linha, int coluna );
 
 
/***********************************************************************
 *
 *  $FC Função: LST alterar a informação contida em uma posição da matriz.
 *
 *  $EP Parâmetros
 *     matriz- lista que deseja realizar a alteração
 *     elemento substituto - informação que deseja colocar na matriz.
 *     linha - linha do elemento a ser alterado
 *     coluna - coluna do elemento a ser alterado
 *     No modo DEBUG, caracter que representa o tipo de elemento da matriz
 *
 *  $ED Descrição da função
 *    Altera o valor que está na posição dada da matriz.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetValorInalterado
 *     MAT_CondRetMatrizInexistente
  *	$AE Assertivas de entrada
 *   - Valem as assertivas estruturais de matriz.
 *   - A função deve receber endereços válidos de matriz e elemento, 
 *     para os tipos Matriz e Elemento, respectivamente, para executar
 *	   corretamente.
 *
 *  $AS Assertivas de saída
 *    - Se a funcao alterar o elemento da matriz corretamente, deve retornar
 *      condicao ok.
 *    - Devolve condicao nao ok, quando recebe um endereco invalido de matriz
 *      para o tipo Matriz
 *
 ***********************************************************************/
 
    MAT_tpCondRet MAT_AlterarValor( TpMatriz* matriz, void* elem_subst, int linha, int coluna
	#ifdef _DEBUG
		,char tipoElemento
	 #endif
	);

/***********************************************************************
 *
 *  $FC Função: MAT Destruir matriz.
 *
 *  $EP Parâmetros
 *     matriz - Matriz que se deseja destruir.
 *     ExcluirValor - Função responsável pela exclusão do elemento.
 *
 *  $ED Descrição da função
 *     Libera todos os ponteiros da matriz, destruindo-a.
 *     Faz nada caso a lista não exista.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetMatrizIntacta
 *
  *  $AE Assertivas de entrada
 *  - Valem as assertivas estruturais de matriz.
 *  - Para executar corretamente, a funcao deve receber 
 *    um endereco valido de matriz para o tipo matriz.
 *  
 *  $AS Assertivas de saída
 *  - A funcao devolve condicao ok, quando destroi a matriz corretamente.
 *
 ***********************************************************************/
 
      MAT_tpCondRet MAT_DestruirMatriz( TpMatriz* matriz, void ( * ExcluirValor) ( void * pDado) );

#ifdef _DEBUG

/***********************************************************************
 *
 *  $FC Função: MAT Altera Ponteiro Sucessor.
 *
 *  $EP Parâmetros
 *     matriz - Matriz que se deseja alterar.
 *     Linha - linha que deseja alterar.
 *     Coluna - Coluna que deseja alterar
 *     Elemento - Elemento que deseja que substitua o atual
 *
 *  $ED Descrição da função
 *     Altera o ponteiro sucessor do elemento informado pelas linhas e colunas
 *     para o elemento fornecido.
 *
 *  $AE Assertivas de entrada
 *  - Valem as assertivas estruturais de matriz.
 *  - Para executar corretamente, a funcao deve receber 
 *    dois inteiros válidos e um ponteiro que pode ser NULL
 *  
 *  $AS Assertivas de saída
 *  - A matriz será deturpada como desejada
 *
 ***********************************************************************/

	  void MAT_AlteraPonteiroSucessor( TpMatriz* matriz, int linha, int coluna, void* elem );

/***********************************************************************
 *
 *  $FC Função: MAT Altera Ponteiro Predecessor.
 *
 *  $EP Parâmetros
 *     matriz - Matriz que se deseja alterar.
 *     Linha - linha que deseja alterar.
 *     Coluna - Coluna que deseja alterar
 *     Elemento - Elemento que deseja que substitua o atual
 *
 *  $ED Descrição da função
 *     Altera o ponteiro predecessor do elemento informado pelas linhas e colunas
 *     para o elemento fornecido.
 *
 *  $AE Assertivas de entrada
 *  - Valem as assertivas estruturais de matriz.
 *  - Para executar corretamente, a funcao deve receber 
 *    dois inteiros válidos e um ponteiro que pode ser NULL
 *  
 *  $AS Assertivas de saída
 *  - A matriz será deturpada como desejada
 *
 ***********************************************************************/

	  void MAT_AlteraPonteiroPredecessor( TpMatriz* matriz, int linha, int coluna, void* elem );

/***********************************************************************
 *
 *  $FC Função: MAT Free Incompleto.
 *
 *  $EP Parâmetros
 *     matriz - Matriz que se deseja alterar.
 *
 *  $ED Descrição da função
 *     Exclui um elemento da lista porem sem liberar seu espaco na memoria.
 *
 *  $AE Assertivas de entrada
 *  - Valem as assertivas estruturais de matriz.
 *  
 *  $AS Assertivas de saída
 *  - A matriz será deturpada como desejada, será excluido o nó
 *    corrente sem liberar seu espaço na memória.
 *
 ***********************************************************************/

	  void MAT_FreeIncompleto(TpMatriz* matriz);

/***********************************************************************
*
*  $FC Função: LST Verifica assertivas de Linha e Coluna
*
*  $EP Parâmetros
*     matriz - matriz que deseja verificar.
*
*  $FV Valor retornado
*	  int -> 0 ou 1
*
*  $ED Descrição da função
*	  Acessa a matriz verificando se o numero de linhas e colunas
*	  estão dentro do permitido
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da matriz.
*
*  $AS Assertivas de Saída
*	Retornará 1 caso haja algum erro, ou 0 se estiver correto.
*
***********************************************************************/

	  int MAT_VerificaAssertivaLinhaColuna (TpMatriz* matriz);

/***********************************************************************
*
*  $FC Função: LST Verifica assertiva Ponteiro para Lista
*
*  $EP Parâmetros
*     matriz - matriz que deseja verificar.
*
*  $FV Valor retornado
*	  int -> 0 ou 1
*
*  $ED Descrição da função
*	  Acessa a matriz verificando se o ponteiro para lista é valido
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da matriz.
*
*  $AS Assertivas de Saída
*	Retornará 1 caso haja algum erro, ou 0 se estiver correto.
*
***********************************************************************/

	  int MAT_VerificaAssertivaPontLista (TpMatriz* matriz);

/***********************************************************************
*
*  $FC Função: LST Verifica assertivas das Listas da Matriz
*
*  $EP Parâmetros
*     matriz - matriz que deseja verificar.
*
*  $FV Valor retornado
*	  int -> 0 ou 1
*
*  $ED Descrição da função
*	  Acessa a matriz verificando se as assertivas das listas que compoe a matriz estao OK
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da matriz.
*
*  $AS Assertivas de Saída
*	Retornará 1 caso haja algum erro, ou 0 se estiver correto.
*
***********************************************************************/

	  int MAT_VerificaAssertivaListas (TpMatriz* matriz);

#endif
/****************************************************************/
 
#undef  MATRIZ_EXT
 
/********** Fim do módulo de definição: Módulo MATRIZ **********/
 
#else
#endif
