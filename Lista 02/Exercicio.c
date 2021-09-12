/*Nome: Jonatas Carrocine
  RA: 143472
  Turma: IB
  Exercício Semana 2*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/*Funcao pra retonar a quantidade de livros*/
int livr(int vales,int v,int livros){
    if(vales>=v){ /*Condicao se a quantidade de vales eh maior que o necessario pra trocar*/
        vales-=v;
        livr(vales+1,v,livros+1);
        /*Chama novamente a funcao, com menos vales e um livro a mais, pois foi feito a troca*/
    }
    else{ /*Se ter menos vales que o necessario pra trocar por um livro, retorna o total de livros*/
        return livros;
    }
}
/*Area principal do programa*/
int main (void)
{
    int n,i; /*Atributos*/
    do{
        scanf("%d",&n); /*Qtd de testes de entrada*/
    }while((n<1)||(n>10)); /*So sera aceito valores entre 1 e 10*/
 
    int d[n],p[n],v[n],livros[n],vales[n]; /*Criando novos atributos*/
    for(i=0;i<n;i++){
        d[i]=0,p[i]=0,v[i]=0;
        do{
            scanf("%d",&d[i]); /*Atribui a quantidade de dinheiro*/
        }while(d[i]<-1);
        do{
            scanf("%d",&p[i]); /*Atribui o preco do livro*/
        }while(p[i]<0);
        do{
            scanf("%d",&v[i]); /*Atribui a quantidade de vales pra trocar por livro*/
        }while(v[i]<1);
    }
    for(i=0;i<n;i++){
        vales[i]=0,livros[i]=0;
        while(d[i]>=p[i]){ /*Enquanto possui dinheiro pra comprar um livro*/
            livros[i]+=1; /*Incrementa a quantidade de livros*/
            vales[i]+=1; /*Incrementa a quantidade de vales*/
            d[i]=d[i]-p[i]; /*Subtrai o dinheiro restante*/
        }
    }
    for(i=0;i<n;i++){
        int x=livr(vales[i],v[i],livros[i]); /*X recebe o valor que retona da funcao*/
        printf("%d\n",x); /*Imprime a quantidade total de livros*/
    }
}
