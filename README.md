# Projeto - Introdução à Ciência da Computação I - 2024

## Integrantes
- Beatriz Alves dos Santos
- Gabriella Almeida
- Gustavo Ramos Santos Pires

## Professor Responsável
- Prof. Dr. Rudinei Goularte

## Descrição do Projeto
O projeto é um sistema de reserva de passagens, baseado em C, utilizando todo o conteúdo ensinado durante o semestre. Existem 7 comandos principais no mesmo, sendo eles:

##### AV
Abertura de vôo, contendo a quantidade de assentos e o valor das passagens;

##### RR
Realiza a reserva, com o usuário inserindo os dados do passageiro;

##### CR
Consulta a reserva, a partir do CPF informado pelo usuário;

##### MR
Modifica a reserva, consultando o CPF informado e alterando as informações do passageiro;

##### CA
Cancela a reserva, a partir do CPF informado pelo usuário;

##### FD
Fecha o dia, retornando para o usuário a quantidade de reservas do vôo e o valor total até o momento;

##### FV
Fecha o vôo, retornando o CPF, nome e assento dos passageiros e o valor total das passagens compradas.

Ao executar o comando FD ou FV, os dados são gravados em um arquivo binário e podem ser consultados através do programa, porém ao executar FV os mesmos não podem ser alterados até que o arquivo seja movido ou excluído (conforme solicitado pelo professor)
