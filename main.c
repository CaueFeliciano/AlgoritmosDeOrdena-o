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

void heapify(int *v, int n, int i)
{
    int largest = i;       // Assume que o nó atual é o maior
    int left = 2 * i + 1;  // Calcula o índice do filho à esquerda
    int right = 2 * i + 2; // Calcula o índice do filho à direita

    // Verifica se o filho à esquerda é maior que o nó atual
    if (left < n && v[left] > v[largest])
    {
        largest = left;
    }

    // Verifica se o filho à direita é maior que o maior nó encontrado até agora
    if (right < n && v[right] > v[largest])
    {
        largest = right;
    }

    // Se o maior valor não está no nó atual, troca os valores
    if (largest != i)
    {
        int temp = v[i];
        v[i] = v[largest];
        v[largest] = temp;

        // Chama recursivamente `heapify` para ajustar a subárvore
        heapify(v, n, largest);
    }
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
        aux = v[i];                      // guarda o elemento atual
        j = i - 1;                       // define o elemento anterior ao atual
        while ((j >= 0) && (aux < v[j])) // loop para percorrer a parte ordenada do vetor
        {
            v[j + 1] = v[j]; // move o elemento para a direita
            j--;             // decrementa o contador
        }
        v[j + 1] = aux; // insere o elemento na posição correta
    }
}

// 3 - Bubble Sort
// OBJETIVO: Repetidamente comparar elementos adjacentes e trocá-los se estiverem na ordem errada.
void bubbleSort(int *v)
{
    int i, j, aux;                      // variáveis para controle
    for (i = 0; i < QTD_ITENS - 1; i++) // loop para percorrer o vetor
    {
        for (j = 0; j < QTD_ITENS - i - 1; j++) // loop para percorrer o vetor
        {
            if (v[j] > v[j + 1]) // verifica se o elemento atual é maior que o próximo elemento
            {
                aux = v[j];      // guarda o elemento atual
                v[j] = v[j + 1]; // troca o elemento atual com o próximo elemento
                v[j + 1] = aux;  // troca o próximo elemento com o elemento atual
            }
        }
    }
}

// 4 - Merge Sort
// OBJETIVO: Criar uma sequência ordenada a partir de duas outras, também ordenadas. Ele divide a sequência em pares de dados, ordenando-as; para depois agrupa-lás. Até chegar em duas partes e então combinar elas.
void merge(int vetor[], int inicio, int meio, int fim)
{                                     // Função merge, é responsável por unir duas metades de um vetor em ordem.
    int tamanho = (fim - inicio) + 1; // Cálculo do tmanho do subarray
    int i, j, posicao;
    int temp[tamanho]; // Array temporario para armazenar os elementos do subarray

    for (i = inicio; i <= fim; i++)
    {
        temp[i - inicio] = vetor[i];
    } // Vai copiar os elementos do vetor origanl, vetor, para o array temporario

    i = 0;                 // Reinicia o índice para ser usado em uma das metades do vetor no array temp
    j = meio - inicio + 1; // Faz a mesma coisa que o i para a segunda metade do vetor no vator array temp
    posicao = inicio;      // Inicia para ser usado na inserção dos elementos de volta no vetor original

    for (; i <= meio - inicio && j <= fim - inicio; posicao++)
    { // Este for contiua enquanto tiver elementos em ambas as metades
        if (temp[i] < temp[j])
        {
            vetor[posicao] = temp[i];
            i++;
        }
        else
        {
            vetor[posicao] = temp[j];
            j++;
        }
    } // Se a primeira metade de temp[i] for menor o da, segunda tem[j], ele é adcionado; se não o elemento da segunda metade é inserido

    for (; i <= meio - inicio; i++, posicao++)
    {
        vetor[posicao] = temp[i];
    } // Caso tenha elementos na primeira metade, ele copia os restantes para o vetor original

    for (; j <= fim - inicio; j++, posicao++)
    {
        vetor[posicao] = temp[j];
    } // Faz a mesma coisa que o ultimo for, porém na segunda metade
}

void mergeSortRec(int vetor[], int inicio, int fim) // Função que realiza a ordenação recursiva
{
    if (inicio < fim) // garante que tem mais de um elemtento para ordenar. Se não, a função não faz nada
    {
        int meio = inicio + (fim - inicio) / 2; // Calcula o meio do vetor
        mergeSortRec(vetor, inicio, meio);
        mergeSortRec(vetor, meio + 1, fim); // Divide o vetor ao meio, para as duas metades até que restam apenas um elemento
        merge(vetor, inicio, meio, fim);    // Uni as duas metades em ordem
    }
};

void mergeSort(int *v) // Função que realiza a chamada inicial da ordenação recursiva
{
    mergeSortRec(v, 0, QTD_ITENS - 1);
}

// 5 - Quick Sort
// OBJETIVO: Dividir o problema de ordenar um conjunto com n itens em dois problemas menores, para esses menores serem ordenados independentemente.
int particionar(int *v, int inicio, int fim)
{
    int pivo = v[(inicio + fim) / 2]; // Pivo é o elemento do meio do vetor
    int i = inicio - 1;               // Inicia o contador do inicio
    int j = fim + 1;                  // Inicia o contador do fim

    while (1)
    {
        do
        {
            i++; // Incrementa o contador
        } while (v[i] < pivo); // Enquanto o elemento for menor que o pivo

        do
        {
            j--; // Decrementa o contador
        } while (v[j] > pivo); // Enquanto o elemento for maior que o pivo

        if (i >= j) // Se os contadores se cruzarem, retorna o contador j
            return j;

        int temp = v[i]; // Troca os elementos
        v[i] = v[j];     // Troca os elementos
        v[j] = temp;     // Troca os elementos
    }
}

// Função recursiva de ordenação para o quicksort
void ordenar(int *v, int inicio, int fim)
{
    if (inicio < fim)
    {
        int p = particionar(v, inicio, fim); // Particiona o vetor
        ordenar(v, inicio, p);               // Ordena a primeira metade
        ordenar(v, p + 1, fim);              // Ordena a segunda metade
    }
}

void quickSort(int *v) // Função de entrada para o quicksort
{
    ordenar(v, 0, QTD_ITENS - 1);
}

// 6 - Heap Sort
// OBJETIVO: Transformar o vetor em uma árvore binária e ordená-la.
void heapSort(int *v)
{
    int i, aux;                              // variáveis para controle
    for (i = QTD_ITENS / 2 - 1; i >= 0; i--) // loop para percorrer o vetor
    {
        heapify(v, QTD_ITENS, i); // transforma o vetor em uma árvore binária
    }
    for (i = QTD_ITENS - 1; i > 0; i--) // loop para percorrer o vetor
    {
        aux = v[0];       // guarda o primeiro elemento
        v[0] = v[i];      // troca o primeiro elemento com o último elemento
        v[i] = aux;       // troca o último elemento com o primeiro elemento
        heapify(v, i, 0); // transforma o vetor em uma árvore binária
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
    medirTempo(bubbleSort, "Bubble Sort");
    medirTempo(mergeSort, "Merge Sort");
    medirTempo(quickSort, "Quick Sort");
    medirTempo(heapSort, "Heap Sort");

    return 0;
}
