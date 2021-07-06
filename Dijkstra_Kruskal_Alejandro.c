//Algoritmo de Dijsktra e Kruskal, AED2, Alejandro da Silva Pereira
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 10000000

struct nodo
{
    int nodoPartida;
    int nodoDestino;
    int peso;
};

void ImprimeMatriz(int **M, int m, int n);
void PreencheMatriz(int **M, int m, int n);
void PreencheMatrizKruskal(int **M, int m, int n);
int Dijsktra(int **M, int *F, int *P, int *D, int n, int inicial, int destino, char caminho[50], int conexo);
void LiberaMatriz(int **M, int n);
char *inverteString(char *s);
void bubble(struct nodo *nodo, int n);
void kruskal(struct nodo *nodo, int n, int v);
int busca(int conjuntos[], int indice);
void uniao(int conjuntos[], int partida, int destino, int v);
void menuKruskal();
void menuDijkstra();
int conexo(int **m, int n);
int main()
{
    int op;

    for (;;)
    {
        printf("         Menu\n1)Algoritmo de Dijsktra\n2)Algoritmo de Kruskal\n3)Sair\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            menuDijkstra();
            break;
        case 2:
            menuKruskal();
        case 3:
            exit(0);
            break;
        default:
            printf("Opcao invalida\n");
            break;
        }
    }

    return 0;
}

void ImprimeMatriz(int **M, int m, int n)
{
    int i, j;
    printf("  ");
    for (i = 0; i < m; i++)
        printf(" %c ", 65 + i);
    printf("\n");
    for (i = 0; i < m; i++)
    {
        printf("%c ", 65 + i);
        for (j = 0; j < n; j++)
        {
            printf(" %d ", M[i][j]);
        }
        printf("\n");
    }
}
void PreencheMatriz(int **M, int m, int n)
{
    int i, j;
    printf("Informe os pesos das arestas entre os vertices.\nInforme 0 caso nao exista a conexao.\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("Conexao vertice %c com %c: ", 65 + i, 65 + j);
            scanf("%d", &M[i][j]);
            if (M[i][j] < 0)
            {
                printf("Nao informe pesos negativos, por favor informe novamente!\n");
                j--;
            }
        }
    }
}

void PreencheMatrizKruskal(int **M, int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            M[i][j] = -1;
        }
    }
    printf("Informe os pesos das arestas entre os vertices.\nInforme 0 caso nao exista a conexao.\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i != j && M[j][i] == -1)
            {
                printf("Conexao vertice %c com %c: ", 65 + i, 65 + j);
                scanf("%d", &M[i][j]);
                M[j][i] = M[i][j];
                if (M[i][j] < 0)
                {
                    printf("Nao informe pesos negativos, por favor informe novamente!\n");
                    j--;
                }
            }
        }
    }
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j)
            {
                M[i][j] = 0;
            }
        }
    }
}

