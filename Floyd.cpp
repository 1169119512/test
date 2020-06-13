#include<iostream>
#include "Gragh.1.cpp"
void Dispath(MatGragh g,int A[][MAXV],int path[][MAXV],int i,int j,int k){
    int apath[MAXV],d;          //反向存放引入当前中继点后的最短路径
    int l;
                if(i==g.n/2&&j==0&&k==-1){
                    printf("path<%d>=:  ",k);
                }
                else if(i==g.n/2&&j==0&&k>=0){
                    printf("path< %d>=:  ",k);
                }
                else if(i!=g.n/2&&j==0){
                    printf("         :  ");
                }
                if(A[i][j]!=INF&&i!=j){
                    l=path[i][j];
                    d=0;apath[d]=j;
                    while(l!=-1&&l!=i){
                    d++;apath[d]=l;
                    l=path[i][l];
                }
                d++;apath[d]=i;
                for(int s=d;s>=0;--s){
                    if(s==d){
                        for(int m=5-s-1;m>0;--m){
                            printf(" ");
                        }
                    }
                    printf("%d",apath[s]);
                }
                }
                else{
                    printf("   ");
                    printf("%d%d",i,j);
                }
                
            if(j==g.n-1){
                printf("  :");
            }

}

void Disdist(MatGragh g,int A[][MAXV],int i,int j,int k){
    if(k==-1){
         if(i==g.n/2&&j==0){
                printf("     A<%d>=:",k);
            }
            else if(i!=g.n/2&&j==0){
                printf("           :");
            }
            if(A[i][j]>=10&&A[i][j]!=INF){
                printf(" ");
            }
            else{
                printf("  ");
            }
            if(A[i][j]!=INF){
                printf("%d",A[i][j]);
            }
            else{
                printf("∞");
            }
            if(j==g.n-1){
                printf("  :");
                printf("\n");
                if(i==g.n-1){
                printf("\n");
            }
            }
            
    }
    else{
  if(i==g.n/2&&j==0){
                printf("     A<%d> =:",k);
            }
            else if(i!=g.n/2&&j==0){
                printf("           :");
            }
            if(A[i][j]>=10&&A[i][j]!=INF){
                printf(" ");
            }
            else{
                printf("  ");
            }
            
            if(A[i][j]!=INF){
                printf("%d",A[i][j]);
            }
            else{
                printf("∞");
            }
            if(j==g.n-1){
                printf("  :");
                printf("\n");
                if(i==g.n-1){
                printf("\n");
            }
            }
             
    }
  
}

void Dislastdistandpath(MatGragh g,int A[][MAXV],int path[][MAXV]){
     int apath[MAXV],d;          //反向存放引入当前中继点后的最短路径
    int i,j,k;
for(i=0;i<g.n;++i){
        for(j=0;j<g.n;++j){
                k=path[i][j];
                d=0;apath[d]=j;
                while(k!=-1&&k!=i){
                    d++;apath[d]=k;
                    k=path[i][k];
                }
                d++;apath[d]=i;
                if(A[i][j]!=INF&&A[i][j]>=10){
                printf("从%d到%d之间的路径长度为 %d  ",i,j,A[i][j]);
                }
                else{
                    printf("从%d到%d之间的路径长度为 %d   ",i,j,A[i][j]);
                }
                for(int s=d;s>=0;--s){
                    if(s>0){
                        printf("%d->",apath[s]);
                    }
                    else{
                        printf("%d",apath[s]);
                    }
                    
                }
                printf("\n");
        }
        printf("\n");
    }
}

void Floyd(MatGragh g){
    int A[MAXV][MAXV],path[MAXV][MAXV];
    int i,j,k;
    for(i=0;i<g.n;++i){
        for(j=0;j<g.n;++j){
            A[i][j]=g.edges[i][j];
            if(i!=j&&g.edges[i][j]<INF){
                path[i][j]=i;
            }
            else{
                path[i][j]=-1;
            }
        }
    }
    for(int i=0;i<g.n;++i){
        for(int j=0;j<g.n;++j){
             Dispath(g,A,path,i,j,-1);
        }
        for(int j=0;j<g.n;++j){
            Disdist(g,A,i,j,-1);
        }
    }


    for(k=0;k<g.n;++k){
        for(i=0;i<g.n;++i){
            for(j=0;j<g.n;++j){
                if(A[i][j]>A[i][k]+A[k][j]){        //每引入一个新的中继点就会更新整个图的最小距离
                    A[i][j]=A[i][k]+A[k][j];
                    path[i][j]=path[k][j];      
                }
              Dispath(g,A,path,i,j,k);
            }
            for(j=0;j<g.n;++j){
               Disdist(g,A,i,j,k);
            }
        }
    }
    Dislastdistandpath(g,A,path);
     
}




int main(){
    MatGragh g;
    int n=4,e=8;
    int A[MAXV][MAXV]={
        {0,1,INF,4},
        {INF,0,9,2},
        {3,5,0,8},
        {INF,INF,6,0}
    };
    CreatMatGragh(g,A,n,e);
    Floyd(g);
    return 0;
}
