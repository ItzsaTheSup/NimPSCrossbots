/*
INFORMA��ES DO PROJETO:
Simulador de Nim para o Processo Seletivo da Crossbots 2024.2
C�digo de participante: 005

Coment�rio: N�o � particularmente um problema dif�cil, mas acho que seja interessante para demonstrar a parte l�gica para al�m da programa��o e
um c�digo enxuto em quest�o de c�digo bruto em si, mas detalhado e claro em quest�o de coment�rios, que acredito que sejam meus melhores pontos.
*/

// Bibliotecas
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

// Fun��es
int validacao_input_int(char input_str[10]){
    int input_int;  // Vari�vel de retorno

    if(atoi(input_str) <= 0 || atol(input_str) > INT_MAX || atof(input_str) - atoi(input_str) != 0){
        /* Se o n�mero for 0 (o que, pela fun��o atoi, pode tamb�m significar que a string n�o pode ser convertida),
        negativo, maior que o valor m�ximo do tipo int ou n�o-inteiro, retorna -1*/
        input_int = -1; // Como Nim s� permite inputs positivos, � v�lido usar -1 como valor de erro.

    } else { // Caso contr�rio, � v�lido e retorna o valor do n�mero digitado.
        input_int = atoi(input_str);
    }

    return input_int;
}

int input_nim(int restantes){ // Fun��o de input do jogador

    char input[10];
    int n_final;      // Vari�vel de armazenamento do input
    int ver = 0;    // Vari�vel de verifica��o do input

    while (1){ // Input da retirada de palitos

        printf("Digite quantos palitos quer pegar (1, 2 ou 3): ");
        ver = scanf("%s", &input);
        n_final = validacao_input_int(input);

        if (ver == 1 && n_final < 4 && n_final > 0 && n_final <= restantes){ // Valida��o do valor
            break;
        } else {
            n_final = 0;
            printf("Quantidade invalida!\n\n");
        }
    }
    return n_final;
}

int bot_nim(int restantes){ // Fun��o do bot

    int retirada; // Quantidade de palitos a ser retirada.

    if (restantes%4 == 0){  // Se est� em posi��o de desvantagem ...
        retirada = 1;       // ... Retira somente 1 palito para o jogo durar mais e ter chance do inimigo dar uma brecha.
    } else {                    // Sen�o, ou seja, se est� em posi��o de vantagem ...
        retirada = restantes%4; // ... Retira o suficiente para manter o inimigo em desvantagem.
    }

    printf ("O computador pegou %d palitos.", retirada);
    return retirada;

    /*

    L�GICA ENVOLVIDA

    A posi��o de desvantagem mais �bvia � ter 4 palitos antes de seu turno, uma vez que, independente de quantos palitos voc�
    retirar, o advers�rio poder� tirar os palitos restantes. Seguindo em diante nessa l�gica, 8 palitos tamb�m seria uma posi��o
    de desvantagem, uma vez que independente de quanto palitos voc� retirar, o advers�rio poder� manter 4 palitos, te colocando
    na posi��o inicial de desvantagem. Seguindo a l�gica, qualquer n�mero de palitos que seja m�ltiplo de 4, ou seja, n%4 == 0,
    � uma posi��o de desvantagem e, o inverso, n% != 4, � uma posi��o de vantagem.

    Como o bot deve, se obtiver vantagem, mant�-la, toda vez que n%4 != 0, o bot dever� retirar a quantidade de palitos exata
    para que o jogador receba n%4 == 0, ou seja, deve retirar o resto resultante. Em caso de estar em desvantagem, opta-se por
    fazer o jogo durar mais, para caso o oponente cometa algum deslize.

    */

    /* Em um projeto profissional, seria de bom tom que o bot estivesse em um arquivo separado, para evitar (ou, pelo menos, atrasar) curiosos.
    Entretanto, para deixar a entrega mais concisa, optei por mant�-lo aqui. */
}

// Corpo do c�digo
int main (void){

    //Texto de introdu��o
    printf("\n     _/       _/  _/  _/      _/\n    ___/     _/      ___/  ___/\n   _/ __/   _/  _/  _/ ____/_/\n  _/   __/ _/  _/  _/  _/  _/\n _/     ___/  _/  _/      _/\n_/       _/  _/  _/      _/\n\n");
    printf("Bem vind@! Esse e\' um programa que simula uma versao simplificada do jogo \"Nim\", em que se deve retirar palitos, em turnos.\n");
    printf("Na nossa versao, havera\' apenas uma linha de palitos e se podera\' retirar de 1 a 3 palitos. O seu objetivo e\' retirar o ultimo palito.\n");
    printf("Boa sorte!\n\n");


    char input_str[10];         // Primeira vari�vel do input
    int n_palitos, retirada;    // Vari�veis que armazenam, respectivamente, o n�mero atual de palitos e os palitos retirados.
    bool jogador = 0;           /* Vari�vel que se o turno � do o jogador. true (1) = jogador; false (0) = m�quina.
                                Pela invers�o no come�o de cada ciclo, a vari�vel come�a em 0 (false), mesmo que
                                o jogador que comece.*/
    int i;                      // Vari�vel de itera��o.
    int verificacao = 0;        // Vari�veis de valida��o do input

    while (1){  // Input da quantidade inicial de palitos.

        printf("Digite a quantidade inicial de palitos: ");
        verificacao = scanf("%s", &input_str);
        n_palitos = validacao_input_int(input_str);

        if (n_palitos > 0 && verificacao != EOF){
            break; // Se h� palitos e uma quantidade v�lida deles, pode se iniciar o jogo.

        } else {
            n_palitos = -1;
            printf("Quantidade invalida!\n\n");
        }

    }

    while (n_palitos > 0){ // Jogo em si:

        jogador = abs(jogador - 1); // Troca-se o jogador (se 0, abs(0 - 1) = 1, se 1, abs(1 - 1) = 0).
        retirada = 0; // Zera-se a vari�vel de retirada.

        // Mensagem gen�rica
        printf("\n");
        for (i = 1; i <= n_palitos; i++){
            printf("| ");
        }
        printf("\nNumero de palitos restantes: %d\n", n_palitos);

        // Retirada de palitos
        if (jogador) {
            retirada = input_nim(n_palitos); // Chama a fun��o de input do jogador.
        } else {
            retirada = bot_nim(n_palitos);  /* Como comentado dentro da pr�pria fun��o, seria de bom tom, em um programa
                                            profissional, que a programa��o do bot ficasse em um arquivo separado.*/
        }
        n_palitos -= retirada;  // Retira o n�mero de palitos selecionado.

    } // Lembrando: Caso n_palitos <= 0, o While acaba.

    //Resultado
    printf("\nFim do Jogo -> ");
    if (jogador){
        printf("Voce");
    } else {
        printf("O computador");
    }
    printf(" venceu!\n\n");
}
