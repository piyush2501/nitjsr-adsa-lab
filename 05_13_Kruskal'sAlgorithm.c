#include <stdio.h>
#include <stdlib.h>
struct Edge { int u,v,w; } e[100];
int parent[50],V,E;

int find(int i){ return parent[i]==i?i:(parent[i]=find(parent[i])); }
void unite(int a,int b){ parent[find(a)]=find(b); }
int cmp(const void *a,const void *b){ return ((struct Edge*)a)->w - ((struct Edge*)b)->w; }

int main(){
    printf("Enter vertices and edges: ");
    scanf("%d%d",&V,&E);
    printf("Enter edges (u v w):\n");
    for(int i=0;i<E;i++) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    for(int i=0;i<V;i++) parent[i]=i;
    qsort(e,E,sizeof(e[0]),cmp);
    printf("Edges in MST:\n");
    for(int i=0,c=0;c<V-1 && i<E;i++)
        if(find(e[i].u)!=find(e[i].v)){
            printf("%d - %d : %d\n",e[i].u,e[i].v,e[i].w);
            unite(e[i].u,e[i].v); c++;
        }
}
