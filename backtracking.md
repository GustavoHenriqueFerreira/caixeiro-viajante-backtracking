# Backtracking

## Panorama 
- Tentar passos em direcao a solucao final
- Armazenar tentativas em uma estrutura de dados
- Caso os passos tomados nao levem a solucao, podem ser removidos da e.d. final

# Exploracao
- Testar possibilidade
- Se valida, retorna sucesso
- Senao, e caso nao houver outra a ser testada, retorna falha
- P/ cada possibilidade (a partir da atual):
    - explore a nova possibilidade
    - se resposta, retorne sucesso
- Retorne falha (nenhum caso de sucesso ao final da recursao)

## Qual a diferenca entre os dois algoritmos nesse caso?
Primeiro vamos dar um panorama de cada funcao

ehAceitavel:
- Vamos testar uma aresta
- Ela nao pode ja ter sido visitada
- Essa aresta precisa conectar com o vertice atual
- Os vertices dessa aresta precisam ter a contagem de grau igual a 2 durante o percurso
    - Isso indica que, em um unico caminho, essa aresta foi percorrida apenas uma vez, conectando dois vertices

aumentaCaminho:
- Vamos aumentar o caminho de uma aresta
- Marcamos essa aresta como visitada
- Acrescentamos o grau dos vertices dessa aresta em 1
- Retornamos o vertice da outra extremidade da aresta para continuacao do caminho

### Estrategia Gulosa
- Percorremos cada aresta uma unica vez (loop de 0 ate G->M)
    - C = C - x
    - Remove a selecao do conjunto de alternativas
- Executamos ate encontrar solucao ou acabarem as alternativas
- Se a aresta eh aceitavel, aumentamos o caminho e retornamos o prox vertice
- O prox vertice sera calculado com a prox aresta
- Comecamos sempre do vertice zero
- Comecamos sempre da aresta zero 
    - O vetor de arestas nao esta necessariamente ordenado

**Como funciona**:
- Depende do vetor de arestas estar ordenado
    - Arestas intermediarias (com vertices de grau > 1) podem causar o algoritmo a falhar
- Isso porque percorremos cada aresta apenas uma vez, selecionando sempre o que vem primeiro no vetor de arestas
- Nunca voltamos atras

### Estrategia de Backtracking
- Tentamos percorrer todas as arestas, enquanto 
    - (i) elas forem validas
    - (ii) ainda nao comporem uma solucao
    - (iii) ainda houverem opcoes (arestas) a serem testadas
- Caso nao seja valida, voltamos atras e removemos a escolha da lista do conjunto solucao
- Caso nao haja mais opcoes e ainda nao tivermos uma solucao, retornamos que nao existem solucoes
- Caso contrario, retorna que existe solucao
- O algoritmo modifica o vetor global arestaUsada e no fim, transfere a solucao para G->S, que determina no grafo quais arestas compoem o caminho que resolve o problema

### Comparacao entre os dois algoritmos
No teste 1, temos um vetor de arestas ja ordenado:

graph TD
0 ---|383| 1
1 ---|886| 2
2 ---|777| 3
3 ---|915| 4
4 ---|793| 5
5 ---|335| 6
6 ---|386| 7
7 ---|492| 8
8 ---|649| 9
9 ---|421| 0
 
- Ambos os algoritmos sao capazes de resolver o problema. Comecam no vertice 0 e aresta "0" (de peso 383)
- Ambos os algoritmos retornam assim que acham solucao, e levam o mesmo tempo pois nao precisam voltar atras nesse caso
- O caso em questao eh o caminho mais feliz para resolver o problema. O caminho ja esta "achado" e esta na ordem dos primeiros elementos do array.
- Ambos os algoritmos (nesse caso) executam (salvo os detalhes minimos que implementa cada conceito) as mesmas operacoes

Ja no teste 2, temos um vetor de arestas que nao constitui o caminho ideal:

graph TD
3 ---|91| 6
5 ---|729| 6
5 ---|545| 2
6 ---|198| 7
4 ---|784| 5
1 ---|925| 5
8 ---|315| 9
4 ---|750| 3
0 ---|873| 6
2 ---|421| 3
1 ---|373| 2
0 ---|229| 1
4 ---|434| 7
7 ---|324| 8
3 ---|124| 7
2 ---|996| 0
4 ---|336| 7
9 ---|370| 0
5 ---|537| 6
3 ---|919| 4

- A ordem do vetor de arestas nao segue a ordem natural dos vertices
- Eh preciso "voltar atras" em diversos casos
    - Ha arestas intermediarias (e invalidas!) entre arestas que compoem a solucao
- O algoritmo guloso nao volta atras. Portanto, ao encontrar uma aresta invalida, tenta a proxima.
    - Se nao houver proxima (no sentido literal do sentido que segue a leitura do array), retorna que nao ha solucoes
- O algoritmo de backtracking volta atras, caso encontre arestas "intermediarias" invalidas.
    - Testa todas as opcoes possiveis de um determinado local (diferente do guloso que so vai atras do "melhor", nesse caso, o mais proximo na leitura do array)

Dessa forma, no teste 2, o algoritmo de backtracking consegue resolver o problema, enquanto o guloso nao encontra solucoes