/*
INFORMAÇÕES DO PROJETO:
Simulador de Nim para o Processo Seletivo da Crossbots 2024.2
Código de participante: 005

Comentário: Não é particularmente um problema difícil, mas acho que seja interessante para demonstrar a parte lógica para além da programação e
um código enxuto em questão de código bruto em si, mas detalhado e claro em questão de comentários, que acredito que sejam meus melhores pontos.
*/

// Bibliotecas
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

// Funções
int validacao_input_int(char input_str[10]){
    int input_int;  // Variável de retorno

    if(atoi(input_str) <= 0 || atol(input_str) > INT_MAX || atof(input_str) - atoi(input_str) != 0){
        /* Se o número for 0 (o que, pela função atoi, pode também significar que a string não pode ser convertida),
        negativo, maior que o valor máximo do tipo int ou não-inteiro, retorna -1*/
        input_int = -1; // Como Nim só permite inputs positivos, é válido usar -1 como valor de erro.

    } else { // Caso contrário, é válido e retorna o valor do número digitado.
        input_int = atoi(input_str);
    }

    return input_int;
}

int input_nim(int restantes){ // Função de input do jogador

    char input[10];
    int n_final;      // Variável de armazenamento do input
    int ver = 0;    // Variável de verificação do input

    while (1){ // Input da retirada de palitos

        printf("Digite quantos palitos quer pegar (1, 2 ou 3): ");
        ver = scanf("%s", &input);
        n_final = validacao_input_int(input);

        if (ver == 1 && n_final < 4 && n_final > 0 && n_final <= restantes){ // Validação do valor
            break;
        } else {
            n_final = 0;
            printf("Quantidade invalida!\n\n");
        }
    }
    return n_final;
}

int bot_nim(int restantes){ // Função do bot

    int retirada; // Quantidade de palitos a ser retirada.

    if (restantes%4 == 0){  // Se está em posição de desvantagem ...
        retirada = 1;       // ... Retira somente 1 palito para o jogo durar mais e ter chance do inimigo dar uma brecha.
    } else {                    // Senão, ou seja, se está em posição de vantagem ...
        retirada = restantes%4; // ... Retira o suficiente para manter o inimigo em desvantagem.
    }

    printf ("O computador pegou %d palitos.", retirada);
    return retirada;

    /*

    LÓGICA ENVOLVIDA

    A posição de desvantagem mais óbvia é ter 4 palitos antes de seu turno, uma vez que, independente de quantos palitos você
    retirar, o adversário poderá tirar os palitos restantes. Seguindo em diante nessa lógica, 8 palitos também seria uma posição
    de desvantagem, uma vez que independente de quanto palitos você retirar, o adversário poderá manter 4 palitos, te colocando
    na posição inicial de desvantagem. Seguindo a lógica, qualquer número de palitos que seja múltiplo de 4, ou seja, n%4 == 0,
    é uma posição de desvantagem e, o inverso, n% != 4, é uma posição de vantagem.

    Como o bot deve, se obtiver vantagem, mantê-la, toda vez que n%4 != 0, o bot deverá retirar a quantidade de palitos exata
    para que o jogador receba n%4 == 0, ou seja, deve retirar o resto resultante. Em caso de estar em desvantagem, opta-se por
    fazer o jogo durar mais, para caso o oponente cometa algum deslize.

    */

    /* Em um projeto profissional, seria de bom tom que o bot estivesse em um arquivo separado, para evitar (ou, pelo menos, atrasar) curiosos.
    Entretanto, para deixar a entrega mais concisa, optei por mantê-lo aqui. */
}

// Corpo do código
int main (void){

    //Texto de introdução
    printf("\n     _/       _/  _/  _/      _/\n    ___/     _/      ___/  ___/\n   _/ __/   _/  _/  _/ ____/_/\n  _/   __/ _/  _/  _/  _/  _/\n _/     ___/  _/  _/      _/\n_/       _/  _/  _/      _/\n\n");
    printf("Bem vind@! Esse e\' um programa que simula uma versao simplificada do jogo \"Nim\", em que se deve retirar palitos, em turnos.\n");
    printf("Na nossa versao, havera\' apenas uma linha de palitos e se podera\' retirar de 1 a 3 palitos. O seu objetivo e\' retirar o ultimo palito.\n");
    printf("Boa sorte!\n\n");


    char input_str[10];         // Primeira variável do input
    int n_palitos, retirada;    // Variáveis que armazenam, respectivamente, o número atual de palitos e os palitos retirados.
    bool jogador = 0;           /* Variável que se o turno é do o jogador. true (1) = jogador; false (0) = máquina.
                                Pela inversão no começo de cada ciclo, a variável começa em 0 (false), mesmo que
                                o jogador que comece.*/
    int i;                      // Variável de iteração.
    int verificacao = 0;        // Variáveis de validação do input

    while (1){  // Input da quantidade inicial de palitos.

        printf("Digite a quantidade inicial de palitos: ");
        verificacao = scanf("%s", &input_str);
        n_palitos = validacao_input_int(input_str);

        if (n_palitos > 0 && verificacao != EOF){
            break; // Se há palitos e uma quantidade válida deles, pode se iniciar o jogo.

        } else {
            n_palitos = -1;
            printf("Quantidade invalida!\n\n");
        }

    }

    while (n_palitos > 0){ // Jogo em si:

        jogador = abs(jogador - 1); // Troca-se o jogador (se 0, abs(0 - 1) = 1, se 1, abs(1 - 1) = 0).
        retirada = 0; // Zera-se a variável de retirada.

        // Mensagem genérica
        printf("\n");
        for (i = 1; i <= n_palitos; i++){
            printf("| ");
        }
        printf("\nNumero de palitos restantes: %d\n", n_palitos);

        // Retirada de palitos
        if (jogador) {
            retirada = input_nim(n_palitos); // Chama a função de input do jogador.
        } else {
            retirada = bot_nim(n_palitos);  /* Como comentado dentro da própria função, seria de bom tom, em um programa
                                            profissional, que a programação do bot ficasse em um arquivo separado.*/
        }
        n_palitos -= retirada;  // Retira o número de palitos selecionado.

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
