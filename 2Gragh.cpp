#include<iostream>
#include "sQueue.cpp"
using namespace std;
#define MAXV 11
#define INF 32767
#define MAX 100

typedef struct 
{
    int no;
    // InfoType info;
} VertexType;

typedef struct 
{
    int edges[MAXV][MAXV];
    int n;
    int e;
    VertexType vexs[MAXV];
} MatGragh;


typedef struct ANode
{
    int adjvex;
    struct ANode *nextare;
    int weight;
} AreNode;

typedef struct VNode
{
    // InfoType info;
    AreNode *firstare;
} VNode;

typedef struct {
    VNode adjlist[MAXV];
    int n,e;    
}   AdjGraph;

//创建图
void CreateAdj(AdjGraph *&G,int A[MAXV][MAXV],int n,int e){
    int i,j;AreNode *p;
    G=new AdjGraph;
    for(i=0;i<n;++i){
        G->adjlist[i].firstare=NULL;
    }
    for(i=0;i<=n-1;++i){
        for(j=n-1;j>=0;--j){
            if(A[i][j]!=0&&A[i][j]!=INF){
                p=new AreNode;
                p->adjvex=j;
                p->weight=A[i][j];
                p->nextare=G->adjlist[i].firstare;
                G->adjlist[i].firstare=p;
            }
        }
    }
    G->n=n;G->e=e;
}

//邻接矩阵转为邻接表
void MatToList(MatGragh g,AdjGraph *&G){
    int i,j;AreNode *p;
    G=new AdjGraph;
    for(i=0;i<g.n;++i){
        G->adjlist[i].firstare=NULL;
    }
    for(i=0;i<g.n;++i){
        for(j=g.n-1;j>=0;--j){
            if(g.edges[i][j]!=0&&g.edges[i][j]!=INF){
                p=new AreNode;
                p->adjvex=j;
                p->weight=g.edges[i][j];
                p->nextare=G->adjlist[i].firstare;
                G->adjlist[i].firstare=p;
            }
        }
    }
    G->n=g.n;G->e=g.e;
}

//输出图
void DispAdj(AdjGraph *G){
    int i;AreNode *p;
    for(i=0;i<G->n;++i){
        p=G->adjlist[i].firstare;
        printf("%d--->",i);
        while(p!=NULL){
            if(p->nextare!=NULL){
                printf("%d--->",p->adjvex);
            }
            else{
                printf("%d",p->adjvex);
            }
            
            p=p->nextare;
        }
        printf("^\n");
    }
}

//创建邻接矩阵
void CreatMatGragh(MatGragh &g,int A[MAXV][MAXV],int n,int e){
    for(int i=0;i<MAXV;++i){
        for(int j=0;j<MAXV;++j){
            g.edges[i][j]=A[i][j];
        }
    }
    g.n=n;g.e=e;
}


//销毁图运算算法
void DestoryAdj(AdjGraph *&G){
    int i;AreNode *pre,*p;
    for(i=0;i<G->n;++i){
        pre=G->adjlist[i].firstare;
        if(pre!=NULL){
            p=pre->nextare;
            while(p!=NULL){
                free(pre);
                pre=p;
                p=p->nextare;
            }
            free(pre);
        }
    }
    free(G);
}

//邻接表转为邻接矩阵
void ListToMat(AdjGraph *G,MatGragh &g){
    for(int i=0;i<G->n;++i){
        ANode *p=G->adjlist[i].firstare;
        while(p!=NULL){
            g.edges[i][p->adjvex]=p->weight;
            p=p->nextare;
        }
    }
    g.n=G->n;g.e=G->e;
}

//输出邻接矩阵
void DisMatGragh(MatGragh g){
    for(int i=0;i<g.n;++i){
        for(int j=0;j<g.n;++j){
            if(g.edges[i][j]==INF){
                printf("∞ \t");
            }
            else{
                printf("%d\t",g.edges[i][j]);
            }
        }
        printf("\n");
    }
}

// 深度优先遍历
int visited[MAX]={0};
void DFS(AdjGraph *G,int v){
    AreNode *p;
    visited[v]=1;
    printf("%d ",v);
    p=G->adjlist[v].firstare;
    while(p!=NULL){
        if(visited[p->adjvex]==0){
            DFS(G,p->adjvex);
        }
        p=p->nextare;
    }
}

//广度优先遍历
void BFS(AdjGraph *G,int v){
    int w,i;AreNode *p;
    SqQueue *qu;
    InitQueue(qu);
    int visited[MAXV];
    for(i=0;i<G->n;++i){
        visited[i]=0;
    }
    printf("%d ",v);
    visited[v]=1;
    enQueue(qu,v);
    while(!QueueEmpty(qu)){
        deQueue(qu,w);
        p=G->adjlist[w].firstare;
        while(p!=NULL){
            if(visited[p->adjvex]==0){
                printf("%d ",p->adjvex);
                visited[p->adjvex]=1;
                enQueue(qu,p->adjvex);
            }
            p=p->nextare;
        }
    }
    printf("\n");
}


int main(){
    AdjGraph *G;MatGragh g;
    int n=11,e=26;int v;
    int A[MAXV][MAXV]={0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,1,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0};
    cout<<"有向图G的邻接矩阵："<<endl;
    CreatMatGragh(g,A,n,e);
    DisMatGragh(g);
    cout<<"图G的邻接矩阵转换为邻接表："<<endl;
    MatToList(g,G);
    DispAdj(G);
    cout<<"以下进行深度优先搜索，请输入起点：" <<endl;
    cin>>v;
    DFS(G,v);
    cout<<endl;
    cout<<"以下进行广度优先搜索，请输入起点：" <<endl;
    cin>>v;
    BFS(G,v);
    return 0;
}
