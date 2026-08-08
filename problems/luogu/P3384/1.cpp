#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>

using namespace std;

#define MAXN 100005

struct Edge{
    int u,v,w,next;
}e[MAXN << 2];

int n,m,r,p;
int cnt_idx = 0;
map<int,int>op1;
map<int,int>op2;
int data[MAXN];


int head[MAXN];
int edge_cnt = 0;


void inline _init() {
    edge_cnt = 0;
    memset(head,-1,sizeof(head));
}

void addedge(int u,int v) {
    edge_cnt++;
    e[edge_cnt].u = u;
    e[edge_cnt].v = v;
    e[edge_cnt].next = head[u];
    head[u] = edge_cnt;
}

int st[MAXN << 2] = {0};
int flag[MAXN << 2] = {0};

inline int lson(int cur) {
    return cur << 1;
}

inline int rson(int cur) {
    return (cur << 1) | 1;
}

inline void push_up(int cur) {
    st[cur] = (st[lson(cur)] + st[rson(cur)]) % p;
}

void push_down(int cur,int m) {
    if(flag[cur]) {
        flag[lson(cur)] += flag[cur];
        flag[rson(cur)] += flag[cur];
        st[lson(cur)] += flag[cur] * (m - (m >> 1)) % p;
        st[rson(cur)] += flag[cur] * (m >> 1) % p;
        flag[cur] = 0;
    }
}

void update(int l1,int r1,int l,int r,int cur,int val) {
    if(l1 <= l && r1 >= r) {
        flag[cur] += val;
        st[cur] += (r - l + 1) * val;
        return;
    }
    push_down(cur,(r - l + 1));
    int mid = (l + r) >> 1;
    if(l1 <= mid) update(l1,r1,l,mid,lson(cur),val);
    if(r1 > mid) update(l1,r1,mid + 1,r,rson(cur),val);
    push_up(cur);
}

int query(int l1,int r1,int l,int r,int cur) {
    if(l1 <= l && r1 >= r) return st[cur];
    int ret = 0;
    push_down(cur,(r - l + 1));
    int mid = (l + r) >> 1;
    if(l1 <= mid) ret += query(l1,r1,l,mid,lson(cur)) % p;
    if(r1 > mid) ret += query(l1,r1,mid + 1,r,rson(cur)) % p;
    return ret % p;
}

int order = 0;

void build(int l,int r,int cur) {
    if(l == r) {
        st[cur] = data[op2[++order]];
        return;
    }
    int mid = (l + r) >> 1;
    build(l,mid,lson(cur));
    build(mid + 1,r,rson(cur));
    push_up(cur);
    return;
}

int son[MAXN],top[MAXN],dep[MAXN],fa[MAXN],size[MAXN];

void DFS1(int u,int pre,int d) {
    dep[u] = d;
    fa[u] = pre;
    size[u] = 1;
    for(int i = head[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if(v == pre) return;
        DFS1(v,u,d + 1);
        size[u] += size[v];
        if(son[u] != -1 || size[v] > size[son[u]]) {
            son[u] = v;
        }
    }
}

void DFS2(int u,int t) {
    top[u] = t;
    op1[u] = ++cnt_idx;
    op2[cnt_idx] = u;
    if(son[u] != -1) {
        DFS2(son[u],t);
    }
    else return;
    for(int i = head[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if(v != son[u] && v != fa[u]) {
            DFS2(v,v);
        }
    }
}

int lca(int a,int b,int val,bool f) {
    int f1 = top[a],f2 = top[b];
    int sum = 0;
    while(f1 != f2) {
        if(dep[f1] < dep[f2]) {
        	swap(f1,f2);
            swap(a,b);
		}
        if(f) sum = (sum + query(op1[f1],op1[a],1,n,1)) % p;
        else update(op1[f1],op1[a],1,n,1,val);
        a = fa[f1];
        f1 = top[a];
    }
    if(dep[a] > dep[b]) {
        swap(a,b);
    }
    if(f) {
        sum = (sum + query(op1[a],op1[b],1,n,1)) % p;
    }
    else {
        update(op1[a],op1[b],1,n,1,val);
    }
    return sum;
}

void __init() {
    memset(son,-1,sizeof(son));
}

void init() {
    _init();
    __init();
    int i;
    int t1,t2;
    for(i = 1; i <= n; i++) {
        scanf("%d",&data[i]);
    }
    for(i = 1; i < n; i++) {
        scanf("%d%d",&t1,&t2);
        addedge(t1,t2);
        addedge(t2,t1);
    }
    DFS1(r,r,1);
    DFS2(r,r);
    build(1,n,1);
}

int main() {
    scanf("%d%d%d%d",&n,&m,&r,&p);
    init();
    int i;
    int t1,t2,t3,t4;
    for(int i = 1; i <= m; i++) {
        scanf("%d",&t1);
        if(t1 == 1) {
            scanf("%d%d%d",&t2,&t3,&t4);
            lca(t2,t3,t4,0);
        }
        if(t1 == 2) {
            scanf("%d%d",&t2,&t3);
            int ans = lca(t2,t3,0,1);
            printf("%d\n",ans);
        }
        if(t1 == 3) {
            scanf("%d%d",&t2,&t3);
            update(op1[t2],op1[t2] + size[t2] - 1,1,n,1,t3);
        }
        if(t1 == 4) {
            scanf("%d",&t2);
            int ans = query(op1[t2],op1[t2] + size[t2] - 1,1,n,1);
            printf("%d\n",ans);
        }
    }
    return 0;
}
