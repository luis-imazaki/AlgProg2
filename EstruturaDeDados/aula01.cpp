#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct{
    void * v;
    int tam;
    void (*cmp)(void *, void *);
}theap;

void assert_vetor(int v[], int res[], int tam) {
    for (int i = 0; i < tam; i++) {
        assert(v[i] == res[i]);
    }
}


int pai(int n){
    return (n-1)/2;
}

void test_pai(){
    /*inicializacao*/
    int r;
    /*chamada e verificacao*/
    r = pai(6);
    assert(r==2);
    r = pai(5);
    assert(r==2);
    r = pai(0);
    assert(r==0);
}

int filho_esq(int n){
    return n*2 + 1;
}

void test_filho_esq(){
    /*inicializacao*/
    int r;
    /*chamada e verificacao*/
    r = filho_esq(0);
    assert(r==1);
    r = filho_esq(1);
    assert(r==3);
    r = filho_esq(2);
    assert(r==5);
}

int filho_dir(int n){
    return n*2 + 2;
}

void test_filho_dir(){
    /*inicializacao*/
    int r;
    /*chamada e verificacao*/
    r = filho_dir(0);
    assert(r==2);
    r = filho_dir(1);
    assert(r==4);
    r = filho_dir(2);
    assert(r==6);
}

