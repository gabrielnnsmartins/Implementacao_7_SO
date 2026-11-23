#include<stdio.h>
#include<stdlib.h>

#define  n_pagina  256
#define n_frame  256
#define tam_pagina  256


void iniciar_TLB_Page_Table(int *page_table[], int *tlb_frame[], int *tlb_page[], int tam_tlb){

    if (page_table!=NULL){
        for(int i = 0; i<n_pagina;i++){
            page_table[i] = -1;
        }
    }

    if(tlb_frame!= NULL && tlb_page!=NULL){
        for(int i = 0; i<tam_tlb; i++){
            tlb_page[i] = -1;
            tlb_frame = -1;
        }
    }
}

void procurar_endereco_tlb(int endereco_logico, int prox_frame, int tlb_hit, int tam_tlb, int *tbl_page[], int *tlb_frame[]){

    int page_number = (endereco_logico >> 8) & 0xFF;
    int offset = endereco_logico & 0xFF;

    int hit = 0;

    for(int i = 0; i<tam_tlb; i++){
        if (tlb)
    }
}