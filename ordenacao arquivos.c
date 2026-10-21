#ifdef _WIN32
#include <direct.h>
#define PEGAR_PASTA(b, t) _getcwd(b, t)
#define CRIAR_PASTA(p)    _mkdir(p)
#define SEPARADOR         '\\'
#else
#define _POSIX_C_SOURCE 200112L
#include <unistd.h>
#include <sys/stat.h>
#define PEGAR_PASTA(b, t) getcwd(b, t)
#define CRIAR_PASTA(p)    mkdir(p, 0755)
#define SEPARADOR         '/'
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

#define MAX          1000
#define TAM_CAMINHO  1024
#define NOME_PASTA   "arquivos_ordenacao"
#define QTD_INICIAL  10

char ARQ_DADOS[TAM_CAMINHO];
char ARQ_ORDENADO[TAM_CAMINHO];

void limparBuffer(void);
int  lerInteiro(const char *msg, int min, int max);

void prepararArquivos(const char *caminhoExe);
int  gravarArquivo(const char *nome, const int v[], int n);
int  lerArquivo(const char *nome, int v[], int max);
void exibirVetor(const char *titulo, const int v[], int n);

void trocar(int *a, int *b);
void bubbleSort(int v[], int n);
void insertionSort(int v[], int n);
void selectionSort(int v[], int n);
void mergeSort(int v[], int inicio, int ultimo);
void intercalar(int v[], int inicio, int meio, int ultimo);
void quickSort(int v[], int inicio, int ultimo);
int  particionar(int v[], int inicio, int ultimo);

const char *escolherEOrdenar(int v[], int n);
void opcaoCriarDados(void);
void opcaoExibirArquivo(const char *nome);
void opcaoOrdenar(void);
void opcaoAlterarValor(void);

void limparBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int lerInteiro(const char *msg, int min, int max)
{
    int x;
    while (1) {
        printf("%s", msg);
        if (scanf("%d", &x) == 1 && x >= min && x <= max) {
            limparBuffer();
            return x;
        }
        if (feof(stdin)) {
            printf("\nFim da entrada. Encerrando.\n");
            exit(0);
        }
        printf("  Valor invalido! Digite um inteiro entre %d e %d.\n", min, max);
        limparBuffer();
    }
}

void prepararArquivos(const char *caminhoExe)
{
    char base[TAM_CAMINHO - 64];
    char pasta[TAM_CAMINHO - 32];
    const char *ultimaBarra;
    const char *p;
    size_t tam;
    int v[QTD_INICIAL], i;
    FILE *f;

    ultimaBarra = NULL;
    for (p = caminhoExe; *p != '\0'; p++)
        if (*p == '/' || *p == '\\')
            ultimaBarra = p;

    if (ultimaBarra != NULL && (size_t)(ultimaBarra - caminhoExe) < sizeof(base) - 1) {
        tam = (size_t)(ultimaBarra - caminhoExe);
        memcpy(base, caminhoExe, tam);
        base[tam] = '\0';
    } else if (PEGAR_PASTA(base, sizeof(base)) == NULL) {
        strcpy(base, ".");
    }

    sprintf(pasta, "%s%c%s", base, SEPARADOR, NOME_PASTA);
    CRIAR_PASTA(pasta);

    sprintf(ARQ_DADOS,    "%s%cdados.txt",    pasta, SEPARADOR);
    sprintf(ARQ_ORDENADO, "%s%cordenado.txt", pasta, SEPARADOR);

    f = fopen(ARQ_DADOS, "r");
    if (f != NULL) {
        fclose(f);
    } else {
        for (i = 0; i < QTD_INICIAL; i++)
            v[i] = rand() % 1000;
        if (!gravarArquivo(ARQ_DADOS, v, QTD_INICIAL)) {
            strcpy(ARQ_DADOS, "dados.txt");
            strcpy(ARQ_ORDENADO, "ordenado.txt");
            gravarArquivo(ARQ_DADOS, v, QTD_INICIAL);
        }
    }

    f = fopen(ARQ_ORDENADO, "r");
    if (f != NULL) {
        fclose(f);
    } else {
        f = fopen(ARQ_ORDENADO, "w");
        if (f != NULL)
            fclose(f);
    }

    printf("Arquivos do programa:\n");
    printf("  dados.txt    -> %s\n", ARQ_DADOS);
    printf("  ordenado.txt -> %s\n", ARQ_ORDENADO);
}

