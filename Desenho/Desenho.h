/***************************************************************************
*
*  $MCD Módulo de definição: Módulo desenho
*
*  Arquivo gerado:              Desenho.h
*  Letras identificadoras:      DES
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: ps - Patrick Sava
*
*  $HA Histórico de evoluçãoo:
*     Versão  Autor    Data     Observações
*       1.00   ps   24/03/2014 Início do desenvolvimento
*
*  $ED Descrição do módulo
*    Este módulo implementa um conjunto de funçoes para tratar do
*	  gerenciamento do desenho a medida que o usuário vai preenchendo a
*	  matriz do Nonogram.
*    Ele integra os módulos de Matriz Genérica, Lista Duplamente Encadeada
*	  Genérica, Célula e Valor para
*	  permitir ao módulo Jogo uma fácil manipulação do campo de jogo.
*
***************************************************************************/

/***********************************************************************
*
*  $TC Tipo de dados: Constantes do módulo
*
***********************************************************************/

#define NUM_LINHAS_MINIMO 5
#define NUM_LINHAS_MAXIMO 10

#define NUM_COLUNAS_MINIMO 5
#define NUM_COLUNAS_MAXIMO 10

#define NUM_MAX_DICAS 10

#define NOME_JOGO_SALVO "ultimo_jogo_salvo.des"

/***********************************************************************
*
*  $TC Tipo de dados: DES Condições de retorno
*
***********************************************************************/

   typedef enum {

      DES_CondRetOK = 0,
            /* Executou correto */

      DES_CondRetFaltouMemoria = 1,
            /* Faltou memória ao alocar dados */

		 DES_CondRetTamanhoInvalido = 2,
			   /* Tamanho de máximo ou mínimo de matriz permitido violado */

		 DES_CondRetDesenhoNaoIniciado = 3,
			   /* Estrutura desenho ainda não foi definida */

		 DES_CondRetCoordenadaInvalida = 4,
			   /* Coordenada de marcação inválida */

		 DES_CondRetSemDicas = 5,
			   /* O usuário não possui mais dicas sobrando */

		 DES_CondRetJogoFinalizado = 6,
			   /* Todas as células devidas já foram pintadas */

       DES_CondRetPonteiroArquivoNulo = 7,
            /* Ponteiro para arquivo de jogo projetado nulo */

       DES_CondRetArquivoInvalido = 8,
            /* Arquivo de jogo projetado com erros */

   } DES_tpCondRet ;



/***********************************************************************
*
*  $FC Função: DES Inicia Desenho
*
*  $ED Descrição da função
*     Cria um desenho de jogo sem nenhum preenchimento.
*     Caso já exista um desenho preparado, ele será destruido e um
*     novo será feito.
*
*  $FV Valor retornado
*     DES_CondRetOK
*     DES_CondRetFaltouMemoria
*     DES_CondRetTamanhoInvalido
*
*  $AE Assertivas de Entrada
*	  - Número de Linhas e Colunas são inteiros entre 3 e 10
*
*  $AS Assertivas de Saída
*	  - O módulo desenho definiu corretamente a estrutura desenho
*      de forma aleatória.
*	  - O tabuleiro possuirá pelo menos uma célula que terá que ser
*	    marcada para acabar o jogo
*	  - Valem as assertivas estruturais da estrutura de desenho e sub-
*	    estruturas.
***********************************************************************/


   DES_tpCondRet DES_IniciaDesenho( unsigned int NumLinhas, unsigned int NumColunas );



/***********************************************************************
*
*  $FC Função: DES Inicia Desenho Vazio
*
*  $ED Descrição da função
*     Cria um desenho de jogo sem nenhum preenchimento e sem 
*     preparar as células que devem ser marcadas.
*
*  $FV Valor retornado
*     DES_CondRetOK
*     DES_CondRetFaltouMemoria
*     DES_CondRetTamanhoInvalido
*
*  $AE Assertivas de Entrada
*    - Número de Linhas e Colunas são inteiros entre 3 e 10
*
*  $AS Assertivas de Saída
*    - O módulo desenho definiu corretamente a estrutura desenho
*      de forma vazia, ou seja, sem marcações previstas. Como se
*      não houvesse um jogo.
*    - Valem as assertivas estruturais da estrutura de desenho e sub-
*      estruturas.
***********************************************************************/


   DES_tpCondRet DES_IniciaDesenhoVazio( unsigned int NumLinhas, unsigned int NumColunas );


/***********************************************************************
*
*  $FC Função: DES Inicia Desenho Vazio
*
*  $ED Descrição da função
*     Cria um desenho de jogo baseado nas informações gravadas no
*     arquivo passado como parâmetro.
*     Fica para responsabilidade do módulo cliente fechar o arquivo
*     de entrada.
*
*  $FV Valor retornado
*     DES_CondRetOK
*     DES_CondRetFaltouMemoria
*     DES_CondRetTamanhoInvalido
*     DES_CondRetArquivoInvalido
*
*  $AE Assertivas de Entrada
*    - O arquivo deve ter sido gerado pelo próprio jogo no modo
*      projeto para que seja válido.
*
*  $AS Assertivas de Saída
*    - O módulo desenho definiu corretamente a estrutura desenho
*      de forma coerente com os valores gravados no arquivo.
*    - Valem as assertivas estruturais da estrutura de desenho e sub-
*      estruturas.
***********************************************************************/


   DES_tpCondRet DES_IniciaDesenhoProjetado( FILE * ArquivoDesenho );


