/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-03 14:59:24
 * oj: poj-3321
 * title: Apple Tree
 * description: dfs-order
 */
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef  long long ll;
const int maxn = 2e6+5;
int n,m;
int a[maxn];
int root = -1;
int apple_status[maxn];

//oisnip_begin邻接表最小实现
/**
 * linklist 的简单实现
 */
// 边结构
struct Edge {
    int to, next;
} e[maxn << 1];

int head[maxn], cnt;

inline void _add(int u,int v) {
    ++cnt;
    e[cnt].to = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}
void add_edge(int u, int v) {
    _add(u, v);
    _add(v,u);
}
//oisnip_end

// dfs-order
int in[maxn],out[maxn];
int dfn_idx;
void dfs_order(int u,int fa) {
    in[u] = ++dfn_idx;

    for(int i = head[u]; i!=-1 ;i = e[i].next)
    {
        int v = e[i].to;
        if(v == fa) continue;
        dfs_order(v,u);
    }
    out[u] = dfn_idx; //最后一个点
}


int tr[maxn*4+5];
typedef int T;
struct sgt_point {
    inline int lp(int p)        { return p<<1;     }
    inline int rp(int p)        { return (p<<1)|1; }
    inline int mid(int l,int r) { return (l+r)>>1; }

    inline void pushup(int p){
        tr[p] = tr[lp(p)] + tr[rp(p)];
    }

    void build(int l,int r,int p){
        if( l == r ) {
            tr[p] = 1; //默认有一个苹果
            // scanf("%d",&tr[p]);
            return;
        }
        int m = mid(l,r);
        build(l,m,lp(p));
        build(m+1,r,rp(p));
        pushup(p);
    }

    void update(int pos,T v,int l,int r,int p){
        if( l == r ) {
            tr[p] += v;
            return;
        }
        int m = mid(l,r);
        if( pos<=m) 
            update(pos,v,l,m,lp(p));
        else 
            update(pos,v,m+1,r,rp(p));
        pushup(p);
    }

    T query(int L,int R,int l,int r,int p){
        if( L <=l && r<=R ) {
            return tr[p];
        }
        int m = mid(l,r);
        T ret = 0;
        if( L <= m ) ret+=query(L,R,l,m,lp(p));
        if( R >=m+1) ret+=query(L,R,m+1,r,rp(p));
        //pushup(p); 因为没有更改，所以不需要
        return ret;
    }
};
sgt_point sgt;


void init(){
    memset(head,-1,sizeof(head));
    std::cin >> n;
    for(int i = 1;i < n ;++i ) // i: 1->n
    {
        int u,v;
        std::cin >> u >> v;
        add_edge(u, v);
    }
    std::cin >> m;
}

signed main (int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();

    dfs_order(1, 0);
    sgt.build(1, n, 1);


    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        char opt;
        int val;
        std::cin >> opt;
        std::cin >> val;
        if( opt == 'Q') {
            int ans = sgt.query(in[val], out[val], 1,n,1) ;
            std::cout << ans << "\n";
        }
        else {
            sgt.update(in[val], apple_status[val] ? 1 : -1 ,1,n,1);
            apple_status[val] ^= 1; 
        }
    }
    
    return 0;
}
