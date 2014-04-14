#if ! defined( LISTA_ )
#define LISTA_

/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo Lista Gen�rica
*
*  Arquivo gerado:              ListaGenerica.H
*  Letras identificadoras:      LST
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mbv - Maria Beatriz Vaz
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*		3.00   mbv   14/abr/2014 Revis�o geral do c�digo e dos coment�rios
*       2.00   mbv   21/mar/2014 Continua�ao do desenvolvimento, reestrutura��o
*       1.00   mbv   19/mar/2014 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     explorar listas duplamente encadeadas.
*	  A lista duplamente encadeada possui um ponteiro para o pr�ximo elemento 
*	  e um ponteiro para o elemento anterior.
*	  Dado um elemento, � poss�vel acessar o pr�ximo e o anterior.
*	  Dado um ponteiro para o �ltimo elemento da lista, � poss�vel
*     percorrer a lista em ordem inversa.
*	  Este m�dulo permite a cria��o de mais de uma lista.
*     Ao iniciar a execu��o do programa n�o existe listas.
*
*  $AE Assertivas Estruturais 
*  Lista cont�m: 
*    - Cabe�a da lista
*    - N� da lista
*   Seja pLista um ponteiro para a cabe�a da Lista e pElem um ponteiro para o n� da lista.
*   Se pElem -> pProx != NULL, ent�o pElem -> pProx -> pAnt == pEle
*   Se pElem -> pAnt != NULL, ent�o pElem -> pAnt -> pProx == pElem
*   Se pLista -> numElementos == 0, ent�o pLista->pNoCorrente == NULL e pLista -> pOrigemLista == NULL e pLista -> pFimLista == NULL
*   Se pLista -> numElementos > 0, ent�o pLista->pNoCorrente != NULL
*   Se pLista -> numElementos == 1,ent�o pLista ->pNoCorrente == pLista-> pNoOrigem e pLista -> pNoCorrente == pLista -> pNoFim 
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
               /* Lista n�o existe. */

		 LST_CondRetInfoNaoEncontrada = 2 ,
               /* Informa��o recebida n�o encontrada na lista.  */

		LST_CondRetListaVazia = 3 ,
			   /* Lista n�o possui elementos. */

		LST_CondRetFimLista = 4 ,
			   /* Pr�ximo ponteiro � NULL. */

         LST_CondRetFaltouMemoria = 5 ,
               /* Faltou mem�ria ao alocar dados */

		LST_CondRetNoNaoPossuiInfo = 6 ,

   } LST_tpCondRet ;
/***********************************************************************
* 
*   $ED Descri��o
*	Especifica a estrutura de dados utilizada no m�dulo.
*
***********************************************************************/
   
   typedef struct tpLista TpLista;

/***********************************************************************
*
*  $FC Fun��o: LST Criar lista gen�rica duplamente encadeada.
*
*  $ED Descri��o da fun��o
*     Cria uma nova lista, zerando todos os seus campos da cabe�a.
*
*  $FV Valor retornado
*     TpLista * pLista - ponteiro para a nova lista
*
*  $AE Assertivas de Entrada
*	O ponteiro para receber a Lista deve ser NULL
*
*  $AS Assertivas de Sa�da
*	Caso tenha espa�o na mem�ria a lista ser� criada e
*	pLista->pNoCorrente = pLista -> pOrigemLista = pLista -> pFimLista = NULL
*   Valem as assertivas estruturais da Lista Duplamente Encadeada
*
***********************************************************************/

   TpLista * LST_CriarLista( void ) ;

/***********************************************************************
*
*  $FC Fun��o: LST Esvaziar lista duplamente encadeada.
*
*  $EP Par�metros
*     pLista - lista que deseja esvaziar.
*	  ExcluirValor - Fun��o respons�vel pela exclus�o do elemento.
*
*  $ED Descri��o da fun��o
*     Libera todos os ponteiros da lista, ressatando a lista como nova.
*     Faz nada caso a lista n�o exista.
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Sa�da
*	Caso a lista seja v�lida, 
*	pLista->pNoCorrente = pLista -> pOrigemLista = pLista -> pFimLista = NULL
*
*
***********************************************************************/

   void LST_EsvaziarLista( TpLista * pLista, void ( * ExcluirValor ) ( void * pDado) ) ;

