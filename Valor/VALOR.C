#include <stdio.h>
#include <stdlib.h>

#include "VALOR.H"


typedef struct tpvalor TpValor;

struct tpvalor 
{
	
	int QntdMarcados;
		/* Inteiro que representa o número de quadrados marcados. */

	int QntdPintados;
		/* Inteiro que representa o número de quadrados já pintados. */
};

VAL_tpCondRet VAL_CriarValor ( TpValor * Valor )
{
	Valor = ( TpValor * ) malloc ( sizeof (TpValor ));

	if ( Valor == NULL )
	{
		return VAL_CondRetFaltouMemoria;
	} /* if */

	/* Zerar os campos da estrutura. */
	Valor->QntdMarcados = NULL;
	Valor->QntdPintados = NULL;

	return VAL_CondRetOk;
}

VAL_tpCondRet VAL_AlterarQntdMarcados ( TpValor * Valor , int quantidade )
{
	
	if ( Valor == NULL )
	{
		return VAL_CondRetValorInexistente;
	} /* if */
	
	Valor->QntdMarcados = quantidade ;
	return VAL_CondRetOk;

}

VAL_tpCondRet VAL_IncrementarQntdPintados ( TpValor * Valor )
{
		
	if ( Valor == NULL )
	{
		return VAL_CondRetValorInexistente;
	} /* if */
	
	Valor->QntdPintados ++;
	return VAL_CondRetOk;

}

VAL_tpCondRet VAL_DecrementarQntdPintados ( TpValor * Valor )
{
		
	if ( Valor == NULL )
	{
		return VAL_CondRetValorInexistente;
	} /* if */
	
	Valor->QntdPintados --;
	return VAL_CondRetOk;

}

VAL_tpCondRet VAL_ObterMarcados ( TpValor * Valor , int * Marcados )
{
			
	if ( Valor == NULL )
	{
		return VAL_CondRetValorInexistente;
	} /* if */
	
	* Marcados = Valor->QntdMarcados;
	return VAL_CondRetOk;
}


VAL_tpCondRet VAL_ObterPintados ( TpValor * Valor , int * Pintados )
{
			
	if ( Valor == NULL )
	{
		return VAL_CondRetValorInexistente;
	} /* if */
	
	* Pintados = Valor->QntdPintados;
	return VAL_CondRetOk;
}

VAL_tpCondRet VAL_DestruirValor ( TpValor * Valor )
{
			
	if ( Valor == NULL )
	{
		return VAL_CondRetValorInexistente;
	} /* if */
	
	free ( Valor );
	return VAL_CondRetOk;
}





