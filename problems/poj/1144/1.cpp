/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-29 09:48:11
 */
#include <sstream>
#include <string>
#include <iostream>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
const int maxe = 4e6+5;
const int mod = 1e9+7;

int n,m;
int a[maxn];


struct linkList {
    typedef struct {int u,v,w,next;} edge;
    edge e[maxe];
    int h[maxn],edge_cnt=0;
    linkList(){
        edge_cnt=0;
        memset(h,-1,sizeof(h));
    }

    void clear() {
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


//oisnip_begincut_node.cpp
// ---- 求割点 ----
int root; //root点
int dfn[maxn],low[maxn],cnt; //dfn是编号,low是能到达的最小编号
bool cut[maxn]; //标记割点
void cut_node(int u,int fa){
    dfn[u] = low[u] = ++cnt; // 编号

    int child=0;//记录root的孩子数
    
    int i;
    for(i=e(u);i!=-1;i=e[i].next){ //遍历相邻点
        int v = e[i].v ;//另一个点
        if(! dfn[v] ){ //v点的编号为0，也就是没有被访问
            child++; // u的孩子数加1
            cut_node(v,fa); //从这个点开始dfs

            //树枝边,用后代的low来更新u的low
            low[u] = min(low[u],low[v]);
            
            if(low[v] >= dfn[u] && u != root) // 情况2
                cut[u] =1;
        }
        // 处理返祖边
        //注意:v可能是u的父亲,但没有关系,最多low[u] == dfn[fa[u]]
        // dfn[v] < dfn[u] 说明v是u的祖先, 
        // 在无向图上其实不可能 dfn[v] > dfn[u]
        // 因为: v 是一个已经访问过的点, 如果dfn[v] > dfn[u] 说明u是v的祖先, 那么v在u的子树上, 
        // 根据dfs 的性质, 应该先访问u, 再访问v,但此时v已经被访问, 所以不可能出现dfn[v] > dfn[u]的情况
        else if(dfn[v] < dfn[u] && v != fa) //v是u的祖先
            low[u] = std::min(low[u],dfn[v]); //回边
    }
    // 退出这个点
    if( u == root && child >1)  //情况1:
        cut[u] = 1;
}
//oisnip_end


void init(){
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(cut,0,sizeof(cut));
    e.clear();

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {

        
    }
    std::string line;
    getline(cin,line); // 消费掉读入 n 后的换行符

    while (1) {
        getline(cin,line);
        if( line == "0") break;

        stringstream ss(line);
        int u,v;
        ss >> u;
        while( ss >> v) {
            e.add2(u,v);
            // std::cout << u << " " << v <<"\n";
        }
    }

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    while (1) {
        std::cin >> n;
        if( n == 0) break;
        init(); //读取这一次的数据

        root = 1;
        // 题目保证图是连通的，所以从 1 号点开始 DFS 即可
        cut_node(1, 0);

        int cnt = 0;
        for(int i = 1;i <= n ;++i ) // i: 1->n
            cnt += cut[i];
        std::cout << cnt << "\n";
    }
    
    return 0;
}
