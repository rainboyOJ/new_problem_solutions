/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-22 15:09:55
 * desc: 多路增广 + 当前弧优化 Dinic
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 205;
const int maxe = 5005*2;

int n,m,s,t;
int dep[maxn]; //分层,点i的层数
int curh[maxn]; // 当前弧优化

struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    //遍历点u 周围点
    template<typename U>
    void for_each(int u,U func){
        for(int i = h[u] ; i !=-1;i = e[i].next)
            func(e[i].u,e[i].v,e[i].w); //u v w
    }

    void add(int u,int v,int w=0){
        e[edge_cnt] = {u,v,w,h[u]};
        h[u] = edge_cnt++;
    }
    void add2(int u,int v,int w=0){
        add(u,v,w);
        add(v,u,w);
    }
    //下标访问
    edge& operator[](int i){ return e[i]; }
    //返回head[u]
    int operator()(int u){ return h[u]; }
} e;



//返回值表示是否能达到t点
bool bfs(){ //给各个点分层
    memset(dep,-1,sizeof(dep)); //初始化
    queue<int> q;
    dep[s] = 1; //起点的 层
    q.push(s);
    
    while(q.empty() == false){
        int now = q.front(); q.pop();
        int i;
        for(i=e.h[now];i!=-1;i=e[i].next){
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

void init() {
    std::cin >> n >> m >> s >> t;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
         int u,v,w;
         std::cin >> u >> v >> w;

    }

} 


signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    
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
