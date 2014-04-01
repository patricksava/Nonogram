/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo Desenho
*
*  Arquivo gerado:              Desenho.c
*  Letras identificadoras:      DES
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: ps  - Patrick Sava
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       1.00   ps   24/03/2014 In�cio do desenvolvimento
*
***************************************************************************/

#include   <stdlib.h>
#include   <stdio.h>
#include   <time.h>

#include   "Desenho.h"

//#include   "ListaGenerica.h"
//#include   "Valor.h"
//#include   "MatrizGenerica.h"
//#include   "Celula.h"

/*****  Constantes encapsuladas no m�dulo  *****/

#define NUM_LINHAS_MINIMO 3
#define NUM_LINHAS_MAXIMO 10

#define NUM_COLUNAS_MINIMO 3
#define NUM_COLUNAS_MAXIMO 10

#define NUM_MAX_DICAS 10

/***********************************************************************
*
*  $TC Tipo de dados: DES Estrutura Desenho Nonogram
*
*
*  $ED Descri��o do tipo
*     Descreve a organiza��o do desenho
*
***********************************************************************/

	typedef struct desenho{

		tpMatrizGen * pMatrizJogo;
			/* Ponteiro para matriz de c�lulas */

		int iLinhas;
			/* N�mero de linhas da matriz */

		int iColunas;
			/* N�mero de colunas da matriz */

		tpLista ** pListasVerticais;
			/* Vetor de Listas de Valores verticais */

		tpLista ** pListasHorizontais;
			/* Vetor de Listas de Valores verticais */

		int iDicas;
			/* N�mero de dicas que cada usu�rio possui por jogo */

	} tpDesenho ;

/*****  Dados encapsulados no m�dulo  *****/

    static tpDesenho * pDesenho = NULL ;
        /* Ponteiro para o desenho */

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

	static void PreencheAleatorioMatriz ( void );

	static DES_tpCondRet InicializaListasHorizontais ( void );

	static DES_tpCondRet InicializaListasVerticais ( void );
	
	static int JogoFinalizado ( void );

	static void ExibeGameOver ( void );

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: DES Inicia Desenho
*
*  Cria aleatoriamente um esquema de nonogram pronto para ser jogado.
*  Gera, de acordo com o resultado de gera�ao aleat�rio, as listas de valores
*  verticais e horizontais que sao cruciais para o fluir do jogo.
*
*  Complexidade: O(n^2)
*
****************************************************************************/

	DES_tpCondRet DES_IniciaDesenho( unsigned int NumLinhas, unsigned int NumColunas )
	{
		int i, j;
		DES_tpCondRet CondRet;

		//Verifica se a quantidade de linhas e de colunas sao v�lidas
		if( NumLinhas < NUM_LINHAS_MINIMO || NumColunas < NUM_COLUNAS_MINIMO ||
		    NumLinhas > NUM_LINHAS_MAXIMO || NumColunas > NUM_COLUNAS_MAXIMO )
			return DES_CondRetTamanhoInvalido;

		//Aloca a estrutura desenho
		pDesenho = ( tpDesenho* ) malloc( sizeof( tpDesenho ) );

		//Falhou a aloca�ao de mem�ria
		if( pDesenho == NULL )
			return DES_CondRetFaltouMemoria;

		pDesenho->iColunas = NumColunas;
		pDesenho->iLinhas = NumLinhas ;
		pDesenho->iDicas = NUM_MAX_DICAS; 

		//Chama o m�dulo de matriz e guarda o ponteiro na estrutura desenho
		CondRet = MAT_CriaMatriz( pDesenho->pMatrizJogo, NumLinhas, NumColunas );
		if(CondRet != DES_CondRetOk)
			return CondRet;

		//Gera o esquema de forma aleat�ria
		PreencheAleatorioMatriz( );

		//Aloca o vetor que vai guardar as cabe�as de listas horizontais
		pDesenho->pListasHorizontais = ( tpLista ** ) malloc( NumLinhas * sizeof( tpLista* ) );
		if(pDesenho->pListasHorizontais == NULL)
			return DES_CondRetFaltouMemoria;

		//Aloca o vetor que vai guardar as cabe�as de listas verticais
		pDesenho->pListasVerticais   = ( tpLista ** ) malloc( NumColunas * sizeof( tpLista* ) );
		if( pDesenho->pListasVerticais == NULL )
			return DES_CondRetFaltouMemoria;

		// Inicializa�ao das Listas e valores de linha
		CondRet = InicializaListasHorizontais( );
		if(CondRet != DES_CondRetOk)
			return CondRet;

		// Inicializa�ao das Listas e valores de coluna
		CondRet = InicializaListasVerticais( );
		if(CondRet != DES_CondRetOk)
			return CondRet;

		return DES_CondRetOk;
	}