void troca(int *a,int *b){
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void desce(int V[],int n, int tam){
    int maior=n,esq=filho_esq(n),dir=filho_dir(n);
    if(esq<tam && V[esq]>V[n]){
        maior = esq;
    }
    if(dir<tam&& V[dir]>V[maior]){
        maior = dir;
    }
    if(maior!=n){
        troca(&V[n],&V[maior]);
        desce(V,maior,tam);
    }

}

void test_desce(){
    /*inicializacao*/
    int entrada[] = {1,5,3,4,10,2,0}, saida[] = {5,10,3,4,1,2,0};
    int max_size = sizeof(entrada)/sizeof(entrada[0]);
    /*chamada e verificacao*/
    desce(entrada,0,max_size);
    for(int i = 0; i<max_size;i++){
        assert(entrada[i]==saida[i]);
    }
}

void constroi_heap(int v[],int max_size){
    for(int i = pai(max_size-1);i>=0;i--){
        desce(v,i,max_size);
    }
}    

void test_constroi_heap(){
    /*inicializacao*/
    int entrada[] = {1,50,20,62,60,25,30}, saida[] = {62,60,30,50,1,25,20};
    /*chamada*/
    int max_size = sizeof(entrada)/sizeof(entrada[0]);
    constroi_heap(entrada,max_size);
        for(int i=0;i<max_size;i++){
            assert(entrada[i]==saida[i]);
        }
}

void sobe(int v[], int n){
    if(v[n]>v[pai(n)]){
        troca(&v[n],&v[pai(n)]);
        sobe(v,pai(n));
    }
}

void test_sobe(void) {
    int vetor[3] = {8, 9, 10};
    sobe(vetor, 2);
    int esperado[3] = {10, 9, 8};
    assert_vetor(vetor, esperado, 3);

    int vetor2[7] = {11, 9, 8, 20, 4, 2, 1};
    sobe(vetor2, 3);
    int esperado2[7] = {20, 11, 8, 9, 4, 2, 1};
    assert_vetor(vetor2, esperado2, 7);

    int vetor3[7] = {25, 24, 23, 22, 21, 24, 19};
    sobe(vetor3, 5);
    int esperado3[7] = {25, 24, 24, 22, 21, 23, 19};
    assert_vetor(vetor3, esperado3, 7);

    int vetor4[7] = {7, 6, 5, 4, 3, 2, 1};
    sobe(vetor4, 6);
    int esperado4[7] = {7, 6, 5, 4, 3, 2, 1};
    assert_vetor(vetor4, esperado4, 7);
}

int acessa_max(int v[]){
    return v[0];
}

void test_acessa_max(){
    int v[] = {100,62,30,50,60,25,20};
    assert(acessa_max(v)==100);

}

int extrai_max(int v[],int *tam){
    int max = v[0];
    *tam-=1;
    v[0] = v[*tam];
    desce(v,0,*tam);
    return max;
}

void test_extrai_max(void) {
    int vetor[3] = {100, 80, 70};
    int tam = 3;
    int esperado[2] = {80, 70};
    extrai_max(vetor, &tam);
    assert_vetor(vetor, esperado, 2);

    int vetor2[7] = {45, 34, 33, 29, 27, 25, 23};
    int tam2 = 7;
    int esperado2[6] = {34, 29, 33, 23, 27, 25};
    extrai_max(vetor2, &tam2);
    assert_vetor(vetor2, esperado2, 6);
}

void altera_prioridade(int v[],int tam,int n,int valor){
    int antigo = v[n];
    v[n] = valor;
    if(valor>antigo)
        sobe(v,n);
    if(valor<antigo)
        desce(v,n,tam);
}

void test_altera_prioridade(void) {
    int vetor[3] = {100, 90, 70};
    int tam = 3;
    int n = 2;
    int valor = 101;
    altera_prioridade(vetor, tam, n, valor);
    int esperado[3] = {101, 90, 100};
    assert_vetor(vetor, esperado, 3);

    int vetor2[3] = {101, 90, 100};
    int tam2 = 3;
    int n2 = 0;
    int valor2 = 70;
    altera_prioridade(vetor2, tam2, n2, valor2);
    int esperado2[3] = {100, 90, 70};
    assert_vetor(vetor2, esperado2, 3);

    int vetor3[7] = {100, 90, 80, 70, 60, 50, 40};
    int tam3 = 7;
    int n3 = 4;
    int valor3 = 110;
    altera_prioridade(vetor3, tam3, n3, valor3);
    int esperado3[7] = {110, 100, 80, 70, 90, 50, 40};
    assert_vetor(vetor3, esperado3, 7);

    int vetor4[7] = {100, 90, 80, 70, 60, 50, 40};
    int tam4 = 7;
    int n4 = 2;
    int valor4 = 30;
    altera_prioridade(vetor4, tam4, n4, valor4);
    int esperado4[7] = {100, 90, 50, 70, 60, 30, 40};
    assert_vetor(vetor4, esperado4, 7);
}

int insere_elemento(int v[], int *tam, int max, int valor) {
    if (*tam == max)
        return EXIT_FAILURE;

    v[*tam] = valor;
    sobe(v, *tam);
    *tam += 1;

    return EXIT_SUCCESS;
}

void test_insere_elemento(){
    /*inicializacao*/
    int max_size = 10;
    int entrada[10] = {100,62,30,50,60,25,20};
    int saida1[]   = {100,70,30,62,60,25,20,50};
    int saida2[]   = {150,100,30,70,60,25,20,50,62};

    int i;
    int tam = 7;
    /*chamada*/
    assert(insere_elemento(entrada,&tam,max_size,70)==EXIT_SUCCESS);
    assert(tam == 8);
    
    /*verificacao*/
    for (i=0;i<tam;i++){
        assert(entrada[i]==saida1[i]);
    }
    /*chamada*/
    assert(insere_elemento(entrada,&tam,max_size,150)==EXIT_SUCCESS);
    assert(tam == 9);
    
    /*verificacao*/
    for (i=0;i<tam;i++){
        assert(entrada[i]==saida2[i]);
    }
}

void heapsort(int v[], int tam){
    for(int i = tam-1;i>=0;i--){
        troca(&v[0],&v[i]);
        desce(v,0,i);
    }
}

void test_heapsort(void) {
    int vetor[3] = {10, 9, 8};
    int esperado[3] = {8, 9, 10};
    heapsort(vetor, 3);
    assert_vetor(vetor, esperado, 3);

    int vetor2[7] = {100, 87, 69, 43, 35, 34, 23};
    int esperado2[7] = {23, 34, 35, 43, 69, 87, 100};
    heapsort(vetor2, 7);
    assert_vetor(vetor2, esperado2, 7);

    int vetor3[15] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int esperado3[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    heapsort(vetor3, 15);
    assert_vetor(vetor3, esperado3, 15);

    int vetor4[2] = {2, 1};
    int esperado4[2] = {1, 2};
    heapsort(vetor4, 2);
    assert_vetor(vetor4, esperado4, 2);

    int vetor5[1] = {3};
    heapsort(vetor5, 1);
}


int main(void){
    
    test_pai();
    test_filho_esq();
    test_filho_dir();
    test_desce();
    test_constroi_heap();
    test_sobe();
    test_acessa_max();
    test_extrai_max();
    test_altera_prioridade();
    test_insere_elemento();
    test_heapsort();
    return EXIT_SUCCESS;
}
