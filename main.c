#include<stdio.h>
#include<stdlib.h>

#define  n_pagina  256
#define n_frame  256
#define tam_pagina  256


void iniciar_TLB_Page_Table(int *page_table, int *tlb_frame, int *tlb_page, int tam_tlb){

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

int procurar_endereco_tlb(int endereco_logico, int page_number, int offset, int tam_tlb, int *tlb_page, int *tlb_frame){

    int hit = 0;

    for(int i = 0; i<tam_tlb; i++){
        if (tlb_page[i] == page_number){
            int frame_number = tlb_frame[i];
            hit += 1;
            return frame_number;
        }
    }

    if(hit == 0){
        return -1;
    }
}

int procurar_tabela(int page_number, int *page_table, signed char *ram, int free_frame, FILE *backing_store){


    int frame_number = page_table[page_number];

    if(frame_number == -1){

        if(free_frame >= frame_number){
            return -2;
        }

        frame_number = free_frame;

        free_frame += 1;

        size_t bites_lidos =  fread(ram[frame_number], sizeof(signed char), tam_pagina, backing_store);

        if (bites_lidos != tam_pagina){
            return -2;
        }

        page_table[page_number] = frame_number;
        return frame_number;
    }
}

int end_fisico(int  frame_number, int offset){
    int endereco_fisico = (frame_number * tam_pagina) + offset;
    return endereco_fisico;
}

void escrever_resultado(int endereco_virtal, int endereco_fisico, signed char valor, FILE *correto, int tbl_hit){
    if(correto!=NULL){
        for(int i = 0; i<n_pagina; i++){
            fprintf(correto,"Virtual address: %d TLB: %d Value: %hhd\n", endereco_virtal, endereco_fisico, value);
        }


    }
}

signed char valor_memoria(signed char *ram, int frame_number, int offset){
    if (ram != NULL){
        signed char valor = ram[frame_number][offset];
        return valor;
    }
}

int main(){

    int page_table[n_pagina];
    signed char ram[n_frame][tam_pagina];
    
    int prox_frame_livre = 0;
    int tlb_hit = 0;
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
        fclose(backing_store);
        return 0;
    }else{

        FILE *correto = fopen("correct.txt", "w");

        if(correto == NULL){
        fclose(backing_store);
        fclose(enderecos);
        return 0;
        }

        int leitor = 1;
        while(leitor == 1){
            int endereco_logico;
            leitor == fscanf(enderecos, &endereco_logico);
            if(leitor == 1){

            int page_number = (endereco_logico >> 8) & 0xFF;
            int offset = endereco_logico & 0xFF;

            int acerto = procurar_endereco_tlb(endereco_logico, page_number, offset, tam_tlb, tlb_page, tlb_frame);

            if (acerto == -1){
                int frame_number = procurar_tabela(endereco_logico, page_number, page_table, ram, &prox_frame_livre, backing_store);
                if (frame_number == -2){
                    break;
                }else{
                    int endereco_fisico = end_fisico(frame_number, offset);
                    signed char valor = valor_memoria(ram, frame_number, offset);

                    escrever_resultado(endereco_logico, endereco_fisico, valor, correto);
                }
            }else{
                tlb_hit += 1;

                int endereco_fisico = end_fisico(acerto, offset);
                signed char valor = valor_memoria(ram, acerto, offset);

                escrever_resultado(endereco_logico, endereco_fisico, valor, correto);
            }
            }
        }
        fclose(correto);
    }


    fclose(backing_store);
    fclose(enderecos);


    return 0;
}