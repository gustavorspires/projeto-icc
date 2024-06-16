/* Autoria:
    Gabriella Almeida - 15528121
    nome de vcs
    nome de vcs
*/
/* Objetivo:
    Este programa gerencia as informações de um voo, armazenando os dados gerais do voo e de cada passageiro.
    O sistema permite que o usuário abra um voo, possibilitando a efetuação de reservas e enquanto o voo estiver
    aberto é possível consultar informações sobre as reservas, modificá-las e cancelá-las. Além disso, ao fim de
    cada dia o usuário pode registrar as informações obtidas no arquivo, e recuperá-las no dia seguinte.
    O fechamento do voo é expresso pelo comando "FV", onde o usuário além de encerrar as reservas, receberá
    um relatório acerca das informações de cada passageiro e o valor arrecadado por esse voo.
    O sistema utiliza arquivos binários para armazenar as informações dos voos e dos passageiros, garantindo
    que os dados sejam preservados entre as execuções do programa.
*/


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

void fecharVoo(FILE **arquivo, Passageiro **ptr, int qtd_de_reservas, Voo *voo); // Protótipo da função fecharVoo

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
       
    } 

    return NULL;
}

Passageiro* realoc_vetor_struct(Passageiro **ptr, int qtd_de_reservas) {
    *ptr = realloc(*ptr, (qtd_de_reservas + 1) * sizeof(Passageiro));

    if (*ptr == NULL) {
        printf("Erro ao realocar memória\n");
        exit(1);
    }

    return *ptr;
}

