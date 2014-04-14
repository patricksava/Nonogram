#if ! defined( LISTA_ )
#define LISTA_

/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Lista Genérica
*
*  Arquivo gerado:              ListaGenerica.H
*  Letras identificadoras:      LST
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mbv - Maria Beatriz Vaz
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		3.00   mbv   14/abr/2014 Revisão geral do código e dos comentários
*       2.00   mbv   21/mar/2014 Continuaçao do desenvolvimento, reestruturação
*       1.00   mbv   19/mar/2014 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar listas duplamente encadeadas.
*	  A lista duplamente encadeada possui um ponteiro para o próximo elemento 
*	  e um ponteiro para o elemento anterior.
*	  Dado um elemento, é possível acessar o próximo e o anterior.
*	  Dado um ponteiro para o último elemento da lista, é possível
*     percorrer a lista em ordem inversa.
*	  Este módulo permite a criação de mais de uma lista.
*     Ao iniciar a execução do programa não existe listas.
*
*  $AE Assertivas Estruturais 
*  Lista contém: 
*    - Cabeça da lista
*    - Nó da lista
*   Seja pLista um ponteiro para a cabeça da Lista e pElem um ponteiro para o nó da lista.
*   Se pElem -> pProx != NULL, então pElem -> pProx -> pAnt == pEle
*   Se pElem -> pAnt != NULL, então pElem -> pAnt -> pProx == pElem
*   Se pLista -> numElementos == 0, então pLista->pNoCorrente == NULL e pLista -> pOrigemLista == NULL e pLista -> pFimLista == NULL
*   Se pLista -> numElementos > 0, então pLista->pNoCorrente != NULL
*   Se pLista -> numElementos == 1,então pLista ->pNoCorrente == pLista-> pNoOrigem e pLista -> pNoCorrente == pLista -> pNoFim 
*
***************************************************************************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif



/***********************************************************************
*
*  $TC Tipo de dados: LST Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         LST_CondRetOK = 0 ,
               /* Executou correto */

         LST_CondRetListaInexistente= 1 ,
               /* Lista não existe. */

		 LST_CondRetInfoNaoEncontrada = 2 ,
               /* Informação recebida não encontrada na lista.  */

		LST_CondRetListaVazia = 3 ,
			   /* Lista não possui elementos. */

		LST_CondRetFimLista = 4 ,
			   /* Próximo ponteiro é NULL. */

         LST_CondRetFaltouMemoria = 5 ,
               /* Faltou memória ao alocar dados */

		LST_CondRetNoNaoPossuiInfo = 6 ,

   } LST_tpCondRet ;
/***********************************************************************
* 
*   $ED Descrição
*	Especifica a estrutura de dados utilizada no módulo.
*
***********************************************************************/
   
   typedef struct tpLista TpLista;

/***********************************************************************
*
*  $FC Função: LST Criar lista genérica duplamente encadeada.
*
*  $ED Descrição da função
*     Cria uma nova lista, zerando todos os seus campos da cabeça.
*
*  $FV Valor retornado
*     TpLista * pLista - ponteiro para a nova lista
*
*  $AE Assertivas de Entrada
*	O ponteiro para receber a Lista deve ser NULL
*
*  $AS Assertivas de Saída
*	Caso tenha espaço na memória a lista será criada e
*	pLista->pNoCorrente = pLista -> pOrigemLista = pLista -> pFimLista = NULL
*   Valem as assertivas estruturais da Lista Duplamente Encadeada
*
***********************************************************************/

   TpLista * LST_CriarLista( void ) ;

/***********************************************************************
*
*  $FC Função: LST Esvaziar lista duplamente encadeada.
*
*  $EP Parâmetros
*     pLista - lista que deseja esvaziar.
*	  ExcluirValor - Função responsável pela exclusão do elemento.
*
*  $ED Descrição da função
*     Libera todos os ponteiros da lista, ressatando a lista como nova.
*     Faz nada caso a lista não exista.
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Saída
*	Caso a lista seja válida, 
*	pLista->pNoCorrente = pLista -> pOrigemLista = pLista -> pFimLista = NULL
*
*
***********************************************************************/

   void LST_EsvaziarLista( TpLista * pLista, void ( * ExcluirValor ) ( void * pDado) ) ;

