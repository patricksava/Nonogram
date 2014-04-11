/***************************************************************************
*  $MCI Módulo de implementação: Módulo Desenho
*
*  Arquivo gerado:              Desenho.c
*  Letras identificadoras:      DES
*
*  Projeto: Disciplina INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: ps  - Patrick Sava
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observaçães
*       1.00   ps   24/03/2014 Início do desenvolvimento
*
***************************************************************************/

#include   <stdlib.h>
#include   <stdio.h>
#include   <time.h>

#include   "Desenho.h"
#include   "../ListaGenerica/LISTA.h"
#include   "../Valor/VALOR.H"
//#include   "MatrizGenerica.h"
//#include   "Celula.h"



/***********************************************************************
*
*  $TC Tipo de dados: DES Estrutura Desenho Nonogram
*
*
*  $ED Descrição do tipo
*     Descreve a organização do desenho
*
***********************************************************************/

	typedef struct desenho{

		tpMatrizGen * pMatrizJogo;
			/* Ponteiro para matriz de células */

		int iLinhas;
			/* Número de linhas da matriz */

		int iColunas;
			/* Número de colunas da matriz */

		TpLista ** pListasVerticais;
			/* Vetor de Listas de Valores verticais */

		TpLista ** pListasHorizontais;
			/* Vetor de Listas de Valores verticais */

		int iDicas;
			/* Número de dicas que cada usuário possui por jogo */

	} tpDesenho ;

/*****  Dados encapsulados no módulo  *****/

    static tpDesenho * pDesenho = NULL ;
        /* Ponteiro para o desenho */

/***** Protótipos das funçães encapuladas no módulo *****/

	static void PreencheAleatorioMatriz ( void );

	static void PreencheMatrizProjetada ( FILE * ArquivoDesenho );

	static DES_tpCondRet InicializaListasHorizontais ( void );

	static DES_tpCondRet InicializaListasVerticais ( void );
	
	//static int JogoFinalizado ( void );

/*****  Código das funçães exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: DES Inicia Desenho
*
*  Cria aleatoriamente um esquema de nonogram pronto para ser jogado.
*  Gera, de acordo com o resultado de geração aleatório, as listas de valores
*  verticais e horizontais que sao cruciais para o fluir do jogo.
*
*  Complexidade: O(n^2)
*
****************************************************************************/

	DES_tpCondRet DES_IniciaDesenho( unsigned int NumLinhas, unsigned int NumColunas )
	{
		int i, j;
		DES_tpCondRet CondRet;

		//Verifica se a quantidade de linhas e de colunas são válidas
		if( NumLinhas < NUM_LINHAS_MINIMO || NumColunas < NUM_COLUNAS_MINIMO ||
		    NumLinhas > NUM_LINHAS_MAXIMO || NumColunas > NUM_COLUNAS_MAXIMO )
			return DES_CondRetTamanhoInvalido;

		//Aloca a estrutura desenho
		pDesenho = ( tpDesenho* ) malloc( sizeof( tpDesenho ) );

		//Falhou a alocação de memória
		if( pDesenho == NULL )
			return DES_CondRetFaltouMemoria;

		pDesenho->iLinhas  = NumLinhas;
		pDesenho->iColunas = NumColunas;
		pDesenho->iDicas   = NUM_MAX_DICAS; 

		//Chama o módulo de matriz e guarda o ponteiro na estrutura desenho
		CondRet = MAT_CriaMatriz( pDesenho->pMatrizJogo, NumLinhas, NumColunas );
		if(CondRet != DES_CondRetOk)
			return CondRet;

		//Gera o esquema de forma aleatória
		PreencheAleatorioMatriz( );

		//Aloca o vetor que vai guardar as cabeças de listas horizontais
		pDesenho->pListasHorizontais = ( TpLista ** ) malloc( NumLinhas * sizeof( TpLista* ) );
		if(pDesenho->pListasHorizontais == NULL)
			return DES_CondRetFaltouMemoria;

		//Aloca o vetor que vai guardar as cabeças de listas verticais
		pDesenho->pListasVerticais   = ( TpLista ** ) malloc( NumColunas * sizeof( TpLista* ) );
		if( pDesenho->pListasVerticais == NULL )
			return DES_CondRetFaltouMemoria;

		// Inicialização das Listas e valores de linha
		CondRet = InicializaListasHorizontais( );
		if(CondRet != DES_CondRetOk)
			return CondRet;

		// Inicialização das Listas e valores de coluna
		CondRet = InicializaListasVerticais( );
		if(CondRet != DES_CondRetOk)
			return CondRet;

		return DES_CondRetOk;
	}


