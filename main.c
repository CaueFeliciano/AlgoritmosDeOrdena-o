#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define QTD_ITENS 100000
// 100
// 1000
// 10000
// 50000
// 100000

int vetor[QTD_ITENS];

void registrarTempo(const char *nome_funcao, double tempo_cpu)
{
    FILE *arq = fopen("tempos_de_execucao.txt", "a");
    if (arq == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fprintf(arq, "ALGORITMO: %s\n", nome_funcao);
    fprintf(arq, "TEMPO DE EXECUÇÃO EM SEGUNDOS: %f\n", tempo_cpu);
    fprintf(arq, "----------------------------------\n");
    fclose(arq);
}

// 1 - Selection Sort
// OBJETIVO: Repetidamente selecionar o menor elemento restante do vetor e colocá-lo no início.
void selectionSort(int *v)
{
    int i, j, min, aux;                 // variáveis para controle
    for (i = 0; i < QTD_ITENS - 1; i++) // loop para percorrer o vetor
    {
        min = i;                            // define o primeiro elemento como o menor
        for (j = i + 1; j < QTD_ITENS; j++) // loop para percorrer o vetor a partir do segundo elemento
        {
            if (v[j] < v[min]) // verifica se o elemento atual é menor que o menor elemento
            {
                min = j; // caso for menor define o elemento atual como o menor
            }
        }
        aux = v[min];  // guarda o menor elemento
        v[min] = v[i]; // troca o menor elemento com o primeiro elemento
        v[i] = aux;    // troca o primeiro elemento com o menor elemento
    }
}

int main()
{
    for (int i = 0; i < QTD_ITENS; i++)
    {
        vetor[i] = rand() % QTD_ITENS;
    }
    clock_t inicio, fim;
    double tempo_cpu;

    inicio = clock();
    selectionSort(vetor);
    fim = clock();
    tempo_cpu = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    registrarTempo("Selection Sort", tempo_cpu);

    return 0;
}