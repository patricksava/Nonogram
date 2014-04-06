//
// Prefix header for all source files of the 'Modular' target in the 'Modular' project.
//




typedef enum {

   
    MAT_CondRetFaltouMemoria = 0, // FALTOU MEMORIA
   
    MAT_CondRetOK = 1 , // RETORNO OK!
   
    MAT_CondRetFalhou = 2 // RETORNO NAO OK!
   
   
}MAT_tpCondRet;


typedef struct tpMatriz TpMatriz;


// CRIAR MATRIZ
MAT_tpCondRet MAT_CriarMatriz( TpMatriz* matriz, int linhas, int colunas );


// INSERIR NOVO ELEMENTO NA MATRIZ
MAT_tpCondRet MAT_InserirNovoElemento(TpMatriz* matriz, *void informacao);


// OBTER VALOR
MAT_tpCondRet MAT_ObterValor( TpMatriz* matriz, int linha, int coluna,  *void informacao );


// SUBSTITUIR (ALTERAR) VALOR
MAT_tpCondRet MAT_AlterarValor( TpMatriz* matriz, int linha, int coluna, void* informacao );


// DESTRUIR MATRIZ
MAT_tpCondRet MAT_DestruirMatriz( TpMatriz* matriz);