/***************************************************************************
*
*  Função: DES Inicia Desenho Vazio
*
*  Cria um esquema de nonogram não para ser jogado, mas sim para ser projetado.
*  Neste modo o usuário poderá marcar todas as células que quiser e salvar 
*  o resultado num arquivo para que ele possa jogar mais tarde.
*
*  Complexidade: O(n^2) -> percorre toda a matriz
*
****************************************************************************/

	DES_tpCondRet DES_IniciaDesenhoVazio( unsigned int NumLinhas, unsigned int NumColunas ) 
	{
		int i, j;
		DES_tpCondRet CondRet;

		//Verifica se a quantidade de linhas e de colunas são válidas
		if( NumLinhas < NUM_LINHAS_MINIMO || NumColunas < NUM_COLUNAS_MINIMO ||
		    NumLinhas > NUM_LINHAS_MAXIMO || NumColunas > NUM_COLUNAS_MAXIMO )
			return DES_CondRetTamanhoInvalido;

		//Aloca a estrutura desenho
		pDesenho = ( tpDesenho* ) malloc( sizeof( tpDesenho ) );

		//Falhou a alocação de memória
		if( pDesenho == NULL )
			return DES_CondRetFaltouMemoria;

		pDesenho->iLinhas  = NumLinhas;
		pDesenho->iColunas = NumColunas;
		pDesenho->iDicas   = 0;

		CondRet = MAT_CriaMatriz( pDesenho->pMatrizJogo, NumLinhas, NumColunas );
		if(CondRet != DES_CondRetOk)
			return CondRet;

		//Aloca o vetor que vai guardar as cabeças de listas horizontais
		pDesenho->pListasHorizontais = ( TpLista ** ) malloc( NumLinhas * sizeof( TpLista* ) );
		if(pDesenho->pListasHorizontais == NULL)
			return DES_CondRetFaltouMemoria;

		//Aloca o vetor que vai guardar as cabeças de listas verticais
		pDesenho->pListasVerticais   = ( TpLista ** ) malloc( NumColunas * sizeof( TpLista* ) );
		if( pDesenho->pListasVerticais == NULL )
			return DES_CondRetFaltouMemoria;

		// Inicialização das Listas e valores de linha
		CondRet = InicializaListasHorizontais( );
		if(CondRet != DES_CondRetOk)
			return CondRet;

		// Inicialização das Listas e valores de coluna
		CondRet = InicializaListasVerticais( );
		if(CondRet != DES_CondRetOk)
			return CondRet;

		return DES_CondRetOk;
	}


