# Ordenação + Arquivos em C

**Atividade Avaliativa 03** — Algoritmos de Ordenação e Manipulação de Arquivos em C

Programa em C que grava números desordenados num arquivo, lê esses números, ordena com o algoritmo escolhido pelo usuário (Bubble, Insertion, Selection, Merge ou Quick Sort) e salva o resultado num segundo arquivo. Também permite alterar um valor no arquivo original e reordenar.

## Integrantes

| Nome | RGM |
|---|---|
| Vinícius Santos Conceição | 47451530 |
| Bruna Soares de Almeida | 47552158 |
| Vinícius Henrique Silva Ferreira | 47449438 |
| Eduardo Silva Morishita | 48501883 |

## Requisitos atendidos

| # | Requisito | Onde no programa |
|---|---|---|
| 1 | Criar e gravar arquivo com dados desordenados | Menu 1 → `opcaoCriarDados()` |
| 2 | Ler os dados do arquivo | `lerArquivo()` (menus 2, 3, 4 e 5) |
| 3 | Escolher o tipo de ordenação | `escolherEOrdenar()` |
| 4 | Ordenar e salvar em um novo arquivo | Menu 3 → `opcaoOrdenar()` |
| 5 | Alterar um valor no arquivo e reordenar | Menu 4 → `opcaoAlterarValor()` |

## Arquivos do repositório

| Arquivo | Conteúdo |
|---|---|
| `ordenacao_arquivos.c` | Código-fonte do programa |
| `documentacao.txt` | Documentação detalhada de todas as funções |
| `teste_de_mesa.docx` | Teste de mesa dos 5 algoritmos com o vetor `[7, 2, 9, 4, 1]` |
| `README.md` | Este arquivo |

## Como compilar e executar

**Linux / macOS**

```bash
gcc ordenacao_arquivos.c -o ordenacao
./ordenacao
```

**Windows (Dev-C++ / Code::Blocks)**

Abra `ordenacao_arquivos.c` e use **Compilar e Executar**.

O código segue o padrão **C89/ANSI** e compila sem avisos com `gcc -std=c89 -pedantic -Wall -Wextra`, inclusive em compiladores antigos.

## Onde os dados são salvos

Ao abrir, o programa cria sozinho a pasta `arquivos_ordenacao` **ao lado do executável**, com os arquivos abaixo, e mostra o caminho completo de cada um na tela.

```
<pasta do executável>/
└── arquivos_ordenacao/
    ├── dados.txt      ← valores originais (desordenados)
    └── ordenado.txt   ← valores ordenados
```

- `dados.txt` é criado na primeira execução com 10 valores aleatórios e só muda pelos menus 1 e 4.
- `ordenado.txt` é regravado a cada ordenação. O arquivo original nunca é ordenado.
- Formato: texto puro, **um número inteiro por linha**.

> ⚠️ **Compiladores online (OnlineGDB, Programiz etc.):** o programa roda num servidor, e os arquivos ficam numa pasta temporária que é apagada ao final. Eles existem e são lidos pelo programa (menus 2 e 5), mas não aparecem no seu computador. Para ver os arquivos, compile e execute localmente.

## Menu

```
========== ORDENACAO + ARQUIVOS ==========
 1 - Criar/gravar novos valores em dados.txt
 2 - Exibir dados.txt
 3 - Ordenar dados.txt e salvar em ordenado.txt
 4 - Alterar um valor em dados.txt e reordenar
 5 - Exibir ordenado.txt
 0 - Sair
```

- **Menu 1:** pede a quantidade (1 a 1000) e se os valores serão digitados ou gerados aleatoriamente (0 a 999).
- **Menu 3:** mostra o vetor antes e depois, pede o algoritmo e grava o resultado.
- **Menu 4:** lista os valores com a posição (1 a n), altera o valor escolhido, regrava `dados.txt` e reordena.

## Exemplo de uso

```
Opcao: 1
Quantos valores deseja gravar (1 a 1000)? 5
1 - Digitar os valores | 2 - Gerar aleatorios: 1
  Valor 1: 7
  Valor 2: 2
  Valor 3: 9
  Valor 4: 4
  Valor 5: 1

Opcao: 3
Antes da ordenacao (5 valores):
     7     2     9     4     1
  Escolha o algoritmo: 5
Depois da ordenacao (5 valores):
     1     2     4     7     9
Resultado (Quick Sort) salvo em:
  .../arquivos_ordenacao/ordenado.txt
```

## Algoritmos implementados

Todos ordenam em ordem **crescente**, direto no vetor.

| Algoritmo | Ideia | Melhor | Médio | Pior | Estável |
|---|---|---|---|---|---|
| **Bubble Sort** | Troca vizinhos fora de ordem; o maior "sobe" para o fim. Para cedo se uma passada não troca nada. | O(n) | O(n²) | O(n²) | Sim |
| **Insertion Sort** | Encaixa cada número na parte já ordenada, deslizando os maiores para a direita. | O(n) | O(n²) | O(n²) | Sim |
| **Selection Sort** | Procura o menor restante e coloca na próxima posição. | O(n²) | O(n²) | O(n²) | Não |
| **Merge Sort** | Divide ao meio até sobrar 1 número e depois junta as metades ordenadas. | O(n log n) | O(n log n) | O(n log n) | Sim |
| **Quick Sort** | Usa o último número do trecho como referência (pivô), separa menores à esquerda e maiores à direita, e repete em cada lado (partição de Lomuto). | O(n log n) | O(n log n) | O(n²) | Não |

> No Quick Sort, o pior caso acontece quando o vetor já está ordenado ou invertido, por causa da escolha do último elemento como pivô.

## Estrutura do código

| Grupo | Funções |
|---|---|
| Entrada pelo teclado | `limparBuffer`, `lerInteiro` |
| Arquivos | `prepararArquivos`, `gravarArquivo`, `lerArquivo`, `exibirVetor` |
| Ordenação | `trocar`, `bubbleSort`, `insertionSort`, `selectionSort`, `mergeSort`, `intercalar`, `quickSort`, `particionar`, `escolherEOrdenar` |
| Menu | `opcaoCriarDados`, `opcaoExibirArquivo`, `opcaoOrdenar`, `opcaoAlterarValor`, `main` |

Os detalhes de cada função estão em [`documentacao.txt`](documentacao.txt).

## Tratamento de erros

- Entrada não numérica ou fora do intervalo: mostra uma mensagem e pede de novo.
- Ordenar ou alterar sem dados: avisa para usar o menu 1.
- Falha ao gravar na pasta do executável: usa a pasta atual como reserva.
- Fim da entrada (EOF): encerra o programa em vez de entrar em loop.

## Limitações

- Máximo de **1000** valores (constante `MAX`).
- Apenas números **inteiros** (`int`).
- A alteração (menu 4) é feita pela **posição**, não pelo valor, para evitar ambiguidade com valores repetidos.

## Testes realizados

- Os 5 algoritmos com 500 a 800 valores aleatórios: resultado conferido contra a ordenação esperada.
- Casos de borda: 1 valor e valores repetidos.
- Fluxo completo: criar `[7, 2, 9, 4, 1]`, ordenar, alterar a posição 3 (9 → 3) e reordenar, resultando em `[1, 2, 3, 4, 7]`.
- Programa executado a partir de outra pasta (como faz uma IDE): os arquivos foram criados ao lado do executável.
- Teste de mesa manual dos 5 algoritmos em `teste_de_mesa.docx`.
