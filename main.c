#include <stdio.h>
#include <time.h>
#define QTD_ITENS 100

int vetor[QTD_ITENS];

void registrarTempo(char nome_funcao, double tempo_cpu)
{
    FILE *arq = fopen("tempos_de_execucao.txt", "a");
    if (arq == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fprintf(arq, "ALGORITMO: %s\n", nome_funcao);
    fprintf(arq, "TEMPO DE EXECUÇÃO: %f\n", tempo_cpu);
    fclose(arq);
}

// 1 - Selection Sort
void selectionSort(int *v)
{
    int i, j, min, aux;
    for (i = 0; i < 9; i++)
    {
        min = i;
        for (j = i + 1; j < 10; j++)
        {
            if (v[j] < v[min])
            {
                min = j;
            }
        }
        aux = v[min];
        v[min] = v[i];
        v[i] = aux;
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
    // algoritmo de ordenação
    fim = clock();
    tempo_cpu = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    registrarTempo("Selection Sort", tempo_cpu);

    return 0;
}