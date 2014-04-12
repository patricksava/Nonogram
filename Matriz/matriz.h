
typedef enum {
	
	
    MAT_CondRetFaltouMemoria = 0, 
	
	MAT_CondRetOK = 1,	
    
	MAT_CondRetFalhou = 2,
	
	
	MAT_CondRetMatrizInexistente = 3,  
	
	MAT_CondRetValorNaoInserido = 4,
	
	MAT_CondRetValorInalterado	= 5,
	
	MAT_CondRetMatrizIntacta = 6, 
	
	MAT_CondRetMatrizCheia = 7,
	
	MAT_CondRetPosicaoInvalida = 8,
	
	MAT_CondRetElementoInexistente = 9
	
	
}MAT_tpCondRet;


typedef struct tpMatriz TpMatriz;


// CRIAR MATRIZ
MAT_tpCondRet MAT_CriarMatriz( TpMatriz* matriz, int linhas, int colunas );


// INSERIR NOVO ELEMENTO NA MATRIZ
MAT_tpCondRet MAT_InserirNovoElemento(TpMatriz* matriz, void* novo);


// MAPEAR AS POSICOES (I E J) DO ELEMENTO DADO
MAT_tpCondRet MAT_ObterPosicaoElemento( TpMatriz* matriz, void* elem_dado, int* num_linha, int* num_coluna );


// MAPEAR O ELEMENTO A PARTIR DE SUAS POSICOES I E J DADAS
MAT_tpCondRet MAT_ObterElemento( TpMatriz* matriz, void* elem_procurado, int linha, int coluna);


// SUBSTITUIR (ALTERAR) VALOR
MAT_tpCondRet MAT_AlterarValor( TpMatriz* matriz, void* elem_subst, int linha, int coluna);

// DESTRUIR MATRIZ
MAT_tpCondRet MAT_DestruirMatriz( TpMatriz* matriz);

//ESVAZIAR MATRIZ
MAT_tpCondRet MAT_EsvaziarMatriz( TpMatriz* matriz );


