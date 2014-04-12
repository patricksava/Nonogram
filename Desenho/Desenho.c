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
#include   "..\ListaGenerica\LISTA.h"
#include   "..\Valor\VALOR.H"
//#include   "Matriz.h"
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

		int iDicas;
			/* Número de dicas que cada usuário possui por jogo */

		int iLinhas;
			/* Número de linhas da matriz */

		int iColunas;
			/* Número de colunas da matriz */

		TpLista ** pListasVerticais;
			/* Vetor de Listas de Valores verticais */

		TpLista ** pListasHorizontais;
			/* Vetor de Listas de Valores horizontais */

		TpMatriz * pMatrizJogo;
			/* Ponteiro para matriz de células */

	} TpDesenho ;

/*****  Dados encapsulados no módulo  *****/

    static TpDesenho * pDesenho = NULL ;
        /* Ponteiro para o desenho */

/***** Protótipos das funçães encapuladas no módulo *****/

	static void PreencheAleatorioMatriz ( void );

	static void PreencheMatrizProjetada ( FILE * ArquivoDesenho );

	static void PreencheMatrizUltimoJogo ( void );

	static DES_tpCondRet InicializaListas ( void );

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
		pDesenho = ( TpDesenho* ) malloc( sizeof( TpDesenho ) );

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

		CondRet = InicializaListas( );
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
		pDesenho = ( TpDesenho* ) malloc( sizeof( TpDesenho ) );

		//Falhou a alocação de memória
		if( pDesenho == NULL )
			return DES_CondRetFaltouMemoria;

		pDesenho->iLinhas  = NumLinhas;
		pDesenho->iColunas = NumColunas;
		pDesenho->iDicas   = 0;

		CondRet = MAT_CriarMatriz( pDesenho->pMatrizJogo, NumLinhas, NumColunas );
		if(CondRet != DES_CondRetOk)
			return CondRet;

		CondRet = InicializaListas( );
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
		pDesenho = ( TpDesenho* ) malloc( sizeof( TpDesenho ) );

		//Falhou a alocação de memória
		if( pDesenho == NULL )
			return DES_CondRetFaltouMemoria;

		pDesenho->iLinhas  = Linhas;
		pDesenho->iColunas = Colunas;
		pDesenho->iDicas   = NUM_MAX_DICAS;

		//Chama o módulo de matriz e guarda o ponteiro na estrutura desenho
		CondRet = MAT_CriaMatriz( pDesenho->pMatrizJogo, Linhas, Colunas );
		if(CondRet != DES_CondRetOk)
			return CondRet;

		//Gera o esquema de forma aleatória
		PreencheMatrizProjetada( ArquivoDesenho );

		CondRet = InicializaListas( );
		if(CondRet != DES_CondRetOk)
			return CondRet;

		return DES_CondRetOk;
	}


