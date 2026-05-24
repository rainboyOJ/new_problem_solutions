/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-02 15:03:03
 * oj: luogu-1972
 * title: [SDOI2009] HH 的项链
 * description: 区间不同元素的数量
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
const int maxn = 2e6+5;
int n,m;
int a[maxn];
int pre[maxn];
int pre_bucket[maxn];

using ll = long long;
struct node {
    int l,r,idx;
    //按l排序
    bool operator<(const node & t) const {
        if( l == t.l) return r < t.r;
        return l < t.l;
    }
};
node q[maxn]; //查询
int ans[maxn]; //存答案
 
template<typename T,int N=maxn>
struct Bit {
    T c[N+5]; // 树状数组, 1-based
    //Bit(){}
    inline int lowbit(int x) { return x & -x;      } // lowbit
    inline int fa(int p)     { return p+lowbit(p); } // update a[p] 时, 下一个要更新的节点
    inline int left(int p)   { return p-lowbit(p); } // query a[1..p] 时, 下一个要求和的节点

    // 单点更新 a[p] += v
    void update(int p, T v){
        for( ; p <= N; p = fa(p) ) c[p] += v;
    }

    // 查询前缀和 a[1..p]
    T query(int p){ //前缀和
        T sum=0;
        for( ;p > 0 ; p = left(p)) sum+= c[p];
        return sum;
    }
};
Bit<ll> bit;

void init(){
    scanf("%d",&n);
    for(int i = 1;i <= n ;++i ) // i: 1->n
        scanf("%d",&a[i]);
    scanf("%d",&m);
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        scanf("%d%d",&q[i].l,&q[i].r);
        q[i].idx = i;
    }
    std::sort(q+1,q+1+m);
}

signed main (int argc, char *argv[]) {
    init();

    // 创建pre数组
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int num = a[i];
        pre[i] = pre_bucket[a[i]];
        pre_bucket[a[i]] = i;
    }
    // pre 分组
    std::vector< std::vector<int> > vec(n+1);
    
    for(int i = 1;i<=n;i++) {
        //表示 pre[i] = 3
        // 前一个位置为3的放在 一组里
        vec[ pre[i] ].push_back(i);
    }

    int l_idx = 1; //遍历 query 数组使用,
    // l_idx 表明 `[l,r]` q[l_idx].l = l 时


    //枚举 pre[] 值
    for(int i = 1 ;i <=n;i++) {

        // 更新 true_arr 对应的BIT
        for( auto pos : vec[i-1]) {
            bit.update(pos, 1);
        }

        // --> 收缩对应的查询区间
        // 更新l_idx, 知道 q[l_idx].l > i
        while( q[l_idx].l <= i && l_idx <=m) {

            if( q[l_idx].l == i)
            {
                int ans_id = q[l_idx].idx;
                ans[ ans_id ] = bit.query(q[l_idx].r) - bit.query(q[l_idx].l - 1);
            }
            l_idx++;
        }
    }
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        printf("%d\n",ans[i]);
    }
    
    return 0;
}
