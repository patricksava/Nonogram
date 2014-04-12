/***************************************************************************
*  $MCI Módulo de implementação: Módulo Valor
*
*  Arquivo gerado:              VALOR.c
*  Letras identificadoras:      VA
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mbv- Maria Beatriz Vaz
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	   2.00   mbv   11/abr/2014 Término do desenvolvimento
*      1.00   mbv   10/abr/2014 Início do desenvolvimento
*
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "VALOR.H"

/***********************************************************************
*
*  $TC Tipo de dados: VAL Tipo Valor
*
*
*  $ED Descrição do tipo
*	
*	Estrutura que possui um valor inteiro referente a
*	quantidade de ocorrências da matriz pintada e outro
*	inteiro que indica a quantidade de ocorrências marcadas
*	no jogo.
*
***********************************************************************/


struct tpvalor 
{
	
	int QntdMarcados;
		/* Inteiro que representa o número de quadrados marcados. */

	int QntdPintados;
		/* Inteiro que representa o número de quadrados já pintados. */
};


/***************************************************************************
*
*  Função: VAL Criar tipo de dados.
*  ****/
TpValor * VAL_CriarValor ( void )
{
	TpValor * Valor;

	Valor = ( TpValor * ) malloc ( sizeof ( TpValor ));

	if ( Valor == NULL )
	{
		return NULL;
	} /* if */

	/* Zerar os campos da estrutura. */
	Valor->QntdMarcados = NULL;
	Valor->QntdPintados = NULL;

	return Valor;
}
 /* Fim função: VAL Criar tipo de dados.*/

/***************************************************************************

*  Função: VAL Alterar a quantidade de quadrados marcados.
***/

VAL_tpCondRet VAL_AlterarQntdMarcados ( TpValor * Valor , int quantidade )
{
	
	if ( Valor == NULL )
	{
		return VAL_CondRetValorInexistente;
	} /* if */
	
	Valor->QntdMarcados = quantidade ;
	
	return VAL_CondRetOk;

}
 /* Fim função: VAL Altera quantidade de quadrados marcados.*/

/***************************************************************************

*  Função: VAL Incramenta a quantidade de pintados.
***/

VAL_tpCondRet VAL_IncrementarQntdPintados ( TpValor * Valor )
{
		
	if ( Valor == NULL )
	{
		return VAL_CondRetValorInexistente;
	} /* if */
	
	Valor->QntdPintados ++;
	return VAL_CondRetOk;

}

 /* Fim função: VAL Incrementa quantidade de marcados*/

/***************************************************************************

*  Função: VAL Decrementa quantidade de pintados. 
***/
VAL_tpCondRet VAL_DecrementarQntdPintados ( TpValor * Valor )
{
		
	if ( Valor == NULL )
	{
		return VAL_CondRetValorInexistente;
	} /* if */
	
	Valor->QntdPintados --;
	return VAL_CondRetOk;

}

 /* Fim função: VAL Decrementa quantidade de pintados.*/

/***************************************************************************

* Função: VAL Obtêm a quantidade de marcados.
***/
int VAL_ObterMarcados ( TpValor * Valor )
{
			
	if ( Valor == NULL )
	{
		printf("valor nao existe");
		return 0;
	} /* if */
	
	return Valor->QntdMarcados;

}

 /* Fim função: VAL Obtem a quantidade de marcados.*/

/***************************************************************************

* Função: VAL obtem quantidade de pintados.
***/
int VAL_ObterPintados ( TpValor * Valor )
{
			
	if ( Valor == NULL )
	{
		printf("Valor não existe");
		return 0;
	} /* if */
	
	return Valor->QntdPintados;

}

 /* Fim função: VAL obtem quantidade de pintados. */

/***************************************************************************

*  Função: VAL Resseta tipo de dados.
***/
VAL_tpCondRet VAL_RessetarValor ( TpValor * Valor )
{
			
	if ( Valor == NULL )
	{
		return VAL_CondRetValorInexistente;
	} /* if */
	
	Valor->QntdMarcados=NULL;
	Valor->QntdPintados=NULL;

	return VAL_CondRetOk;
}


 /* Fim função: VAL Resseta tipo de dados. */

/***************************************************************************

*  Função: VAL Destrói tipo de dados.
***/

VAL_tpCondRet VAL_DestruirValor ( TpValor * Valor )
{
			
	if ( Valor == NULL )
	{
		return VAL_CondRetValorInexistente;
	} /* if */
	
	free ( Valor );
	return VAL_CondRetOk;
}

 /* Fim função: VAL destrói tipo de dados. */

/***************************************************************************

/********** Fim do módulo de implementação: Módulo VALOR **********/



