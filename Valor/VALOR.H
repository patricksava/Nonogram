#include <stdio.h>


typedef struct tpvalor TpValor;

VAL_tpCondRet VAL_CriarValor ( TpValor * Valor );

VAL_tpCondRet VAL_AlterarQntdMarcados ( TpValor * Valor , int quantidade );

VAL_tpCondRet VAL_IncrementarQntdPintados ( TpValor * Valor );

VAL_tpCondRet VAL_DecrementarQntdPintados ( TpValor * Valor );

VAL_tpCondRet VAL_ObterMarcados ( TpValor * Valor , int * Marcados );

VAL_tpCondRet VAL_ObterPintados ( TpValor * Valor , int * Pintados );

VAL_tpCondRet VAL_DestruirValor ( TpValor * Valor );