int Dijsktra(int **M, int *F, int *P, int *D, int n, int inicial, int destino, char caminho[50], int conexo)
{

    int custo[n][n];
    int contador, menordistancia, proximo, i, j, k;
    k = 0;

    if (inicial < n && destino < n && destino >= 0 && inicial >= 0)
    {
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (M[i][j] == 0)
                    custo[i][j] = INF;
                else
                    custo[i][j] = M[i][j];

        for (i = 0; i < n; i++)
        {
            F[i] = 0;
            D[i] = custo[inicial][i];
            P[i] = inicial;
        }
        F[inicial] = 1;
        D[inicial] = 0;
        contador = 1;

        while (contador < n - 1)
        {
            menordistancia = INF;

            for (i = 0; i < n; i++)
                if (D[i] < menordistancia && !F[i])
                {
                    menordistancia = D[i];
                    proximo = i;
                }
            F[proximo] = 1;
            for (i = 0; i < n; i++)
            {
                if (!F[i])
                    if (menordistancia + custo[proximo][i] < D[i])
                    {
                        D[i] = menordistancia + custo[proximo][i];
                        P[i] = proximo;
                    }
            }
            contador++;
        }

        for (i = 0; i < n; i++)
            if (i == destino)
            {
                if (D[i] != INF)
                {
                    if (conexo == 0)
                    {
                        printf("Menor distancia de %c para %c = %d\n", 65 + inicial, 65 + destino, D[i]);
                        printf("Caminho = ");
                        caminho[k] = 'A' + i;
                        k++;
                        j = i;
                        do
                        {
                            j = P[j];
                            caminho[k] = ' ';
                            k++;
                            caminho[k] = '>';
                            k++;
                            caminho[k] = '-';
                            k++;
                            caminho[k] = ' ';
                            k++;
                            caminho[k] = 'A' + j;
                            k++;
                        } while (j != inicial);
                        caminho[k] = '\0';
                        printf("%s", inverteString(caminho));
                    }
                    else
                    {
                        return 1;
                    }
                }
                else
                {
                    if (conexo == 0)
                    {
                        printf("Caminho nao encontrado!\n");
                    }
                    else
                    {
                        return 0;
                    }
                }
            }
    }
    else
    {
        printf("Nodo invalido informado!\n");
    }
    return 0;
}
void LiberaMatriz(int **M, int n)
{
    int i;
    for (i = 0; i < n; i++)
        free(M[i]);
    free(M);
}
char *inverteString(char *s)
{
    int i, j;
    char aux;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        aux = s[i];
        s[i] = s[j];
        s[j] = aux;
    }

    return s;
}

void bubble(struct nodo *nodo, int n)
{
    int i, j;
    struct nodo temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (nodo[j].peso > nodo[j + 1].peso)
            {
                temp = nodo[j];
                nodo[j] = nodo[j + 1];
                nodo[j + 1] = temp;
            }
        }
    }
}
void kruskal(struct nodo *nodo, int n, int v)
{
    struct nodo *mst;
    int conjuntos[v], i, j, salvaNoPartida, salvaNoDestino, pesoTotal;

    mst = (struct nodo *)malloc((v - 1) * sizeof(struct nodo));
    j = 0;
    pesoTotal = 0;

    for (i = 0; i < v; i++)
    {
        conjuntos[i] = i;
    }

    for (i = 0; i < n; i++)
    {
        salvaNoPartida = busca(conjuntos, nodo[i].nodoPartida);
        salvaNoDestino = busca(conjuntos, nodo[i].nodoDestino);

        if (salvaNoPartida != salvaNoDestino)
        {
            mst[j] = nodo[i];
            j++;
            uniao(conjuntos, salvaNoPartida, salvaNoDestino, v);
        }
    }
    printf("Arvore Gerador Minima:\n");
    for (i = 0; i < v - 1; i++)
    {
        printf("Vertices(%c,%c), Custo: %d\n", (65 + mst[i].nodoDestino), (65 + mst[i].nodoPartida), mst[i].peso);
        pesoTotal += mst[i].peso;
    }
    printf("Custo minimo total: %d", pesoTotal);
}

int busca(int conjuntos[], int indice)
{
    return (conjuntos[indice]);
}

