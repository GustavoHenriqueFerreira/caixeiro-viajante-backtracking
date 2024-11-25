/**
 * @file ep.c
 * @brief Contém uma aplicação da estratégia de tentativa e erro (backtracking).
 * @author Gustavo Henrique Ferreira Alves NUSP 15674466
 */
#include "ep.h"

#define TRUE 1
#define FALSE 0
#define Boolean int

int *arestaUtilizada;      // vetor que indicará se as arestas do grafo já foram usadas ou não
int *arestaUtilizadaMenorSolucaoEncontrada; // vetor que indica o estado do grafo quando encontra-se a menor solucao
int *grauDoVertice;    // vetor que armazenará o grau de cada vértice (quantas arestas estão conectadas a ele)
int menorCusto = -1;   // variável global para armazenar o menor custo encontrado no caminho (inicialmente não encontrado)

char *autor(void) {
    return "Gustavo Henrique Ferreira Alves ; 15674466";
}

// função que verifica se todos os vértices têm grau 2 (ou seja, caso tenha tido uma visita na ida e a outra na volta da recursao), o que significa que o caminho é um caminho hamiltoniano válido
Boolean ehSolucao(struct grafo *G) {
    for (int i = 0; i < G->N; i++) {  // G->N é o número de vértices do grafo
        if (grauDoVertice[i] != 2) return FALSE;  // se algum vértice não tiver grau 2, não é uma solução
    }
    return TRUE;  // se todos os vértices têm grau 2, então é uma solução válida
}

// função que verifica se a aresta pode ser usada para continuar o caminho
Boolean ehAceitavel(struct grafo *G, int arestaParaTestar, int verticeAtual) {
    if (arestaUtilizada[arestaParaTestar]) return FALSE;  // ae a aresta já foi usada, não pode ser usada novamente

    int origem = G->A[3 * arestaParaTestar];  // o vértice de origem da aresta
    int destino = G->A[3 * arestaParaTestar + 1];  // o vértice de destino da aresta

    // verifica se a aresta é aceitável em ambas as direções (grafo não-direcional)
    if ((origem == verticeAtual && grauDoVertice[destino] < 2) || 
        (destino == verticeAtual && grauDoVertice[origem] < 2)) {
        return TRUE;  // se a aresta pode ser usada, então o poderá continuar o caminho
    }

    return FALSE;  // caso contrário, a aresta não pode ser usada
}

// função que "aumenta" o caminho, ou seja, inclui uma aresta no caminho atual e atualiza os graus dos vértices
int aumentarCaminho(struct grafo *G, int arestaParaAcrescentar, int verticeAtual) {
    int origem = G->A[3 * arestaParaAcrescentar];  // pega o vértice de origem da aresta
    int destino = G->A[3 * arestaParaAcrescentar + 1];  // pega o vértice de destino da aresta

    arestaUtilizada[arestaParaAcrescentar] = TRUE;  // marca a aresta como usada.
    grauDoVertice[origem]++;  // aumenta o grau do vértice de origem.
    grauDoVertice[destino]++;  // aumenta o grau do vértice de destino.

    // retorna o próximo vértice do caminho, independente do sentido devido ao grafo não-direcional 
    return (origem == verticeAtual) ? destino : origem;
}

// função que "remove" a aresta do caminho, ou seja, desfaz a adição da aresta e reverte os graus dos vértices
void removerCaminho(struct grafo *G, int arestaParaRemover) {
    int origem = G->A[3 * arestaParaRemover];  // pega o vértice de origem da aresta
    int destino = G->A[3 * arestaParaRemover + 1];  // pega o vértice de destino da aresta

    arestaUtilizada[arestaParaRemover] = FALSE;  // marca a aresta como não usada
    grauDoVertice[origem]--;  // diminui o grau do vértice de origem
    grauDoVertice[destino]--;  // diminui o grau do vértice de destino
}

// função de backtracking (tentativa e erro) para tentar encontrar o caminho de menor custo
Boolean realizarBacktracking(struct grafo *G, int verticeAtual, int numeroArestasUsadas, int custoAtual) {
    // verifica se já foram usadas todas as arestas e se a solução é válida
    if (G->N == numeroArestasUsadas && ehSolucao(G)) {
        if (menorCusto == -1 || custoAtual < menorCusto) {
            menorCusto = custoAtual;  // atualiza o menor custo se necessário
        }

        for (int i = 0; i < G->M; i++) {
            arestaUtilizadaMenorSolucaoEncontrada[i] = arestaUtilizada[i]; // copia o estado do grafo quando encontra-se a menor solucao
        }
        
        return TRUE;  // se encontrar uma solução válida, retorna TRUE
    }

    Boolean encontrouSolucao = FALSE;

    // tenta cada aresta possível para ver se ela pode ser adicionada ao caminho
    for (int aresta = 0; aresta < G->M; aresta++) {  // G->M é o número de arestas do grafo
        if (ehAceitavel(G, aresta, verticeAtual)) {  // se a aresta for aceitável para o caminho atual
            int proximoVertice = aumentarCaminho(G, aresta, verticeAtual);  // aumenta o caminho com a aresta
            int custoAresta = G->A[3 * aresta + 2]; 

            // se o custo atual somado ao custo da aresta for menor que o menor custo encontrado, continua a busca
            if (menorCusto == -1 || custoAtual + custoAresta < menorCusto) {
                encontrouSolucao = realizarBacktracking(G, proximoVertice, numeroArestasUsadas + 1, custoAtual + custoAresta) || encontrouSolucao;
            }

            removerCaminho(G, aresta);  // se não encontrar uma solução, remove a aresta do caminho
        }
    }

    return encontrouSolucao;  // retorna se uma solução foi encontrada ou não
}

int iniciaEexecuta(struct grafo *G, int verticeInicial) {
    grauDoVertice = calloc(G->N, sizeof(int));  
    arestaUtilizada = calloc(G->M, sizeof(int)); 
    arestaUtilizadaMenorSolucaoEncontrada = calloc(G->M, sizeof(int)); 

    menorCusto = -1;  // inicializa o menor custo como não encontrado
    int resultado = realizarBacktracking(G, verticeInicial, 0, 0);  // chama o backtracking começando pelo vértice inicial

    if (resultado && menorCusto != -1) {
        printf("Menor custo encontrado: %d\n", menorCusto);  // se encontrar uma solução, imprime o menor custo
    } else {
        puts("Não achou solução");  // se não encontrar uma solução, imprime uma mensagem de erro
    }

    // atualiza o vetor de arestas do grafo com as arestas usadas no caminho encontrado
    for (int i = 0; i < G->M; i++) {
        G->S[i] = arestaUtilizadaMenorSolucaoEncontrada[i];  // G->S é o vetor de arestas usadas no grafo
    }

    return resultado;  // retorna se foi encontrada uma solução
}

void termina() {
    free(grauDoVertice); 
    free(arestaUtilizada); 
    free(arestaUtilizadaMenorSolucaoEncontrada);
}