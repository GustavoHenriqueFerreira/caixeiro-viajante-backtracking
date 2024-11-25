# Problema do Caixeiro Viajante (Versão com Estratégia Gulosa e Backtracking)
Este projeto implementa uma solução para uma variação do problema clássico do Caixeiro Viajante. O problema consiste em encontrar um ciclo hamiltoniano em um grafo, onde o caixeiro deve visitar todas as cidades exatamente uma vez e retornar à cidade de origem, com o menor custo possível.

## Descrição do Projeto
Este programa aplica uma abordagem gulosa inicial, seguida de uma solução por tentativa e erro (backtracking), para resolver o problema do Caixeiro Viajante. A solução utiliza um grafo para representar o mapa de cidades e estradas, onde:

- **Vértices** representam as cidades.
- **Arestas** representam as estradas entre as cidades.
O ciclo hamiltoniano, que é o caminho que o caixeiro deve seguir, é determinado ao tentar visitar todas as cidades de forma eficiente, minimizando o custo total da rota.

## Estrutura do Código
O programa é modularizado em diferentes arquivos, cada um com uma função específica para resolver o problema:

### Arquivos:
- grafo.{c,h}: Contém as definições das estruturas de dados para representar grafos e as funções para manipulação dessas estruturas.
- ep.h: Especificação que deve ser implementada para que a solução proposta possa ser avaliada.
- ep.c: Implementação da estratégia de backtracking para encontrar o ciclo hamiltoniano com menor custo.
- testador.c: Programa de teste que inicia a execução do algoritmo e verifica se a solução proposta encontra o ciclo hamiltoniano.

### Algoritmo:
1. **Estratégia Gulosa Inicial**: O algoritmo começa selecionando um conjunto vazio de arestas e tenta adicionar as arestas, uma de cada vez, de acordo com a ordem das arestas fornecida. A cada adição, o algoritmo verifica se o caminho já é uma solução válida. Caso contrário, ele tenta outras arestas.

2. **Backtracking**: Quando o algoritmo guloso não encontra a solução ideal, é aplicado o backtracking para tentar todas as possibilidades e encontrar a rota com o menor custo. O backtracking explora todas as arestas possíveis e remove as opções quando uma solução não é válida.

3. **Verificação de Solução**: A solução é válida quando todos os vértices possuem grau 2, indicando que o caixeiro visitou todas as cidades exatamente uma vez e retornou à cidade inicial.

4. **Cálculo do Custo**: O custo de cada aresta é armazenado, e o menor custo encontrado é reportado ao final da execução.

### Funções Principais:
- ehSolucao: Verifica se o caminho atual é um ciclo hamiltoniano válido.
- ehAceitavel: Verifica se uma aresta pode ser adicionada ao caminho atual, garantindo que não se formem ciclos prematuros.
- aumentarCaminho: Adiciona uma aresta ao caminho e atualiza os graus dos vértices.
- removerCaminho: Remove uma aresta do caminho e reverte as alterações nos vértices.
- realizarBacktracking: Implementa a estratégia de backtracking para explorar todas as possíveis soluções.
- iniciaEexecuta: Inicializa o algoritmo e executa o backtracking a partir do vértice inicial.

## Execução
### Requisitos:
- **Compilador C**: O programa é escrito em C e pode ser compilado com qualquer compilador C padrão.
- **Bibliotecas**: O código depende de bibliotecas padrão de C para alocação dinâmica de memória, impressão e controle de fluxo.

### Como Rodar:
1. Compile o programa:
```bash
gcc -o caixeiro_viajante ep.c testador.c -lm
```
2. Execute o programa:
```bash
./caixeiro_viajante
```
### Saída Esperada:
O programa tentará encontrar uma solução para o problema do Caixeiro Viajante e, se encontrar, exibirá o menor custo encontrado. Caso contrário, será exibida uma mensagem informando que não foi encontrada uma solução.

Exemplo de saída:
```yaml
Menor custo encontrado: 120
Encontrou solução.
```

### Testes:
O arquivo testador.c contém exemplos de execução com grafos aleatórios e com pesos variados. O teste verifica se o algoritmo é capaz de encontrar o ciclo hamiltoniano correto em diferentes cenários.

## Função de Teste:
- **Teste 1**: Grafo aleatório com pesos variáveis.
- **Teste 2**: Grafo com peso fixo e possibilidade de ciclos.

## Considerações Finais
Este projeto implementa uma solução eficaz para o problema do Caixeiro Viajante utilizando uma combinação de abordagens gulosa e backtracking. Embora a abordagem gulosa possa não ser a solução ótima, ela serve como uma boa heurística inicial para reduzir o número de tentativas do algoritmo de backtracking.