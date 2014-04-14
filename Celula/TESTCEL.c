
/***************************************************************************
 *  $MCI Módulo de implementação: TCEL Teste Estrutura Celula
 *
 *  Arquivo gerado:              TESTCEL.C
 *  Letras identificadoras:      TCEL
 *
 *  Projeto: INF 1301 
 *  Gestor:  LES/DI/PUC-Rio
 *  Autor:   lm
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data     Observações
 *	   2       lm   12/abr/2014  Término do desenvolvimento
 *     1       lm   11/abr/2014  início desenvolvimento
 *
 ***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>

#include    "TST_Espc.h"
#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "CELULA.H"



/* Tabela dos nomes dos comandos de teste específicos */

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


/***** Protótipo da função encapulada no módulo *****/

static int ValidarInxCelula( int inxcelula , int Modo );

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
 *
 *  $FC Função: TCEL & Testar valor
 *
 *  $ED Descrição da função
 *     Podem ser criadas até 10 estruturas, identificadas pelos índices 0 a 10
 *
 *     Comandos disponíveis:
 *
 *     =resetteste
 *           - anula o vetor de valores. Provoca vazamento de memória
 *    
 *		=criarcelula						inxcelula
 *		=destruircelula						inxcelula
 *		=alteraratual                       inxcelula
 *		=obtervalesperado					inxcelula string  CondretPonteiro
 *		=obtervalatual						inxcelula string  CondretPonteiro
 *								
 ***********************************************************************/




TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
{
	
	int inxcelula  = -1,
	    numLidos   = -1, 
	    CondRetEsp = -1;
	
	CEL_tpCondRet CondRet;
	
	int i ;
	
	int numElem = -1,
	    marc_esp = -1,
		marc_atual = -1;
	
	
	/* Efetuar reset de teste de valor */
	
	if ( strcmp( ComandoTeste , RESET_CEL_CMD ) == 0 )
	{
		
		for( i = 0 ; i < DIM_VT_CELULA ; i++ )
		{
			vetcelulas[ i ] = NULL ;
		} /* for */
		
		return TST_CondRetOK ;
		
	} /* fim ativa: Efetuar reset de teste de valor */
	
	
	
	 /* Testar CriaCelula */
	
	else if ( strcmp( ComandoTeste , CRIAR_CELULA_CMD ) == 0 )
	{
		
		numLidos = LER_LerParametros( "iii" ,
									 &inxcelula, &marc_esp, &marc_atual) ;
		
		
		if ( ( numLidos != 3 ) 
			|| ( ! ValidarInxCelula( inxcelula , VAZIO )))
		{
			return TST_CondRetParm ;
		} /* if */
		
		
		vetcelulas[inxcelula] = CEL_CriaCelula(marc_esp, marc_atual); 
		
		
		return TST_CompararPonteiroNulo( 1 , vetcelulas[ inxcelula ] ,
										"Erro em ponteiro de nova celula."  ) ;
	} /* fim ativa: Testar CriaCelula*/
	
	
	/* Testar MarcacaoEsperada */
	
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
							   CEL_MarcacaoEsperada( vetcelulas[ inxcelula ]) ,
							   "Condicao de retorno errada ao obter marcacao esperada" ) ;
		
	} /* fim ativa: MarcacaoEsperada*/
	
	
	/* Testar DestruirCelula */
	
	else if ( strcmp( ComandoTeste , DESTRUIR_CELULA_CMD ) == 0 )
	{
		
		numLidos = LER_LerParametros( "ii" ,
									 &inxcelula, &CondRetEsp ) ;
		
		if ( ( numLidos != 2 )
			|| ( ! ValidarInxCelula( inxcelula , NAO_VAZIO )) )
		{
			return TST_CondRetParm ;
		} /* if */
		
		
		CondRet = CEL_DestruirCelula ( vetcelulas[ inxcelula ] ) ;
		
		if (CondRet != CondRetEsp)
		{
            return TST_CompararInt( CondRetEsp , CondRet ,
								   "Condicao de retorno errada ao excluir."                   ) ;
		} /* if */
		
		vetcelulas[ inxcelula ] = NULL ;
		
		return TST_CondRetOK ; 
		
	} /* fim ativa: Testar DestruirCelula */
	
	
	
	
	/* Testar MarcacaoAtual */
	
	else if ( strcmp( ComandoTeste , OBTERATUAL_CELULA_CMD ) == 0 )
	{
		
		numLidos = LER_LerParametros( "ii" ,
									 &inxcelula, &numElem ) ;
		
		if ( ( numLidos != 2 )
			|| ( ! ValidarInxCelula( inxcelula , NAO_VAZIO )))
		{
			return TST_CondRetParm ;
		} /* if */
		
		
		return TST_CompararInt( numElem ,
							   CEL_MarcacaoAtual( vetcelulas[ inxcelula ]) ,
							   "Condicao de retorno errada ao obter valor marcado" ) ;
		
	} /* fim ativa: Testar MarcacaoAtual */
	
	
	/* Testar AlteraMarcacao */
	else if ( strcmp( ComandoTeste , ALTERAR_CELULA_CMD ) == 0 )
	{
		
		numLidos = LER_LerParametros( "ii" ,
									 &inxcelula, &CondRetEsp ) ;
		
		if ( ( numLidos != 2 )
			|| ( ! ValidarInxCelula( inxcelula , NAO_VAZIO )))
		{
			return TST_CondRetParm ;
		} /* if */
		
		CondRet = CEL_AlteraMarcacao( vetcelulas[ inxcelula ] ) ;
		
		if ( CondRet != CEL_CondRetOK )
		{
			return TST_CompararInt( CondRetEsp , CondRet ,
								   "Condicao de retorno errada ao alterar valor atual."); 
		} /* if */
		
		return TST_CondRetOK ;
	} /* fim ativa: Testar AlteraMarcacao */

	return TST_CondRetNaoConhec ;

}	


/*****  Código das funções encapsuladas no módulo  *****/



/***********************************************************************
 
 
 /***********************************************************************
 *
 *  $FC Função: TVAL -Validar indice da celula
 *
 ***********************************************************************/




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
	
} 	/* Fim função: TCEL -Validar indice de CELULA */

/********** Fim do módulo de implementação: TCEL Teste de Estrutura do tipo celula **********/



