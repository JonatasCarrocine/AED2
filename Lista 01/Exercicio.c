/*Nome: Jonatas Carrocine
  RA: 143472
  Turma: IB
  Exercício Semana 1*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int primo(int n)  /*Funcao para verificar se o valor eh primo ou nao*/
{
    int i; /*Atributo para o laco de repeticao*/
    int valor=0; /*Atributo para verificar se o valor nao eh primo*/
    if(n==1) /*O valor "1" nao pode ser considerado primo, logo ele retorna 0*/
        return 0;
    else{ /*Se for diferente de 1, faz o laco*/
        for(i=2; i<=n/2; i++)
        {
            if(n%i==0)  /*Se o resto for 0, significa que o 'n' eh divisivel por 'i'*/
            {
                valor=1; /*Atributo valor recebe 1*/
                //break; /*Para o laco*/
            }
        }
    }
    if(valor==1)
        return 0; /*Retorna 0 se 'n' nao for primo*/
    else
        return 1; /*Retorna 1 se 'n' for primo*/
}
 
/*Area principal do programa*/
int main (void)
{
    int i,n;
    /*i -> laco de repeticao
      n -> inteiro para obter a quantidade de entradas*/
    do
    {
        scanf("%d",&n); /*Armazena o valor*/
    }
    while(n>10 || n<1);   /*Pede se para digitar o valor entre 1 e 10*/
    int x[n]; /*Valor inteiro dessa posicao do array*/
    for(i=0; i<n; i++)
    {
        do
        {
            scanf("%d",&x[i]);
        }
        while(x[i]>1000000 || x[i]<1);  /*Pede se para digitar o valor entre 2 e 1000000*/
    }
    for(i=0; i<n; i++)
    {
        printf("%d %d\n",x[i],primo(x[i])); /*Imprime o resultado o numero e se eh primo ou nao, representado por 1 e 0*/
    }
}
