#include <stdlib.h>
#include <stdio.h>
#include "headers.h"

/*-------------------------------------------------------------------------------------------------------------------------------------*/

Grafo* cria_Grafo(int nro_vertices, int grau_max){
  Grafo *gr=(Grafo*) malloc (sizeof(struct grafo));            //alocamos dinamicamente os elementos do Grafo
  if(gr != NULL){
    int i;
    gr->nro_vertices = nro_vertices;
    gr->grau_max = grau_max;

    gr->eh_ponderado = 1;

    gr->grau = (int*)calloc(nro_vertices, sizeof(int));
    gr->arestas = (int **)malloc(nro_vertices*sizeof(int*));

    for(i=0; i<nro_vertices; i++){
      gr->arestas[i] = (int*)malloc(grau_max*sizeof(int));
    }

    gr->pesos = (float**) malloc(nro_vertices*sizeof(float*));

    for(i = 0; i <nro_vertices; i++){
       gr->pesos[i] = (float*)malloc(grau_max*sizeof(float));
    }

  }
  printf("\033[0;33m");
  printf("\nGrafo criado com sucesso! Pronto para inserir os dados.\n\n");           //avisamos que tudo ocorreu bem
  printf("\033[0m");
  return gr;
}

/*-------------------------------------------------------------------------------------------------------------------------------------*/


void libera_Grafo(Grafo* gr){
  if(gr != NULL){
    int i;
    for(i=0; i<gr->nro_vertices; i++){
      free(gr->arestas[i]);                 //libera o que foi previamente alocado
    }
    free(gr->arestas);

    if(gr->eh_ponderado){
      for(i=0; i<gr->nro_vertices; i++){
        free(gr->pesos[i]);
      }
      free(gr->pesos);
    }
    free(gr->grau);
    free(gr);
  }
}

/*-------------------------------------------------------------------------------------------------------------------------------------*/

int insereAresta(Grafo* gr, int orig, int destino, float peso){

  if(gr == NULL){                                           //condicionais que dizem se a aresta foi adicionada ou nao
    printf("\033[1;31m");
    printf("Aresta não adicionada!\n");
    printf("\n");
    printf("\033[0m");
    return 0;
  }
  if(orig < 0 || orig >= gr->nro_vertices){
    printf("\033[1;31m");
    printf("Aresta não adicionada!\n");
    printf("\n");
    printf("\033[0m");
    return 0;
  }
  if(destino < 0 || destino >= gr->nro_vertices){
    printf("\033[1;31m");
    printf("Aresta não adicionada!\n");
    printf("\n");
    printf("\033[0m");
    return 0;
  }


  gr->arestas[orig][gr->grau[orig]] = destino;                  //atribuicao de valores
  gr->pesos[orig][gr->grau[orig]] = peso;

  gr->grau[orig]++;                    //atualizamos a origem

  //printf("\033[1;31m");
  //printf("Aresta adicionada! \n");
  //printf("\033[0m");

  return 1;
}

/*-------------------------------------------------------------------------------------------------------------------------------------*/

int removeAresta(Grafo *gr, int orig, int destino, int eh_digrafo){                   //segue funcao mesmo nao implementada na main

  if(gr == NULL){                                   //condicionais que impedem a remoção da aresta
    return 0;
  }
  if(orig < 0 || orig >= gr->nro_vertices){
    return 0;
  }
  if(destino < 0 || destino >= gr->nro_vertices){
    return 0;
  }

  int i=0;

  while (i<gr->grau[orig] && gr->arestas[orig][i] != destino){              //procura aresta
    i++;
  }

  if(i == gr->grau[orig]){          //elemento nao encontrado
    return 0;
  }

  gr->grau[orig]--;
  gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]];   //remove e desloca elemento

  if(gr->eh_ponderado){
    gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]];            //atualiza o peso
  }

  if(eh_digrafo == 0){
    removeAresta(gr, destino, orig, 1);           //remove em sentido contrario se Digrafo
  }

  return 0;
}

