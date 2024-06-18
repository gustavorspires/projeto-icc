/* Autoria:
    Gabriella Almeida - 15528121
    Beatriz Alves dos Santos - 15588630
    Gustavo Ramos Santos Pires - 15458030
*/
/* Objetivo:
    Este programa gerencia as informações de um voo, armazenando os dados gerais do voo e de cada passageiro.
    O sistema permite que o usuário abra um voo, possibilitando a efetuação de reservas e, enquanto o voo estiver
    aberto, é possível consultar informações sobre as reservas, modificá-las e cancelá-las. Além disso, ao fim de
    cada dia o usuário pode registrar as informações obtidas no arquivo, e recuperá-las no dia seguinte.
    O fechamento do voo é expresso pelo comando "FV", onde o usuário além de encerrar as reservas, receberá
    um relatório acerca das informações de cada passageiro e o valor arrecadado por esse voo.
    O sistema utiliza arquivos binários para armazenar as informações dos voos e dos passageiros, garantindo
    que os dados sejam preservados entre as execuções do programa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------ Declaração das estruturas ------------------------------------ */

typedef struct
{
    int assentos;
    float valorEconomica;
    float valorExecutiva;
    int aberto;
} Voo;

typedef struct
{
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

/* ------------------------------------ Protótipos das funções ---------------------------------------*/
void imprimeVooFechado(Passageiro *ptr, Voo *voo, int qtd_de_reservas);
int arq_existe(const char *nome);
void descarregarDados(FILE *arquivo, Voo *voo, Passageiro *ptr, int qtd_de_reservas);
Passageiro *realoc_vetor_struct(Passageiro **ptr, int qtd_de_reservas);
void recuperando_dados_arqv(FILE **arquivo, Passageiro **ptr, int *qtd_de_reservas, Voo *voo);

Passageiro *abrirVoo(FILE **arquivo, int *var_abrir_voo, Voo *voo, int *qtd_de_reservas);
void realizarReserva(int *qtd_de_reservas, Passageiro **ptr, Voo *voo, FILE **arquivo);
void consultaReserva(Passageiro **ptr, int qtd_de_reservas);
void modificaReserva(Passageiro **ptr, int qtd_de_reservas, Voo *voo);
void cancelaReserva(Passageiro **ptr, int *qtd_de_reservas, Voo *voo);
void fecharVoo(FILE **arquivo, Passageiro **ptr, int qtd_de_reservas, Voo *voo);
void fecharDia(FILE **arquivo, Passageiro **ptr, int qtd_de_reservas, Voo *voo);

/* ------------------------------------------ Funções ----------------------------------------------- */
// Funções auxiliares à execução dos comandos:

/* A função recuperando_dados_arqv recebe como parâmetros o ponteiro para o
arquivo (**arquivo), o vetor de passageiros (**ptr), a quantidade de reservas
e o ponteiro para a estrutura Voo.

A função então pega todos os dados já gravados no arquivo e os grava na
estrutura *voo e no vetor **ptr. */

void recuperando_dados_arqv(FILE **arquivo, Passageiro **ptr, int *qtd_de_reservas, Voo *voo)
{
    *arquivo = fopen("abertura_voo.bin", "rb");
    if (*arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    fseek(*arquivo, 0, SEEK_END);   // Move o cursor para o final do arquivo
    long tamArqv = ftell(*arquivo); // Tamanho total do arquivo
    rewind(*arquivo);

    if (tamArqv > 0)
    {                                                                    // verificando se o arquivo nao esta vazio
        *qtd_de_reservas = (tamArqv - sizeof(Voo)) / sizeof(Passageiro); // obtendo num de reservas

        *ptr = (Passageiro *)malloc((*qtd_de_reservas) * sizeof(Passageiro)); // aloca as structs

        // lendo os dados da struct voo e passageiros do arquivo
        fread(voo, sizeof(Voo), 1, *arquivo);
        fread(*ptr, sizeof(Passageiro), *qtd_de_reservas, *arquivo);
        fclose(*arquivo);
    }
}

/* A função imprimeVooFechado recebe como parâmetros o vetor de passageiros e
o ponteiro voo, além da quantidade de reservas. Essa função é responsável por
imprimir os dados dos passageiros. É utilizada após o fechamento do voo e após
uma tentativa de alterar um voo fechado.*/

void imprimeVooFechado(Passageiro *ptr, Voo *voo, int qtd_de_reservas)
{
    int auxEcon = 0;
    int auxExec = 0;

    for (int i = 0; i < qtd_de_reservas; i++)
    {
        if (strcmp(ptr[i].classe, "economica") == 0)
        {
            auxEcon++;
        }
        else
        {
            auxExec++;
        }
    }
    float total = (auxEcon * voo->valorEconomica) + (auxExec * voo->valorExecutiva);

    printf("Voo fechado!\n\n");

    for (int i = 0; i < qtd_de_reservas; i++)
    {
        printf(
            "%s\n%s %s\n%s\n\n",
            (ptr)[i].cpf,
            (ptr)[i].nome,
            (ptr)[i].sobrenome,
            (ptr)[i].assento);
    }
    printf("Valor Total: %0.2f\n", total);
    printf("--------------------------------------------------\n");
}

/* Função arq_existe apenas verifica a existência ou não do arquivo para
evitar possíveis erros, recebendo como parâmetro apenas o nome do arquivo. */

int arq_existe(const char *nome)
{
    FILE *fp = fopen(nome, "r");
    if (fp){
        fclose(fp);
        return 1;
    }
    return 0;
}

/* A função descarregarDados recebe como parâmetros o arquivo, o ponteiro com
os dados do vôo, o vetor de passageiros e a quantidade de reservas feitas. A
função é responsável por gravar todos os dados do ponteiro voo e do vetor ptr
no arquivo. */

void descarregarDados(FILE *arquivo, Voo *voo, Passageiro *ptr, int qtd_de_reservas)
{
    arquivo = fopen("abertura_voo.bin", "wb");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    fwrite(voo, sizeof(Voo), 1, arquivo);
    fwrite(ptr, sizeof(Passageiro), qtd_de_reservas, arquivo);
    fclose(arquivo);
}

/* A função realoc_vetor_struct é autoexplicativa, realocando a memória 
disponibilizada para o vetor de passageiros a depender da quantidade de
reservas*/

Passageiro *realoc_vetor_struct(Passageiro **ptr, int qtd_de_reservas)
{
    *ptr = realloc(*ptr, (qtd_de_reservas + 1) * sizeof(Passageiro));

    if (*ptr == NULL)
    {
        printf("Erro ao realocar memoria\n");
        exit(1);
    }

    return *ptr;
}

// Funções referentes à execução dos comandos:

/* A função abrirVoo recebe como parâmetro o arquivo, a variável de voo 
aberto, a struct voo e o vetor de passageiros. Essa função é responsável por 
abrir voos, abrindo o arquivo e setando os parametros do voo */

Passageiro *abrirVoo(FILE **arquivo, int *var_abrir_voo, Voo *voo, int *qtd_de_reservas)
{

    if(voo->aberto){
        Passageiro *ptr = (Passageiro *)malloc(sizeof(Passageiro));

        *arquivo = fopen("abertura_voo.bin", "wb");
        *qtd_de_reservas = 0;

        if (*arquivo == NULL)
        {
            printf("Erro ao abrir o arquivo\n");
            exit(1);
        }

        int qntAssentos;
        float valorEcon;
        float valorExe;

        scanf("%d %f %f", &qntAssentos, &valorEcon, &valorExe);

        voo->assentos = qntAssentos;
        voo->valorEconomica = valorEcon;
        voo->valorExecutiva = valorExe;

        (*var_abrir_voo)++;
        voo->aberto = 1;

        return ptr;
    } 
    else
    {   
        printf("Voo fechado!\n");
        exit(0);
    }
}

/* A função realizarReserva recebe como parâmetro a quantidade de reservas, o 
arquivo, a estrutura voo e o vetor de passageiros. Essa função é responsável 
por ler os dados das reservas realizadas e guardá-las no vetor de 
passageiros, realocando a memória antes para poder guardar todos os dados. */

void realizarReserva(int *qtd_de_reservas, Passageiro **ptr, Voo *voo, FILE **arquivo)
{
    if (voo->assentos != 0 && voo->aberto == 1)
    {
        if (*qtd_de_reservas > 0)
        {
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
              (*ptr)[*qtd_de_reservas].destino);

        (*qtd_de_reservas)++;
        voo->assentos--;

        if (voo->assentos == 0)
        {
            fecharVoo(arquivo, ptr, *qtd_de_reservas, voo); // quantidade de assentos = 0, fechamento automático
        }
    }
    else // Voo fechado manualmente
    { 
        while (getchar() != '\n');
        imprimeVooFechado(*ptr, voo, *qtd_de_reservas);
    }
}

/* A função consultaReserva recebe como parâmetros a quantidade de reservas e 
o vetor de passageiros. Ela busca o valor do CPF indicado pelo usuário no 
vetor de passageiros e, ao localizar, imprime os dados da reserva. */

void consultaReserva(Passageiro **ptr, int qtd_de_reservas)
{
    char cpf_consulta[15];
    int encontrado = 0;
    scanf("%s", cpf_consulta);

    for (int i = 0; i < qtd_de_reservas; i++)
    {
        if (strcmp(cpf_consulta, (*ptr)[i].cpf) == 0)
        {
            encontrado = 1;
            printf(
                "%s\n%s %s\n%s/%s/%s\nVoo: %s\nAssento: %s\nClasse: %s\nTrecho: %s %s\nValor: %s\n",
                (*ptr)[i].cpf,
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
                (*ptr)[i].valor);
            printf("--------------------------------------------------\n");
        }
    }
    if (encontrado == 0)
    {
        printf("CPF invalido\n");
    }
}

/* A função modificaReserva recebe como parâmetro a quantidade de reservas, a 
estrutura voo e o vetor de passageiros. A função consulta o CPF inserido pelo 
usuário no vetor de passageiros e, ao localizar, altera os dados informados 
pelo usuário dentro dos parâmetros do vetor. */

void modificaReserva(Passageiro **ptr, int qtd_de_reservas, Voo *voo)
{
    char cpf_consulta[15], novo_nome[15], novo_sobrenome[15], novo_cpf[15], novo_assento[4];
    int encontrado = 1;
    scanf(" %s %s %s %s %s", cpf_consulta, novo_nome, novo_sobrenome, novo_cpf, novo_assento);

    if (voo->aberto)
    {
        for (int i = 0; i < qtd_de_reservas; i++)
        {
            if (strcmp((*ptr)[i].cpf, cpf_consulta) == 0)
            {
                encontrado = 1;

                strcpy((*ptr)[i].nome, novo_nome);
                strcpy((*ptr)[i].sobrenome, novo_sobrenome);
                strcpy((*ptr)[i].cpf, novo_cpf);
                strcpy((*ptr)[i].assento, novo_assento);

                printf("Reserva Modificada: \n");
                printf("%s\n", (*ptr)[i].cpf);
                printf("%s %s\n", (*ptr)[i].nome, (*ptr)[i].sobrenome);
                printf("%s/%s/%s\n", (*ptr)[i].dia, (*ptr)[i].mes, (*ptr)[i].ano);
                printf("Voo: %s\n", (*ptr)[i].numVoo);
                printf("Assento: %s\n", (*ptr)[i].assento);
                printf("Classe: %s\n", (*ptr)[i].classe);
                printf("Trecho: %s %s\n", (*ptr)[i].origem, (*ptr)[i].destino);
                printf("Valor: %s\n", (*ptr)[i].valor);
                printf("--------------------------------------------------\n");
                break;
            }
        }

        if (!encontrado)
        {
            printf("Reserva nao encontrada para o CPF: %s\n", cpf_consulta);
        }
    }
    else
    {
        imprimeVooFechado(*ptr, voo, qtd_de_reservas);
    }
}

/* A função cancelaReserva recebe como parâmetro a quantidade de reservas, a 
estrutura voo e o vetor de passageiros. A função busca o CPF informado pelo 
usuário no vetor de passageiros e, ao localizar, move todos os valores 
sucessores uma casa para trás e realoca a memória. */

void cancelaReserva(Passageiro **ptr, int *qtd_de_reservas, Voo *voo)
{
    int encontrado = 0;
    char cpf[14];

    scanf("%s", cpf);
    if (voo->aberto)
    {
        for (int i = 0; i < *qtd_de_reservas; i++)
        {
            if (strcmp((*ptr)[i].cpf, cpf) == 0)
            {
                encontrado = 1;
                for (int j = i; j < *qtd_de_reservas - 1; j++)
                {
                    (*ptr)[j] = (*ptr)[j + 1];
                }
                (*qtd_de_reservas)--;
                voo->assentos++;
            }
        }
        if (encontrado == 1)
        {
            realoc_vetor_struct(ptr, *qtd_de_reservas);
        }
    }
    else
    {
        imprimeVooFechado(*ptr, voo, *qtd_de_reservas);
    }
}

/* A função fecharDia recebe como parâmetro o arquivo, a quantidade de 
reservas, a estrutura voo e o vetor de passageiros. A função calcula o valor 
das passagens e imprime, ao final do dia, a quantidade de reservas realizadas 
até o momento e o valor total até o fechamento do dia, além de gravar todos 
os dados no arquivo. */

void fecharDia(FILE **arquivo, Passageiro **ptr, int qtd_de_reservas, Voo *voo)
{
    int auxEcon = 0;
    int auxExec = 0;

    for (int i = 0; i < qtd_de_reservas; i++)
    {
        if (strcmp((*ptr)[i].classe, "economica") == 0)
        {
            auxEcon++;
        }
        else
        {
            auxExec++;
        }
    }
    float total = (auxEcon * voo->valorEconomica) + (auxExec * voo->valorExecutiva);

    printf("Fechamento do dia:\n");
    printf("Quantidade de reservas: %d\nPosicao: %0.2f\n", qtd_de_reservas, total);
    printf("--------------------------------------------------\n");

    descarregarDados(*arquivo, voo, *ptr, qtd_de_reservas);

    // Libera a memória alocada do vetor de structs de passageiros
    free(*ptr);
    // Define o ponteiro como NULL para evitar referências inválidas
    *ptr = NULL;
    exit(0); // sai do programa no fim do dia
}

/* A função fecharVoo recebe como parâmetro o arquivo, a quantidade de 
reservas, a estrutura voo e o vetor de passageiros. A função imprime, ao 
final do dia, os dados das reservas finalizadas e os guarda no arquivo, 
liberando as estruturas e finalizando o programa. */

void fecharVoo(FILE **arquivo, Passageiro **ptr, int qtd_de_reservas, Voo *voo)
{
    voo->aberto = 0;
    imprimeVooFechado(*ptr, voo, qtd_de_reservas);

    descarregarDados(*arquivo, voo, *ptr, qtd_de_reservas);

    // Libera a memória alocada do vetor de structs de passageiros
    free(*ptr);
    // Define o ponteiro como NULL para evitar referências inválidas
    *ptr = NULL;
    exit(0);
}

/* A função main inicializa algumas das variáveis, verifica as entradas e 
executa os comandos a depender do valor ASCII somado das entradas */

int main(void)
{
    int var_abrir_voo = 0;
    int qtd_de_reservas = 0;
    FILE *arquivo = NULL;
    Passageiro *ptr = NULL;
    Voo voo;

    if (arq_existe("abertura_voo.bin"))
        recuperando_dados_arqv(&arquivo, &ptr, &qtd_de_reservas, &voo);

    while (1)
    {
        char str[3];
        scanf("%s", str);

        switch (str[0] + str[1])
        {
        case 151:
            ptr = abrirVoo(&arquivo, &var_abrir_voo, &voo, &qtd_de_reservas);
            break;
        case 164:
            realizarReserva(&qtd_de_reservas, &ptr, &voo, &arquivo);
            break;
        case 149:
            consultaReserva(&ptr, qtd_de_reservas);
            break;
        case 159:
            modificaReserva(&ptr, qtd_de_reservas, &voo);
            break;
        case 132:
            cancelaReserva(&ptr, &qtd_de_reservas, &voo);
            break;
        case 138:
            fecharDia(&arquivo, &ptr, qtd_de_reservas, &voo);
            break;
        case 156:
            fecharVoo(&arquivo, &ptr, qtd_de_reservas, &voo);
            break;
        default:
            printf("Comando nao identificado.\n");
        }
    }
}
