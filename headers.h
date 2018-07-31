#include <stdlib.h>
#include <stdio.h>


typedef struct grafo{
  int eh_ponderado;
  int nro_vertices;
  int grau_max;                          //declarando o grafo, e o tipo "Grafo"
  int** arestas;                         //o grafo apresenta diferentes propriedades, como peso, grau, numero de vertices, etc.
  float** pesos;
  int* grau;
} Grafo;

Grafo *cria_Grafo(int nro_vertices, int grau_max);

void libera_Grafo(Grafo *gr);

int insereAresta(Grafo *gr, int orig, int destino, float peso);

int removeAresta(Grafo *gr, int orig, int destino, int eh_digrafo);

int menor_distancia(float *dist, int *visitado, int NumVert);

void dijkstra_caminho(Grafo *gr, int inicial, int *ant, float *distancia, double *pes);        /*ant eh o anterior aquele vertice (ordem) e o dist sao as distancias entre eles*/

void algPRIM(Grafo *gr, int orig, int *pai, long double *Pesototal, double *pesP);
