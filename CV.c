# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include "grafo.c"
# include "lista.c"
int m[10][10]= {0,30,84,56,-1,70,-1,75,-1,80,30,0,65,-1,-1,-1,70,-1,-1,40,84,65,0,74,52,55,-1,60,143,48,56,-1,74,0,135,-1,-1,20,-1,-1,-1,-1,52,135,0,70,-1,122,98,80,70,-1,55,-1,70,0,63,-1,82,35,-1,70,-1,-1,-1,63,0,-1,120,57,75,-1,135,20,122,-1,-1,0,-1,-1,-1,-1,143,-1,98,82,120,-1,0,-1,80,40,48,-1,80,35,57,-1,-1,0};

void Fronteira(TGrafo * g, Lista * front, int E)
{
    while(g->E != E)
    {
        g = g->prox;
    }
    TVizinho *v = g->prim_viz;
    while(v != NULL)
    {
        inserirFim(front, v->Ev);
        v = v->prox;
    }
    return;
}

Lista* PrimeiraSolucao(TGrafo * g,Lista *front, Lista * vizitados, int i )
{
    srand( (unsigned)time(NULL) );
    while(1)
    {
        inserirFim(vizitados,i);
        //imprimir_lista(vizitados);
        int e = i;
        int a = 0;
        int f = 0;
        
        for (int i = 1; i < 10; i++)
        {
            Fronteira(g,front,e);
            //imprimir_lista(front);
            int y = 0;
            
            while(1) // Escolhando o proximo
            {
                int x = 1 + rand() % 10;
                //printf("X = %d\n",x);
                //printf("front:\n");
                //imprimir_lista(front);
                //printf("visitados:\n");
                //imprimir_lista(vizitados);
                int t = Busca_lista(front,x);
                int k = Busca_lista(vizitados,x);
                if(k==0 && t==1)
                {
                    inserirFim(vizitados,x);
                    //printf("e = %d, x = %d\n",e,x);
                    //printf("m = %d\n",m[e-1][x-1]);
                    f = f + m[e-1][x-1];
                    //printf("%d\n",f);
                    //imprimir_lista(vizitados);
                    front = inicializa_lista();
                    e = x;
                    break;
                }
                if(t == 1)
                {
                    y++;
                    if (y==front->tam)
                    {
                        a = 1;
                        break;
                    }
                    
                }
            }
            if(a == 1)
            {
                break;
            }
        }
        Fronteira(g,front,vizitados->fim->valor);
        int k = Busca_lista(front,i);
        if(k==1 && vizitados->tam ==10 && a==0)
        {
            vizitados->f = f;
            //imprimir_lista(vizitados);
            //printf("\n");
            return vizitados;
        }
        //printf("\n");
        //imprimir_lista(vizitados);
        front = inicializa_lista();
        vizitados = inicializa_lista();
    }
    
}

int Aleatorio(Lista * visitados, int i, int x)
{
    
    int p;
    while (1)
    {
        p = 1 + rand() % 10;
        int k = Busca_lista(visitados,p);
        if (p != i && k != 1 && p != x)
        {
            return p;
        }
    }
}

void troca(Lista * test, int x, int x2)
{
    No * aux = test->inicio;
    No * aux2, *aux3;
    for(int i = 0; i<10; i++)
    {
        if(aux->valor == x)
        {
            aux2 = aux;
        }
        if(aux->valor == x2)
        {
            aux3 = aux;
        }
        aux = aux->proximo;

    }
    aux2->valor = x2;
    aux3->valor = x;
    //imprimir_lista(test);
}

int Conectados(TGrafo * g, Lista * test)
{
    No * aux = test->inicio;
    int ft = 0;
    for (int f = 0; f < 9; f++)
    {
        int a = aux->valor;
        int p = aux->proximo->valor;
        //printf("%d-> %d\n",a,p);

        //printf("%d\nFront:\n",a);
        Lista * front = inicializa_lista();
        Fronteira(g,front,a);
        //imprimir_lista(front);

        No * aux2 = front->inicio;
        int t = (front->tam);
        while (aux2 !=NULL)
        {
            //printf("o = %d\n",o);
            if(aux2->valor == p || aux2 == NULL)
            {
                //printf("ACHOU\n");
                break;
            }
            aux2 = aux2->proximo;
            if(aux2 == NULL)
            {
                //printf("Não conectado\n\n");
                test->f = ft;
                return 0;
            }
        }
        //printf("oi");
        //printf("%d-> %d\n",a,p);
        //printf("m = %d\n",m[a-1][p-1]);
        ft = ft + m[a-1][p-1];
        //printf("ft = %d\n",ft);
        aux = aux->proximo;
    }
    //printf("-oi");
    test->f = ft;
    return 1;
}

Lista * permuta(TGrafo *g, int i,Lista * ini, Lista * melhor)
{
    srand( (unsigned)time(NULL) );
    int x,x2,fmenor = 9999;
    Lista * visitados = inicializa_lista();
    Lista * visitados2 = inicializa_lista();
    for (int s = 1; s < 9; s++)
    {
        //printf("-------------S = %d-------------\n",s);
        x = Aleatorio(visitados,i,0);
        inserirFim(visitados2, x);
        
        for (int k = 1; k < 9; k++)
        {
            //printf("\nk = %d\n",k);
            
            Lista * test = inicializa_lista();
            copy(ini,test);
            //imprimir_lista(test);

            x2 = Aleatorio(visitados,i,x);
            inserirFim(visitados,x2);

            //printf("x = %d, x2 = %d\n",x,x2);
            troca(test,x,x2);

            int h = Conectados(g,test);
            //printf("H = %d ",h);
            if ( h == 0)
            {
                //printf("Nó não conectado");
            }
            else
            {
                //imprimir_lista(test);
                //printf("\n");
                //printf("%d < %d",test->f,fmenor);
                if(test->f < fmenor)
                {
                    fmenor = test->f;
                    melhor = inicializa_lista();
                    copy(test,melhor);
                }
            }
            //printf("\n");
        }
        visitados = inicializa_lista();
    }
    return melhor;
}

int main()
{
    int i;
    printf("Escolha o estado cidade natal:\n");
    scanf("%d",&i);
    TGrafo *g = inicializa();
    g = geraGrafo(g);
    //imprime(g);
    Lista * front = inicializa_lista();
    Lista * visitados = inicializa_lista();
    visitados = PrimeiraSolucao(g,front,visitados,i);
    //imprimir_lista(ini);
    Lista * melhor = inicializa_lista();
    melhor = permuta(g,i,visitados, melhor);
    if(melhor->f < visitados->f)
    {
        printf("Assim a melhor rota saindo da cidade %d e:\n",i);
        imprimir_lista(melhor);
    }
    else
    {
        printf("Assim a melhor rota saindo da cidade %d e:\n",i);
        imprimir_lista(visitados);
    }
    
    return 0;
}