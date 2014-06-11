/***************************************************************************
 *  $MCI Módulo de implementação: Módulo Celula
 *
 *  Arquivo gerado:              CELULA.C
 *  Letras identificadoras:      CE
 *
 *  Projeto: Disciplinas INF 1301
 *  Gestor:  DI/PUC-Rio
 *  Autores: lm- Leandro Morgado
 *
 *  $HA Histórico de evolução:
 *     Versão  Autor    Data         Observações
 *      2.00   lm   12/abr/2014  Término do desenvolvimento
 *      1.00   lm   11/abr/2014  Início do desenvolvimento
 *
 *************************************************************************/
 
 
#include <stdio.h>
#include <stdlib.h>
 
 
#include "CELULA.H"
 
 
/***********************************************************************
 *
 *  $TC Tipo de dados: CEL Tipo Celula
 *
 *  $ED Descrição do tipo
 * 
 *  Estrutura que possui um valor inteiro referente a
 *  marcação atual da célula da matriz e outro que indica
 *  a marcação esperada.
 *
 ***********************************************************************/
 
 
struct celula {
 
    int atual;
    /* Inteiro que representa a marcação atual*/
     
    int esperado;
    /* Inteiro que representa a marcação esperada*/
};
 
/***************************************************************************
 *
 *  Função: CEL Criar tipo de dados.
 *  ****/
 
Celula* CEL_CriaCelula(int marcacao_esperada, int marcacao_atual )
{
 
 
    Celula* cell = (Celula*)malloc(sizeof(Celula));
                            
    if (cell == NULL) {
     
            return NULL;              
    }/* if */

 
    /*marcacoes atual e esperada só podem ser 1 ou 0*/
    if(marcacao_esperada > 0)
        marcacao_esperada = 1;
 
    if(marcacao_atual > 0)
        marcacao_atual = 1;
 
 
    if(marcacao_esperada < 0)
        marcacao_esperada = 0;
 
    if(marcacao_atual < 0)
        marcacao_atual = 0;
 
 
    /*Preencher campos da estrutura*/
    cell -> esperado = marcacao_esperada;
    cell -> atual = marcacao_atual;
     
 
    return cell;
 
}/* Fim função: CEL Criar tipo de dados.*/
 
/***************************************************************************
  
 *  Função: CEL Retornar a marcação esperada na célula.
 ***/
 
 
int CEL_MarcacaoEsperada( Celula* cell) {
                            
    if( cell == NULL )
        exit (1); /* if */
                            
    return cell -> esperado;                   
                                                                         
} /* Fim função: CEL Retornar a marcação esperada na célula.*/
 
 
/***************************************************************************
  
 *  Função: CEL Retornar a marcação atual na célula.
 ***/
 
int CEL_MarcacaoAtual( Celula* cell) {
                            
    if( cell == NULL ) {
        exit (1);
    } /* if */
         
    return  cell -> atual;
                            
}/* Fim função: CEL Retornar a marcação esperada na célula. */
 
/***************************************************************************
  
 *  Função: CEL altera marcação da célula.
 ***/
 
CEL_tpCondRet CEL_AlteraMarcacao( Celula* cell) {
 
    if( cell == NULL ) {
         
        CEL_CondRetCelulaVazia;
     
    } /* if */                    
 
    if( cell -> atual == 0) {
         
        cell -> atual = 1;
     
    } else 
    {
        cell -> atual = 0;
      
    }/* if */
     
    return  CEL_CondRetOK;                
                            
} /* Fim função: CEL altera marcação da célula*/
 
/***************************************************************************
  
  
 *  Função: CEL Destrói tipo de dados.
 ***/
     
CEL_tpCondRet CEL_DestruirCelula( Celula* cell ) {
                            
    if( cell == NULL){
        return CEL_CondRetCelulaVazia;
	}
                 
    free(cell);
	                     
    return CEL_CondRetOK;
                            
} /* Fim função: CEL destrói tipo de dados. */
 
/***************************************************************************
  
 /********** Fim do módulo de implementação: Módulo CELULA **********/ 