/***********************************************************************
*
*  $FC Fun��o: LST Destruir lista duplamente encadeada.
*
*  $EP Par�metros
*     pLista - lista que deseja destruir.
*	  ExcluirValor - Fun��o respons�vel pela exclus�o do elemento.
*
*  $ED Descri��o da fun��o
*     Libera todos os ponteiros da lista, anulando-a.
*     Faz nada caso a lista n�o exista.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetListaInexistente
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*   A fun��o ExcluirValor deve ser respons�vel pela exclus�o do Valor do n�.
*
*  $AS Assertivas de Sa�da
*	Caso a lista seja v�lida, o espa�o alocado na mem�ria ser� liberado.
*
*
***********************************************************************/

   LST_tpCondRet LST_DestruirLista( TpLista * pLista, void ( * ExcluirValor) ( void * pDado) ) ;

/***********************************************************************
*
*  $FC Fun��o: LST Adicionar novo n� no inicio da lista duplamente encadeada.
*
*  $ED Descri��o da fun��o
*     Insere um elemento no �nicio da lista .
*
*  $EP Par�metros
*     pLista - lista que deseja realizar a busca e a 
*	  informacao - informa��o que deseja inserir.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetFaltouMemoria
*	  LST_CondRetListaInexistente
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Sa�da
*	Caso a lista seja v�lida, o n� foi inserido e 
*	pLista->pNoCorrente = pLista -> pOrigemLista = NovoNo
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_InserirNovoNoInicio( TpLista * pLista , void * informacao ) ;


/***********************************************************************
*
*  $FC Fun��o: LST Adicionar novo n� no fim da lista duplamente encadeada.
*
*  $ED Descri��o da fun��o
*     Insere elemento no final da lista.
*
*  $EP Par�metros
*     pLista - lista que deseja realizar a busca e a 
*	  informacao - informa��o que deseja inserir.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetFaltouMemoria
*	  LST_CondRetListaInexistente
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Sa�da
*	Caso a lista seja v�lida, o n� foi inserido
*	pLista->pNoCorrente = pLista -> pFimLista = NovoNo
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_InserirNovoNoFim( TpLista * pLista , void * informacao ) ;

/***********************************************************************
*
*  $FC Fun��o: LST Inserir novo n� antes do n� corrente.
*
*  $ED Descri��o da fun��o
*     Insere um elemento antes do elemento corrente. N�o cria uma nova lista,
*	  caso essa n�o exista.
*
*  $EP Par�metros
*     pLista - lista que deseja realizar a busca e a 
*	  informacao - informa��o que deseja inserir.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetFaltouMemoria
*	  LST_CondRetCriouLista
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Sa�da
*	Caso a lista seja v�lida, o n� foi inserido e 
*	pLista->pNoCorrente = NovoNo
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_InserirNoAntes( TpLista * pLista , void * informacao ) ;


/***********************************************************************
*
*  $FC Fun��o: LST Inserir novo n� ap�s n� corrente.
*  $ED Descri��o da fun��o
*     Insere elemento no final da lista e, caso essa n�o exista, cria.
*
*  $EP Par�metros
*     pLista - lista que deseja realizar a busca e a 
*	  informacao - informa��o que deseja buscar.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetFaltouMemoria
*	  LST_CondRetListaInexistente
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Sa�da
*	Caso a lista seja v�lida, o n� foi inserido e  
*	pLista->pNoCorrente = NovoNo
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_InserirNoApos( TpLista * pLista , void * informacao ) ;

/***********************************************************************
*
*  $FC Fun��o: LST Liberar n� corrente.
*
*  $EP Par�metros
*     pLista - lista que deseja liberar o n�.
*	  ExcluirValor - Fun��o respons�vel pela exclus�o do elemento.
*
*  $ED Descri��o da fun��o
*     Libera o ponteiro para o n� corrente.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetListaInexistente
*	  LST_CondRetListaVazia
*
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*   O ponteiro corrente aponta para o n� a ser excluido
*
*  $AS Assertivas de Sa�da
*	Caso a lista seja v�lida, o n� foi excluido e o ponteiro corrente aponta
*	para o pr�ximo n� ou NULL caso a lista tenha acado.
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_LiberarNoCorrente( TpLista * Lista, void ( * ExcluirValor) (void * pDado) ) ;
   
/***********************************************************************
*
*  $FC Fun��o: LST obter a informa��o contida no n� corrente
*
*  $EP Par�metros
*     pLista - lista que deseja realizar a busca e a 
*	  informacao - ponteiro para armazenar a informacao.
*
*  $ED Descri��o da fun��o
*	  Obtem o valor que est� dentro da informa��o
*	  que o n� corrente da lista cont�m.
*
*  $FV Valor retornado
*     void * informacao - ponteiro para informa��o retornada
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*	O ponteiro corrente aponta para o n� que se deseja obter as informa��es
*
*  $AS Assertivas de Sa�da
*	Caso a lista seja v�lida, o valor do n� corrente sera retornado
*	Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   void * LST_ObterValor( TpLista * pLista ) ;

/***********************************************************************
*
*  $FC Fun��o: LST alterar a informa��o contida no n� corrente.
*
*  $EP Par�metros
*     pLista - lista que deseja realizar a busca e a 
*	  informacao - informa��o que deseja alterar.
*
*  $ED Descri��o da fun��o
*	  Altera o valor que est� dentro do n� corrente.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetListaInexistente
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*	O ponteiro corrente aponta para o n� que se deseja alterar
*	A informa��o gen�rica deve ser v�lida.
*
*  $AS Assertivas de Sa�da
*	Caso a lista seja v�lida, o valor do n� corrente sera alterado
*	Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_AlterarValor( TpLista * pLista , void * informacao ) ;

/***********************************************************************
*
	*  $FC Fun��o: LST Busca informa��o.
*
*  $EP Par�metros
*     pLista - lista que deseja realizar a busca e a 
*	  informacao - informa��o que deseja buscar.
*     Compara - fun��o respons�vel por comparar 2 elementos
*				retornando 0 caso sejam iguais
*
*  $ED Descri��o da fun��o
*	  Realiza a busca de uma informa��o dentro de uma lista,
*	  apontando o n� corrente para o n� que contem a informa��o, caso ache.
*
*  $FV Valor retornado
*     LST_CondRetOK
*	  LST_CondRetInfoNaoEncontrada
*     LST_CondRetListaInexistente
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*	A fun��o busca deve ser v�lida para o tipo de informa��o do n�
*
*  $AS Assertivas de Sa�da
*	Caso a lista seja v�lida, o valor poder� ser encontrado ou n�o.
*	Se o valor for encontrado, o ponteiro corrente apontar� para ele.
*	Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_Busca( TpLista * pLista , void * informacao , int (Compara)(void *pDado , void * pDado2) ) ;

/***********************************************************************
*
	*  $FC Fun��o: LST Ir para o inicio da lista duplamente encadeada.
*
*  $EP Par�metros
*     pLista - lista que deseja percorrer.
*
*  $ED Descri��o da fun��o
*	  Percorre a lista at� achar seu in�cio, apontando para ele.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetListaInexistente
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Sa�da
*	Caso a lista seja v�lida, pLista -> pNoCorrente == pLista -> pOrigemLista.
*   Ou ponteiro corrente apontar� para NULL caso lista esteja vazia.
*	Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_IrInicio( TpLista * pLista ) ;

/***********************************************************************
*
	*  $FC Fun��o: LST Ir para o fim da lista duplamente encadeada.
*
*  $EP Par�metros
*     pLista - lista que deseja percorrer.
*
*  $ED Descri��o da fun��o
*	  Percorre a lista at� achar seu fim, apontado para ele.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetListaInexistente
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Sa�da
*	Caso a lista seja v�lida, pLista -> pNoCorrente == pLista -> pFimLista.
*   Ou ponteiro corrente apontar� para NULL caso lista esteja vazia.
*	Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_IrFim( TpLista * pLista ) ;

/***********************************************************************
*
	*  $FC Fun��o: LST Ir para o pr�ximo n� na lista duplamente encadeada.
*
*  $EP Par�metros
*     pLista - lista que deseja percorrer.
*     numElem - numero de elementos que deseja percorrer.
*               (Caso seja negativo, andar "para tr�s".)
*
*  $ED Descri��o da fun��o
*	  Avan�a o ponteiro do n� corrente o numero de elementos desejado.
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
*  $AS Assertivas de Sa�da
*	Caso a lista seja v�lida e o n�mero de elementos que deseja andar
*	esteja dentro do limite da lista, o ponteiro corrente apontar� para o 
*	ponteiro desejado.
*	Caso o limite seja ultrapassado, o ponteiro corrente apontar� para o
*	fim ou origem da lista ( dependendo da dire��o que segue).
*	Valem as assertivas estruturais da lista duplamente encadeada.
*
***********************************************************************/

   LST_tpCondRet LST_Avancar( TpLista * pLista, int numElem ) ;

/***********************************************************************
*
	*  $FC Fun��o: LST Retorna n�mero de elementos da lista duplamente encadeada.
*
*  $EP Par�metros
*     pLista - lista que deseja informa��o.
*
*  $ED Descri��o da fun��o
*	  Retorna o n�mero de elementos de uma lista.
*
*  $FV Valor retornado
*     int - N�mero de elementos na lista.
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Sa�da
*	Caso a lista seja v�lida, o n�mero de elementos � retornado.
*	Valem as assertivas estruturais da lista duplamente encadeada.
*
***********************************************************************/

	 int LST_RetornaNumElementos( TpLista* pLista );

/****************************************************************/

#undef	LISTA_EXT

/********** Fim do m�dulo de defini��o: M�dulo Lista **********/

#else
#endif