/***************************************************************************
*
*  Função: DES Inicia Desenho Projetado
*
*  Dado um arquivo como parâmetro, sendo esse arquivo válido, esta função
*  inicia a estrutura desenho e a matriz de tal forma que condiz com as 
*  informações do arquivo. Este arquivo deve ser resultado da gravação no modo
*  de projeto. Após a geração da matriz, o jogo está pronto para ser iniciado.
*
*  Complexidade: O(n^2) -> percorre toda a matriz
*
****************************************************************************/

	DES_tpCondRet DES_IniciaDesenhoProjetado( FILE * ArquivoDesenho ) 
	{
		int i, j;
		int Linhas, Colunas;
		DES_tpCondRet CondRet;

		if( ArquivoDesenho == NULL )
			return DES_CondRetPonteiroArquivoNulo;

		if( fscanf(ArquivoDesenho, "%d %d", &Linhas, %&Colunas) != 2 )
			return DES_CondRetArquivoInvalido;

		//Verifica se a quantidade de linhas e de colunas são válidas
		if( Linhas < NUM_LINHAS_MINIMO || Colunas < NUM_COLUNAS_MINIMO ||
		    Linhas > NUM_LINHAS_MAXIMO || Colunas > NUM_COLUNAS_MAXIMO )
			return DES_CondRetTamanhoInvalido;

		//Aloca a estrutura desenho
		pDesenho = ( tpDesenho* ) malloc( sizeof( tpDesenho ) );

		//Falhou a alocação de memória
		if( pDesenho == NULL )
			return DES_CondRetFaltouMemoria;

		pDesenho->iLinhas  = NumLinhas;
		pDesenho->iColunas = NumColunas;
		pDesenho->iDicas   = NUM_MAX_DICAS;

		//Chama o módulo de matriz e guarda o ponteiro na estrutura desenho
		CondRet = MAT_CriaMatriz( pDesenho->pMatrizJogo, NumLinhas, NumColunas );
		if(CondRet != DES_CondRetOk)
			return CondRet;

		//Gera o esquema de forma aleatória
		PreencheMatrizProjetada( ArquivoDesenho );

		//Aloca o vetor que vai guardar as cabeças de listas horizontais
		pDesenho->pListasHorizontais = ( TpLista ** ) malloc( NumLinhas * sizeof( TpLista* ) );
		if(pDesenho->pListasHorizontais == NULL)
			return DES_CondRetFaltouMemoria;

		//Aloca o vetor que vai guardar as cabeças de listas verticais
		pDesenho->pListasVerticais   = ( TpLista ** ) malloc( NumColunas * sizeof( TpLista* ) );
		if( pDesenho->pListasVerticais == NULL )
			return DES_CondRetFaltouMemoria;

		// Inicialização das Listas e valores de linha
		CondRet = InicializaListasHorizontais( );
		if(CondRet != DES_CondRetOk)
			return CondRet;

		// Inicialização das Listas e valores de coluna
		CondRet = InicializaListasVerticais( );
		if(CondRet != DES_CondRetOk)
			return CondRet;

		return DES_CondRetOk;
	}


/***************************************************************************
*
*  Função: DES Destroi desenho
*
*  Libera cada ponteiro dentro da estrutura desenho e depois libera a 
*  estrutura desenho.
*
*  Complexidade: O(n)
*
****************************************************************************/

	DES_tpCondRet DES_DestroiDesenho( void )
	{

		// Testa se o ponteiro desenho já foi iniciado;
		if( pDesenho == NULL )
			return DES_CondRetDesenhoNaoIniciado;

		int i; //Contador

		// Libera cada cabeça de lista
		for( i = 0; i < pDesenho->iLinhas; i++ )
			LST_LiberaLista(pDesenho->pListasHorizontais[i]);

		// Libera o vetor de cabeças de lista
		free(pDesenho->pListasHorizontais);

		// Libera cada cabeça de lista
		for( i = 0; i < pDesenho->iColunas; i++ )
			LST_LiberaLista(pDesenho->pListasVerticais[i]);

		// Libera o vetor de cabeças de lista
		free(pDesenho->pListasVerticais);

		// Libera a matriz de jogo
		MAT_LiberaMatriz( pDesenho->pMatrizJogo );

		// Libera o ponteiro para estrutura encapsulada Desenho 
		free( pDesenho );

		return DES_CondRetOk;
	}

/***************************************************************************
*
*  Função: DES Altera Marcação de Coordenada
*
*  Dada uma coordenada (X,Y), a função busca pela célula referente e altera
*  sua marcação atual. Se ela já estava marcada passa a ficar em branco e
*  vice-versa.
*
*  Complexidade: O(n) -> Custo de encontrar na lista o elemento.
*
****************************************************************************/

	DES_tpCondRet DES_AlteraMarcacaoCoordenada( unsigned int Coord_X, unsigned int Coord_Y )
	{

		//Teste se a estrutura desenho já existe
		if( pDesenho == NULL )
			return DES_CondRetDesenhoNaoIniciado;

		//Teste se as coordenadas dadas estão dentro do permitido
		if( Coord_X > pDesenho->iLinhas || Coord_Y > pDesenho->iColunas )
			return DES_CondRetCoordenadaInvalida;

		Celula * pCelula = ( Celula * ) MAT_RetornaValor( Coord_X, Coord_Y );
		CEL_AlteraMarcacao( pCelula );

		return DES_tpCondRet;
	}