/***************************************************************************
*
*  Fun��o: DES Altera Marca��o de Coordenada
*
*  Dada uma coordenada (X,Y), a fun��o busca pela c�lula referente e altera
*  sua marca��o atual. Se ela j� estava marcada passa a ficar em branco e
*  vice-versa.
*
*  Complexidade: O(n) -> Custo de encontrar na lista o elemento.
*
****************************************************************************/

	DES_tpCondRet DES_AlteraMarcacaoCoordenada( unsigned int Coord_X, unsigned int Coord_Y )
	{

		//Teste se a estrutura desenho j� existe
		if( pDesenho == NULL )
			return DES_CondRetDesenhoNaoIniciado;

		//Teste se as coordenadas dadas est�o dentro do permitido
		if( Coord_X > pDesenho->iLinhas || Coord_Y > pDesenho->iColunas )
			return DES_CondRetCoordenadaInvalida;

		Celula * pCelula = ( Celula * ) MAT_RetornaValor( Coord_X, Coord_Y );
		CEL_AlteraMarcacao( pCelula );

		if( JogoFinalizado( ) )
			ExibeGameOver( );

		return DES_tpCondRet;
	}

/***************************************************************************
*
*  Fun��o: DES Ativa Dica
*
*  Marca uma c�lula do tabuleiro que deveria ser marcada mas ainda est�
*  em branco
*
*  Complexidade: O(n^2) -> Pode percorrer toda a matriz.
*
****************************************************************************/

	DES_tpCondRet DES_AtivaDica( void )
	{
		int i, j;
		
		//Teste desenho instanciado
		if( pDesenho == NULL ) 
			return DES_CondRetDesenhoNaoIniciado;

		//Teste ainda possui dicas
		if( pDesenho->iDicas == 0 )
			return DES_CondRetSemDicas;

		//Procura por c�lula a ser pintada de baixo para cima, esquerda para direita
		for( i = pDesenho->iLinhas - 1 ; i >= 0 ; i-- )
		{
			for( j = 0 ; j < pDesenho->iColunas ; j++ )
			{
				Celula * pCelula = ( Celula * ) MAT_RetornaValor( i, j );
				//Se a celula � para ser pintada mas n�o est� pintada
				if( CEL_MarcacaoEsperada( pCelula ) && !CEL_MarcacaoAtual( pCelula ) )
				{
					//Marca a c�lula
					DES_AlteraMarcacaoCoordenada( i, j );
					//Decrementa as dicas
					(pDesenho->iDicas)--;
					return DES_CondRetOk;
				}/* if */
			} /* for */
		}/* for */

		return DES_CondRetJogoFinalizado;
	}

/***************************************************************************
*
*  Fun��o: DES ImprimeMatrizJogo
*
*  Imprime a matriz de jogo conforme as marcações do momento
*
*  Complexidade: O(n^2) -> Percorre toda a matriz.
*
****************************************************************************/
	DES_tpCondRet DES_ImprimeMatrizJogo( void )
	{
		//TODO:Implementar isso depois.
	}

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/



/***********************************************************************
*
*  $FC Fun��o: DES Preenche Aleatoriamente Matriz
*
*	Preenche a matriz de jogo de forma aleat�ria para gerar um
*	esquema de nonogram.
*	Toda coluna e toda linha tem pelo menos uma c�lula para ser marcada
*
*	Complexidade: O(n^2)
*
***********************************************************************/

	static void PreencheAleatorioMatriz( void )
	{
		int i, j;

		//Inicia o gerador aleat�rio sem delay de cria�ao
		srand(time(NULL));

		//Percorre cada linha e cada coluna ligando ou nao a marca�ao
		for( i = 0 ; i < pDesenho->iLinhas ; i++ )
		{
			for( j = 0 ; j < pDesenho->iColunas ; j++ )
			{
				int ramdomNumber = rand() % 2;

				Celula * pCelula;

				// Se o resultado � �mpar, liga a c�lula. 50% de chance.
				if( randomNumber ){
					//Cria c�lula com valor de marca��o esperada 1
					CEL_CriaCelula( pCelula, 1 );
				} /* if */
				else 
				{
					//Cria c�lula com valor de marca��o esperada 0
					CEL_CriaCelula( pCelula, 0 );
				}/* else */

				MAT_InsereValor( pCelula, i, j );

			}/* for */
		}/* for */
	}