/***************************************************************************
*
*  Função: DES Retoma Ultimo Jogo Salvo
*
*  Busca se existe um jogo salvo e monta a matriz de jogo baseado no que 
*  foi salvo.
*
*  Complexidade: O(n^2) -> percorre toda a matriz
*
****************************************************************************/

	DES_tpCondRet DES_RetomaUltimoJogoSalvo( void ) 
	{
		int i, j;
		int Linhas, Colunas, Dicas;
		DES_tpCondRet CondRet;

		FILE * ArquivoDesenho = fopen( NOME_JOGO_SALVO, "r" );

		if( ArquivoDesenho == NULL )
			return DES_CondRetPonteiroArquivoNulo;

		if( fscanf(ArquivoDesenho, "%d %d %d", &Linhas, &Colunas, &Dicas) != 3 )
			return DES_CondRetArquivoInvalido;

		//Verifica se a quantidade de linhas e de colunas são válidas
		if( Linhas < NUM_LINHAS_MINIMO || Colunas < NUM_COLUNAS_MINIMO ||
		    Linhas > NUM_LINHAS_MAXIMO || Colunas > NUM_COLUNAS_MAXIMO )
			return DES_CondRetTamanhoInvalido;

		//Aloca a estrutura desenho
		pDesenho = ( TpDesenho* ) malloc( sizeof( TpDesenho ) );

		//Falhou a alocação de memória
		if( pDesenho == NULL )
			return DES_CondRetFaltouMemoria;

		pDesenho->iLinhas  = Linhas;
		pDesenho->iColunas = Colunas;
		pDesenho->iDicas   = Dicas;

		//Chama o módulo de matriz e guarda o ponteiro na estrutura desenho
		CondRet = MAT_CriaMatriz( pDesenho->pMatrizJogo, Linhas, Colunas );
		if(CondRet != DES_CondRetOk)
			return CondRet;

		//Gera o esquema de forma aleatória
		PreencheMatrizUltimoJogo( ArquivoDesenho );

		CondRet = InicializaListas( );
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
		int i; 

		// Testa se o ponteiro desenho já foi iniciado;
		if( pDesenho == NULL )
			return DES_CondRetDesenhoNaoIniciado;

		// Libera cada cabeça de lista
		for( i = 0; i < pDesenho->iLinhas; i++ )
			LST_DestruirLista( pDesenho->pListasHorizontais[i] );

		// Libera o vetor de cabeças de lista
		free( pDesenho->pListasHorizontais );

		// Libera cada cabeça de lista
		for( i = 0; i < pDesenho->iColunas; i++ )
			LST_DestruirLista( pDesenho->pListasVerticais[i] );

		// Libera o vetor de cabeças de lista
		free( pDesenho->pListasVerticais );

		// Libera a matriz de jogo
		MAT_DestruirMatriz( pDesenho->pMatrizJogo );

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

		Celula * pCelula = ( Celula * ) MAT_ObterElemento( Coord_X, Coord_Y );
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
		
		//Teste desenho definido
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
				Celula * pCelula = ( Celula * ) MAT_ObterElemento( i, j );
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


/***************************************************************************
*
*  Função: DES Grava Jogo Atual
*
*  Grava em arquivo a matriz projetada pelo usuário no modo projeto.
*
*  Exemplo de arquivo válido:
*		5                // número de linhas
*		8                // número de colunas
*		3				 // número de dicas que sobraram
*		0 0 1 1 1 1 0 0 0 0 1 0 1 0 0 0  // primeira linha de células ( marcação esperada, marcação feita )
*		1 1 1 1 0 0 0 0 0 0 0 0 1 0 1 0  // segunda linha de células
*		0 0 0 0 1 0 1 0 1 0 1 0 0 0 0 0
*		1 1 1 1 0 0 0 0 0 0 0 0 1 1 1 1
*		0 0 1 1 1 1 0 0 0 0 1 1 1 1 0 0  // quinta linha de células
*
*  Complexidade: O(n^2) -> Percorre toda a matriz.
*
****************************************************************************/

	DES_tpCondRet DES_GravaJogoAtual( void )
	{
		FILE * ArquivoDesenho;

		// Testa se a estrutura desenho está definida
		if( pDesenho == NULL )
			return DES_CondRetDesenhoNaoIniciado;


		// Abre o arquivo para salvar com o nome dado pelo usuário
		ArquivoDesenho = fopen( NOME_JOGO_SALVO, "w" );

		// Teste se conseguiu abrir o arquivo
		if( ArquivoDesenho == NULL )
			return DES_CondRetFaltouMemoria;

		// Imprime a primeira linha que representa número de linhas
		fprintf( ArquivoDesenho, "%d\n", pDesenho->iLinhas );

		// Imprime a segunda linha que representa número de linhas
		fprintf( ArquivoDesenho, "%d\n", pDesenho->iColunas );

		// Imprime a segunda linha que representa número de dicas que ainda sobraram
		fprintf( ArquivoDesenho, "%d\n", pDesenho->iDicas );


		// Imprime as linhas
		for( i = 0; i < pDesenho->iLinhas; i++)
		{
			// Imprime as colunas
			for( j = 0; j < pDesenho->iColunas; i++ )
			{
				// Recupera o elemento dentro da matriz na posição i, j e imprime se ele está marcado ou não
				Celula * pCelula = ( Celula * ) MAT_ObterElemento( pDesenho->pMatrizJogo, i, j );
				fprintf( ArquivoDesenho, "%d %d ", CEL_MarcacaoEsperada( pCelula ), CEL_MarcacaoAtual( pCelula ) );
			}

			fprintf( ArquivoDesenho, "\n" );
		}

		fclose( ArquivoDesenho );

		return DES_CondRetOk;
	}


/***************************************************************************
*
*  Função: DES Grava Matriz Projetada
*
*  Grava em arquivo a matriz projetada pelo usuário no modo projeto.
*
*	Exemplo de arquivo válido:
*		5                // número de linhas
*		8                // número de colunas
*		0 1 1 0 0 1 1 0  // primeira linha de células
*		1 1 0 0 0 0 1 1  // segunda linha de células
*		0 0 1 1 1 1 0 0
*		1 1 0 0 0 0 1 1
*		0 1 1 0 0 1 1 0  // quinta linha de células
*
*  Complexidade: O(n^2) -> Percorre toda a matriz.
*
****************************************************************************/

	DES_tpCondRet DES_GravaMatrizProjetada( char* NomeArquivo )
	{
		FILE * ArquivoDesenho;
		int tamStringNome;

		// Testa se a estrutura desenho está definida
		if( pDesenho == NULL )
			return DES_CondRetDesenhoNaoIniciado;

		// Tamanho da string dada + tamanho de ".des" + '\0'
		tamStringNome = strlen( NomeArquivo ) + 5;

		// Cria uma string com tamanho adequando
		char * NomeExtArquivo = ( char* ) malloc( tamStringNome * sizeof( char ) ) ; 
		strcpy( NomeExtArquivo, NomeArquivo );
		strcat( NomeExtArquivo, ".des");
		NomeExtArquivo[ tamStringNome - 1 ] = '\0';


		// Abre o arquivo para salvar com o nome dado pelo usuário
		ArquivoDesenho = fopen( NomeExtArquivo, "w" );

		// Teste se conseguiu abrir o arquivo
		if( ArquivoDesenho == NULL )
			return DES_CondRetFaltouMemoria;

		// Imprime a primeira linha que representa número de linhas
		fprintf( ArquivoDesenho, "%d\n", pDesenho->iLinhas );

		// Imprime a segunda linha que representa número de linhas
		fprintf( ArquivoDesenho, "%d\n", pDesenho->iColunas );

		// Imprime as linhas
		for( i = 0; i < pDesenho->iLinhas; i++)
		{
			// Imprime as colunas
			for( j = 0; j < pDesenho->iColunas; i++ )
			{
				// Recupera o elemento dentro da matriz na posição i, j e imprime se ele está marcado ou não
				Celula * pCelula = ( Celula * ) MAT_ObterElemento( pDesenho->pMatrizJogo, i, j );
				fprintf( ArquivoDesenho, "%d ", CEL_MarcacaoEsperada( pCelula ) );
			}

			fprintf( ArquivoDesenho, "\n" );
		}

		fclose( ArquivoDesenho );

		return DES_CondRetOk;
	}


/***********************************************************************
*
*   Função: DES JogoFinalizado
*
*	Retorna 1 se a matriz estiver completamente corretamente preenchida,
*	0 caso contrário.
*
*	Complexidade: O(n^2) -> pode percorrer toda a matriz
*
***********************************************************************/

	int DES_DesenhoFinalizado ( void )
	{
		int i, j;

		// Desenho não definido;
		if( pDesenho == NULL )
			return 0;

		// Percorre toda a Matriz em busca de uma célula que não está de acordo.
		for( i = 0; i<pDesenho->iLinhas; i++ )
		{ 
			for( j = 0; j< pDesenho->iColunas; j++ )
			{
				// Recupera a célula correspondente àquela coordenada
				Celula * pCelula = ( Celula * ) MAT_ObterElemento( i, j );

				//Compara marcação atual com esperada, se forem diferentes o jogo não está terminado
				if( CEL_MarcacaoEsperada( pCelula ) != CEL_MarcacaoAtual( pCelula ) )
					return 0;
			}
		}

		// Perfeito, o jogo acabou
		return 1;
	}


/*****  Código das funçães encapsuladas no módulo  *****/



/***********************************************************************
*
*  Função: DES Preenche Aleatoriamente Matriz
*
*  Preenche a matriz de jogo de forma aleatória para gerar um
*  esquema de nonogram.
*
*  Complexidade: O(n^2)
*
***********************************************************************/

	static void PreencheAleatorioMatriz( void )
	{
		int i, j;

		//Inicia o gerador aleatório sem delay de criaóao
		srand( time( NULL ) );

		//Percorre cada linha e cada coluna ligando ou nao a marcaóao
		for( i = 0 ; i < pDesenho->iLinhas ; i++ )
		{
			for( j = 0 ; j < pDesenho->iColunas ; j++ )
			{
				int randomNumber = rand( ) % 2;

				Celula * pCelula;

				// Se o resultado é impar, liga a célula. 50% de chance.
				CEL_CriaCelula( pCelula, randomNumber, 0 );

				MAT_InserirNovoElemento( pCelula, i, j );

			}/* for */
		}/* for */
	}


/***********************************************************************
*
*   Função: DES Preenche Matriz Projetada
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
				int Marcacao; // indica se a célula deve ser marcada

				if( fscanf(ArquivoDesenho, "%d ", &Marcacao) != 1 )
					return DES_CondRetArquivoInvalido;

				// Cria célula com valor de marcação lido no arquivo e não marcado
				CEL_CriaCelula( pCelula, Marcacao, 0 );

				MAT_InserirNovoElemento( pCelula, i, j );

			}/* for */
		}/* for */

		return DES_CondRetOk;
	}