/***************************************************************************
*
*  Função: DES Ativa Dica
*
*  Marca uma célula do tabuleiro que deveria ser marcada mas ainda está
*  em branco
*
*  Complexidade: O(n^2) -> Pode percorrer toda a matriz.
*
****************************************************************************/

	DES_tpCondRet DES_AtivaDica( void )
	{
		int i, j; // Linha, Coluna
		
		//Teste desenho instanciado
		if( pDesenho == NULL ) 
			return DES_CondRetDesenhoNaoIniciado;

		//Teste ainda possui dicas
		if( pDesenho->iDicas == 0 )
			return DES_CondRetSemDicas;

		//Procura por célula a ser pintada de baixo para cima, esquerda para direita
		for( i = pDesenho->iLinhas - 1 ; i >= 0 ; i-- )
		{
			for( j = 0 ; j < pDesenho->iColunas ; j++ )
			{
				Celula * pCelula = ( Celula * ) MAT_RetornaValor( i, j );
				//Se a celula é para ser pintada mas não está pintada
				if( CEL_MarcacaoEsperada( pCelula ) && !CEL_MarcacaoAtual( pCelula ) )
				{
					//Marca a célula
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
*  Função: DES ImprimeMatrizJogo
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

/*****  Código das funçães encapsuladas no módulo  *****/



/***********************************************************************
*
*  $FC Função: DES Preenche Aleatoriamente Matriz
*
*	Preenche a matriz de jogo de forma aleatória para gerar um
*	esquema de nonogram.
*
*	Complexidade: O(n^2)
*
***********************************************************************/

	static void PreencheAleatorioMatriz( void )
	{
		int i, j;

		//Inicia o gerador aleatório sem delay de criaóao
		srand(time(NULL));

		//Percorre cada linha e cada coluna ligando ou nao a marcaóao
		for( i = 0 ; i < pDesenho->iLinhas ; i++ )
		{
			for( j = 0 ; j < pDesenho->iColunas ; j++ )
			{
				int ramdomNumber = rand() % 2;

				Celula * pCelula;

				// Se o resultado é impar, liga a célula. 50% de chance.
				if( randomNumber ){
					//Cria célula com valor de marcação esperada 1
					CEL_CriaCelula( pCelula, 1 );
				} /* if */
				else 
				{
					//Cria célula com valor de marcação esperada 0
					CEL_CriaCelula( pCelula, 0 );
				}/* else */

				MAT_InsereValor( pCelula, i, j );

			}/* for */
		}/* for */
	}


/***********************************************************************
*
*  $FC Função: DES Preenche Matriz Projetada
*
*	Preenche a matriz de jogo de forma coerente com o arquivo dado como
*   entrada para gerar um esquema de nonogram.
*
*	Complexidade: O(n^2)
*
***********************************************************************/

	static DES_tpCondRet PreencheMatrizProjetada( FILE * ArquivoDesenho )
	{
		int i, j;

		//Percorre cada linha e cada coluna ligando ou nao a marcaóao
		for( i = 0 ; i < pDesenho->iLinhas ; i++ )
		{
			for( j = 0 ; j < pDesenho->iColunas ; j++ )
			{
				Celula * pCelula;
				int Marcado;

				if( fscanf(ArquivoDesenho, "%d", &Marcado) != 1 )
					return DES_CondRetArquivoInvalido;

				// Se foi lido 1 no arquivo, cria a célula como marcada
				if( Marcado ){
					//Cria célula com valor de marcação esperada 1
					CEL_CriaCelula( pCelula, 1 );
				} /* if */
				else 
				{
					//Cria célula com valor de marcação esperada 0
					CEL_CriaCelula( pCelula, 0 );
				}/* else */

				MAT_InsereValor( pCelula, i, j );

			}/* for */
		}/* for */

		return DES_CondRetOk;
	}


/***********************************************************************
*
*  $FC Função: DES Inicializa Listas Horizontais
*
*	Cria a lista de valores da horizontal baseado nos valores em cada
*   célula da matriz de jogo.
*
*	Complexidade: O(n^2)
*
***********************************************************************/

	static DES_tpCondRet InicializaListasHorizontais( void )
	{
		int i, j;
		// Inicialização das Listas e valores de linha
		for( i = 0; i < NumLinhas; i++ )
		{
			int sequencia = 0;
			TpValor * pValor;
			VAL_CriarValor( pValor );

			LST_CriaLista( pDesenho->pListasHorizontais[i] );
			LST_InsereFinal( pDesenho->pListasHorizontais[i], pValor );
			for( j = 0; j < NumColinas; j++ )
			{
				//Recupera a célula na posição (i,j)
				Celula* pCelula = ( Celula * ) MAT_RetornaValor( i, j );
				if( CEL_MarcacaoEsperada( pCelula ) )
				{
					//Célula de marcação esperada
					if( !sequencia )
					{
						VAL_CriarValor( pValor );
						LST_InsereFinal( pDesenho->pListasHorizontais[i], pValor );
					}
					//Indica que existe uma sequencia e incrementa a estrutura Valor
					sequencia = 1;
					VAL_IncrementarQntdMarcados( (TpValor*)LST_RetornaUltimo( pDesenho->pListasHorizontais[i] ) );
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
*  $FC Função: DES Inicializa Listas Verticais
*
*	Cria a lista de valores da vertical baseado nos valores em cada
*   célula da matriz de jogo.
*
*	Complexidade: O(n^2)
*
***********************************************************************/

	static DES_tpCondRet InicializaListasVerticais ( void )
	{
		int i, j;
		//Inicialização de listas e valores de coluna
		for( j = 0; j < NumColunas; j++ )
		{
			int sequencia = 0;

			TpValor * pValor;
			VAL_CriarValor( pValor );

			LST_CriaLista( pDesenho->pListasVerticais[j] );
			LST_InsereFinal( pDesenho->pListasVerticais[j], pValor );
			for( i = 0; i < NumLinhas; j++ )
			{
				//Recupera a célula na posição (i,j)
				Celula* pCelula = ( Celula * ) MAT_RetornaValor( i, j );
				if( CEL_MarcacaoEsperada( pCelula ) )
				{
					//Célula de marcação esperada
					if( !sequencia )
					{
						VAL_CriarValor( pValor );
						//Nova sequencia, insere um novo elemento na lista
						LST_InsereFinal( pDesenho->pListasVerticais[j], pValor );
					}
					//Indica que existe uma sequencia e incrementa a estrutura Valor
					sequencia = 1;
					VAL_IncrementarQntdMarcados( ( TpValor* ) LST_RetornaUltimo( pDesenho->pListasVerticais[j] ) );
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
*  $FC Função: DES JogoFinalizado
*
*	Retorna 1 se a matriz estiver completamente corretamente preenchida,
*	0 caso contrário.
*
*	Complexidade: O(n^2) -> pode percorrer toda a matriz
*
***********************************************************************/
/*
	static int JogoFinalizado ( void )
	{
		int i, j;
		// Percorre toda a Matriz em busca de uma célula que não está de acordo.
		for(i = 0; i<pDesenho->iLinhas; i++)
		{
			for(j = 0; j< pDesenho->iColunas; j++)
			{
				// Recupera a célula correspondente àquela coordenada
				Celula* celula = (Celula *) MAT_RetornaValor(i, j);

				//Compara marcação atual com esperada, se forem diferentes o jogo não está terminado
				if(CEL_MarcacaoEsperada( pCelula ) != CEL_MarcacaoAtual( pCelula ))
					return 0;
			}
		}

		// Perfeito, o jogo acabou
		return 1;
	}
*/