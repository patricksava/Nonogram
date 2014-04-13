
#include    <string.h>
#include    <stdio.h>


#include    "TST_Espc.h"
#include    "Generico.h"
#include    "LerParm.h"

#include    "celula.h"


static const char RESET_CEL_CMD             [ ] = "=resetteste"      ;

static const char CRIAR_CELULA_CMD          [ ] = "=criarcelula"     ;

static const char DESTRUIR_CELULA_CMD       [ ] = "=destruircelula"  ;

static const char OBTERESP_CELULA_CMD		[ ] = "=obtervalesperado";

static const char OBTERATUAL_CELULA_CMD     [ ] = "=obtervalatual"   ;

static const char ALTERAR_CELULA_CMD		[ ] = "=alteraratual"	 ;



#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_CELULA   10

#define DIM_CELULA     100


Celula*  vetcelulas[ DIM_VT_CELULA ] ;


static int ValidarInxCelula( int inxcelula , int Modo );






TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	
	int inxcelula  = -1 , numLidos   = -1 , CondRetEsp = -1  ;
	
	CEL_tpCondRet CondRet;
	
	
	
	
	int i ;
	
	int numElem = -1 ;
	
	int marc_esp = -1;
	
	int marc_atual = -1;
	
	
		
	// RESETAR A CELULA
	
	if ( strcmp( ComandoTeste , RESET_CEL_CMD ) == 0 )
	{
		
		for( i = 0 ; i < DIM_VT_CELULA ; i++ )
		{
			vetcelulas[ i ] = NULL ;
		} 
		
		return TST_CondRetOK ;
		
	} 
	
	
	
	// CRIAR CELULA
	
	else if ( strcmp( ComandoTeste , CRIAR_CELULA_CMD ) == 0 )
	{
		
		numLidos = LER_LerParametros( "iiii" ,
									 &inxcelula, &marc_esp, &marc_atual, &CondRetEsp) ;
		
		
		if ( ( numLidos != 4 ) || ( ! ValidarInxCelula( inxcelula , VAZIO )))
		{
			return TST_CondRetParm ;
		} 
		
		
		CondRet = Cel_CriaCelula( vetcelulas[ inxcelula ], marc_esp, marc_atual ) ;
		
		if ( CondRet != CEL_CondRetOK )
		{
			return TST_CompararInt( CondRetEsp , CondRet ,
								   "Condicao de retorno errada ao incrementar pintados."); 
		} 
		
		
		return TST_CompararPonteiroNulo( 1 , vetcelulas[ inxcelula ] ,
										"Erro em ponteiro de nova lista."  ) ;
		
	} 
	
	
	
	
	//OBTER VALOR ESPERADO
	
	else if ( strcmp( ComandoTeste , OBTERESP_CELULA_CMD ) == 0 )
	{
		
		numLidos = LER_LerParametros( "ii" ,
									 &inxcelula, &numElem ) ;
		
		if ( ( numLidos != 2 )
			|| ( ! ValidarInxCelula( inxcelula , NAO_VAZIO )))
		{
			return TST_CondRetParm ;
		} /* if */
		
		
		return TST_CompararInt( numElem ,
							   Cel_MarcacaoEsperada( vetcelulas[ inxcelula ]) ,
							   "Condicao de retorno errada ao obter valor marcados" ) ;
		
	} 
	
	
	
	// DESTRUIR CELULA
	
	else if ( strcmp( ComandoTeste , DESTRUIR_CELULA_CMD ) == 0 )
	{
		
		numLidos = LER_LerParametros( "ii" ,
									 &inxcelula, &CondRetEsp ) ;
		
		if ( ( numLidos != 2 )
			|| ( ! ValidarInxCelula( inxcelula , NAO_VAZIO )) )
		{
			return TST_CondRetParm ;
		} /* if */
		
		
		CondRet = Cel_DestruirCelula ( vetcelulas[ inxcelula ] ) ;
		
		if (CondRet != CondRetEsp)
		{
            return TST_CompararInt( CondRetEsp , CondRet ,
								   "Condicao de retorno errada ao excluir."                   ) ;
		} /* if */
		
		vetcelulas[ inxcelula ] = NULL ;
		
		return TST_CondRetOK ; 
		
	} 
	
	
	
	
	// OBTER VALOR ATUAL
	
	else if ( strcmp( ComandoTeste , OBTERATUAL_CELULA_CMD ) == 0 )
	{
		
		numLidos = LER_LerParametros( "ii" ,
									 &inxcelula, &numElem ) ;
		
		if ( ( numLidos != 2 )
			|| ( ! ValidarInxCelula( inxcelula , NAO_VAZIO )))
		{
			return TST_CondRetParm ;
		} 
		
		
		return TST_CompararInt( numElem ,
							   Cel_MarcacaoAtual( vetcelulas[ inxcelula ]) ,
							   "Condicao de retorno errada ao obter valor marcados" ) ;
		
	} 
	
	
	
	// ALTERAR CELULA
	else if ( strcmp( ComandoTeste , ALTERAR_CELULA_CMD ) == 0 )
	{
		
		numLidos = LER_LerParametros( "ii" ,
									 &inxcelula, &CondRetEsp ) ;
		
		if ( ( numLidos != 2 )
			|| ( ! ValidarInxCelula( inxcelula , NAO_VAZIO )))
		{
			return TST_CondRetParm ;
		} 
		
		CondRet = Cel_AlteraMarcacao( vetcelulas[ inxcelula ] ) ;
		
		if ( CondRet != CEL_CondRetOK )
		{
			return TST_CompararInt( CondRetEsp , CondRet ,
								   "Condicao de retorno errada ao decrementar pintados."); 
		} 
		
		
		return TST_CondRetOK ;
		
	}
}	

int ValidarInxCelula( int inxcelula , int Modo )
{
	
	if ( ( inxcelula <  0 )
		|| ( inxcelula >= DIM_VT_CELULA ))
	{
		return FALSE ;
	} /* if */
	
	if ( Modo == VAZIO )
	{
		if ( vetcelulas[ inxcelula ] != 0 )
		{
			return FALSE ;
		} /* if */
	} else
	{
		if ( vetcelulas[ inxcelula ] == 0 )
		{
			return FALSE ;
		} /* if */
	} /* if */
	
	return TRUE ;
	
} 	



