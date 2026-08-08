/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-28 09:05:09
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
const int maxe = 4e6+5;
const int mod = 1e9+7;

int n,m;
int a[maxn];
int _time[maxn];
int ftime[maxn]; //finish_time

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

struct TopSort {
    int in_degree[maxn];
    std::queue<int> q; //队列
    std::vector<int> sorted;
    
    void topsort(int n){
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            if( in_degree[i] == 0) q.push(i);
        }

        while( !q.empty() )
        {
            int u = q.front();
            sorted.push_back(u);
            q.pop();
            for(int i = e(u) ; ~i;i = e[i].next){
                int v = e[i].v;
                in_degree[v]--;
                if( in_degree[v] == 0) q.push(v);
            }
        }
    }

} topsort;


void init(){

    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int u;
        std::cin >> u;
        cin >> _time[u];
        int v;
        while (1) {
            std::cin >> v;
            // std::cout << v << " ";
            if( v == 0) break;
            // std::cout << v << " " << u << "\n";
            e.add(v,u);
            topsort.in_degree[u]++;
        }
        // std::cout  << "\n";
    }
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    topsort.topsort(n);

    int ans = 1;
    for( auto u : topsort.sorted ) {
        // std::cout << u << " ";
        if( ftime[u] == 0) ftime[u] = _time[u];

        for(int i = e(u) ; ~i;i = e[i].next) {
            int v  = e[i].v;
            ftime[v] = max(ftime[v],ftime[u] + _time[v] );
            ans = max(ftime[v],ans);
        }
    }
    // std::cout << "\n";
    std::cout << ans << "\n";
    
    return 0;
}
