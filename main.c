#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int assentos;
    float valorEconomica;
    float valorExecutiva;
} Voo;

typedef struct {
    char nome[15];
    char sobrenome[15];
    char cpf[12];
    char dia[3];
    char mes[3];
    char ano[5];
    char numVoo[5];
    char assento[5];
    char classe[15];
    char valor[10];
    char origem[15];
    char destino[15];
} Passageiro;

Passageiro* abrirVoo(int *var_abrir_voo, Voo *voo) {
    if (*var_abrir_voo == 0) {
        Passageiro *ptr = (Passageiro *) malloc (sizeof(Passageiro));

        FILE *arquivo = fopen("abertura_voo.bin", "wb");

        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo\n");
            exit(1);
        }

        int qntAssentos;
        float valorEcon;
        float valorExe;

        // lendo as informacoes do voo
        
        scanf("%d %f %f", &qntAssentos, &valorEcon, &valorExe);

        voo->assentos = qntAssentos;
        voo->valorEconomica = valorEcon;
        voo->valorExecutiva = valorExe;

        // passando a struct para o arqv binário
        fwrite(voo, sizeof(Voo), 1, arquivo);
        fclose(arquivo);

        (*var_abrir_voo)++;
        
        return ptr;
    } else {
        printf("O voo já está aberto! \n");
        return NULL;
    }
}

Passageiro* realoc_vetor_struct(Passageiro **ptr, int qtd_de_reservas) {
    *ptr = realloc(*ptr, (qtd_de_reservas + 1) * sizeof(Passageiro)); 

    if (*ptr == NULL) {
        printf("Erro ao realocar memória\n");
        exit(1);
    }

    return *ptr;
}

void realizarReserva(int *qtd_de_reservas, Passageiro **ptr, Voo *voo) {

    if(voo->assentos != 0){
        if(*qtd_de_reservas > 0){
            realoc_vetor_struct(ptr, *qtd_de_reservas);
        }

        scanf("%s %s %s %s %s %s %s %s %s %s %s %s", 
            (*ptr)[*qtd_de_reservas].nome,
            (*ptr)[*qtd_de_reservas].sobrenome,
            (*ptr)[*qtd_de_reservas].cpf,
            (*ptr)[*qtd_de_reservas].dia,
            (*ptr)[*qtd_de_reservas].mes,
            (*ptr)[*qtd_de_reservas].ano,
            (*ptr)[*qtd_de_reservas].numVoo,
            (*ptr)[*qtd_de_reservas].assento,
            (*ptr)[*qtd_de_reservas].classe,
            (*ptr)[*qtd_de_reservas].valor,
            (*ptr)[*qtd_de_reservas].origem,
            (*ptr)[*qtd_de_reservas].destino
        );

        (*qtd_de_reservas)++;
        voo->assentos--; 
    } 
    else {
        printf("Nao tem mais assento disponivel\n"); 
        exit(1);
    }

    
}

void consultaReserva(Passageiro **ptr, int qtd_de_reservas) {
    char cpf_consulta[12];
    int encontrado = 0;
    scanf("%s", cpf_consulta);

    for(int i = 0; i<qtd_de_reservas; i++){
        if(strcmp(cpf_consulta, (*ptr)[i].cpf) == 0){
            encontrado = 1;
            printf(
            "%s %s %s %s %s %s %s %s %s %s %s %s", 
             (*ptr)[i].nome,
                (*ptr)[i].sobrenome,
                (*ptr)[i].cpf,
                (*ptr)[i].dia,
                (*ptr)[i].mes,
                (*ptr)[i].ano,
                (*ptr)[i].numVoo,
                (*ptr)[i].assento,
                (*ptr)[i].classe,
                (*ptr)[i].valor,
                (*ptr)[i].origem,
                (*ptr)[i].destino
            );
        } 
    }
    if(encontrado == 0){
        printf("CPF inválido");
    }
}

void modificaReserva() {
    // Implementação necessária
}

void cancelaReserva() {
    // Implementação necessária
}

void fecharDia() {
    //descarregar structs ate o momento no arqv???
}

void fecharVoo() {
    // Idescarregar structs no aqrv
}

int main(void) {
   int var_abrir_voo = 0;
   int qtd_de_reservas = 0;
   Passageiro *ptr = NULL;
   Voo voo;

   while(1){
        char str[3];
        scanf("%s", str);

        switch (str[0] + str[1])
        {
        case 151: 
             ptr = abrirVoo(&var_abrir_voo, &voo);
            break;
        case 164: 
            realizarReserva(&qtd_de_reservas, &ptr, &voo);
            break;
        case 149: 
            consultaReserva(&ptr, qtd_de_reservas);
            break;
        case 159:  
            modificaReserva();
            break;
        case 132: 
            cancelaReserva();
            break;
        case 138: 
            fecharDia();
            break;
        case 156: 
            fecharVoo();
            break;
        default: 
            printf("Comando não identificado.\n--------------------------------------------------\n");
        }
    }
}
