#if ! defined( MATRIZ_ )
#define MATRIZ_
 
/***************************************************************************
 *
 *  $MCD M�dulo de defini��o: M�dulo MATRIZ
 *
 *  Arquivo gerado:              MATRIZ.H
 *  Letras identificadoras:      MAT
 *
 *  Projeto: Disciplinas INF 1301
 *  Gestor:  DI/PUC-Rio
 *  Autores: lm - Leandro Morgado
 *
 *  $HA Hist�rico de evolu��o:
 *     Vers�o  Autor    Data      Observa��es
 *       2.00   lm   12/abr/2014  Continua�ao do desenvolvimento e revisao
 *       1.00   lm   11/abr/2014  In�cio do desenvolvimento
 *
 *  $ED Descri��o do m�dulo
 *     Este m�dulo implementa um conjunto simples de fun��es para criar e
 *     explorar matrizes. Uma matriz � formada por um vetor de ponteiros,
 *     que apontam para listas duplamente encadeadas, com tantas posi��es
 *     quanto forem o n�mero de colunas da matriz.
 *     Os �ndices do vetor de ponteiros d�o acesso as colunas da matriz com
 *     tantos elementos quanto forem o n�mero de linhas da matriz.
 *    
 *     Este m�dulo permite a cria��o de mais de uma matriz.
 *     Ao iniciar a execu��o do programa n�o existe matriz.
 *
 *  $AE Assertivas Estrturais
 *   Matriz cont�m:
 *       - N�mero de Linhas
 *       - N�mero de Colunas
 *       - Ponteira para lista duplamente encadeada
 *   Seja pMatriz um ponteiro para uma matriz, ent�o pMatriz-> numColunas > 0 e pMatriz-> numLinhas >0
 *   Se pMatriz n�o � nula, ent�o pMatriz->pLista != NULL
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
    /*Matriz n�o existe*/
     
    MAT_CondRetValorNaoInserido = 3,
    /*Valor n�o inserido na matriz*/
     
    MAT_CondRetValorInalterado  = 4,
    /*Elemento da matriz n�o alterado*/
     
    MAT_CondRetMatrizIntacta = 5,
    /*Matriz n�o destru�da*/
     
}MAT_tpCondRet;
 
 
/***********************************************************************
 *
 *   $ED Descri��o
 *  Especifica a estrutura de dados utilizada no m�dulo.
 *
 ***********************************************************************/
 
 
    typedef struct tpMatriz TpMatriz;
 
 
/***********************************************************************
 *
 *  $FC Fun��o: MAT Criar Matriz.
 *
 *  $ED Descri��o da fun��o
 *     Cria uma nova matriz, vazia, pronta para ser preenchida
 *
 *  $EP Par�metros
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
 *  $AS Assertivas de sa�da
 *  - Se a fun��o n�o devolve um endereco inv�lido de mem�ria, ent�o,
 *   devolve um endere�o para o tipo matriz.
 *    
 ***********************************************************************/
   
     TpMatriz* MAT_CriarMatriz( int linhas, int colunas
	#ifdef _DEBUG
		,char tipoElemento
	 #endif
		);
 
/***********************************************************************
 *
 *  $FC Fun��o: MAT inserir novo elemento na matriz.
 *
 *  $ED Descri��o da fun��o
 *     Insere um elemento na primeira posi��o vazia da matriz.
 *     A leitura da matriz � feita da esquerda para direita e  
 *     de cima para baixo at� se encontrar uma c�lula vazia.
 *
 *  $EP Par�metros
 *     matriz - matriz que se deseja realizar a inser��o 
 *     novo - elemento que se deseja inserir.
 *     Compara - fun��o respons�vel por comparar 2 elementos
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
 *   $AS Assertivas de sa�da
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
 *  $FC Fun��o: MAT Obter elemento.
 *
 *  $EP Par�metros
 *     matriz - matriz que se deseja realizar a busca
 *     linha -  linha da matriz onde se procura o elemento.
 *     coluna - coluna da matriz onde se procura o elemento.
 *
 *  $ED Descri��o da fun��o
 *    Realiza-se a busca de uma informa��o dentro de uma matriz,
 *    apartir das coordenadas linha e coluna.
 *
 *  $FV Valor retornado
 *   void* informa��o - ponteiro para a informa��o retornada. 
 *
  *  $AE Assertivas de entrada
 *   - Valem as assertivas estruturais de matriz
 *   - Para se obter um elemento, a matriz para o tipo Matriz deve
       possuir um endere�o v�lido.
 * 
 *	$AS Assertivas de sa�da
 *  - Dada a linha e coluna, a fun��o retorna um endere�o valido 
 *    para o tipo do elemento procurado ou endere�o inv�lido
 *
 ***********************************************************************/  
 
    void* MAT_ObterElemento( TpMatriz* matriz, int linha, int coluna );
 
 
/***********************************************************************
 *
 *  $FC Fun��o: LST alterar a informa��o contida em uma posi��o da matriz.
 *
 *  $EP Par�metros
 *     matriz- lista que deseja realizar a altera��o
 *     elemento substituto - informa��o que deseja colocar na matriz.
 *     linha - linha do elemento a ser alterado
 *     coluna - coluna do elemento a ser alterado
 *     No modo DEBUG, caracter que representa o tipo de elemento da matriz
 *
 *  $ED Descri��o da fun��o
 *    Altera o valor que est� na posi��o dada da matriz.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetValorInalterado
 *     MAT_CondRetMatrizInexistente
  *	$AE Assertivas de entrada
 *   - Valem as assertivas estruturais de matriz.
 *   - A fun��o deve receber endere�os v�lidos de matriz e elemento, 
 *     para os tipos Matriz e Elemento, respectivamente, para executar
 *	   corretamente.
 *
 *  $AS Assertivas de sa�da
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
 *  $FC Fun��o: MAT Destruir matriz.
 *
 *  $EP Par�metros
 *     matriz - Matriz que se deseja destruir.
 *     ExcluirValor - Fun��o respons�vel pela exclus�o do elemento.
 *
 *  $ED Descri��o da fun��o
 *     Libera todos os ponteiros da matriz, destruindo-a.
 *     Faz nada caso a lista n�o exista.
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
 *  $AS Assertivas de sa�da
 *  - A funcao devolve condicao ok, quando destroi a matriz corretamente.
 *
 ***********************************************************************/
 
      MAT_tpCondRet MAT_DestruirMatriz( TpMatriz* matriz, void ( * ExcluirValor) ( void * pDado) );

