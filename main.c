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
    char cpf[15];
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

void fecharVoo(FILE **arquivo, Passageiro **ptr, int qtd_de_reservas); //protótipo da função fecharVoo

Passageiro* abrirVoo(FILE **arquivo, int *var_abrir_voo, Voo *voo) {
    if (*var_abrir_voo == 0) {
        Passageiro *ptr = (Passageiro *) malloc (sizeof(Passageiro));

        *arquivo = fopen("abertura_voo.bin", "wb");
        if (*arquivo == NULL) {
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

void realizarReserva(int *qtd_de_reservas, Passageiro **ptr, Voo *voo, FILE **arquivo) {
    int reservas = *qtd_de_reservas;

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
        printf("Voo Fechado!\n");
        fecharVoo(arquivo, ptr, reservas);  // quantidade de assentos = 0, fechamento automatico
    }
}

void consultaReserva(Passageiro **ptr, int qtd_de_reservas) {
    char cpf_consulta[15];
    int encontrado = 0;
    scanf("%s", cpf_consulta);

    for(int i = 0; i<qtd_de_reservas; i++){
        if(strcmp(cpf_consulta, (*ptr)[i].cpf) == 0){
            encontrado = 1;
            printf(
            "%s %s\n%s/%s/%s\nVoo: %s\nAssento: %s\nClasse: %s\nTrecho: %s %s\nValor: %s\n",
             (*ptr)[i].nome,
                (*ptr)[i].sobrenome,
                (*ptr)[i].dia,
                (*ptr)[i].mes,
                (*ptr)[i].ano,
                (*ptr)[i].numVoo,
                (*ptr)[i].assento,
                (*ptr)[i].classe,
                (*ptr)[i].origem,
                (*ptr)[i].destino,
                (*ptr)[i].valor
            );
        }
    }
    if(encontrado == 0){
        printf("CPF inválido");
    }
}

void modificaReserva() {
   
}

void cancelaReserva() {
    // Implementação necessária
}

void fecharDia(FILE **arquivo, Passageiro **ptr, int qtd_de_reservas, Voo *voo) {
    int auxEcon = 0;
    int auxExec = 0;
    for(int i = 0; i< qtd_de_reservas; i++){
        if(strcmp((*ptr)[i].classe, "economica") == 0){
            auxEcon += 1;
        } else {
            auxExec += 1;
        }
    }
    float total = (auxEcon * voo->valorEconomica) + (auxExec * voo->valorExecutiva);

    printf("--------------------------------------------------\n");
    printf("Fechamento do dia:\n");
    printf("Quantidade de reservas: %d\nPosição: %0.2f\n", qtd_de_reservas, total);
    printf("--------------------------------------------------\n");

    fwrite(*ptr, sizeof(Passageiro) ,qtd_de_reservas, *arquivo);
    fclose(*arquivo);
    exit(1); //sai do programa no fim do dia
   
}

void recuperando_dados_arqv(FILE **arquivo, Passageiro **ptr, int *qtd_de_reservas){
    *arquivo = fopen("abertura_voo.bin", "rb");
    
    
    fseek(*arquivo, 0, SEEK_END);
    long fileSize = ftell(*arquivo);
    rewind(*arquivo);

   
    *qtd_de_reservas = fileSize / sizeof(Passageiro); //obtendo num de reservas

    *ptr = (Passageiro*)malloc((*qtd_de_reservas) * sizeof(Passageiro)); //aloc as structs

    // lendo os dados do arquivo
    fread(*ptr, sizeof(Passageiro), *qtd_de_reservas, *arquivo);
    fclose(*arquivo);
}

void fecharVoo(FILE **arquivo, Passageiro **ptr, int qtd_de_reservas) {

   printf("--------------------------------------------------\n");
   printf("Voo fechado!\n\n");
   
    for(int i = 0; i<qtd_de_reservas; i++){
        printf(
        "%s\n%s %s\n%s\n\n",
            (*ptr)[i].cpf,
            (*ptr)[i].nome,
            (*ptr)[i].sobrenome,
            (*ptr)[i].assento
        );
    }
    printf("--------------------------------------------------\n");
   
    //enviando os dados para o arquivo
    *arquivo = fopen("abertura_voo.bin", "wb");
    fwrite(*ptr, sizeof(Passageiro) , qtd_de_reservas, *arquivo);
    fclose(*arquivo);
}

int main(void) {
   int var_abrir_voo = 0;
   int qtd_de_reservas = 0;
   FILE *arquivo = NULL;
   Passageiro *ptr = NULL;
   Voo voo;

   
    recuperando_dados_arqv(&arquivo, &ptr, &qtd_de_reservas);
   
 
   while(1){
        char str[3];
        scanf("%s", str);

        switch (str[0] + str[1])
        {
        case 151:
             ptr = abrirVoo(&arquivo, &var_abrir_voo, &voo);
            break;
        case 164:
            realizarReserva(&qtd_de_reservas, &ptr, &voo, &arquivo);
            break;
        case 149:
            consultaReserva(&ptr, qtd_de_reservas);
            break;
        case 159:  
            modificaReserva(&ptr);
            break;
        case 132:
            cancelaReserva();
            break;
        case 138:
            fecharDia(&arquivo, &ptr, qtd_de_reservas, &voo);
            break;
        case 156:
            fecharVoo(&arquivo, &ptr, qtd_de_reservas);
            break;
        default:
            printf("Comando não identificado.\n--------------------------------------------------\n");
        }
    }
}