#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;

int n,m;
int unique_cnt;
int a[maxn],b[maxn];
int root[maxn]; // root[i] 第i颗树的根
struct Node {
    int l,r,sum; // sum 区间内权值(数字的数量)
} tree[maxn << 5]; // 2^5 倍

int node_cnt = 0;
int get_node() {return ++node_cnt;}

// 建立线段树
void build() {

}

int update(int u,int l,int r,int val) {
    int rt = get_node();
    tree[rt] = tree[u]; // 复制原来的结点
    tree[rt].sum++; // 多了一个值,增加1

    if( l==r) return rt; // 叶子结点,返回

    int mid = (l+r) >>1;
    if( val <= mid ) tree[rt].l = update(tree[u].l,l,mid,val);
    if( val > mid) tree[rt].r = update(tree[u].r,mid+1,r,val);
    return rt;
}

// u,v 对以两个树上对应的结点
int query(int u,int v,int l,int r,int k)
{
    if( l == r) return l;

    // 当前结点的左子树sum
    int lsum  = tree[ tree[v].l ].sum  - tree[ tree[u].l].sum;
    int mid = (l+r) >>1;
    if( lsum >= k ) 
        return query(tree[u].l,tree[v].l,l,mid,k);
    else
        return query(tree[u].r,tree[v].r, mid+1, r, k-lsum);

}


void init() {
    std::cin >> n >> m;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
        b[i] = a[i];
    }
    sort(b+1,b+1+n);
    unique_cnt= std::unique(b+1,b+1+n)- (b+1);// 离散化

}

int main (int argc, char *argv[]) {
    init();

    // 建立n颗线段树
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        // 找到a[i] 对应的离散化后的值
        int id = lower_bound(b+1, b+1+unique_cnt, a[i]) - b;
        root[i] = update(root[i-1],1,unique_cnt,id);
    }

    while (m--) {
        int x,y,k;
        std::cin >> x >> y >> k;
        int t =  query(root[x-1], root[y],1,unique_cnt,k);
        std::cout << b[t] << "\n";
    }

    
    return 0;
}
