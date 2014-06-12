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
*		2.00   ps	01/06/2014 Instrumentação incluída
*
***************************************************************************/

#include   <stdlib.h>
#include   <stdio.h>
#include   <string.h>
#include   <time.h>

#include   "DESENHO.h"
#include   "LISTA.h"
#include   "VALOR.H"
#include   "MATRIZ.h"
#include   "CELULA.h"


#ifdef _DEBUG
   #include "CONTA.H"
   #include "CESPDIN.H"
#endif

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

#ifdef _DEBUG
	typedef enum{
		D_DESTROI_CORRENTE = 1,

		D_NULL_SUCESSOR = 2,

		D_NULL_PREDECESSOR = 3,

		D_LIXO_SUCESSOR = 4,

		D_LIXO_PREDECESSOR = 5,

		D_NULL_COORDENADA = 6,

		D_ALT_COORDENADA = 7,

		D_FREE_INCOMPLETO = 8,

		D_NULL_CORRENTE = 9,

		D_NULL_ORIGEM = 10
	};
#endif

/*****  Dados encapsulados no módulo  *****/

    static TpDesenho * pDesenho = NULL ;
        /* Ponteiro para o desenho */

/***** Protótipos das funçães encapuladas no módulo *****/

	static void PreencheAleatorioMatriz ( void );

	static void PreencheMatrizZerada ( void );

	static DES_tpCondRet PreencheMatrizProjetada ( FILE * ArquivoDesenho );

	static DES_tpCondRet PreencheMatrizUltimoJogo ( void );

	static DES_tpCondRet InicializaListas ( void );

	static DES_tpCondRet InicializaListasHorizontais ( void );

	static DES_tpCondRet InicializaListasVerticais ( void );

	void ExcluiValor( void * pDado );

	void ExcluiCelula( void * pDado );

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

	DES_tpCondRet DES_IniciaDesenho( int NumLinhas, int NumColunas )
	{
		int CondRet;

		//Se existe uma estrutura desenho definida, destroi ela antes de criar outra
		if( pDesenho != NULL )
			DES_DestroiDesenho( );

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

		#ifdef _DEBUG
			CED_MarcarEspacoAtivo( pDesenho );
		#endif

		//Chama o módulo de matriz e guarda o ponteiro na estrutura desenho
		pDesenho->pMatrizJogo = MAT_CriarMatriz( NumLinhas, NumColunas 
		#ifdef _DEBUG
		 , 'c'
		#endif
		 );
		if( pDesenho->pMatrizJogo == NULL )
			return DES_CondRetErroForaDoModuloDesenho;

		//Gera o esquema de forma aleatória
		PreencheAleatorioMatriz( );

		CondRet = InicializaListas( );

		if( CondRet != DES_CondRetOk )
			return ( DES_tpCondRet ) CondRet;

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

	DES_tpCondRet DES_IniciaDesenhoVazio( int NumLinhas, int NumColunas ) 
	{
		int CondRet;

		//Se existe uma estrutura desenho definida, destroi ela antes de criar outra
		if( pDesenho != NULL )
			DES_DestroiDesenho( );

		//Verifica se a quantidade de linhas e de colunas são válidas
		if( NumLinhas < NUM_LINHAS_MINIMO || NumColunas < NUM_COLUNAS_MINIMO ||
		    NumLinhas > NUM_LINHAS_MAXIMO || NumColunas > NUM_COLUNAS_MAXIMO )
			return DES_CondRetTamanhoInvalido;

		//Aloca a estrutura desenho
		pDesenho = ( TpDesenho* ) malloc( sizeof( TpDesenho ) );

		//Falhou a alocação de memória
		if( pDesenho == NULL )
			return DES_CondRetFaltouMemoria;

		#ifdef _DEBUG
			CED_MarcarEspacoAtivo( pDesenho );
		#endif

		pDesenho->iLinhas  = NumLinhas;
		pDesenho->iColunas = NumColunas;
		pDesenho->iDicas   = 0;

		pDesenho->pMatrizJogo = MAT_CriarMatriz( NumLinhas, NumColunas 
		#ifdef _DEBUG
		 , 'c'
	    #endif
		 );
		if( pDesenho->pMatrizJogo == NULL )
			return DES_CondRetErroForaDoModuloDesenho;

		//Preenche a matriz com células (0,0)
		PreencheMatrizZerada( );

		CondRet = InicializaListas( );
		if( CondRet != DES_CondRetOk )
			return ( DES_tpCondRet ) CondRet;

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
		int Linhas, Colunas;
		int CondRet;

		//Se existe uma estrutura desenho definida, destroi ela antes de criar outra
		if( pDesenho != NULL )
			DES_DestroiDesenho( );

		if( ArquivoDesenho == NULL )
			return DES_CondRetPonteiroArquivoNulo;

		if( fscanf(ArquivoDesenho, "%d %d", &Linhas, &Colunas) != 2 )
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

		#ifdef _DEBUG
			CED_MarcarEspacoAtivo( pDesenho );
		#endif

		pDesenho->iLinhas  = Linhas;
		pDesenho->iColunas = Colunas;
		pDesenho->iDicas   = NUM_MAX_DICAS;

		//Chama o módulo de matriz e guarda o ponteiro na estrutura desenho
		pDesenho->pMatrizJogo = MAT_CriarMatriz( Linhas, Colunas 
		#ifdef _DEBUG
		 , 'c'
		 #endif
		 );
		if( pDesenho->pMatrizJogo == NULL )
			return DES_CondRetErroForaDoModuloDesenho;

		//Gera o esquema de forma aleatória
		PreencheMatrizProjetada( ArquivoDesenho );

		CondRet = InicializaListas( );
		if( CondRet != DES_CondRetOk )
			return ( DES_tpCondRet ) CondRet;

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
		int CondRet;

		FILE * ArquivoDesenho = fopen( NOME_JOGO_SALVO, "r" );
		if( ArquivoDesenho == NULL )
			return DES_CondRetPonteiroArquivoNulo;

		//Se existe uma estrutura desenho definida, destroi ela antes de criar outra
		if( pDesenho != NULL )
			DES_DestroiDesenho( );

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

		#ifdef _DEBUG
			CED_MarcarEspacoAtivo( pDesenho );
		#endif

		pDesenho->iLinhas  = Linhas;
		pDesenho->iColunas = Colunas;
		pDesenho->iDicas   = Dicas;

		//Chama o módulo de matriz e guarda o ponteiro na estrutura desenho
		pDesenho->pMatrizJogo = MAT_CriarMatriz( Linhas, Colunas 
		#ifdef _DEBUG
		 , 'c'
	    #endif
		 );
		if( pDesenho->pMatrizJogo == NULL )
			return DES_CondRetErroForaDoModuloDesenho;

		//Gera o esquema de forma aleatória
		PreencheMatrizUltimoJogo( ArquivoDesenho );

		CondRet = InicializaListas( );
		if( CondRet != DES_CondRetOk )
			return ( DES_tpCondRet ) CondRet;

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
			LST_DestruirLista( pDesenho->pListasHorizontais[i], ExcluiValor );

		#ifdef _DEBUG
			CED_MarcarEspacoNaoAtivo( pDesenho->pListasHorizontais );
		#endif
		// Libera o vetor de cabeças de lista
		free( pDesenho->pListasHorizontais );

		// Libera cada cabeça de lista
		for( i = 0; i < pDesenho->iColunas; i++ )
			LST_DestruirLista( pDesenho->pListasVerticais[i], ExcluiValor );

		#ifdef _DEBUG
			CED_MarcarEspacoNaoAtivo( pDesenho->pListasVerticais );
		#endif
		// Libera o vetor de cabeças de lista
		free( pDesenho->pListasVerticais );

		// Libera a matriz de jogo
		MAT_DestruirMatriz( pDesenho->pMatrizJogo, ExcluiCelula );

		#ifdef _DEBUG
			CED_MarcarEspacoNaoAtivo( pDesenho->pMatrizJogo );
		#endif
		// Libera o ponteiro para estrutura matriz
		free( pDesenho->pMatrizJogo );

		#ifdef _DEBUG
			CED_MarcarEspacoNaoAtivo( pDesenho );
		#endif
		// Libera o ponteiro para estrutura encapsulada Desenho 
		free( pDesenho );

		pDesenho = NULL;

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

	DES_tpCondRet DES_AlteraMarcacaoCoordenada( int Coord_X, int Coord_Y )
	{
		Celula* pCelula;
		//Teste se a estrutura desenho já existe
		if( pDesenho == NULL )
			return DES_CondRetDesenhoNaoIniciado;

		//Teste se as coordenadas dadas estão dentro do permitido
		if( Coord_X > pDesenho->iLinhas || Coord_Y > pDesenho->iColunas || Coord_X < 1 || Coord_Y < 1 )
			return DES_CondRetCoordenadaInvalida;

		pCelula = ( Celula* ) MAT_ObterElemento( pDesenho->pMatrizJogo, Coord_X - 1, Coord_Y - 1 );

		CEL_AlteraMarcacao( pCelula );

		return DES_CondRetOk;
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
		for( i = pDesenho->iLinhas ; i > 0 ; i-- )
		{
			for( j = 1 ; j <= pDesenho->iColunas ; j++ )
			{
				Celula * pCelula = NULL;
				pCelula = ( Celula* ) MAT_ObterElemento( pDesenho->pMatrizJogo, i-1, j-1 );
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
		int i, j;

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
			for( j = 0; j < pDesenho->iColunas; j++ )
			{
				// Recupera o elemento dentro da matriz na posição i, j e imprime se ele está marcado ou não
				Celula * pCelula = NULL;
				pCelula = ( Celula* ) MAT_ObterElemento( pDesenho->pMatrizJogo, i, j );
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
		int i, j;
		char * NomeExtArquivo;

		// Testa se a estrutura desenho está definida
		if( pDesenho == NULL )
			return DES_CondRetDesenhoNaoIniciado;

		// Tamanho da string dada + tamanho de ".des" + '\0'
		tamStringNome = strlen( NomeArquivo ) + 5;

		// Cria uma string com tamanho adequando
		NomeExtArquivo = ( char* ) malloc( tamStringNome * sizeof( char ) ) ; 
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
		for( i = 0; i < pDesenho->iLinhas; i++ )
		{
			// Imprime as colunas
			for( j = 0; j < pDesenho->iColunas; j++ )
			{
				// Recupera o elemento dentro da matriz na posição i, j e imprime se ele está marcado ou não
				Celula * pCelula = NULL;
				pCelula = ( Celula* ) MAT_ObterElemento( pDesenho->pMatrizJogo, i, j );
				fprintf( ArquivoDesenho, "%d ", CEL_MarcacaoAtual( pCelula ) );
			}

			fprintf( ArquivoDesenho, " \n" );
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
				Celula * pCelula = NULL;
				pCelula = (Celula*) MAT_ObterElemento( pDesenho->pMatrizJogo, i, j );

				//Compara marcação atual com esperada, se forem diferentes o jogo não está terminado
				if( CEL_MarcacaoEsperada( pCelula ) != CEL_MarcacaoAtual( pCelula ) )
					return 0;
			}
		}

		// Perfeito, o jogo acabou
		return 1;
	}


/***********************************************************************
*
*   Função: DES ImprimeDesenho
*
*	Imprime completamente a matriz de jogo e as listas de valores.
*
*	Complexidade: O(n^2) -> pode percorrer toda a matriz
*
***********************************************************************/
		DES_tpCondRet DES_ImprimeDesenho ( void )
	{
		
		int i, j;
		int PaddingHorizontal = 0, PaddingVertical = 0;

		if( pDesenho == NULL )
			return DES_CondRetDesenhoNaoIniciado;

		printf( "\nQuantidade de Dicas restantes: %d\n\n", pDesenho->iDicas );
		//Imprime coordenadas de coluna
		printf("    ");
		for( i = 1; i <= pDesenho->iColunas; i++ )
		{
			printf(" %2d  ", i);
		}
		printf("\n");

		printf("    ");
		for( i = 1; i <= pDesenho->iColunas; i++ )
		{
			printf("-----", i);
		}
		printf("\n");
		//Verifica o número máximo de elementos em listas horizontais
		for( i = 0; i < pDesenho->iLinhas; i++ )
		{
			int NumElementos = LST_RetornaNumElementos( pDesenho->pListasHorizontais[i] );
			if( NumElementos > PaddingHorizontal )
				PaddingHorizontal = NumElementos;
		}

		//Verifica o número máximo de elementos em listas verticais
		for( i = 0; i < pDesenho->iColunas; i++ )
		{
			int NumElementos = LST_RetornaNumElementos( pDesenho->pListasVerticais[i] );
			if( NumElementos > PaddingVertical )
				PaddingVertical = NumElementos;
		}
		
		/*****************************************************************************/
		// INICIO -> Imprime valores de linha

		// Volta todas as listas para a posição inicial
		for( j = 0; j < pDesenho->iColunas; j++ )
			LST_IrInicio( pDesenho->pListasHorizontais[j] ); 

		// Imprime para cada linha
		for ( i = 0; i < pDesenho->iLinhas; i++ )
		{
			int k;
			TpValor* Valor = NULL;

			printf(" %2d ", i+1);
			// Marca x se a célula estiver preenchida
			for(k = 0; k < pDesenho->iColunas; k++ ){
				Celula* pCelula = ( Celula* ) MAT_ObterElemento( pDesenho->pMatrizJogo, i, k );
				printf("|");
				if( CEL_MarcacaoAtual( pCelula ) )
					printf(" X ");
				else
					printf("   ");
				printf("|");
			}
			// Após marcar todas as células da linha, imprime a lista de valores
			for ( j = 0; j < PaddingHorizontal; j++ )
			{
				Valor = ( TpValor* ) LST_ObterValor( pDesenho->pListasHorizontais[i] );
				// Como a função avançar não move o No corrente para NULL, tenho que 
				// certificar que não vai imprimir se já terminou
				if( LST_RetornaNumElementos( pDesenho->pListasHorizontais[i] ) > j )
				{
					if( Valor != NULL )
					{
						printf(" %d", VAL_ObterPintados( Valor ) );
						LST_Avancar( pDesenho->pListasHorizontais[i], 1 );
					}
				} else {
					printf("  ");
				}
			}
			printf("\n");
			printf("    ");
			for( j = 0; j < pDesenho->iColunas; j++)
			{
				printf("-----");
			}
			printf("\n");
		}

		// FIM -> Imprime valores de linha
		/*****************************************************************************/
		/*****************************************************************************/
		// INICIO -> Imprime valores de coluna

		// Volta todas as listas para a posição inicial
		for( j = 0; j < pDesenho->iLinhas; j++ )
				LST_IrInicio( pDesenho->pListasVerticais[j] ); 

		// Imprime as listas verticais.
		
		for( i = 0; i < PaddingVertical; i++ )
		{
			printf("    ");
			for( j = 0; j < pDesenho->iColunas; j++ )
			{
				TpValor* Valor = NULL;
				Valor = ( TpValor* ) LST_ObterValor( pDesenho->pListasVerticais[j] );
				// Como a função avançar não move o No corrente para NULL, tenho que 
				// certificar que não vai imprimir se já terminou
				if( LST_RetornaNumElementos( pDesenho->pListasVerticais[j] ) > i )
				{
					if( Valor != NULL )
					{
						printf(" %2d  ", VAL_ObterPintados( Valor ) );
						LST_Avancar( pDesenho->pListasVerticais[j], 1 );
					}
				} else {
					printf("     ");
				}
			}
			printf("\n");

		}

		// FIM -> Imprime valores de coluna
		/*****************************************************************************/

		printf("\n\n\n");
		return DES_CondRetOk;
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
				Celula * pCelula = NULL;
				int randomNumber = rand( ) % 2;

				// Se o resultado é impar, liga a célula. 50% de chance.
				pCelula = CEL_CriaCelula( randomNumber, 0 );

				MAT_AlterarValor( pDesenho->pMatrizJogo, pCelula, i, j
					#ifdef _DEBUG
						, 'c'
					#endif
					);

			}/* for */
		}/* for */
	}


/***********************************************************************
*
*  Função: DES Preenche Matriz Zerada
*
*  Preenche a matriz de jogo com células zeradas para gerar um
*  esquema de projeto de nonogram.
*
*  Complexidade: O(n^2)
*
***********************************************************************/

	static void PreencheMatrizZerada( void )
	{
		int i, j;

		//Percorre cada linha e cada coluna ligando ou nao a marcaóao
		for( i = 0 ; i < pDesenho->iLinhas ; i++ )
		{
			for( j = 0 ; j < pDesenho->iColunas ; j++ )
			{
				Celula * pCelula = NULL;
				pCelula = CEL_CriaCelula( 0, 0 );

				MAT_AlterarValor( pDesenho->pMatrizJogo, pCelula, i, j 
					#ifdef _DEBUG
						, 'c'
					#endif
					);

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
				Celula * pCelula = NULL;
				int Marcacao; // indica se a célula deve ser marcada

				if( fscanf(ArquivoDesenho, "%d ", &Marcacao) != 1 )
					return DES_CondRetArquivoInvalido;

				// Cria célula com valor de marcação lido no arquivo e não marcado
				pCelula = CEL_CriaCelula( Marcacao, 0 );

				MAT_AlterarValor( pDesenho->pMatrizJogo, pCelula, i, j
					#ifdef _DEBUG
						, 'c'
					#endif
					);

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

				if( fscanf ( ArquivoDesenho, "%d %d ", &Marcacao, &Marcado ) != 2 )
					return DES_CondRetArquivoInvalido;

				pCelula = CEL_CriaCelula( Marcacao, Marcado );

				MAT_AlterarValor(pDesenho->pMatrizJogo, pCelula, i, j 
					#ifdef _DEBUG
						, 'c'
					#endif
					);

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
		DES_tpCondRet CondRet;

		//Aloca o vetor que vai guardar as cabeças de listas horizontais
		pDesenho->pListasHorizontais = ( TpLista ** ) malloc( pDesenho->iLinhas * sizeof( TpLista* ) );
		if(pDesenho->pListasHorizontais == NULL)
			return DES_CondRetFaltouMemoria;

		#ifdef _DEBUG
			CED_MarcarEspacoAtivo( pDesenho->pListasHorizontais );
		#endif

		//Aloca o vetor que vai guardar as cabeças de listas verticais
		pDesenho->pListasVerticais = ( TpLista ** ) malloc( pDesenho->iColunas * sizeof( TpLista* ) );
		if( pDesenho->pListasVerticais == NULL )
			return DES_CondRetFaltouMemoria;

		#ifdef _DEBUG
			CED_MarcarEspacoAtivo( pDesenho->pListasVerticais );
		#endif

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
		for( i = 0; i < pDesenho->iLinhas; i++ )
		{
			int sequencia = 0;
			
			TpValor * pValor = NULL;

			pDesenho->pListasHorizontais[i] = LST_CriarLista( 	
				#ifdef _DEBUG
					'v'
				#endif
			 );
			for( j = 0; j < pDesenho->iColunas; j++ )
			{
				//Recupera a célula na posição (i,j)
				Celula* pCelula = NULL;
				pCelula = ( Celula* ) MAT_ObterElemento( pDesenho->pMatrizJogo, i, j );
				if( CEL_MarcacaoEsperada( pCelula ) )
				{
					if( !sequencia )
					{
						pValor = VAL_CriarValor( );
						LST_InserirNovoNoFim( pDesenho->pListasHorizontais[i], pValor
								#ifdef _DEBUG
									 , 'v'
								 #endif
						 );
					}
					//Indica que existe uma sequencia e incrementa a estrutura Valor
					sequencia = 1;
					LST_IrFim( pDesenho->pListasHorizontais[i] );
					VAL_IncrementarQntdPintados( ( TpValor* ) LST_ObterValor( pDesenho->pListasHorizontais[i] ) );
				}
				else
				{
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
		for( j = 0; j < pDesenho->iColunas; j++ )
		{
			int sequencia = 0;

			TpValor * pValor = NULL;

			pDesenho->pListasVerticais[j] = LST_CriarLista( 	
			#ifdef _DEBUG
					 'v'
			#endif
						 );
			for( i = 0; i < pDesenho->iLinhas; i++ )
			{
				//Recupera a célula na posição (i,j)
				Celula* pCelula = NULL;
				pCelula = ( Celula* )MAT_ObterElemento( pDesenho->pMatrizJogo, i, j );
				if( CEL_MarcacaoEsperada( pCelula ) )
				{
					if( !sequencia )
					{
						pValor = VAL_CriarValor( );
						LST_InserirNovoNoFim( pDesenho->pListasVerticais[j], pValor 
							#ifdef _DEBUG
									 , 'v'
							#endif
						 );
					}
					//Indica que existe uma sequencia e incrementa a estrutura Valor
					sequencia = 1;
					LST_IrFim( pDesenho->pListasVerticais[j] );
					VAL_IncrementarQntdPintados( ( TpValor* ) LST_ObterValor( pDesenho->pListasVerticais[j] ) );
				}
				else
				{
					sequencia = 0;
				}
			}
		}/* for */

		return DES_CondRetOk;
	}


/***********************************************************************
*
*   Função: Exclui Valor
*
*	Essa função é passada por parâmetro para outros módulos que precisam
*	de funções específicas de exclusão de estruturas. Usada para exluir
*	valores.
*
***********************************************************************/

	void ExcluiValor(void * pDado)
	{
		VAL_DestruirValor( (TpValor*) pDado );
	}

/***********************************************************************
*
*   Função: Exclui Célula
*
*	Essa função é passada por parâmetro para outros módulos que precisam
*	de funções específicas de exclusão de estruturas. Usada para exluir
*	células.
*
***********************************************************************/

	void ExcluiCelula(void * pDado)
	{
		CEL_DestruirCelula( (Celula*) pDado );
	}


#ifdef _DEBUG

/***********************************************************************
*
*   Função: DES Verifica
*
*   Essa função é do modo DEBUG e tem o objetivo de destruir as 
*	assertivas estruturais do módulo Desenho com intuito de testar
*	possíveis falhas/inconsistências no tempo de execução.
*
***********************************************************************/
	DES_tpCondRet DES_Verifica ( int* numErros )
	{
		int i = 0, aux=0;
		
		*numErros = 0;
		for ( i =0 ; i< pDesenho->iLinhas ; i++ )
		{
			aux = LST_VerificaAssertivaAnt ( pDesenho ->pListasHorizontais [i] );
			if(aux > 0)
			{
				CNT_CONTAR("DES_AssertivaListaHorizontalPonteiroAnt_ComErro");
				printf ( "\n Erro no ponteiro para celula predecessora na Lista Horizontal \n Linhas : %d \n", i );
			} /* if */
			else
			{
				CNT_CONTAR("DES_AssertivaListaHorizontalPonteiroAnt_OK");
			} /* else */
			*numErros += aux;

			aux = LST_VerificaAssertivaProx ( pDesenho ->pListasHorizontais [i] );
			if(aux > 0)
			{
				CNT_CONTAR("DES_AssertivaListaHorizontalPonteiroProx_ComErro");
				printf ("\n Erro no ponteiro para celula sucessora na Lista Horizontal \n Linhas : %d \n", i );
			} /* if */
			else
			{
				CNT_CONTAR("DES_AssertivaListaHorizontalPonteiroProx_OK");
			} /*else*/
			*numErros += aux;

            aux = LST_VerificaAssertivaListaVazia ( pDesenho ->pListasHorizontais [i] );
			if(aux > 0)
			{
				CNT_CONTAR("DES_AssertivaListaHorizontalVazio_ComErro");
				printf ("\nErro nas assertivas de uma lista horizontal vazia \n Linhas : %d \n", i);
			} /* if */
			else
			{
				CNT_CONTAR("DES_AssertivaListaHorizontalVazio_OK");
			} /* else */
			*numErros += aux;

            aux = LST_VerificaAssertivaListaElemUnico ( pDesenho ->pListasHorizontais [i] );
			if(aux > 0)
			{
				CNT_CONTAR("DES_AssertivaListaHorizontalElemUnico_ComErro");
				printf ("\nErro nas assertivas de uma lista horizontal com elemento unico \n Linhas : %d \n", i);
			} /* if */
			else
			{
				CNT_CONTAR("DES_AssertivaListaHorizontalElemUnico_OK");
			} /* else */
			*numErros += aux;

            aux = LST_VerificaAssertivaListaPreenchida ( pDesenho ->pListasHorizontais [i] );
			if(aux > 0)
			{
				CNT_CONTAR("DES_AssertivaListaHorizontalPreenchida_ComErro");
				printf ("\nErro nas assertivas de uma lista horizontal com mais 1 um elementos \n Linhas : %d \n", i);
			} /* if */
			else
			{
				CNT_CONTAR("DES_AssertivaListaHorizontalPreenchida_OK");
			} /* else */
			*numErros += aux;

			aux = LST_VerificaAssertivaTipoListaElementos( pDesenho ->pListasHorizontais [i] );
			if(aux > 0)
			{
				CNT_CONTAR("DES_AssertivaListaHorizontalTipoListaElementos_ComErro");
				printf ("\nErro: Tipos de conteudo inconsistentes na lista horizontal %d\n", i);
			} /* if */ 
			else 
			{
				CNT_CONTAR("DES_AssertivaListaHorizontalTipoListaElementos_Ok");
			} /* else */
			*numErros += aux;
		} /* for */
		for ( i =0 ; i< pDesenho->iColunas ; i++ )
		{

			aux = LST_VerificaAssertivaAnt ( pDesenho ->pListasVerticais [i] );
			if(aux > 0)
			{
				CNT_CONTAR("DES_AssertivaListaVerticalPonteiroAnt_ComErro");
				printf ("\n Erro no ponteiro para celula anterior na coluna : %d \n", i );
			} /* if */
			else
			{
				CNT_CONTAR("DES_AssertivaListaVerticalPonteiroAnt_OK");
			} /* else */
			*numErros += aux;

			aux = LST_VerificaAssertivaProx ( pDesenho ->pListasVerticais [i] );
			if(aux > 0)
			{
				CNT_CONTAR("DES_AssertivaListaVerticalPonteiroProx_ComErro");
				printf ("\n Erro no ponteiro para celula sucessora na coluna : %d \n", i );
			} /* if */
			else
			{
				CNT_CONTAR("DES_AssertivaListaVerticalPonteiroProx_OK");
			} /* else */
			*numErros += aux;

            aux = LST_VerificaAssertivaListaVazia ( pDesenho ->pListasVerticais [i] );
			if(aux > 0)
			{
				CNT_CONTAR("DES_AssertivaListaVerticalVazio_ComErro");
				printf ("\n Erro na assertiva de lista vazia na coluna : %d \n", i );
			} /* if */

			else
			{
				CNT_CONTAR("DES_AssertivaListaVerticalVazio_OK");
			} /*else */
			*numErros += aux;

            aux = LST_VerificaAssertivaListaElemUnico ( pDesenho ->pListasVerticais [i] );
			if(aux > 0)
			{
				CNT_CONTAR("DES_AssertivaListaVerticalElemUnico_ComErro");
				printf ("\n Erro na assertiva de lista vertical com elemento unico : %d \n", i );
			} /* if */
			else
			{
				CNT_CONTAR("DES_AssertivaListaVerticalElemUnico_OK");
			} /* else */
			*numErros += aux;


            aux = LST_VerificaAssertivaListaPreenchida ( pDesenho ->pListasVerticais [i] );
			if(aux > 0)
			{
				CNT_CONTAR("DES_AssertivaListaVerticalPreenchida_ComErro");
				printf ("\n Erro na assertiva de lista vertical preenchida : %d \n", i );
			} /* if */
			else
			{
				CNT_CONTAR("DES_AssertivaListaVerticalPreenchida_OK");
			}/* else */

			*numErros += aux;


			aux = LST_VerificaAssertivaTipoListaElementos( pDesenho ->pListasVerticais [i] );
			if(aux > 0)
			{
				CNT_CONTAR("DES_AssertivaListaVerticalTipoListaElementos_ComErro");
				printf ("\nErro: Tipos de conteudo inconsistentes na lista vertical %d\n", i);
			} /* if */
			else 
			{
				CNT_CONTAR("DES_AssertivaListaVerticalTipoListaElementos_Ok");
			}/* else */
			*numErros += aux;

		} /* for */

		aux = MAT_VerificaAssertivaLinhaColuna( pDesenho->pMatrizJogo );
		if(aux > 0)
		{
			CNT_CONTAR("DES_AssertivaMatrizLinhaColuna_ComErro");
			printf ("\n Erro na assertiva de numero de linhas e colunas" );
		} /* if */
		else
		{
			CNT_CONTAR("DES_AssertivaMatrizLinhaColuna_OK");
		} /* else */
		*numErros += aux;

		aux = MAT_VerificaAssertivaPontLista( pDesenho->pMatrizJogo );
		if(aux > 0)
		{
				CNT_CONTAR("DES_AssertivaMatrizPonteiroLista_ComErro");
				printf ("\n Erro no ponteiro para lista da matriz" );
		} /* if */
		else
		{
				CNT_CONTAR("DES_AssertivaMatrizPonteiroLista_OK");
		} /* else */
		*numErros += aux;

		aux = MAT_VerificaAssertivaListas( pDesenho->pMatrizJogo );
		if(aux > 0)
		{
				CNT_CONTAR("DES_AssertivaMatrizListas_ComErro");
				printf ("\n Erro na assertiva da lista da matriz" );
		} /* if */
		else
		{
			CNT_CONTAR("DES_AssertivaMatrizListas_OK");
		} /*else */
		*numErros += aux;
	}

/***********************************************************************
*
*   Função: DES Deturpar
*
*   Essa função é do modo DEBUG e tem o objetivo de destruir as 
*	assertivas estruturais do módulo Desenho com intuito de testar
*	possíveis falhas/inconsistências no tempo de execução.
*
***********************************************************************/

	DES_tpCondRet DES_Deturpar ( int opcao ) 
	{
		int lixo;
		int valor_aleatorio = 99;
		switch ( opcao )
		{
		case D_DESTROI_CORRENTE :
			LST_LiberarNoCorrente( pDesenho->pListasHorizontais[0], ExcluiValor, 1 );
			break;
		
		case D_NULL_SUCESSOR:
			//Considerando o elemento mediano (2,2)
			MAT_AlteraPonteiroSucessor( pDesenho->pMatrizJogo, 2, 2, NULL );
			break;

		case D_NULL_PREDECESSOR:
			//Considerando o elemento mediano (2,2)
			MAT_AlteraPonteiroPredecessor( pDesenho->pMatrizJogo, 2, 2, NULL );
			break;

		case D_LIXO_SUCESSOR:
			MAT_AlteraPonteiroSucessor( pDesenho->pMatrizJogo, 4, 1, &lixo );
			break;

		case D_LIXO_PREDECESSOR:
			MAT_AlteraPonteiroPredecessor( pDesenho->pMatrizJogo, 3, 3, &lixo );
			break;
		
		case D_NULL_COORDENADA:
			MAT_AlterarValor( pDesenho->pMatrizJogo, NULL, 3, 4, 'N' );
			break;
		
		case D_ALT_COORDENADA:
			MAT_AlterarValor( pDesenho->pMatrizJogo, &valor_aleatorio, 1, 1, 'I' );
			break;
		
		case D_FREE_INCOMPLETO:
			MAT_FreeIncompleto( pDesenho->pMatrizJogo);
			break;
		
		case D_NULL_CORRENTE:
			LST_NuloCorrente( pDesenho->pListasVerticais[1] );
			break;
		case D_NULL_ORIGEM:
			LST_NuloOrigem( pDesenho->pListasHorizontais[0] );
			break;
		default:
			printf("Caso de deturpação inválido\n");
			break;
		}

		return DES_CondRetOk;
	}

#endif 
