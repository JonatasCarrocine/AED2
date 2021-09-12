/*Nome: Jonatas Carrocine
  RA: 143472
  Turma: IB
  Tarefa 10*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define black 0
#define red 1
 
/*Gera as informacoes de um no*/
struct TNo
{
    int valor;
    int cor;
    struct TNo *pai;
    struct TNo *esq;
    struct TNo *dir;
    int tamanho;
};
 
struct TNo* raiz=NULL;
 
/*Funcao para gerar um novo no na nossa arvore*/
struct TNo* NovoNo(int valor)
{
    struct TNo *novo=(struct TNo *)malloc(sizeof(struct TNo)); /*Aloca espaco para o no a ser adicionado*/
    novo->valor = valor; /*O no recebe o valor dele*/
    novo->esq = NULL;
    novo->dir = NULL; /*Como o novo no eh um no folha, ele nao possui filhos, logo 'esq' e 'dir' sao nulos*/
    novo->tamanho = 1; /*No sempre tem tamanho 1*/
    novo->cor = red;
    return novo;
}
 
/*Funcao para procurar o no pai*/
struct TNo *procPai(struct TNo *Arvore, struct TNo *vazio)
{
    if(Arvore==NULL) /*Se a arvore for vazia, retorna nulo*/
        return NULL;
    struct TNo *Pai=NULL;
    if(Arvore->esq==vazio) /*Se nao tiver filho a esquerda, retorna a arvore*/
        return Arvore;
    if(Arvore->dir==vazio) /*Se nao tiver filho a direita, retorna a arvore*/
        return Arvore;
    Pai=procPai(Arvore->dir,vazio);
    if(Pai==NULL)
        Pai=procPai(Arvore->esq,vazio);
    return Pai;
}
 
/*Funcao pra recolorir os nos da arvore, se for necessario*/
void recolor(struct TNo *D,struct TNo *C,struct TNo *A)
{
    if(D!=NULL) /*Se o no D nao for vazio, sua cor eh preta*/
        D->cor=black;
    C->cor=red; /*O no C eh de cor vermelha*/
    if(D!=NULL)
        A->cor=black; /*No A eh de cor preta*/
}
 
/*Funcao para rotacionar a subarvore pra direita*/
struct TNo *RR(struct TNo *pA)
{
    struct TNo *pB;
    pB=pA->esq;
    pA->esq=pB->dir;
    pB->dir=pA;
    return pB;
}
 
/*Funcao para rotacionar a subarvore pra esquerda*/
struct TNo *LL(struct TNo *pA)
{
    struct TNo *pB;
    pB=pA->dir;
    pA->dir=pB->esq;
    pB->esq=pA;
    return pB;
}
 
/*Funcao para inserir um novo no*/
struct TNo *insere(struct TNo *A,struct TNo *B, struct TNo *Raiz)
{
    struct TNo *D, *pC,*C=procPai(Raiz,A);//procura o pai de A
    if(C==NULL || A->cor==black) /*Se o no C for vazio, ou A for preto, retorna a Raiz*/
        return Raiz;
    if(A==C->esq) /*Se A for o filho a esquerda de C, logo D eh o filho a direita de C*/
        D=C->dir;
    else /*Se A for o filho a direita de C, logo D eh o filho a esquerda de C*/
        D=C->esq;
    pC=procPai(Raiz,C); /*Procura o pai de C*/
    if(D==NULL || D->cor==black)  /*Se D for preto, verificamos os seguintes casos*/
    {
        if(A==C->esq && B==A->dir) //Caso 2a
        {
            A=LL(A); /*Rotaciona A para esquerda*/
            C->esq=A;
            B=A->esq;
        }
        else if(A==C->dir && B==A->esq)  //Caso 2b
        {
            A=RR(A); /*Rotaciona A para direita*/
            C->dir=A;
            B=A->dir;
        }
        if(A==C->esq && B==A->esq) //Caso 3a
        {
            if(pC!=NULL)  /*Se C tiver um pai, verifica as condicoes*/
            {
                if(C==pC->esq) /*Se C for o filho esquerdo de pC*/
                    pC->esq=RR(C); /*Rotaciona o filho esquerdo de pC para a direita*/
                else
                    pC->dir=RR(C); /*Rotaciona o filho direito de pC para a direita*/
            }
            else
            {
                Raiz=RR(C); /*Rotaciona o C para a direita*/
            }
            A->cor=black; /*No A eh preto*/
            C->cor=red; /*No C eh vermelho*/
        }
        if(A==C->dir && B==A->dir) //Caso 3b
        {
            if(pC!=NULL)
            {
                if(C==pC->esq)
                    pC->esq=LL(C); /*Rotaciona o filho esquerdo de pC para a esquerda*/
                else
                    pC->dir=LL(C); /*Rotaciona o filho direito de pC para a esquerda*/
            }
            else
            {
                Raiz=LL(C); /*Rotaciona o C para a esquerda*/
            }
            A->cor=black;
            C->cor=red;
        }
    }
    else if (D->cor==red)   /*Se D for vermelho*/
    {
        recolor(D,C,A); /*Muda as cores dos nos*/
        pC=procPai(Raiz,C); /*Procura o pai de C*/
        if(pC!=NULL && pC->cor==red)  /*Se o pai de C for vermelho, insere o no*/
        {
            Raiz=insere(pC,C,Raiz);
        }
    }
    return Raiz;
}
 
