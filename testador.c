/** @file testador.c
 * @brief Programa para início da execução do algoritmo.
 * 
 * O teste, que será feito para calcular a nota, será feito com uma versão 
 * ampliada deste programa. Esta é uma versão de referência para mostrar como
 * os testes serão executados. Note que podem ser feitas várias execuções em
 * sequência.
 * 
 * No EP, espera-se que o aluno implemente uma solução por tentativa e erro
 * (backtracking) para esta variação do Problema do Caixeiro Viajante.
 * 
 * \image latex /home/fabio/Documentos/IAA-2021/EP-Hamiltoniano/guloso/Captura2021-09-14.png "Captura de tela do editor online do Mermaid processando o texto de saída do programa"
 * \image latex /home/fabio/Documentos/IAA-2021/EP-Hamiltoniano/guloso/mermaid-diagram-20210914191457.png "grafo gerado com circuito hamiltoniano e completado com arestas geradas aleatoriamente"
 * \image latex /home/fabio/Documentos/IAA-2021/EP-Hamiltoniano/guloso/mermaid-diagram-20210914191644.png "o mesmo grafo, após a execução do algoritmo. Em linha cheia as arestas que fazem parte do circuito hamiltoniano, em pontilhado as arestas que não fazem parte. Neste caso específico, a ordem das arestas e o algoritmo de seleção são tais que o circuito é encontrado"
 *  
 * @author Fábio Nakano
 * @date 2021-09-14
 * 
 */
#include "ep.h"

#define NV 10
#define NA 20

void main (void) {
    struct grafo *G;
    
    // Teste 1 - Grafo aleatório com peso variado
    G = criaGrafo(NV, NA);
    preencheHamiltonianoAleatorio(G, 0, 0);  // Peso aleatório, orientado por padrão
    imprimeGrafoMermaid(G, NULL);
    puts(autor());
    if (iniciaEexecuta(G, 0)) {
        puts("Encontrou solução.");
        imprimeGrafoMermaid(G, G->S);
    } else {
        puts("Não encontrou solução.");
    }
    termina();
    free(G);
    
    // Teste 2 - Grafo com peso fixo e possibilidade de ciclos
    G = criaGrafo(NV, NA);
    preencheHamiltonianoAleatorio(G, 1, 0);  // Peso fixo, orientado por padrão
    imprimeGrafoMermaid(G, NULL);
    puts(autor());
    if (iniciaEexecuta(G, 0)) {
        puts("Encontrou solução.");
        imprimeGrafoMermaid(G, G->S);
    } else {
        puts("Não encontrou solução.");
    }
    termina();
    free(G);

    // Teste 3 - Grafo mais denso (número de arestas aumentado)
    G = criaGrafo(NV, NA + 10);  // Adicionando mais arestas
    preencheHamiltonianoAleatorio(G, 1, 0);  // Peso fixo
    imprimeGrafoMermaid(G, NULL);
    puts(autor());
    if (iniciaEexecuta(G, 0)) {
        puts("Encontrou solução.");
        imprimeGrafoMermaid(G, G->S);
    } else {
        puts("Não encontrou solução.");
    }
    termina();
    free(G);

    // Teste 4 - Grafo com menor número de arestas (mais esparso)
    G = criaGrafo(NV, NA - 10);  // Diminuindo arestas, mais esparso
    preencheHamiltonianoAleatorio(G, 1, 1);  // Peso fixo, direcionado
    imprimeGrafoMermaid(G, NULL);
    puts(autor());
    if (iniciaEexecuta(G, 0)) {
        puts("Encontrou solução.");
        imprimeGrafoMermaid(G, G->S);
    } else {
        puts("Não encontrou solução.");
    }
    termina();
    free(G);

    // Teste 5 - Grafo completo (NV*(NV-1)/2 arestas)
    G = criaGrafo(NV, NV * (NV - 1) / 2);  // Grafo completo
    preencheHamiltonianoAleatorio(G, 0, 1);  // Peso aleatório, direcionado
    imprimeGrafoMermaid(G, NULL);
    puts(autor());
    if (iniciaEexecuta(G, 0)) {
        puts("Encontrou solução.");
        imprimeGrafoMermaid(G, G->S);
    } else {
        puts("Não encontrou solução.");
    }
    termina();
    free(G);

    // Teste 6 - Grafo com alguns vértices isolados (caminho incompleto)
    G = criaGrafo(NV, NV / 2);  // Menos arestas, provável ausência de caminho
    preencheHamiltonianoAleatorio(G, 1, 1);  // Peso fixo, direcionado
    imprimeGrafoMermaid(G, NULL);
    puts(autor());
    if (iniciaEexecuta(G, 0)) {
        puts("Encontrou solução.");
        imprimeGrafoMermaid(G, G->S);
    } else {
        puts("Não encontrou solução.");
    }
    termina();
    free(G);
}

