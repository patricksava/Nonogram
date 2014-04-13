
typedef struct celula Celula;

typedef enum {

	CEL_CondRetFaltouMemoria,
	
	CEL_CondRetOK,

	CEL_CondRetMesmaMarcacao,
	
	CEL_CondRetCelulaMorta

}CEL_tpCondRet;


// CRIAR CELULA
CEL_tpCondRet Cel_CriaCelula( Celula* cell, int marcacao_esperada, int marcacao_atual );


// MARCACAO ESPERADA NA CELULA
int Cel_MarcacaoEsperada( Celula* cell);


// MARCACAO ATUAL DA CELULA
int Cel_MarcacaoAtual( Celula* cell);


// MUDA A MARCACAO ATUAL
CEL_tpCondRet Cel_AlteraMarcacao( Celula* cell);

//DESTROI CELULA
CEL_tpCondRet Cel_DestruirCelula( Celula* cell);