#ifdef _DEBUG

/***********************************************************************
 *
 *  $FC Fun��o: MAT Altera Ponteiro Sucessor.
 *
 *  $EP Par�metros
 *     matriz - Matriz que se deseja alterar.
 *     Linha - linha que deseja alterar.
 *     Coluna - Coluna que deseja alterar
 *     Elemento - Elemento que deseja que substitua o atual
 *
 *  $ED Descri��o da fun��o
 *     Altera o ponteiro sucessor do elemento informado pelas linhas e colunas
 *     para o elemento fornecido.
 *
 *  $AE Assertivas de entrada
 *  - Valem as assertivas estruturais de matriz.
 *  - Para executar corretamente, a funcao deve receber 
 *    dois inteiros v�lidos e um ponteiro que pode ser NULL
 *  
 *  $AS Assertivas de sa�da
 *  - A matriz ser� deturpada como desejada
 *
 ***********************************************************************/

	  void MAT_AlteraPonteiroSucessor( TpMatriz* matriz, int linha, int coluna, void* elem );

/***********************************************************************
 *
 *  $FC Fun��o: MAT Altera Ponteiro Predecessor.
 *
 *  $EP Par�metros
 *     matriz - Matriz que se deseja alterar.
 *     Linha - linha que deseja alterar.
 *     Coluna - Coluna que deseja alterar
 *     Elemento - Elemento que deseja que substitua o atual
 *
 *  $ED Descri��o da fun��o
 *     Altera o ponteiro predecessor do elemento informado pelas linhas e colunas
 *     para o elemento fornecido.
 *
 *  $AE Assertivas de entrada
 *  - Valem as assertivas estruturais de matriz.
 *  - Para executar corretamente, a funcao deve receber 
 *    dois inteiros v�lidos e um ponteiro que pode ser NULL
 *  
 *  $AS Assertivas de sa�da
 *  - A matriz ser� deturpada como desejada
 *
 ***********************************************************************/

	  void MAT_AlteraPonteiroPredecessor( TpMatriz* matriz, int linha, int coluna, void* elem );

/***********************************************************************
 *
 *  $FC Fun��o: MAT Free Incompleto.
 *
 *  $EP Par�metros
 *     matriz - Matriz que se deseja alterar.
 *
 *  $ED Descri��o da fun��o
 *     Exclui um elemento da lista porem sem liberar seu espaco na memoria.
 *
 *  $AE Assertivas de entrada
 *  - Valem as assertivas estruturais de matriz.
 *  
 *  $AS Assertivas de sa�da
 *  - A matriz ser� deturpada como desejada, ser� excluido o n�
 *    corrente sem liberar seu espa�o na mem�ria.
 *
 ***********************************************************************/

	  void MAT_FreeIncompleto(TpMatriz* matriz);

/***********************************************************************
*
*  $FC Fun��o: LST Verifica assertivas de Linha e Coluna
*
*  $EP Par�metros
*     matriz - matriz que deseja verificar.
*
*  $FV Valor retornado
*	  int -> 0 ou 1
*
*  $ED Descri��o da fun��o
*	  Acessa a matriz verificando se o numero de linhas e colunas
*	  est�o dentro do permitido
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da matriz.
*
*  $AS Assertivas de Sa�da
*	Retornar� 1 caso haja algum erro, ou 0 se estiver correto.
*
***********************************************************************/

	  int MAT_VerificaAssertivaLinhaColuna (TpMatriz* matriz);

/***********************************************************************
*
*  $FC Fun��o: LST Verifica assertiva Ponteiro para Lista
*
*  $EP Par�metros
*     matriz - matriz que deseja verificar.
*
*  $FV Valor retornado
*	  int -> 0 ou 1
*
*  $ED Descri��o da fun��o
*	  Acessa a matriz verificando se o ponteiro para lista � valido
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da matriz.
*
*  $AS Assertivas de Sa�da
*	Retornar� 1 caso haja algum erro, ou 0 se estiver correto.
*
***********************************************************************/

	  int MAT_VerificaAssertivaPontLista (TpMatriz* matriz);

/***********************************************************************
*
*  $FC Fun��o: LST Verifica assertivas das Listas da Matriz
*
*  $EP Par�metros
*     matriz - matriz que deseja verificar.
*
*  $FV Valor retornado
*	  int -> 0 ou 1
*
*  $ED Descri��o da fun��o
*	  Acessa a matriz verificando se as assertivas das listas que compoe a matriz estao OK
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da matriz.
*
*  $AS Assertivas de Sa�da
*	Retornar� 1 caso haja algum erro, ou 0 se estiver correto.
*
***********************************************************************/

	  int MAT_VerificaAssertivaListas (TpMatriz* matriz);

#endif
/****************************************************************/
 
#undef  MATRIZ_EXT
 
/********** Fim do m�dulo de defini��o: M�dulo MATRIZ **********/
 
#else
#endif