/***********************************************************************
*
*   Função: DES Preenche Matriz Ultimo Jogo
*
*	Preenche a matriz de jogo de forma coerente com o arquivo dado como
*   entrada para gerar um esquema de nonogram.
*
*	Complexidade: O(n^2)
*
***********************************************************************/

	static DES_tpCondRet PreencheMatrizUltimoJogo( FILE * ArquivoDesenho )
	{
		int i, j;

		//Percorre cada linha e cada coluna ligando ou nao a marcaóao
		for( i = 0 ; i < pDesenho->iLinhas ; i++ )
		{
			for( j = 0 ; j < pDesenho->iColunas ; j++ )
			{
				Celula * pCelula;
				int Marcacao; // indica se a célula deve ser marcada
				int Marcado;  // indica se a célula estava marcada quando o jogo foi salvo

				if( fscanf(ArquivoDesenho, "%d %d ", &Marcacao, &Marcado ) != 2 )
					return DES_CondRetArquivoInvalido;

				CEL_CriaCelula( pCelula, Marcacao, Marcado );

				MAT_InserirNovoElemento( pCelula, i, j );

			}/* for */
		}/* for */

		return DES_CondRetOk;
	}


/***********************************************************************
*
*   Função: DES Inicializa Listas
*
*	Preenche os vetores de listas da estrutura desenho.
*
*	Complexidade: O(n^2)
*
***********************************************************************/

	static DES_tpCondRet InicializaListas( void )
	{
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

/***********************************************************************
*
*   Função: DES Inicializa Listas Horizontais
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
			
			TpValor * pValor = VAL_CriarValor( );

			LST_CriaLista( pDesenho->pListasHorizontais[i] );
			LST_InserirNovoNoFim( pDesenho->pListasHorizontais[i], pValor );
			for( j = 0; j < NumColinas; j++ )
			{
				//Recupera a célula na posição (i,j)
				Celula* pCelula = ( Celula * ) MAT_ObterElemento( i, j );
				if( CEL_MarcacaoEsperada( pCelula ) )
				{
					//Célula de marcação esperada
					if( !sequencia )
					{
						VAL_CriarValor( pValor );
						LST_InserirNovoNoFim( pDesenho->pListasHorizontais[i], pValor );
					}
					//Indica que existe uma sequencia e incrementa a estrutura Valor
					sequencia = 1;
					VAL_IncrementarQntdMarcados( (TpValor*) LST_RetornaUltimo( pDesenho->pListasHorizontais[i] ) );
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
*   Função: DES Inicializa Listas Verticais
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

			TpValor * pValor = VAL_CriarValor( );

			LST_CriaLista( pDesenho->pListasVerticais[j] );
			LST_InserirNovoNoFim( pDesenho->pListasVerticais[j], pValor );
			for( i = 0; i < NumLinhas; j++ )
			{
				//Recupera a célula na posição (i,j)
				Celula* pCelula = ( Celula * ) MAT_ObterElemento( i, j );
				if( CEL_MarcacaoEsperada( pCelula ) )
				{
					//Célula de marcação esperada
					if( !sequencia )
					{
						VAL_CriarValor( pValor );
						//Nova sequencia, insere um novo elemento na lista
						LST_InserirNovoNoFim( pDesenho->pListasVerticais[j], pValor );
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