/*-------------------------------------------------------------------------------------------------------------------------------------*/

int menor_distancia(float *dist, int *visitado, int NumVert){       //uma funcao auxiliar da principal, no algoritmo de Dijkstra

  int i;
  int menor = -1;                                                 //atribuicao de valores
  int primeiro = 1;

  for(i=0; i<NumVert; i++){
    if(dist[i] >= 0 && visitado[i] == 0){           //procura vertice nao visitado mais perto
      if(primeiro){
        menor = i;                                   //menor eh atualizado quando necessario
        primeiro = 0;
      }
      else{
        if(dist[menor] > dist[i]){
          menor = i;                           //buscamnos a menor distancia por meio de comparações
       }
      }
    }
  }
  return menor;                //retorna esse vertice
}

/*-------------------------------------------------------------------------------------------------------------------------------------*/

void dijkstra_caminho(Grafo *gr, int inicial, int *ant, float *distancia, double *pes){
  int i, cont, NumVert, indice, *visitado, u;
  cont = NumVert = gr->nro_vertices;                     //auxiliar contador de numero de vertices

  visitado = (int*) malloc(NumVert * sizeof(int));

  for(i=0; i<NumVert; i++){                        //cria vetor auxiliar, inicializa distancias
    ant[i] = -1;
    distancia[i] = -1;
    visitado[i] = 0;
  }

  distancia[inicial] = 0;

  while(cont > 0){

    u = menor_distancia(distancia, visitado, NumVert);      //procura vertices com menor distancia e o marca como visitado
    if(u == -1){
      break;
    }
    visitado[u] = 1;
    cont--;

    for(i=0; i<gr->grau[u]; i++){                     //atualiza distancias para cada vertice vizinho
      indice = gr->arestas[u][i];
      if(distancia[indice] < 0){
        distancia[indice] = distancia[u] + gr->pesos[u][i];
        ant[indice]=u;
        pes[indice] = gr->pesos[u][i];
      }
      else{
        if(distancia[indice] > distancia[u] + gr->pesos[u][i]){
        distancia[indice] = distancia[u] + gr->pesos[u][i];
        ant[indice] = u;
        pes[indice] = gr->pesos[u][i];
        }
      }
    }
  }

  free(visitado);
}

/*-------------------------------------------------------------------------------------------------------------------------------------*/

void algPRIM(Grafo *gr, int orig, int *pai, long double *Pesototal, double *pesP){

    int i, j, dest, primeiro, NumVert = gr->nro_vertices;
    double menorPeso, aux = 0;;

    for(i=0; i<NumVert; i++){
      pai[i] = -1;                 //vertices nao tem pai
    }
    pai[orig] = orig;
    while(1){           //percorremos todo o grafo
      primeiro = 1;

      for(i=1; i<NumVert; i++){
        if(pai[i] != -1){                    //achamos o que foi visitado
          for(j=0; j<gr->grau[i]; j++){
            if(pai[gr->arestas[i][j]] == -1){ //percorremos seus vizinhos e achamos o menor peso
              if(primeiro){
                menorPeso = gr->pesos[i][j];
                orig = i;
                dest = gr->arestas[i][j];
                primeiro = 0;
              }
              else{
                if(menorPeso > gr->pesos[i][j]){
                  menorPeso = gr->pesos[i][j];
                  orig = i;
                  dest = gr->arestas[i][j];
                }
              }
            }
          }
        }
      }
      if(primeiro == 1){
        break;
      }

/*
      printf("\033[1;34m");
      printf("Menor Peso: %.2lf\n", menorPeso);
      printf("\033[0m");

*/
      pai[dest] = orig;
      pesP[dest] = menorPeso;
      aux = *Pesototal;
      *Pesototal = aux + menorPeso;
    }

  printf("\n");
}

/*-------------------------------------------------------------------------------------------------------------------------------------*/
