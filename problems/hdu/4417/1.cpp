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

int update(int u,int l,int r,int id) {
    int rt = get_node();
    tree[rt] = tree[u]; // 复制原来的结点
    tree[rt].sum ++; // 多了一个值,增加1

    if( l==r) return rt; // 叶子结点,返回

    int mid = (l+r) >>1;
    if( id <= mid ) tree[rt].l = update(tree[u].l,l,mid,id);
    if( id > mid) tree[rt].r = update(tree[u].r,mid+1,r,id);
    return rt;
}

// u,v 对以两个树上对应的结点
// 本质是求区间和
int query(int u,int v,int l,int r,int k)
{
    // 结点对应的区间,完全被包含
    if( r <= k ) {
        return tree[v].sum - tree[u].sum;
    }

    if( l == r) {
        return tree[v].sum - tree[u].sum;
    }
        
    // 当前结点的左子树sum
    int mid = (l+r) >>1;
    int lsum = 0, rsum = 0;
    if( mid >= 1 ) 
        lsum = query(tree[u].l,tree[v].l,l,mid,k);
    if( mid+1 <= k)
        rsum = query(tree[u].r,tree[v].r, mid+1, r, k);

    return lsum + rsum;

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
    int T;
    std::cin >> T;
    int case_num = 1;
    while (T--) {
        printf("Case %d:\n", case_num++);
        node_cnt = 0;
        init();

        // 建立n颗线段树
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            // 找到a[i] 对应的离散化后的值
            int id = lower_bound(b+1, b+1+unique_cnt, a[i]) - b;
            // cout << id << " ";
            root[i] = update(root[i-1],1,unique_cnt,id);
        }
        // cout << endl;

        while (m--) {
            int x,y,k;
            std::cin >> x >> y >> k;
            x++;y++;
            // 得到k对应的离散化后的值
            int kk = lower_bound(b+1, b+1+unique_cnt,k) - b;

            // 细节!!: 如果查询到的值就是k
            // 表明k 本身 离散化后存在
            // 如果k 不在离散化后的值,
            if( b[kk] != k ) {
                kk--;
            }
            if( kk == 0) { // 特判
                // 这里是一个细节 
                // 线段树里面的区间 [1,unique_cnt]
                // 如果要 查询 <=0,那么 就会出现错误
                printf("0\n");
            }
            else {
                int t =  query(root[x-1], root[y],1,unique_cnt,kk);
                std::cout << t << "\n";
            }
        }
    }
    
    return 0;
}
