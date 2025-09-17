#include <stdio.h>
int V,g[20][20],vis[20],st[20],top=0,small=1e9,large=0;

void dfs(int u,int p){
    vis[u]=1; st[top++]=u;
    for(int v=0;v<V;v++) if(g[u][v]){
        if(!vis[v]) dfs(v,u);
        else if(v!=p){ // found cycle
            int len=0; for(int i=top-1;i>=0 && st[i]!=v;i--) len++; len++;
            if(len>2){ if(len<small) small=len; if(len>large) large=len; }
        }
    }
    top--; vis[u]=0;
}

int main(){
    printf("Enter vertices: "); scanf("%d",&V);
    printf("Enter adjacency matrix:\n");
    for(int i=0;i<V;i++) for(int j=0;j<V;j++) scanf("%d",&g[i][j]);
    for(int i=0;i<V;i++) dfs(i,-1);
    if(small==1e9) printf("No cycle found\n");
    else printf("Smallest=%d Largest=%d\n",small,large);
}

/*input for output
4
0 1 1 0
1 0 1 1
1 1 0 1
0 1 1 0*/