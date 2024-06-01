#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int assentos;
    float valorEconomica;
    float valorExecutiva;
} Voo;

typedef struct{
    char *nome;
    char *sobrenome;
    char *CPF;
    char *dataViagem;
    int numeroVoo;
    char *assento;
    char *classe;
    float valor;
    char *origem;
    char *destino;
} Passageiro;

void abrirVoo(int *qntAssentos, int *valorEcon, int *valorExe)
{
    //antes deve ter a logica do switch para entrar na func com o comando arquivo AV
    FILE *arquivo = fopen("abertura_voo.txt", "w"); //se o arquivo nao existir, cria o arquivo e abre em modo de escrita

    if(arquivo == NULL){//tratamento em caso de erro;
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    scanf("%d %d %d", qntAssentos, valorEcon, valorExe); //os números precisam ser usados na lógica, então eles sao armazenados em variáveis inteiras;

    fprintf(arquivo, "%d %d %d", *qntAssentos, *valorEcon, *valorExe);
    
    fclose(arquivo);//fecha o arquivo
}
void realizarReserva(int *qntAssentos){
    char *str = (char *)malloc(100 * sizeof(char));
    FILE *arquivo = fopen("abertura_voo.txt", "w");
    if(*qntAssentos != 0){
        scanf(" %[^\n]s", str);
        (*qntAssentos)--;
    } else {
        exit(1);
    }
    fclose(arquivo);//fecha o arquivo
    free(str);
    str = NULL;
}

void consultaReserva(){

}
void modificaReserva(){

}
void cancelaReserva(){

}
void fecharDia(){

}
void fecharVoo(){

}

int main(void)
{
    int *qntAssentos, *valorEcon, *valorExe;
    FILE **arquivo;
    char str[2];
    scanf("%s ", str);

    switch (str[0] + str[1])
    {
    case 151: // Abertura de vôo
        abrirVoo(qntAssentos, valorEcon, valorExe);
        break;
    case 164: // Realização de reserva
        realizarReserva(qntAssentos);
        break;
    case 149: // Consultar reserva
        consultaReserva();
        break;
    case 159: // Modificação de reserva
        modificaReserva();
        break;
    case 132: // Cancelamento de reserva
        cancelaReserva();
        break;
    case 138: // Fechamento de dia
        fecharDia();
        break;
    case 156: // Fechamento de voo
        fecharVoo();
        break;
    default: // caso nenhuma das condições seja satisfeita
        printf("Comando não identificado.\n--------------------------------------------------\n");
    }
}