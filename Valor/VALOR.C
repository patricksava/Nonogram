/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo Valor
*
*  Arquivo gerado:              VALOR.c
*  Letras identificadoras:      VAL
*
*  Projeto: Disciplinas INF 1301
*  Gestor:  DI/PUC-Rio
*  Autores: mbv- Maria Beatriz Vaz
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*	   3.00   mbv   14/abr/2014 Revis�o do c�digo e dos coment�rios
*	   2.00   mbv   11/abr/2014 T�rmino do desenvolvimento
*      1.00   mbv   10/abr/2014 In�cio do desenvolvimento
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
*  $ED Descri��o do tipo
*	
*	Estrutura que possui um valor inteiro referente a
*	quantidade de ocorr�ncias da matriz pintada e outro
*	inteiro que indica a quantidade de ocorr�ncias marcadas
*	no jogo.
*
***********************************************************************/


struct tpvalor 
{
	
	int QntdMarcados;
		/* Inteiro que representa o n�mero de quadrados marcados. */

	int QntdPintados;
		/* Inteiro que representa o n�mero de quadrados j� pintados. */
};


/***************************************************************************
*
*  Fun��o: VAL Criar tipo de dados.
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
 /* Fim fun��o: VAL Criar tipo de dados.*/

/***************************************************************************

*  Fun��o: VAL Alterar a quantidade de quadrados marcados.
***/

VAL_tpCondRet VAL_AlterarQntdMarcados ( TpValor * Valor , int quantidade )
{
	
	if ( Valor == NULL )
	{
		return VAL_CondRetValorInexistente;
	} /* if */
	
	Valor->QntdMarcados = quantidade ;
	/*alterar a quantidade*/

	return VAL_CondRetOk;

}
 /* Fim fun��o: VAL Altera quantidade de quadrados marcados.*/

/***************************************************************************

*  Fun��o: VAL Incramenta a quantidade de pintados.
***/

VAL_tpCondRet VAL_IncrementarQntdPintados ( TpValor * Valor )
{
		
	if ( Valor == NULL )
	{
		return VAL_CondRetValorInexistente;
	} /* if */
	
	Valor->QntdPintados ++;
	/* Aumenta em 1 a quantidade de pintados */

	return VAL_CondRetOk;

}

 /* Fim fun��o: VAL Incrementa quantidade de marcados*/

/***************************************************************************

*  Fun��o: VAL Decrementa quantidade de pintados. 
***/
VAL_tpCondRet VAL_DecrementarQntdPintados ( TpValor * Valor )
{
		
	if ( Valor == NULL )
	{
		return VAL_CondRetValorInexistente;
	} /* if */
	
	Valor->QntdPintados --;
	/* Diminui em 1 a quantidade de pintados */

	return VAL_CondRetOk;

}

 /* Fim fun��o: VAL Decrementa quantidade de pintados.*/

/***************************************************************************

* Fun��o: VAL Obt�m a quantidade de marcados.
***/
int VAL_ObterMarcados ( TpValor * Valor )
{
			
	if ( Valor == NULL )
	{
		printf("Valor nao existe");
		return 0;
	} /* if */
	
	return Valor->QntdMarcados;

}

 /* Fim fun��o: VAL Obtem a quantidade de marcados.*/

/***************************************************************************

* Fun��o: VAL obtem quantidade de pintados.
***/
int VAL_ObterPintados ( TpValor * Valor )
{
			
	if ( Valor == NULL )
	{
		printf("Valor n�o existe");
		return 0;
	} /* if */
	
	return Valor->QntdPintados;

}

 /* Fim fun��o: VAL obtem quantidade de pintados. */

/***************************************************************************

*  Fun��o: VAL Resseta tipo de dados.
***/
VAL_tpCondRet VAL_RessetarValor ( TpValor * Valor )
{
			
	if ( Valor == NULL )
	{
		return VAL_CondRetValorInexistente;
	} /* if */
	
	Valor->QntdMarcados=NULL;
	Valor->QntdPintados=NULL;
	/* Zerar os campos da estrutura */

	return VAL_CondRetOk;
}


 /* Fim fun��o: VAL Resseta tipo de dados. */

/***************************************************************************

*  Fun��o: VAL Destr�i tipo de dados.
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

 /* Fim fun��o: VAL destr�i tipo de dados. */

/***************************************************************************

/********** Fim do m�dulo de implementa��o: M�dulo VALOR **********/



