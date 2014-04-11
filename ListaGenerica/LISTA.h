#if ! defined( LISTA_ )
#define LISTA_

/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Lista Genérica
*
*  Arquivo gerado:              ListaGenerica.H
*  Letras identificadoras:      LST
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mbv - Maria Beatriz Vaz
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
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
***************************************************************************/
 
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

		 LST_CondRetCriouLista = 2 ,
               /* Criou uma nova lista.  */

		 LST_CondRetInfoNaoEncontrada = 3 ,
               /* Informação recebida não encontrada na lista.  */

		LST_CondRetListaVazia = 4 ,
			   /* Lista não possui elementos. */

		LST_CondRetFimLista = 5 ,
			   /* Próximo ponteiro é NULL. */

         LST_CondRetFaltouMemoria = 6 ,
               /* Faltou memória ao alocar dados */

		LST_CondRetNoNaoPossuiInfo = 7 ,

   } LST_tpCondRet ;
/***********************************************************************
* 
*   $ED Descrição
*	Especifica a estrutura de dados utilizada no módulo.
*
***********************************************************************/

   typedef struct tpNoLista TpNoLista;
   
   typedef struct tpLista TpLista;

/***********************************************************************
*
*  $FC Função: LST Criar lista genérica duplamente encadeada.
*
*  $ED Descrição da função
*     Cria um nó para uma nova lista.
*
*  $EP Parâmetros
*     pLista - Lista que deseja criar.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetFaltouMemoria
*
***********************************************************************/

   TpLista * LST_CriarLista( TpLista * pLista ) ;


/***********************************************************************
*
*  $FC Função: LST Destruir lista duplamente encadeada.
*
*  $EP Parâmetros
*     pLista - lista que deseja destruir.
*
*  $ED Descrição da função
*     Libera todos os ponteiros da lista, anulando-a.
*     Faz nada caso a lista não exista.
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetListaInexistente
*
***********************************************************************/

   LST_tpCondRet LST_DestruirLista( TpLista * pLista ) ;

/***********************************************************************
*
*  $FC Função: LST Adicionar novo nó no inicio da lista duplamente encadeada.
*
*  $ED Descrição da função
*     Insere um elemento no ínicio da lista e caso não exista, cria lista.
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
***********************************************************************/

   LST_tpCondRet LST_InserirNovoNoInicio( TpLista * pLista , void * informacao ) ;


/***********************************************************************
*
*  $FC Função: LST Adicionar novo nó no fim da lista duplamente encadeada.
*
*  $ED Descrição da função
*     Insere elemento no final da lista, e caso não exista, cria lista.
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
***********************************************************************/

   LST_tpCondRet LST_InserirNoApos( TpLista * pLista , void * informacao ) ;

/***********************************************************************
*
*  $FC Função: LST Liberar nó corrente.
*
*  $EP Parâmetros
*     pLista - lista que deseja liberar o nó.
*
*  $ED Descrição da função
*     Libera o ponteiro para o nó corrente.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetListaInexistente
*	  LST_CondRetListaVazia
*
***********************************************************************/

   LST_tpCondRet LST_LiberarNoCorrente( TpLista * Lista ) ;
   
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
*     LST_CondRetOK
*     LST_CondRetNoNaoPossuiInfo
*	  LST_CondRetListaInexistente
*	  LST_CondRetListaVazia
*
***********************************************************************/

   LST_tpCondRet LST_ObterValor( TpLista * pLista , void * informacao ) ;

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
***********************************************************************/

   LST_tpCondRet LST_AlterarValor( TpLista * pLista , void * informacao ) ;

/***********************************************************************
*
	*  $FC Função: LST Busca informação.
*
*  $EP Parâmetros
*     pLista - lista que deseja realizar a busca e a 
*	  informacao - informação que deseja buscar.
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
***********************************************************************/

   LST_tpCondRet LST_Busca( TpLista * pLista , void * informacao ) ;

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
*	  Avança o ponteiro do nó corrente para o próximo nó.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetListaInexistente
*     LST_CondRetFimLista
*
***********************************************************************/

   LST_tpCondRet LST_Avancar( TpLista * pLista, int numElem ) ;

/****************************************************************/

#undef	LISTA_EXT

/********** Fim do módulo de definição: Módulo Lista **********/

#else
#endif
