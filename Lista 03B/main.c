/*Nome: Jonatas Carrocine
  RA: 143472
  Turma: IB
  Exercício 3B Semana 3*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000 /*Define o tamanho maximo para o vetor x*/
 
/*Funcao 'insertion'*/
void insertion(int x[],int n,int y){
    if(n<=1) /*Se for menor que 2, nao precisa ordenar o vetor*/
        return;
    insertion(x,n-1,y+1);
    /*Chama a funcao novamente, aumentando o nivel de recursao 'y', e verificar o proximo elemento do vetor*/
    int ultimo=x[n-1]; /*Guarda o elemento do vetor que esta fora de ordem*/
    int j=n-2; /*Verifica o elemento anterior ao encontrado*/
    while(j>=0 && x[j]>ultimo){
        /*Enquanto o elemento nao estiver na posicao certa, os elementos anteriores se deslocam pra direita*/
        x[j+1]=x[j];
        j--;
    }
    x[j+1]=ultimo; /*Atribui o elemento fora de ordem, agora na posicao correta*/
    /*Imprime o nivel de recursao, o valor da chave e a localizacao do elemento da chave no vetor*/
    printf("%d %d %d\n",y,x[j+1],j+1);
}
 
/*Funcao 'imprime'*/
void imprime(int x[],int n){
    int i;
    for(i=0;i<n;i++)
    {
        printf("%d ",x[i]); /*Imprime o vetor que ja estah ordenado*/
    }
}
 
/*Funcao main*/
int main (void)
{
    int n,i; /*Declarando atributos*/
    int y=1; /*'y' vai ser o nivel de recursao*/
    int x[MAX]; /*Declarando vetor*/
    scanf("%d",&n); /*Recebe a qtd de valores que serao inseridos*/
    for(i=0;i<n;i++){
        scanf("%d",&x[i]); /*Digitar o valor em cada posicao*/
    }
    insertion(x,n,y); /*Vai pra funcao 'insertion'*/
    imprime(x,n); /*Funcao para imprimir o vetor ordenado*/
}
