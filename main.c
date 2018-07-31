#include <stdlib.h>
#include <stdio.h>
#include "headers.h"
#include <time.h>


/*
Feito por:

Guilherme Braga Pinto
Gabriel Matheus da Rocha de Oliveira

Last Update: 26/06/2018
UnB
*/


int main(){

/*-------------------------------------------------------------------------------------------------------------------------------------*/


  clock_t Ticks[2];
  Ticks[0] = clock();       //inicio da funcao que pega o tempo

  int aux_vertices;
  int aux_grau_max;
  int i, j, op1, op2, tes, cont = 0;
  int aux_origem = 0;
  int aux_destino = 0;
  int primeiro_vertice = 0;                  //declarações
  float aux_peso = 0;
  long double Pesototal = 0;
  int opt = 0;



  FILE *file1;
  file1 = fopen("dados.txt", "r");               //abrindo o arquivo do grafo

  FILE *file2;
  file2 = fopen("resultado.txt", "w");       // criando/reescrevendo arquivo de resultado

  fscanf(file1, "%d", &aux_vertices);
  aux_vertices++;
  aux_grau_max = (aux_vertices - 1);                      //scaneia o vertice, grau maximo de cada vertice eh seu "limite" menos 1 (ele mesmo)
  Grafo *gr = cria_Grafo(aux_vertices, aux_grau_max);     //cria Grafo

  int ant[aux_vertices];
  float distancia[aux_vertices];
  int pai[aux_vertices];
  int caminho[aux_vertices];            //declarações
  int o_caminho_2[aux_vertices];
  double pes[aux_vertices];
  double pes2[aux_vertices];
  double pesP[aux_vertices];

  printf("\033[0;33m");
  printf("Lembretes: \n-> Defina seu grafo em um arquivo chamado dados.txt independente da quantidade de vertices\n-> Cuidado com o arquivo de resultados, executar repetidamente o programa resulta em apagar e criar um novo resultado.txt\n-> Um grafo grande PODE DEMORAR MAIS DO QUE O NORMAL para ser processado por completo!\n\n");
  printf("\033[0m");


  while(!feof(file1)) {               //enquanto o arquivo nao esta vazio, ele le com auxiliares o bota no Grafo que criamos
    fscanf(file1, "%d %d %f", &aux_origem, &aux_destino, &aux_peso);
    // printf("Aresta: %d %d %.2f\n", aux_origem, aux_destino, aux_peso);
    insereAresta(gr, aux_origem, aux_destino, aux_peso);
    insereAresta(gr, aux_destino, aux_origem, aux_peso);
    if(cont == 0){
      primeiro_vertice = aux_origem;                     //pegamos o primeiro vertice, primeira execucao do while
    }
    cont++;
  }

  printf("\033[0;33m");
  printf("Para executar o Algoritmo de Prim, digite 1.\nPara executar o Algoritmo de Dijkstra, digite 2.\n\n");      //pegamos a opcao de execucao
  printf("\033[0m");

  scanf("%d", &opt);

  /*
  -faz-se um if pro usuario escolher o funcionamento do programa
  */

/*---------------------------------------------------   executando os Algoritmos  -------------------------------------------------------------------*/

  if(opt == 1){

    printf("\033[1;34m");
    printf("\n\nAlgoritmo de Prim:\n\n");
    printf("\033[0m");

    printf("\033[1;31m");
    printf("\nPor favor aguarde...\n");
    printf("\n");

    algPRIM(gr, 1 , pai, &Pesototal, pesP);              //chamando o algoritmo de Prim

    for(i = 1; i < aux_vertices; i++){    //printa o caminho
      printf("\033[0;32m");
      printf("%d %d %.2f\n",pai[i], i, pesP[i]);
      fprintf(file2, "%d %d %.2f\n",pai[i], i, pesP[i]);
      printf("\033[0m");
    }

    //caso se queira ver o peso, por favor adicionar este comando:

    /*
    printf("\033[1;34m");
    printf("\nPeso total final: %.2Lf\n\n", Pesototal);
    printf("\033[0m");
    */

    printf("\n");

    }

/*-------------------------------------------------------------------------------------------------------------------------------------*/

  if(opt == 2){

    printf("\033[0;33m");
    printf("\n\nDefina origem e destino para o Algoritmo de Dijkstra\n-> Lembrete: Entre com dados condizentes com o grafo que foi dado ao programa para evitar problemas.\n\n");
    printf("\033[0m");

    scanf("%d %d", &op1, &op2);

    printf("\033[1;31m");
    printf("\nPor favor aguarde...\n");
    printf("\n");

    dijkstra_caminho(gr, op1 , ant, distancia, pes);          //chamamos a funcao

    printf("\033[1;34m");
    printf("\nAlgoritmo de dijkstra:\n");
    printf("\033[0m");

    tes = op2;

    i = 0;

    while(tes != op1){

      o_caminho_2[i] = tes;
      pes2[i] = pes[tes];        //pegamos o caminho ao contrario, botamos em ordem definindo em cada passada "tes" como sendo seu antecessor

      tes = ant[tes];
      i++;
    }
    o_caminho_2[i] = op1;

    printf("\033[1;34m");
    printf("\nElementos no caminho: %d\n\n", i);          //printando o contador do ultimo loop
    printf("\033[0m");


    while(i != 0){
      printf("\033[0;32m");
      printf("%d %d %.2f\n", o_caminho_2[i], o_caminho_2[i-1], pes2[i - 1]);               //printamos corretamente o caminho, no formato que foi entao pedido
      fprintf(file2, "%d %d %.2f\n", o_caminho_2[i], o_caminho_2[i-1], pes2[i - 1]);
      printf("\033[0m");
      i--;
    }

    printf("\033[1;34m");
    printf("\n\nAnt: %d, Dist: %.2f\n", ant[op2], distancia[op2]);              //printando o elemento anterior ao elemento final, e o peso do caminho
    printf("\033[0m");

    printf("\n");
  }

  /*-------------------------------------------------------------------------------------------------------------------------------------*/

  Ticks[1] = clock();
  double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;              //printando o tempo gasto

  printf("\nTempo gasto: %g ms.\n\n", Tempo);

  libera_Grafo(gr);

  fclose(file1);
  fclose(file2);

  return 0;
}