/*Funcao para procurar os nos na arvore*/
struct TNo *proc(int N, struct TNo *NoAtual,int i,struct TNo *Raiz)
{
    int tamanho=0, alturaesq=0, alturadir=0, altura=0; /*Atrivutos para usar caso encontre o valor na arvore*/
    if(NoAtual==NULL) /*Se nao tiver nenhum valor na arvore, cria um novo no*/
    {
        return NovoNo(N);
    }
    if(NoAtual->dir!=NULL && N>NoAtual->valor)
    {
        Raiz=proc(N,NoAtual->dir,i,Raiz); /*Verifica a direita desse no encontrado*/
    }
    else if(NoAtual->dir==NULL && N>NoAtual->valor)  //inserção do no a direita
    {
        NoAtual->dir=NovoNo(N);
        Raiz=insere(NoAtual,NoAtual->dir,Raiz);
    }
    else if(NoAtual->esq!=NULL && N<NoAtual->valor)
    {
        Raiz=proc(N,NoAtual->esq,i,Raiz); /*Verifica a esquerda desse no encontrado*/
    }
    else if(NoAtual->esq==NULL && N<NoAtual->valor)  //inserção do no a esquerda
    {
        NoAtual->esq=NovoNo(N);
        Raiz=insere(NoAtual,NoAtual->esq,Raiz);
    }
    else if(N == NoAtual->valor)   /*Se o no pesquisado estiver na arvore, busca as suas alturas*/
    {
        Altura(NoAtual->esq, &alturaesq,1,&tamanho);
        Altura(NoAtual->dir, &alturadir,1,&tamanho);
        altura=maiorTamanho(alturaesq,alturadir);
        printf("%d, %d, %d\n",altura, alturaesq, alturadir); /*Imprime as alturas*/
        return Raiz;
    }
    return Raiz;
}
 
/*Funcao para buscar um no pesquisado*/
struct TNo* busca(struct TNo *Raiz, int valor)
{
    if(Raiz!=NULL)  /*Se o no estiver na arvore, faz o que segue*/
    {
        if(Raiz->valor==valor)  /*Se o valor da raiz for igual ao valor para busca, retorna o no*/
            return Raiz;
        else if(valor<Raiz->valor) /*Se o valor buscado for menor que o no atual, busca o no a esquerda*/
            return busca(Raiz->esq,valor);
        else  /*Se o valor buscado for maior que o no atual, busca o no a direita*/
            return busca(Raiz->dir,valor);
    }
    return 0; /*Se o valor nao estiver na arvore, retorna 0*/
}
 
/*Funcao para verificar a altura*/
int Altura(struct TNo *Raiz, int *altura, int aux, int *tam)
{
    if(Raiz==NULL) /*Se o valor pequisado nao estiver na arvore, retorna nulo*/
    {
        return;
    }
    if(Raiz->esq!=NULL)
    {
        Altura(Raiz->esq, altura, aux+1, tam); /*Chama a funcao recursivamente, a partir do no a esquerda*/
    }
    if(Raiz->dir!=NULL)
    {
        Altura(Raiz->dir, altura, aux+1, tam); /*Chama a funcao recursivamente, a partir do no a direita*/
    }
    if(aux>=*altura)
    {
        *altura=aux;
    }
    *tam+=1;
}
 