void uniao(int conjuntos[], int partida, int destino, int v)
{
    int i;

    for (i = 0; i < v; i++)
    {

        if (conjuntos[i] == destino)
        {
            conjuntos[i] = partida;
        }
    }
}
void menuDijkstra()
{
    int n, **M, *fechado, *predecessor, *distancia, i, opcao;
    char nodoInicial, nodoDestino, caminho[50];
    n = -1;
    for (;;)
    {
        printf("\n      Algoritmo de Dijsktra\n1)Criar grafo\n2)Mostrar grafo\n3)Calcular menor distancia\n4)Voltar\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            do
            {
                printf("Informe o numero de vertices do grafo: ");
                scanf("%d", &n);

                if (n <= 20)
                {
                    M = (int **)malloc(sizeof(int *) * n);
                    fechado = (int *)malloc(sizeof(int) * n);
                    predecessor = (int *)malloc(sizeof(int) * n);
                    distancia = (int *)malloc(sizeof(int) * n);
                    if (M == NULL)
                    {
                        printf("Memoria insuficiente.\n");
                        exit(1);
                    }
                    for (i = 0; i < n; i++)
                    {
                        M[i] = (int *)malloc(sizeof(int) * n);
                        if (M[i] == NULL)
                        {
                            printf("Memoria insuficiente.\n");
                            exit(1);
                        }
                    }
                    PreencheMatriz(M, n, n);
                }
                else
                {
                    printf("Numero de vertices nao pode ser maior que 20.\n");
                }
            } while (n > 20 || n <= 0);
            break;
        case 2:
            if (n == -1)
            {
                printf("Nenhum grafo foi criado!\n");
            }
            else
            {
                ImprimeMatriz(M, n, n);
            }
            break;
        case 3:
            if (n == -1)
            {
                printf("Nenhum grafo foi criado!\n");
            }
            else
            {
                printf("Informe o nodo inicial e o nodo destino: ");
                getchar();
                scanf("%c %c", &nodoInicial, &nodoDestino);
                getchar();
                Dijsktra(M, fechado, predecessor, distancia, n, nodoInicial - 65, nodoDestino - 65, caminho, 0);
            }
            break;
        case 4:
            LiberaMatriz(M, n);
            free(fechado);
            free(predecessor);
            free(distancia);
            main();
            break;
        default:
            printf("Opcao invalida\n");
            break;
        }
    }
}
void menuKruskal()
{
    struct nodo *nodos;
    int **M, n, a, i, j, k, opcao;
    n = -1;
    for (;;)
    {

        a = 0;
        k = 0;
        printf("\n      Algoritmo de Kruskal\n1)Criar grafo\n2)Mostrar grafo\n3)Gerar AGM\n4)Voltar\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            do
            {
                printf("Informe o numero de vertices do grafo: ");
                scanf("%d", &n);

                if (n <= 20)
                {
                    M = (int **)malloc(sizeof(int *) * n);
                    if (M == NULL)
                    {
                        printf("Memoria insuficiente.\n");
                        exit(1);
                    }
                    for (i = 0; i < n; i++)
                    {
                        M[i] = (int *)malloc(sizeof(int) * n);
                        if (M[i] == NULL)
                        {
                            printf("Memoria insuficiente.\n");
                            exit(1);
                        }
                    }
                    PreencheMatrizKruskal(M, n, n);
                }
                else
                {
                    printf("Numero de vertices nao pode ser maior que 20.\n");
                }
            } while (n > 20 || n <= 0);
            break;
        case 2:
            if (n == -1)
            {
                printf("Nenhum grafo foi criado!\n");
            }
            else
            {
                ImprimeMatriz(M, n, n);
            }
            break;
        case 3:
            if (n == -1)
            {
                printf("Nenhum Grafo Criado\n");
            }
            else
            {
                for (i = 0; i < n; i++)
                {
                    for (j = 0; j < n; j++)
                    {
                        if (M[i][j] != 0 && M[i][j] != -1)
                        {
                            a++;
                        }
                    }
                }
                nodos = (struct nodo *)malloc(sizeof(struct nodo) * a);

                for (i = 0; i < n; i++)
                {
                    for (j = 0; j < n; j++)
                    {
                        if (M[i][j] != 0)
                        {
                            nodos[k].nodoDestino = i;
                            nodos[k].nodoPartida = j;
                            nodos[k].peso = M[i][j];
                            k++;
                        }
                    }
                }
                if (conexo(M, n) == 1)
                {
                    bubble(nodos, a);
                    kruskal(nodos, a, n);
                }
                else
                {
                    printf("Impossivel calcular AGM, grafo desconexo!\n");
                }
            }
            break;
        case 4:
            free(nodos);
            LiberaMatriz(M, n);
            main();
            break;
        default:
            printf("Opcao invalida\n");
            break;
        }
    }
}
int conexo(int **m, int n)
{
    int i, j, *fechado, *predecessor, *distancia;
    char caminho[50];
    fechado = (int *)malloc(sizeof(int) * n);
    predecessor = (int *)malloc(sizeof(int) * n);
    distancia = (int *)malloc(sizeof(int) * n);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i != j)
            {
                if (Dijsktra(m, fechado, predecessor, distancia, n, i, j, caminho, 1) == 0)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}