/***********************************************************************
*
*  $FC Função: LST Destruir lista duplamente encadeada.
*
*  $EP Parâmetros
*     pLista - lista que deseja destruir.
*	  ExcluirValor - Função responsável pela exclusão do elemento.
*
*  $ED Descrição da função
*     Libera todos os ponteiros da lista, anulando-a.
*     Faz nada caso a lista não exista.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetListaInexistente
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*   A função ExcluirValor deve ser responsável pela exclusão do Valor do nó.
*
*  $AS Assertivas de Saída
*	Caso a lista seja válida, o espaço alocado na memória será liberado.
*
*
***********************************************************************/

   LST_tpCondRet LST_DestruirLista( TpLista * pLista, void ( * ExcluirValor) ( void * pDado) ) ;

/***********************************************************************
*
*  $FC Função: LST Adicionar novo nó no inicio da lista duplamente encadeada.
*
*  $ED Descrição da função
*     Insere um elemento no ínicio da lista .
*
*  $EP Parâmetros
*     pLista - lista que deseja realizar a busca e a 
*	  informacao - informação que deseja inserir.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetFaltouMemoria
*	  LST_CondRetListaInexistente
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Saída
*	Caso a lista seja válida, o nó foi inserido e 
*	pLista->pNoCorrente = pLista -> pOrigemLista = NovoNo
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_InserirNovoNoInicio( TpLista * pLista , void * informacao ) ;


/***********************************************************************
*
*  $FC Função: LST Adicionar novo nó no fim da lista duplamente encadeada.
*
*  $ED Descrição da função
*     Insere elemento no final da lista.
*
*  $EP Parâmetros
*     pLista - lista que deseja realizar a busca e a 
*	  informacao - informação que deseja inserir.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetFaltouMemoria
*	  LST_CondRetListaInexistente
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Saída
*	Caso a lista seja válida, o nó foi inserido
*	pLista->pNoCorrente = pLista -> pFimLista = NovoNo
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_InserirNovoNoFim( TpLista * pLista , void * informacao ) ;

/***********************************************************************
*
*  $FC Função: LST Inserir novo nó antes do nó corrente.
*
*  $ED Descrição da função
*     Insere um elemento antes do elemento corrente. Não cria uma nova lista,
*	  caso essa não exista.
*
*  $EP Parâmetros
*     pLista - lista que deseja realizar a busca e a 
*	  informacao - informação que deseja inserir.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetFaltouMemoria
*	  LST_CondRetCriouLista
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Saída
*	Caso a lista seja válida, o nó foi inserido e 
*	pLista->pNoCorrente = NovoNo
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_InserirNoAntes( TpLista * pLista , void * informacao ) ;


/***********************************************************************
*
*  $FC Função: LST Inserir novo nó após nó corrente.
*  $ED Descrição da função
*     Insere elemento no final da lista e, caso essa não exista, cria.
*
*  $EP Parâmetros
*     pLista - lista que deseja realizar a busca e a 
*	  informacao - informação que deseja buscar.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetFaltouMemoria
*	  LST_CondRetListaInexistente
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Saída
*	Caso a lista seja válida, o nó foi inserido e  
*	pLista->pNoCorrente = NovoNo
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_InserirNoApos( TpLista * pLista , void * informacao ) ;

/***********************************************************************
*
*  $FC Função: LST Liberar nó corrente.
*
*  $EP Parâmetros
*     pLista - lista que deseja liberar o nó.
*	  ExcluirValor - Função responsável pela exclusão do elemento.
*
*  $ED Descrição da função
*     Libera o ponteiro para o nó corrente.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetListaInexistente
*	  LST_CondRetListaVazia
*
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*   O ponteiro corrente aponta para o nó a ser excluido
*
*  $AS Assertivas de Saída
*	Caso a lista seja válida, o nó foi excluido e o ponteiro corrente aponta
*	para o próximo nó ou NULL caso a lista tenha acado.
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_LiberarNoCorrente( TpLista * Lista, void ( * ExcluirValor) (void * pDado) ) ;
   
/***********************************************************************
*
*  $FC Função: LST obter a informação contida no nó corrente
*
*  $EP Parâmetros
*     pLista - lista que deseja realizar a busca e a 
*	  informacao - ponteiro para armazenar a informacao.
*
*  $ED Descrição da função
*	  Obtem o valor que está dentro da informação
*	  que o nó corrente da lista contém.
*
*  $FV Valor retornado
*     void * informacao - ponteiro para informação retornada
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*	O ponteiro corrente aponta para o nó que se deseja obter as informações
*
*  $AS Assertivas de Saída
*	Caso a lista seja válida, o valor do nó corrente sera retornado
*	Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   void * LST_ObterValor( TpLista * pLista ) ;

/***********************************************************************
*
*  $FC Função: LST alterar a informação contida no nó corrente.
*
*  $EP Parâmetros
*     pLista - lista que deseja realizar a busca e a 
*	  informacao - informação que deseja alterar.
*
*  $ED Descrição da função
*	  Altera o valor que está dentro do nó corrente.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetListaInexistente
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*	O ponteiro corrente aponta para o nó que se deseja alterar
*	A informação genérica deve ser válida.
*
*  $AS Assertivas de Saída
*	Caso a lista seja válida, o valor do nó corrente sera alterado
*	Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_AlterarValor( TpLista * pLista , void * informacao ) ;

/***********************************************************************
*
	*  $FC Função: LST Busca informação.
*
*  $EP Parâmetros
*     pLista - lista que deseja realizar a busca e a 
*	  informacao - informação que deseja buscar.
*     Compara - função responsável por comparar 2 elementos
*				retornando 0 caso sejam iguais
*
*  $ED Descrição da função
*	  Realiza a busca de uma informação dentro de uma lista,
*	  apontando o nó corrente para o nó que contem a informação, caso ache.
*
*  $FV Valor retornado
*     LST_CondRetOK
*	  LST_CondRetInfoNaoEncontrada
*     LST_CondRetListaInexistente
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*	A função busca deve ser válida para o tipo de informação do nó
*
*  $AS Assertivas de Saída
*	Caso a lista seja válida, o valor poderá ser encontrado ou não.
*	Se o valor for encontrado, o ponteiro corrente apontará para ele.
*	Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_Busca( TpLista * pLista , void * informacao , int (Compara)(void *pDado , void * pDado2) ) ;

/***********************************************************************
*
	*  $FC Função: LST Ir para o inicio da lista duplamente encadeada.
*
*  $EP Parâmetros
*     pLista - lista que deseja percorrer.
*
*  $ED Descrição da função
*	  Percorre a lista até achar seu início, apontando para ele.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetListaInexistente
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Saída
*	Caso a lista seja válida, pLista -> pNoCorrente == pLista -> pOrigemLista.
*   Ou ponteiro corrente apontará para NULL caso lista esteja vazia.
*	Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_IrInicio( TpLista * pLista ) ;

/***********************************************************************
*
	*  $FC Função: LST Ir para o fim da lista duplamente encadeada.
*
*  $EP Parâmetros
*     pLista - lista que deseja percorrer.
*
*  $ED Descrição da função
*	  Percorre a lista até achar seu fim, apontado para ele.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetListaInexistente
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Saída
*	Caso a lista seja válida, pLista -> pNoCorrente == pLista -> pFimLista.
*   Ou ponteiro corrente apontará para NULL caso lista esteja vazia.
*	Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_IrFim( TpLista * pLista ) ;

/***********************************************************************
*
	*  $FC Função: LST Ir para o próximo nó na lista duplamente encadeada.
*
*  $EP Parâmetros
*     pLista - lista que deseja percorrer.
*     numElem - numero de elementos que deseja percorrer.
*               (Caso seja negativo, andar "para trás".)
*
*  $ED Descrição da função
*	  Avança o ponteiro do nó corrente o numero de elementos desejado.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetListaInexistente
*     LST_CondRetFimLista
*	  LST_CondRetInicioLista
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Saída
*	Caso a lista seja válida e o número de elementos que deseja andar
*	esteja dentro do limite da lista, o ponteiro corrente apontará para o 
*	ponteiro desejado.
*	Caso o limite seja ultrapassado, o ponteiro corrente apontará para o
*	fim ou origem da lista ( dependendo da direção que segue).
*	Valem as assertivas estruturais da lista duplamente encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_Avancar( TpLista * pLista, int numElem ) ;

/***********************************************************************
*
	*  $FC Função: LST Retorna número de elementos da lista duplamente encadeada.
*
*  $EP Parâmetros
*     pLista - lista que deseja informação.
*
*  $ED Descrição da função
*	  Retorna o número de elementos de uma lista.
*
*  $FV Valor retornado
*     int - Número de elementos na lista.
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Saída
*	Caso a lista seja válida, o número de elementos é retornado.
*	Valem as assertivas estruturais da lista duplamente encadeada.
*
***********************************************************************/

	 int LST_RetornaNumElementos( TpLista* pLista );

/****************************************************************/

#undef	LISTA_EXT

/********** Fim do módulo de definição: Módulo Lista **********/

#else
#endif