/*Funcao para retornar a altura da arvore composta so por nos pretos*/
int AlturaPreto(struct TNo *Raiz, int *altura, int aux, int *tam)
{
    if(Raiz==NULL) /*Se o valor pequisado nao estiver na arvore, retorna nulo*/
    {
        return;
    }
    if(Raiz->esq!=NULL && Raiz->esq->cor==1)
    {
        Altura(Raiz->esq, altura, aux+1, tam);
    }
    if(Raiz->esq!=NULL && Raiz->esq->cor==0)
    {
        Altura(Raiz->esq, altura, aux, tam);
    }
    if(Raiz->dir!=NULL && Raiz->dir->cor==1)
    {
        Altura(Raiz->dir, altura, aux+1, tam);
    }
    if(Raiz->dir!=NULL && Raiz->dir->cor==0)
    {
        Altura(Raiz->dir, altura, aux, tam);
    }
    if(aux>=*altura)
    {
        *altura=aux;
    }
    *tam+=1;
}
 
/*Funcao para verificar qual das duas alturas sao maiores, para ser atribuido em 'altura'*/
int maiorTamanho(int alturaEsq, int alturaDir)
{
    if(alturaEsq>alturaDir) /*Se a altura da esquerda for maior, retorna a sua altura*/
    {
        return alturaEsq;
    }
    else /*Caso contrario, retorna a altura a direita*/
    {
        return alturaDir;
    }
}
 
/*Funcao main*/
int main ()
{
    int numeros, numPesquisa;
    int tamanho=0, alturaesq=0, alturadir=0, altura=0;
    struct TNo *raiz=NULL; /*Gera um no raiz vazio*/
    scanf("%d",&numeros);
    while(numeros!=-1)  /*Insere os nos na arvore, enquanto nao digitar -1*/
    {
        raiz=proc(numeros,raiz,0,raiz);
        scanf("%d",&numeros);
    }
 
    Altura(raiz->esq, &alturaesq,1,&tamanho); /*Obtem a altura da arvore do lado esquerdo*/
    Altura(raiz->dir, &alturadir,1,&tamanho); /*Obtem a altura da arvore do lado direito*/
    altura = maiorTamanho(alturaesq,alturadir);
    printf("%d, %d, %d\n", altura, alturaesq, alturadir); /*Imprime as alturas*/
 
    tamanho=0,alturaesq=0,alturadir=0,altura=0;
    scanf("%d",&numeros); /*Agora os numeros serao inseridos se nao tiver na arvore, e excluidos se tiverem*/
    while(numeros!=-1)
    {
        raiz=proc(numeros,raiz,0,raiz);
        scanf("%d",&numeros);
    }
    tamanho=0,alturaesq=0,alturadir=0,altura=0; /*Reseta as variaveis*/
 
    scanf("%d",&numPesquisa);
    raiz=busca(raiz,numPesquisa); /*Busca um valor para encontrar a altura deste no a esquerda e direita*/
    if(raiz==0)  /*Se o valor retornar 0, significa que nao foi encontrado na arvore*/
    {
        printf("Valor nao encontrado");
    }
    else  /*Senao, busca a altura a partir desse no, do lado esquerdo e direito*/
    {
        if(raiz->cor==red)  /*Se o no for vermelho, seu tamanho nao eh contabilizado*/
        {
            AlturaPreto(raiz->esq, &alturaesq,0,&tamanho);
            AlturaPreto(raiz->dir, &alturadir,0,&tamanho);
        }
        else  /*Se o no a ser pesquisado for preto, ele eh incluido na hora de calcular a altura*/
        {
            AlturaPreto(raiz->esq, &alturaesq,1,&tamanho);
            AlturaPreto(raiz->dir, &alturadir,1,&tamanho);
        }
        altura = maiorTamanho(alturaesq,alturadir);
        printf("%d\n",altura); /*Imprime as alturas*/
    }
    return 0;
}
