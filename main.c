#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define QTD_ITENS 50000
// 100
// 1000
// 10000
// 50000
// 100000

int vetor[QTD_ITENS]; // vetor global para armazenar os valores

int *copiarVetor(int *origem)
{
    int *v = (int *)malloc(QTD_ITENS * sizeof(int)); // aloca memória
    if (v == NULL)
    {
        perror("Erro ao alocar memória");
        return NULL;
    }

    for (int i = 0; i < QTD_ITENS; i++)
    {
        v[i] = origem[i];
    }

    return v;
}

void registrarTempo(const char *nome_funcao, double tempo_cpu) // função para registrar o tempo de execução
{
    FILE *arq = fopen("tempos_de_execucao.txt", "a");
    if (arq == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fprintf(arq, "ALGORITMO: %s\n", nome_funcao);
    fprintf(arq, "TEMPO DE EXECUÇÃO EM SEGUNDOS: %f\n", tempo_cpu);
    fprintf(arq, "QUANTIDADE DE ITENS: %d\n", QTD_ITENS);
    fprintf(arq, "----------------------------------\n");
    fclose(arq);
}

void medirTempo(void (*funcao)(int *), const char *nome) // função para medir o tempo de execução de uma função
{
    int *v = copiarVetor(vetor); // copia o vetor global
    if (v == NULL)
        return; // verifica se houve erro na alocação de memória

    clock_t inicio = clock();
    funcao(v); // executa o algoritmo de ordenação
    clock_t fim = clock();

    double tempo_cpu = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    registrarTempo(nome, tempo_cpu);

    free(v); // libera a memória alocada
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

// 2 - Insertion Sort
// OBJETIVO: Repetidamente inserir um elemento não ordenado na parte ordenada do vetor.
void insertionSort(int *v)
{
    int i, j, aux;                  // variáveis para controle
    for (i = 1; i < QTD_ITENS; i++) // loop para percorrer o vetor
    {
        aux = v[i];                  // guarda o elemento atual
        j = i - 1;                   // define o elemento anterior ao atual
        while (j >= 0 && v[j] > aux) // loop para percorrer o vetor a partir do elemento anterior ao atual
        {
            v[j + 1] = v[j]; // move o elemento para a direita
            j--;             // decrementa o contador
        }
        v[j + 1] = aux; // insere o elemento na posição correta
    }
}

int main()
{
    srand(time(NULL));                  // inicializa o gerador de números aleatórios
    for (int i = 0; i < QTD_ITENS; i++) // preenche o vetor com valores aleatórios
    {
        vetor[i] = rand() % QTD_ITENS; // gera um número aleatório entre 0 e QTD_ITENS
    }

    medirTempo(selectionSort, "Selection Sort");
    medirTempo(insertionSort, "Insertion Sort");

    return 0;
}