int gravarArquivo(const char *nome, const int v[], int n)
{
    FILE *f;
    int i;

    f = fopen(nome, "w");
    if (f == NULL) {
        printf("Erro: nao foi possivel abrir %s para escrita.\n", nome);
        return 0;
    }
    for (i = 0; i < n; i++)
        fprintf(f, "%d\n", v[i]);
    fclose(f);
    return 1;
}

int lerArquivo(const char *nome, int v[], int max)
{
    FILE *f;
    int n = 0;

    f = fopen(nome, "r");
    if (f == NULL)
        return -1;
    while (n < max && fscanf(f, "%d", &v[n]) == 1)
        n++;
    fclose(f);
    return n;
}

void exibirVetor(const char *titulo, const int v[], int n)
{
    int i;
    printf("%s (%d valores):\n", titulo, n);
    for (i = 0; i < n; i++) {
        printf("%6d", v[i]);
        if ((i + 1) % 10 == 0 || i == n - 1)
            printf("\n");
    }
}

void trocar(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void bubbleSort(int v[], int n)
{
    int i, j, houveTroca;
    for (i = 0; i < n - 1; i++) {
        houveTroca = 0;
        for (j = 0; j < n - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                trocar(&v[j], &v[j + 1]);
                houveTroca = 1;
            }
        }
        if (!houveTroca)
            break;
    }
}

