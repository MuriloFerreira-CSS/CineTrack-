#include <stdio.h>
#include <string.h>

void ordenarFilmes(char nomes[][50], int ingressos[], int n) {
    int i, j, temp;
    char nomeTemp[50];

    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (ingressos[j] < ingressos[j+1]) {
                temp = ingressos[j];
                ingressos[j] = ingressos[j+1];
                ingressos[j+1] = temp;
                strcpy(nomeTemp, nomes[j]);
                strcpy(nomes[j], nomes[j+1]);
                strcpy(nomes[j+1], nomeTemp);
            }
        }
    }
}

int main() {
    int filmes, i, opcao;
    int total = 0, maisVendido, menosVendido, posMais, posMenos;
    float media;
    
    printf("=============================================\n");
    printf("         Bem-vindo ao CineTrack+   \n");
    printf("   Sistema de Monitoramento de Vendas de     \n");
    printf("                Ingressos de Cinema          \n");
    printf("=============================================\n\n");
    printf("Digite o numero de filmes em cartaz: ");
    scanf("%d", &filmes);

    int ingressos[filmes];
    char nomes[filmes][50];
    for (i = 0; i < filmes; i++) {
        printf("\nDigite o nome do filme %d: ", i+1);
        getchar();
        fgets(nomes[i], sizeof(nomes[i]), stdin);
        nomes[i][strcspn(nomes[i], "\n")] = '\0';

        printf("Digite o numero de ingressos vendidos para '%s': ", nomes[i]);
        scanf("%d", &ingressos[i]);
    }

    do {
        printf("\n=========== MENU PRINCIPAL ===========\n");
        printf("1. Exibir Relatorio de Vendas\n");
        printf("2. Exibir Ranking dos Filmes\n");
        printf("3. Exibir Grafico de Barras\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                total = 0;
                maisVendido = -1; menosVendido = 999999;
                posMais = 0; posMenos = 0;

                for (i = 0; i < filmes; i++) {
                    total += ingressos[i];
                    if (ingressos[i] > maisVendido) {
                        maisVendido = ingressos[i];
                        posMais = i;
                    }
                    if (ingressos[i] < menosVendido) {
                        menosVendido = ingressos[i];
                        posMenos = i;
                    }
                }

                media = (float) total / filmes;

                printf("\n=========== RELATORIO DE VENDAS ===========\n");
                printf("Total de ingressos vendidos: %d\n", total);
                printf("Media de ingressos por filme: %.2f\n", media);
                printf("Filme mais assistido: %s (%d ingressos)\n", nomes[posMais], maisVendido);
                printf("Filme menos assistido: %s (%d ingressos)\n", nomes[posMenos], menosVendido);

                printf("\nPercentual de vendas por filme:\n");
                for (i = 0; i < filmes; i++) {
                    float percentual = (ingressos[i] * 100.0) / total;
                    printf("%-20s -> %.2f%%\n", nomes[i], percentual);
                }
                printf("===========================================\n");
                break;

            case 2:
                {
                    int copiaIngressos[filmes];
                    char copiaNomes[filmes][50];

                    for (i = 0; i < filmes; i++) {
                        copiaIngressos[i] = ingressos[i];
                        strcpy(copiaNomes[i], nomes[i]);
                    }

                    ordenarFilmes(copiaNomes, copiaIngressos, filmes);

                    printf("\n=========== RANKING DE FILMES ===========\n");
                    for (i = 0; i < filmes; i++) {
                        printf("%dº - %-20s (%d ingressos)\n", i+1, copiaNomes[i], copiaIngressos[i]);
                    }
                    printf("==========================================\n");
                }
                break;

            case 3:
                {
                    int max = 0;
                    for (i = 0; i < filmes; i++) {
                        if (ingressos[i] > max) {
                            max = ingressos[i];
                        }
                    }

                    printf("\n=========== GRAFICO DE VENDAS ===========\n");
                    for (i = 0; i < filmes; i++) {
                        printf("%-20s | ", nomes[i]);
                        int barras = (ingressos[i] * 50) / max;
                        for (int j = 0; j < barras; j++) {
                            printf("|");
                        }
                        printf(" (%d)\n", ingressos[i]);
                    }
                    printf("==========================================\n");
                }
                break;

            case 4:
                printf("\nEncerrando o CineTrack+... Obrigado!\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while(opcao != 4);

    return 0;
}
