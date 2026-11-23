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

void procurar_endereco_tlb(int endereco_logico, int page_number, int , int prox_frame, int tlb_hit, int tam_tlb, int *tbl_page[], int *tlb_frame[]){

    int page_number = (endereco_logico >> 8) & 0xFF;
    int offset = endereco_logico & 0xFF;

    int hit = 0;

    for(int i = 0; i<tam_tlb; i++){
        if (tlb_page[i] == page_number){
            frame_number = tbl_frame[i];
            hit += 1;
            brerak;
        }
    }

    if(hit == 0){

    }

    tbl_hit += hit;




}

void procurar_tabela(int endereco_logico, int *page_table[], signed_char *ram[], int free_frame, FILE *backing_store, int offset, int page_number){


    int frame_number = page_table[page_number];

    if(frame_number == -1){

        if(next_free_frame >= frame_number){
            return;
        }

        frame = free_frame;

        free_frame += 1;

        tam_bites =  fread(ram[frame_number], sizeof(signed char), tam_pagina, backing_store);

        if (tam_bites != tam_pagina){
            return;
        }

        page_table[page_number] = frame_number;
    }
}

int end_fisico(int page_number ,int  frame_number, int offset){
    int endereco_fisico = (frame_number * tam_pagina) + offset;
    return endereco_fisico;
}

signed char valor_memoria(signed char *ram[], int frame_number, int offset){
    if (ram != NULL){
        signed char valor = ram[frame_number][offset];
        return valor;
    }
}

int main(){

    int page_table[n_pagina];
    signed char ram[n_frame][tam_pagina];
    
    int prox_livre_tlb = 0;
    int tlb hit = 0;
    int tam_tlb = 32;
    int tlb_page[32];
    int tlb_frame[32];

    iniciar_TLB_Page_Table(page_table, tlb_frame, tlb_page, tam_tlb);

    FILE *backing_store = fopen("BACKING_STORE.bin", "rb");

    if(backing_store == NULL){
        return 0;
    }

    FILE *enderecos = fopen("Addresses.txt", "r");

    if(enderecos == NULL){
        return 0;
    }else{
        
    }





    return 0;
}