#include <stdio.h>
#include <stdlib.h>

 typedef struct No {
    int valor;
    struct No *proximo;
} No;

typedef struct {
    No *inicio, *fim;
    int f;
    int tam;
} Lista;


// imprimir a lista
void imprimir_lista(Lista *lista) {
    No *inicio = lista->inicio;
    //printf("Tamanho da lista: %d\n", lista->tam);
    while(inicio != NULL) {
        printf("%d -> ", inicio->valor);
        inicio = inicio->proximo;
    }
    printf("%d\n",lista->inicio->valor);
    printf("f = %d\n",lista->f);
    //printf("\n");
}

// inserir no final da lista
void inserirFim(Lista *lista, int valor) {
    No *novo = (No*)malloc(sizeof(No)); // cria um novo nó
    novo->valor = valor;
    novo->proximo = NULL;

    if(lista->inicio == NULL) { // lista vazia
        lista->inicio = novo;
        lista->fim = novo;
    } else { // lista não vazia
        lista->fim->proximo = novo;
        lista->fim = novo;
    }
    lista->tam++;
}

void copy(Lista * lista, Lista * lista2)
{
    No *inicio = lista->inicio;
    while(inicio != NULL) {
        inserirFim(lista2,inicio->valor);
        inicio = inicio->proximo;
    }
    lista2->f = lista->f;
}

int Busca_lista(Lista *lista, int e) {
    No *inicio = lista->inicio;
    while(inicio != NULL) {
        if(inicio->valor == e)
        {
            return 1;
        }
        inicio = inicio->proximo;
    }
    return 0;
}

Lista * inicializa_lista()
{
    Lista * l = malloc (sizeof (Lista));
    l->inicio = NULL;
    l->fim = NULL;
    l->tam = 0;
    return l;
}
/*
int main()
{
    int valor;
    Lista * h = inicializa_lista();

    for (int i = 0; i < 10; ++i)
    {
        scanf("%d",&valor);
        inserirFim(h,valor);
    }
    imprimir_lista(h);
    for (int i = 0; i < 10; ++i)
    {
        scanf("%d",&valor);
        inserirFim(h,valor);
    }
    imprimir_lista(h);
    return 0;
}*/