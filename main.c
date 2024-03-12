/* 
 * REPRESENTACAO DE GRAFOS - Versao 2024/1
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <memory.h>


/* 
 * Estrutura de dados para representar grafos
 */
typedef struct arst{ /* Celula de uma lista de arestas */
	int    nome;
	struct arst *prox;
}Aresta;

typedef struct vert{  /* Cada vertice tem um ponteiro para uma lista de arestas incidentes nele */
	int nome;
	Aresta *prim;
}Vertice;

/*
 * Declaracoes das funcoes para manipulacao de grafos 
 */
void criarGrafo(Vertice **G, int ordem);
void destruirGrafo(Vertice **G, int ordem);
int  incluirAresta(Vertice G[], int ordem, int v1, int v2);
void imprimirGrafo(Vertice G[], int ordem);

 
/*
 * Criacao de um grafo com ordem predefinida (passada como argumento),
 *   e, inicilamente, sem nenhuma aresta 
 */
void criarGrafo(Vertice **G, int ordem){
	int i;
	*G= (Vertice*) malloc(sizeof(Vertice)*ordem); /* Alcacao dinamica de um vetor de vertices */
	
	for(i=0; i<ordem; i++){
		(*G)[i].nome= i;
		(*G)[i].prim= NULL;    /* Cada vertice sem nenua aresta incidente */
	}
}

/*
 * Deasaloca a memoria dinamica usada para armazenar um grafo.
 */
void destruirGrafo(Vertice **G, int ordem){
	int i;
    Aresta *a, *n;
    
	for(i=0; i<ordem; i++){ /* Remove lista de adjacencia de cada vertice */
	    a= (*G)[i].prim;
        while (a!= NULL){
              n= a->prox;
              free(a);
              a= n;
        }
	}
    free(*G);
}

/*  
 * Acrescenta uma nova aresta em um grafo previamente criado. 
 *   Devem ser passados os extremos v1 e v2 da aresta a ser acrescentada 
 * Como o grafo nao e orientado, para uma aresta com extremos i e j
 *   serao criadas, na estrutura de dados, arestas (i,j) e (j,i)
 */
int incluirAresta(Vertice G[], int ordem, int v1, int v2){
    Aresta * A1, *A2;
    
	if (v1<0 || v1 >= ordem) /* Testo se vertices sao validos */
	   return 0;
	if (v2<0 || v2 >= ordem)
	   return 0;
	
	/* Acrescento aresta na lista do vertice v1 */
	A1= (Aresta *) malloc(sizeof(Aresta));
	A1->nome= v2;
	A1->prox= G[v1].prim;
	G[v1].prim= A1;

	if (v1 == v2) return 1; /* Aresta e� um laco */

	/* Acrescento aresta na lista do vertice v2 se v2 != v1 */	
	A2= (Aresta *) malloc(sizeof(Aresta));
	A2->nome= v1;
	A2->prox= G[v2].prim;
	G[v2].prim= A2;
	
	return 1;
}


/*  
 * Imprime um grafo com uma notacao similar a uma lista de adjacencia.
 */
void imprimirGrafo(Vertice G[], int ordem){
	int i;
	Aresta *aux;

	printf("\nOrdem:   %d",ordem);
	printf("\nLista de Adjacencia:\n");

	for (i=0; i<ordem; i++){
		printf("\n    v%d: ", i);
		aux= G[i].prim;
		for( ; aux != NULL; aux= aux->prox)
			printf("  v%d", aux->nome);
	}
	printf("\n\n");
}

/*
 * Programa simples simples para testar a representacao de grafo
 */
int main(int argc, char *argv[]) {
    int i;
	Vertice *G;
	int ordemG= 8; 
		
	criarGrafo(&G, ordemG);
	incluirAresta(G,ordemG,0,0);
	incluirAresta(G,ordemG,0,1);
	incluirAresta(G,ordemG,0,1);
	incluirAresta(G,ordemG,0,2);
	incluirAresta(G,ordemG,0,3);
	incluirAresta(G,ordemG,2,4);
	incluirAresta(G,ordemG,2,5);
	incluirAresta(G,ordemG,3,5);
	incluirAresta(G,ordemG,4,5);
	incluirAresta(G,ordemG,6,7);

	imprimirGrafo(G, ordemG);
       
	destruirGrafo(&G, ordemG);
    system("PAUSE");
	return 0;
}