/***********************************************************************
*
*  $FC Função: DES Inicia Desenho Vazio
*
*  $ED Descrição da função
*     Cria um desenho de jogo baseado nas informações gravadas no
*     arquivo passado como parâmetro.
*     Fica para responsabilidade do módulo cliente fechar o arquivo
*     de entrada.
*
*  $FV Valor retornado
*     DES_CondRetOK
*     DES_CondRetFaltouMemoria
*     DES_CondRetPonteiroArquivoNulo
*     DES_CondRetTamanhoInvalido
*     DES_CondRetArquivoInvalido
*
*  $AE Assertivas de Entrada
*    - Existe um jogo salvo com o nome NOME_JOGO_SALVO
*
*  $AS Assertivas de Saída
*    - O módulo desenho definiu corretamente a estrutura desenho
*      de forma coerente com os valores gravados no arquivo.
*    - Valem as assertivas estruturais da estrutura de desenho e sub-
*      estruturas.
*
***********************************************************************/


   DES_tpCondRet DES_RetomaUltimoJogoSalvo( void );


/***********************************************************************
*
*  $FC Função: DES Destroi Desenho
*
*  $ED Descrição da função
*     Libera a estrutura desenho encapsulado no módulo desenho
*
*  $FV Valor retornado
*     DES_CondRetOK
*     DES_CondRetDesenhoNaoIniciado
*
*  $AE Assertivas de Entrada
*
*  $AS Assertivas de Saída
*	  - A variável desenho encapsulada no módulo foi liberada e 
*     agora não aponta para nada.
***********************************************************************/


   DES_tpCondRet DES_DestroiDesenho( void );


/***********************************************************************
*
*  $FC Função: DES Altera Marcação de Coordenada
*
*  $ED Descrição da função
*     Dada uma coordenada (X,Y), a função busca pela célula referente e altera
*     sua marcação atual. Se ela já estava marcada passa a ficar em branco e
*     vice-versa. Essa função automaticamente informa se o jogo terminou.
*
*  $FV Valor retornado
*     DES_CondRetOK
*     DES_CondRetDesenhoNaoIniciado
*     DES_CondRetCoordenadaInvalida
*
*  $AE Assertivas de Entrada
*	  - Coord_X e Coord_Y devem ser valores entre 0 e o máximo do tabuleiro
*	  - Valem as assertivas estruturais da estrutura de desenho e sub-
*	    estruturas.
*
*  $AS Assertivas de Saída
*	  - Sendo pCelula a célula referente a coordenada (X,Y) dada,
*	    //Depois CEL_ExibeMarcação(pCelula) == !CEL_ExibeMarcacao(pCelula) //Antes
***********************************************************************/


   DES_tpCondRet DES_AlteraMarcacaoCoordenada( unsigned int Coord_X, unsigned int Coord_Y );


/***********************************************************************
*
*  $FC Função: DES Ativa Dica
*
*  $ED Descrição da função
*     Marca uma célula do tabuleiro que deveria ser marcada mas ainda está
*     em branco
*
*  $FV Valor retornado
*     DES_CondRetOK
*     DES_CondRetSemDicas
*     DES_CondRetDesenhoNaoIniciado
*     DES_CondRetJogoFinalizado
*
*  $AE Assertivas de Entrada
*	  - Valem as assertivas estruturais da estrutura de desenho e sub-
*	    estruturas.
*
*  $AS Assertivas de Saída
*	  - Uma nova célula será marcada
*
***********************************************************************/


   DES_tpCondRet DES_AtivaDica ( void );


/***********************************************************************
*
*  $FC Função: DES Imprime Matriz Jogo
*
*  $ED Descrição da função
*     Imprime na tela a matriz de jogo com as marcações feitas até o
*     momento
*
*  $FV Valor retornado
*     DES_CondRetOK
*     DES_CondRetDesenhoNaoIniciado
*
*  $AE Assertivas de Entrada
*
*  $AS Assertivas de Saída
*
***********************************************************************/


   DES_tpCondRet DES_ImprimeMatrizJogo( void );


/***********************************************************************
*
*  $FC Função: DES Grava Matriz Projetada
*
*  $ED Descrição da função
*     Salva em arquivo a matriz preenchida pelo usuário no modo projeto.
*     Pode ser retomado um jogo a partir deste arquivo.
*
*  $FV Valor retornado
*     DES_CondRetOK
*     DES_CondRetDesenhoNaoIniciado
*     DES_CondRetFaltouMemoria
*
*  $AE Assertivas de Entrada
*     - Valem as assertivas estruturais da estrutura de desenho e sub-
*      estruturas.
*
*  $AS Assertivas de Saída
*     - Valem as assertivas estruturais da estrutura de desenho e sub-
*      estruturas.
*     - Um arquivo com o nome dado pelo usuário deve ser gerado na pasta
*      de projetos de jogo.
*
***********************************************************************/


   DES_tpCondRet DES_GravaMatrizProjetada( char* NomeArquivo );


/***********************************************************************
*
*  $FC Função: DES Desenho Finalizado
*
*  $ED Descrição da função
*     Retorna 1 se o desenho foi completamente preenchido, 0 caso 
*     ainda não esteja terminado.
*
*  $FV Valor retornado
*     1 -> verdade
*     0 -> falso
*
*  $AE Assertivas de Entrada
*     - A estrutura desenho deve estar definida
*
*  $AS Assertivas de Saída
*
***********************************************************************/


   int DES_DesenhoFinalizado ( void );

