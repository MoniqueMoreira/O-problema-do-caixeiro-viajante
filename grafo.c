# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct vizinho 
{
    int Ev;
    struct vizinho * prox;
}TVizinho;

typedef struct grafo
{
    int E;
    TVizinho * prim_viz;
    struct grafo * prox;
}TGrafo;

TGrafo * inicializa (){
    return NULL;
}

void imprime(TGrafo *g)
{
    printf("----------------------------GRAFO----------------------------\n");
    while(g != NULL)
    {
        printf("Vertice (%d)\n", g->E);
        printf("Vizinhos: ");
        TVizinho *v = g->prim_viz;
        while(v != NULL)
        {
            printf("(%d) ", v->Ev);
            v = v->prox;
        }
    printf("\n\n");
    g = g->prox;
    }
}

TGrafo * busca_vertice(TGrafo * g, int e)
{
    while ((g != NULL) && (g->E != e ))
    {
        g = g->prox;
    }
    return g;
}


TGrafo *insere_vertice(TGrafo *g, int e)
{
    TGrafo * p = busca_vertice(g, e);
    if(p == NULL)
    {
        p = (TGrafo*) malloc(sizeof(TGrafo));
        p->E = e;
        p->prox = g;
        p->prim_viz = NULL;
        g=p;
    }
    return g;
}

TVizinho* busca_aresta(TGrafo *g, int v1,int v2)
{
    TGrafo *pv1 = busca_vertice(g,v1);
    TGrafo *pv2 = busca_vertice(g,v2);
    TVizinho *resp = NULL;
    //checa se ambos os vértices existem
    if((pv1 != NULL) && (pv2 != NULL)) 
    {
        //percorre a lista de vizinhos de v1 procurando por v2
        resp = pv1->prim_viz;
        while ((resp != NULL) && (resp->Ev != v2)) 
        {
            resp = resp->prox;
        }
    }
    return resp;
}

void insere_um_sentido(TGrafo *g, int v1,int v2)
{
    TGrafo *p = busca_vertice(g, v1);
    TVizinho *nova = (TVizinho *) malloc(sizeof(TVizinho));
    nova->Ev = v2;
    nova->prox = p->prim_viz;
    p->prim_viz = nova;
}

void insere_aresta(TGrafo *g, int v1, int v2)
{

    TVizinho *v = busca_aresta(g, v1, v2);
    if(v == NULL)
    {
            insere_um_sentido(g,v1, v2);
            insere_um_sentido(g,v2, v1); 
    }
}

void imprimirM(int matriz[10][10])
{
    for (int i=0; i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
    return;
}


TGrafo * geraGrafo(TGrafo *g)
{
    //TGrafo * g = inicializa();
    int m[10][10]= {0,30,84,56,-1,70,-1,75,-1,80,30,0,65,-1,-1,-1,70,-1,-1,40,84,65,0,74,52,55,-1,60,143,48,56,-1,74,0,135,-1,-1,20,-1,-1,-1,-1,52,135,0,70,-1,122,98,80,70,-1,55,-1,70,0,63,-1,82,35,-1,70,-1,-1,-1,63,0,-1,120,57,75,-1,135,20,122,-1,-1,0,-1,-1,-1,-1,143,-1,98,82,120,-1,0,-1,80,40,48,-1,80,35,57,-1,-1,0};
    //imprimirM(m);
    for(int k=1;k<11;k++)
    {
        g = insere_vertice(g,k);
    }
    //imprime(g);
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            //printf("%d\n",m[i][j]);
            if(m[i][j]>0)
            {
                //printf("%d -> %d\n",i+1,j+1);

                insere_aresta(g,i+1,j+1);
                //imprime(g);
            }
        }
    }
    return g;

}

/*
int main()
{
    TGrafo * g = inicializa();
    g= geraGrafo(g);
    imprime(g);
    return 0;
}
*/