/***********************************************************************
*
*  $FC Fun��o: DES Inicializa Listas Horizontais
*
*	Cria a lista de valores da horizontal baseado nos valores em cada
*   c�lula da matriz de jogo.
*
*	Complexidade: O(n^2)
*
***********************************************************************/

	static DES_tpCondRet InicializaListasHorizontais( )
	{
		// Inicializa�ao das Listas e valores de linha
		for( i = 0; i < NumLinhas; i++ )
		{
			int sequencia = 0;
			LST_CriaLista( pDesenho->pListasHorizontais[i] );
			LST_InsereFinal( pDesenho->pListasHorizontais[i], VAL_CriaValor( ) );
			for( j = 0; j < NumColinas; j++ )
			{
				//Recupera a c�lula na posi�ao (i,j)
				Celula* pCelula = ( Celula * ) MAT_RetornaValor( i, j );
				if( CEL_MarcacaoEsperada(pCelula) )
				{
					//C�lula de marca�ao esperada
					if( !sequencia )
					{
						//Nova sequencia, insere um novo elemento na lista
						LST_InsereFinal( pDesenho->pListasHorizontais[i], VAL_CriaValor( ) );
					}
					//Indica que existe uma sequencia e incrementa a estrutura Valor
					sequencia = 1;
					VAL_IncrementaValor( LST_RetornaUltimo( pDesenho->pListasHorizontais[i] ) );
				}
				else
				{
					//Zera a sequencia
					sequencia = 0;
				}
			}
		}/* for */

		return DES_CondRetOk;
	}

/***********************************************************************
*
*  $FC Fun��o: DES Inicializa Listas Verticais
*
*	Cria a lista de valores da vertical baseado nos valores em cada
*   c�lula da matriz de jogo.
*
*	Complexidade: O(n^2)
*
***********************************************************************/

	static DES_tpCondRet InicializaListasVerticais ( void )
	{
		//Inicializacao de listas e valores de coluna
		for( j = 0; j < NumColunas; j++ )
		{
			int sequencia = 0;
			LST_CriaLista( pDesenho->pListasVerticais[j] );
			LST_InsereFinal( pDesenho->pListasVerticais[j], VAL_CriaValor() );
			for( i = 0; i < NumLinhas; j++ )
			{
				//Recupera a c�lula na posi�ao (i,j)
				Celula* pCelula = ( Celula * ) MAT_RetornaValor( i, j );
				if( CEL_MarcacaoEsperada( pCelula ) )
				{
					//C�lula de marca�ao esperada
					if( !sequencia )
					{
						//Nova sequencia, insere um novo elemento na lista
						LST_InsereFinal( pDesenho->pListasVerticais[j], VAL_CriaValor() );
					}
					//Indica que existe uma sequencia e incrementa a estrutura Valor
					sequencia = 1;
					VAL_IncrementaValor( LST_RetornaUltimo( pDesenho->pListasVerticais[j] ) );
				}
				else
				{
					//Zera a sequencia
					sequencia = 0;
				}
			}
		}/* for */

		return DES_CondRetOk;
	}
/***********************************************************************
*
*  $FC Fun��o: DES JogoFinalizado
*
*	Retorna 1 se a matriz estiver completamente corretamente preenchida,
*	0 caso contrário.
*
*	Complexidade: O(n^2) -> pode percorrer toda a matriz
*
***********************************************************************/
	static int JogoFinalizado ( void )
	{
		int i, j;
		// Percorre toda a Matriz em busca de uma célula que não está de acordo.
		for(i = 0; i<pDesenho->iLinhas; i++){
			for(j = 0; j< pDesenho->iColunas; j++){
				Celula* celula = (Celula *) MAT_RetornaValor(i, j);
				if(CEL_MarcacaoEsperada( pCelula ) != CEL_MarcacaoAtual( pCelula ))
					return 0;
			}
		}
		return 1;
	}

	static void ExibeGameOver ( void )
	{
		printf("The game is over!\n You won!\n\n");
		//TODO:A ser implementado o resto
	}
