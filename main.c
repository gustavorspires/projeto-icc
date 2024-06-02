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

void abrirVoo(int *qntAssentos, float *valorEcon, float *valorExe)
{
    //antes deve ter a logica do switch para entrar na func com o comando arquivo AV
    FILE *arquivo = fopen("abertura_voo.txt", "w"); //se o arquivo nao existir, cria o arquivo e abre em modo de escrita

    if(arquivo == NULL){//tratamento em caso de erro;
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    scanf("%d %f %f", qntAssentos, valorEcon, valorExe); //os números precisam ser usados na lógica, então eles sao armazenados em variáveis inteiras;

    fprintf(arquivo, "%d %f %f\n", *qntAssentos, *valorEcon, *valorExe);
    
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
    char cpf[15], nome[15], sobrenome[15], dia[3], mes[3], ano[5], numVoo[15], assento[5], classe[15], valor[10], origem[15], destino[15], cpf_consulta[15]; //passar para aloc dinamica dps!!

    // coloca o ponteiro para a segunda linha
    char linha[100];
    fgets(linha, 100, arquivo);
    long pos = ftell(arquivo);
    fseek(arquivo, pos, SEEK_SET);

    scanf("%s",cpf_consulta);
    //procura o cpf
    while (fscanf(arquivo, "%s %s %s %s %s %s %s %s %s %s %s %s", nome, sobrenome, cpf, dia, mes, ano, numVoo, assento, classe, valor, origem, destino) == 12){ //leitura de todas as infos de cada linhas (falta ainda)

        if(strcmp(cpf, cpf_consulta) == 0){
            printf("%s\n", cpf);
            printf("%s %s\n", nome, sobrenome);
            printf("%s/%s/%s\n", dia, mes, ano);
            printf("Voo: %s\n", numVoo);
            printf("Assento: %s\n", assento);
            printf("Classe: %s\n", classe);
            printf("Trecho: %s %s\n", origem, destino);
            printf("Valor: %s\n", valor);
        }
    }
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