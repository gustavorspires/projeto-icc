#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int assentos;
    float valorEconomica;
    float valorExecutiva;
} Voo;

typedef struct{
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
}Passageiro;

void abrirVoo(int *qntAssentos, float *valorEcon, float *valorExe)
{
    //antes deve ter a logica do switch para entrar na func com o comando arquivo AV
    FILE *arquivo = fopen("abertura_voo.txt", "w"); //se o arquivo nao existir, cria o arquivo e abre em modo de escrita

    if(arquivo == NULL){//tratamento em caso de erro;
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    scanf("%d %f %f", qntAssentos, valorEcon, valorExe); //os números precisam ser usados na lógica, então eles sao armazenados em variáveis inteiras;

    fprintf(arquivo, "%d %.2f %.2f\n", *qntAssentos, *valorEcon, *valorExe);
    
    fclose(arquivo);//fecha o arquivo
}

void realizarReserva(int *qntAssentos){
    char *str = (char *)malloc(100 * sizeof(char)); //alocação dinâmica da string com os dados da reserva
    FILE *arquivo = fopen("abertura_voo.txt", "r+");
    fseek(arquivo, 0, SEEK_END); //move o ponteiro para o fim do arquivo (para não sobrescrever)

    if(*qntAssentos != 0){
        scanf(" %[^\n]s", str);
        fprintf(arquivo, "%s\n", str);
        (*qntAssentos)--;
    } else {
        printf("Nao tem mais assento disponivel"); //mudar isso aqui depois, coloquei só pra debug
        exit(1);
    }

    fclose(arquivo);//fecha o arquivo
    free(str);
    str = NULL;
}

void consultaReserva(){
    FILE *arquivo = fopen("abertura_voo.txt", "r");
    Passageiro *passageiro = (Passageiro *) malloc(sizeof(Passageiro));
    char *cpf_consulta = (char *)malloc(15 * sizeof(char *)); //passar para aloc dinamica dps!!

    // coloca o ponteiro para a segunda linha
    char linha[100];
    fgets(linha, 100, arquivo);
    long pos = ftell(arquivo);
    fseek(arquivo, pos, SEEK_SET);

    scanf("%s",cpf_consulta);
    //procura o cpf
    while (fscanf(arquivo, "%s %s %s %s %s %s %s %s %s %s %s %s", passageiro->nome, passageiro->sobrenome, passageiro->cpf, passageiro->dia, passageiro->mes, passageiro->ano, passageiro->numVoo, passageiro->assento, passageiro->classe, passageiro->valor, passageiro->origem, passageiro->destino) == 12){ //leitura de todas as infos de cada linhas (falta ainda)

        if(strcmp(passageiro->cpf, cpf_consulta) == 0){
            printf("%s\n", passageiro->cpf);
            printf("%s %s\n", passageiro->nome, passageiro->sobrenome);
            printf("%s/%s/%s\n", passageiro->dia, passageiro->mes, passageiro->ano);
            printf("Voo: %s\n", passageiro->numVoo);
            printf("Assento: %s\n", passageiro->assento);
            printf("Classe: %s\n", passageiro->classe);
            printf("Trecho: %s %s\n", passageiro->origem, passageiro->destino);
            printf("Valor: %s\n", passageiro->valor);
        }
    }
    fclose(arquivo);
    free(passageiro);
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
    int qntAssentos;
    float valorEcon, valorExe;
   while(1){
        char str[2];
        scanf("%s", str);

        switch (str[0] + str[1])
        {
        case 151: // Abertura de vôo
            abrirVoo(&qntAssentos, &valorEcon, &valorExe);
            break;
        case 164: // Realização de reserva
            realizarReserva(&qntAssentos);
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
}