void realizarReserva(int *qtd_de_reservas, Passageiro **ptr, Voo *voo, FILE **arquivo){
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
        int reservas = *qtd_de_reservas;
        fecharVoo(arquivo, ptr, reservas, voo);  // quantidade de assentos = 0, fechamento automático
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

void modificaReserva(Passageiro **ptr, int qtd_de_reservas) {
    char cpf_consulta[15], novo_nome[15], novo_sobrenome[15], novo_cpf[15], novo_assento[4];
    int encontrado = 1;
    scanf(" %s %s %s %s %s", cpf_consulta, novo_nome, novo_sobrenome, novo_cpf, novo_assento);

    for (int i = 0; i < qtd_de_reservas; i++){
        if (strcmp((*ptr)[i].cpf, cpf_consulta) == 0){
            encontrado = 1;

            strcpy((*ptr)[i].nome, novo_nome);
            strcpy((*ptr)[i].sobrenome, novo_sobrenome);
            strcpy((*ptr)[i].cpf, novo_cpf);
            strcpy((*ptr)[i].assento, novo_assento);

            printf("Reserva Modificada: \n");
            printf("%s\n", (*ptr)[i].cpf);
            printf("%s %s\n", (*ptr)[i].nome, (*ptr)[i].sobrenome);
            printf("%s %s %s\n", (*ptr)[i].dia, (*ptr)[i].mes, (*ptr)[i].ano);
            printf("Voo: %s\n", (*ptr)[i].numVoo);
            printf("Assento: %s\n", (*ptr)[i].assento);
            printf("Classe: %s\n", (*ptr)[i].classe);
            printf("Trecho: %s %s\n", (*ptr)[i].origem, (*ptr)[i].destino);
            printf("Valor: %s\n", (*ptr)[i].valor);
            printf("--------------------------------------------------\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Reserva não encontrada para o CPF: %s\n", cpf_consulta);
    }
}

void cancelaReserva(Passageiro **ptr, int qtd_de_reservas) {
    char cpf[14];

    scanf("%s", cpf);

    for(int i = 0; i < qtd_de_reservas; i++){
        if(strcmp((*ptr)[i].cpf, cpf) == 0){
            for(int j = i; j < qtd_de_reservas - 1; j++){
                (*ptr)[j] = (*ptr)[j+1];
            }
            qtd_de_reservas--;
        }
    }
}

void fecharDia(FILE **arquivo, Passageiro **ptr, int qtd_de_reservas, Voo *voo) {
     int auxEcon = 0;
    int auxExec = 0;

    for(int i = 0; i < qtd_de_reservas; i++){
        if(strcmp((*ptr)[i].classe, "economica") == 0){
            auxEcon++;
        } else {
            auxExec++;
        }
    }
    float total = (auxEcon * voo->valorEconomica) + (auxExec * voo->valorExecutiva);

    printf("Fechamento do dia:\n");
    printf("Quantidade de reservas: %d\nPosição: %0.2f\n", qtd_de_reservas, total);
    printf("--------------------------------------------------\n");
   
    *arquivo = fopen("abertura_voo.bin", "wb");
    if (*arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    fwrite(voo, sizeof(Voo), 1, *arquivo);
    fwrite(*ptr, sizeof(Passageiro) ,qtd_de_reservas, *arquivo);
    fclose(*arquivo);
   
    // Libera a memória alocada do vetor de structs de passageiros e da struct voo
    free(*ptr);
    // Define os ponteiros como NULL para evitar referências inválidas
    *ptr = NULL;
    exit(0); //sai do programa no fim do dia
}

void recuperando_dados_arqv(FILE **arquivo, Passageiro **ptr, int *qtd_de_reservas, Voo *voo) {
    *arquivo = fopen("abertura_voo.bin", "rb");
    if (*arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
   
    fseek(*arquivo, 0, SEEK_END); // Move o cursor para o final do arquivo
    long tamArqv = ftell(*arquivo); // Tamanho total do arquivo
    rewind(*arquivo);
   
    if(tamArqv > 0){ //verificando se o arquivo nao esta vazio
    *qtd_de_reservas = (tamArqv - sizeof(Voo)) / sizeof(Passageiro); // obtendo num de reservas

    *ptr = (Passageiro*)malloc((*qtd_de_reservas) * sizeof(Passageiro)); // aloca as structs

    // lendo os dados da struct voo e passageiros do arquivo
    fread(voo, sizeof(Voo), 1, *arquivo);
    fread(*ptr, sizeof(Passageiro), *qtd_de_reservas, *arquivo);
    fclose(*arquivo);
    }
}

void fecharVoo(FILE **arquivo, Passageiro **ptr, int qtd_de_reservas, Voo *voo) {
    int auxEcon = 0;
    int auxExec = 0;

    for(int i = 0; i < qtd_de_reservas; i++){
        if(strcmp((*ptr)[i].classe, "economica") == 0){
            auxEcon++;
        } else {
            auxExec++;
        }
    }
    float total = (auxEcon * voo->valorEconomica) + (auxExec * voo->valorExecutiva);

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
    printf("Valor Total: %0.2f\n", total);
    printf("--------------------------------------------------\n");
   
   *arquivo = fopen("abertura_voo.bin", "wb");//apaga as linhas ao inves de remover por completo
    if (*arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    fclose(*arquivo);

     // Libera a memória alocada do vetor de structs de passageiros e da struct voo
    free(*ptr);
    // Define os ponteiros como NULL para evitar referências inválidas
    *ptr = NULL;
    exit(0);
}

int main(void) {
    int var_abrir_voo = 0;
    int qtd_de_reservas = 0;
    FILE *arquivo = NULL;
    Passageiro *ptr = NULL;
    Voo voo;

    recuperando_dados_arqv(&arquivo, &ptr, &qtd_de_reservas, &voo);
 
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
            modificaReserva(&ptr, qtd_de_reservas);
            break;
        case 132:
            cancelaReserva(&ptr, qtd_de_reservas);
            break;
        case 138:
            fecharDia(&arquivo, &ptr, qtd_de_reservas, &voo);
            break;
        case 156:
            fecharVoo(&arquivo, &ptr, qtd_de_reservas, &voo);
            break;
        default:
            printf("Comando não identificado.\n");
        }
    }
}
