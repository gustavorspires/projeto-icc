#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int assentos;
    float valorEconomica;
    float valorExecutiva;
}Voo;

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
}Passageiro;

void abrirVoo()
{
}
void realizarReserva()
{
}

int main(void)
{
    char str[2];
    scanf("%s ", str);

    switch (str[0] + str[1])
    {
    case 151: // Abertura de vôo
        abrirVoo();
        break;
    case 164: // Realização de reserva
        realizarReserva();
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
        fechamentoDia();
        break;
    case 156: // Fechamento de voo
        fecharVoo();
        break;
    default: // caso nenhuma das condições seja satisfeita
        printf("Comando não identificado.\n--------------------------------------------------\n");
    }
}