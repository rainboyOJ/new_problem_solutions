/* 
 * 多路增广 Dinic
 * */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

#define maxn 10005
#define maxe 200005

int n,m,s,t;
int dep[maxn]; //分层,点i的层数


//向量星
struct _e {
    int u,v,next,cap;
};
_e e[maxe];
int head[maxn];
int cnt = 0;

//边的编号从0开始
void addEdge(int u,int v,int cap){
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].cap = cap;
    e[cnt].next = head[u];
    head[u] = cnt++;
}


//返回值表示是否能达到t点
bool bfs(){ //给各个点分层
    memset(dep,-1,sizeof(dep)); //初始化
    queue<int> q;
    dep[s] = 1; //起点的 层
    q.push(s);
    
    while(q.empty() == false){
        int now = q.front(); q.pop();
        int i;
        for(i=head[now];i!=-1;i=e[i].next){
            int v = e[i].v;
            //v没有访问过 且 容量可通行
            if(dep[v] == -1 && e[i].cap >0){ 
                dep[v] = dep[now] +1;
                q.push(v);
            }
        }
    }

    return dep[t] != -1; // !=-1 表示能分层到汇点
}

// u 当前点,low u前面的路径上的最小容量
int dfs(int u,int low){
    if( u == t) return low;
    int i;
    int ret = low;
    for(i=head[u]; i !=-1;i=e[i].next){
        int v = e[i].v;
        // 是下一层的点 且 可通行
        if(dep[v] == dep[u]+1 && e[i].cap > 0){
            int flow = dfs(v,min(ret,e[i].cap));

            //剪枝 去掉增广完毕的点
            // 证明: flow ==0 点v
            if( flow == 0) dep[v] = 0;

            e[i].cap -=flow;    //同向容量 缩小
            e[i^1].cap += flow; //反向容量 加大
            ret -= flow;

            if(!ret) break;
        }
    }
    
    return low-ret;
}

int dinic(){
    int tmp  = 0;
    while( bfs()){ //分层
        tmp += dfs(s,0x7f7f7f7f);
    }

    return tmp;
}


int main(){
    
    scanf("%d%d",&n,&m);
    scanf("%d%d",&s,&t);
    int t1,t2,t3;
    int i,j,k;
    memset(head,-1,sizeof(head));
    for (i=1;i<=m;i++){
        scanf("%d%d%d",&t1,&t2,&t3);
        addEdge(t1,t2,t3); //正向边
        addEdge(t2,t1,0);  //反向边
    }
    int maxflow =dinic();
    printf("%d\n",maxflow);
    return 0;
}