void insertionSort(int v[], int n)
{
    int i, j, chave;
    for (i = 1; i < n; i++) {
        chave = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

void selectionSort(int v[], int n)
{
    int i, j, menor;
    for (i = 0; i < n - 1; i++) {
        menor = i;
        for (j = i + 1; j < n; j++) {
            if (v[j] < v[menor])
                menor = j;
        }
        if (menor != i)
            trocar(&v[i], &v[menor]);
    }
}

void mergeSort(int v[], int inicio, int ultimo)
{
    int meio;
    if (inicio < ultimo) {
        meio = (inicio + ultimo) / 2;
        mergeSort(v, inicio, meio);
        mergeSort(v, meio + 1, ultimo);
        intercalar(v, inicio, meio, ultimo);
    }
}

void intercalar(int v[], int inicio, int meio, int ultimo)
{
    int aux[MAX];
    int i = inicio, j = meio + 1, k = 0;

    while (i <= meio && j <= ultimo) {
        if (v[i] <= v[j])
            aux[k++] = v[i++];
        else
            aux[k++] = v[j++];
    }
    while (i <= meio)
        aux[k++] = v[i++];
    while (j <= ultimo)
        aux[k++] = v[j++];

    for (k = 0; k <= ultimo - inicio; k++)
        v[inicio + k] = aux[k];
}

void quickSort(int v[], int inicio, int ultimo)
{
    int p;
    if (inicio < ultimo) {
        p = particionar(v, inicio, ultimo);
        quickSort(v, inicio, p - 1);
        quickSort(v, p + 1, ultimo);
    }
}

int particionar(int v[], int inicio, int ultimo)
{
    int referencia = v[ultimo];
    int i = inicio - 1;
    int j;

    for (j = inicio; j < ultimo; j++) {
        if (v[j] <= referencia) {
            i++;
            trocar(&v[i], &v[j]);
        }
    }
    trocar(&v[i + 1], &v[ultimo]);
    return i + 1;
}

const char *escolherEOrdenar(int v[], int n)
{
    int op;
    printf("\n  Algoritmos de ordenacao:\n");
    printf("   1 - Bubble Sort\n");
    printf("   2 - Insertion Sort\n");
    printf("   3 - Selection Sort\n");
    printf("   4 - Merge Sort\n");
    printf("   5 - Quick Sort\n");
    op = lerInteiro("  Escolha o algoritmo: ", 1, 5);

    switch (op) {
        case 1:  bubbleSort(v, n);        return "Bubble Sort";
        case 2:  insertionSort(v, n);     return "Insertion Sort";
        case 3:  selectionSort(v, n);     return "Selection Sort";
        case 4:  mergeSort(v, 0, n - 1);  return "Merge Sort";
        default: quickSort(v, 0, n - 1);  return "Quick Sort";
    }
}

void opcaoCriarDados(void)
{
    int v[MAX], n, i, modo;
    char msg[40];

    n = lerInteiro("Quantos valores deseja gravar (1 a 1000)? ", 1, MAX);
    modo = lerInteiro("1 - Digitar os valores | 2 - Gerar aleatorios: ", 1, 2);

    if (modo == 1) {
        for (i = 0; i < n; i++) {
            sprintf(msg, "  Valor %d: ", i + 1);
            v[i] = lerInteiro(msg, INT_MIN, INT_MAX);
        }
    } else {
        for (i = 0; i < n; i++)
            v[i] = rand() % 1000;
    }

    if (gravarArquivo(ARQ_DADOS, v, n)) {
        printf("\nArquivo gravado com sucesso em:\n  %s\n", ARQ_DADOS);
        exibirVetor("Dados gravados", v, n);
    }
}

void opcaoExibirArquivo(const char *nome)
{
    int v[MAX], n;

    n = lerArquivo(nome, v, MAX);
    if (n < 0) {
        printf("Arquivo nao existe ainda:\n  %s\n", nome);
        return;
    }
    if (n == 0) {
        printf("Arquivo vazio (ainda nao houve ordenacao):\n  %s\n", nome);
        return;
    }
    printf("\nConteudo de %s\n", nome);
    exibirVetor("Valores", v, n);
}

void opcaoOrdenar(void)
{
    int v[MAX], n;
    const char *algoritmo;

    n = lerArquivo(ARQ_DADOS, v, MAX);
    if (n <= 0) {
        printf("dados.txt nao existe ou esta vazio. Use a opcao 1 primeiro.\n");
        return;
    }

    exibirVetor("\nAntes da ordenacao", v, n);
    algoritmo = escolherEOrdenar(v, n);
    exibirVetor("\nDepois da ordenacao", v, n);

    if (gravarArquivo(ARQ_ORDENADO, v, n))
        printf("Resultado (%s) salvo em:\n  %s\n", algoritmo, ARQ_ORDENADO);
}

void opcaoAlterarValor(void)
{
    int v[MAX], n, pos, novo, i;

    n = lerArquivo(ARQ_DADOS, v, MAX);
    if (n <= 0) {
        printf("dados.txt nao existe ou esta vazio. Use a opcao 1 primeiro.\n");
        return;
    }

    printf("\nValores atuais de dados.txt:\n");
    for (i = 0; i < n; i++)
        printf("  [%d] %d\n", i + 1, v[i]);

    pos  = lerInteiro("Posicao do valor a alterar: ", 1, n);
    novo = lerInteiro("Novo valor: ", INT_MIN, INT_MAX);

    printf("Posicao %d: %d -> %d\n", pos, v[pos - 1], novo);
    v[pos - 1] = novo;

    if (!gravarArquivo(ARQ_DADOS, v, n))
        return;
    printf("dados.txt atualizado.\n");

    opcaoOrdenar();
}

int main(int argc, char *argv[])
{
    int op;

    srand((unsigned) time(NULL));
    prepararArquivos(argc > 0 ? argv[0] : "");

    do {
        printf("\n========== ORDENACAO + ARQUIVOS ==========\n");
        printf(" 1 - Criar/gravar novos valores em dados.txt\n");
        printf(" 2 - Exibir dados.txt\n");
        printf(" 3 - Ordenar dados.txt e salvar em ordenado.txt\n");
        printf(" 4 - Alterar um valor em dados.txt e reordenar\n");
        printf(" 5 - Exibir ordenado.txt\n");
        printf(" 0 - Sair\n");
        op = lerInteiro("Opcao: ", 0, 5);

        switch (op) {
            case 1: opcaoCriarDados();                 break;
            case 2: opcaoExibirArquivo(ARQ_DADOS);     break;
            case 3: opcaoOrdenar();                    break;
            case 4: opcaoAlterarValor();               break;
            case 5: opcaoExibirArquivo(ARQ_ORDENADO);  break;
            case 0: printf("Encerrando o programa.\n"); break;
        }
    } while (op != 0);

    return 0;
}
