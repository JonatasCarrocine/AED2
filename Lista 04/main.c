/*Nome: Jonatas Carrocine
  RA: 143472
  Turma: IB
  Exercício Semana 4*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100000 /*Define o tamanho maximo para o vetor x*/
 
/*Funcao que vai ordenar da maneira Merge*/
int mergeSort(int x[], int esquerdo, int direito, int k){
    int meio, cont=0;
    /*Se a ultima posicao for maior que a primeira, encontra a posicao do meio*/
    if(direito>esquerdo){
        meio=(direito+esquerdo)/2;
        cont+=mergeSort(x,esquerdo,meio,k); /*Chama de forma recursiva a funcao, no intervalo do inicio ao meio do vetor*/
        cont+=mergeSort(x,meio+1,direito,k); /*Chama de forma recursiva a funcao, no intervalo do meio ao fim vetor*/
        cont+=merge(x,esquerdo,meio+1,direito,k);
    }
    return cont;
}
 
/*Funcao que vai ordenar e comparar os valores requisitados pelo exercicio*/
int merge(int x[], int esquerdo, int meio, int direito, int k){
    int v1,v2,v3; /*Gerando atributos para armazenar as posicoes*/
    int cont=0; /*Atributo que mostra a qtd de pares que satisfaz o problema*/
    v1=esquerdo;
    v2=meio;
    v3=v1;
 
    int aux[direito];
    while((v1<meio)&&(v2<=direito)){
        if(x[v1]>k*x[v2]){ /*Se a condicao eh verdadeira, incrementa v3 e v2 e recebe o valor do contador*/
            v3++;v2++;
            cont=cont+(meio-v1);
        }
        else{ /*Senao, a condicao nao eh a exigida pelo exercicio, incrementa a posicao de v3 e v1*/
            v3++;v1++;
        }
    }
    merge2(x,aux,esquerdo,meio,direito,k); /*Chama a funcao merge2*/
    return cont;
}
 
/*Funcao que vai ordenar os valores no vetor principal*/
void merge2(int x[], int aux[], int esquerdo, int meio, int direito, int k){
    int v1,v2,v3; /*Gera os atributos e atribui os valores*/
    v1=esquerdo;
    v2=meio;
    v3=v1;
 
    while((v1<meio)&&(v2<=direito)){
        if(x[v1]>x[v2]){ /*Verifica se o valor na posicao v1 for maior que o da posicao v2*/
            aux[v3++]=x[v2++]; /*Vetor auxiliar recebe x[v2] (valor a direita), pois eh menor*/
        }
        else{
            aux[v3++]=x[v1++]; /*Vetor auxiliar recebe x[v1] (valor a esquerda), pois eh menor*/
        }
    }
    while(v1<meio){
        aux[v3++]=x[v1++];
    }
    while(v2<=direito){
        aux[v3++]=x[v2++];
    }
    for(v1=esquerdo;v1<=direito;v1++){
        x[v1]=aux[v1]; /*O vetor principal recebe os valores ordenado do vetor auxiliar*/
    }
 
}
/*Funcao main*/
int main (void)
{
    int n,k,i; /*Declarando atributos*/
    int x[MAX]; /*Declarando vetor*/
    scanf("%d",&n); /*Recebe a qtd de valores que serao inseridos*/
    scanf("%d",&k); /*Recebe o valor para comparar no problema*/
    for(i=0;i<n;i++){
        scanf("%d",&x[i]); /*Digitar o valor em cada posicao*/
    }
    printf("%d",mergeSort(x,0,n-1,k));
    return 0;
}
