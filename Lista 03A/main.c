/*Nome: Jonatas Carrocine
  RA: 143472
  Turma: IB
  Exercício 3A Semana 3*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000 /*Define o tamanho maximo para o vetor x*/
 
/*Funcao onde ocorrera a troca entre as duas posicoes do vetor*/
void troca(int *xp,int *yp){
    int aux = *xp; /*Aux recebe o valor em xp*/
    *xp=*yp; /*xp recebe o valor em yp*/
    *yp=aux; /*yp recebe o valor em aux*/
}
 
/*Funcao que sera verificado o vetor, utilizando o bubble sort*/
void bubble(int x[], int n){
    int i,j;
    int qtdTrocas=0; /*Atributo que vai contar a qtd de vezes que trocou de posicao, pra determinar o vencedor*/
    for(i=1;i<n;i++){ /*Percorre a varredura ate a ultima posicao do vetor*/
        for(j=0;j<n-i;j++){ /*'j' vai ser usado pra comparar posicao por posicao do vetor*/
            if(x[j]>x[j+1]){ /*Se a posicao atual tiver um valor maior que o da posicao seguinte, esta fora de ordem*/
                troca(&x[j],&x[j+1]); /*Chama a funcao 'troca' e incrementa o  atributo 'qtdTrocas'*/
                qtdTrocas++;
            }
        }
    }
    for(i=0;i<n;i++){
        printf("%d ",x[i]); /*Mostra o vetor, agora ordenado*/
    }
    if(qtdTrocas%2==1){/*Se der resto 1, signifca que o Marcelo ganhou, pois ele foi o primeiro a jogar*/
        printf("\nMarcelo");
    }
    else{ /*Senao, o Carlos ganhou o jogo*/
        printf("\nCarlos");
    }
}
 
/*Funcao main*/
int main (void)
{
    int n,i; /*Declarando atrivutos*/
    int x[MAX]; /*Declarando vetor*/
    scanf("%d",&n); /*Recebe a qtd de valores que serao inseridos*/
    for(i=0;i<n;i++){
        scanf("%d",&x[i]); /*Digita o valor em cada posicao*/
    }
    bubble(x,n); /*Vai pra funcao 'bubble'*/
}
