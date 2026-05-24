/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-25 14:52:17
 * desc: 在b1.cpp 的基础上 优化 check
 */
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
ll n,k,m;
ll a[maxn];
ll pre_b[maxn];

ll range_sum(int l,int r){
    return pre_b[r] - pre_b[l-1];
}

void init(){
    scanf("%lld%lld%lld",&n,&k,&m);
    for(int i = 1;i <= n ;++i ) scanf("%lld",&a[i]);
}

//这是最快的写法
int mid(int l,int r) { return (l+r) >> 1; }

//检查pos位置的值是否符合要求
bool check(int val){
    // 构造b数组 pre
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        bool t = (a[i] >= val);
        pre_b[i] = pre_b[i-1] + t;
    }
    // printf("b : ");
    // for(int i = 1;i <= n ;++i ) printf("%d ",a[i] >= val);
    // printf("\n");

    ll tot = 0;
    for(int j = k;j<=n;j++) { //枚举结尾
        // for(int i = 1 ; i <= j-k+1;i++){ //固定结尾j的开头
        //     if ( range_sum(i, j) >= k){
        //         // printf("[%d,%d] ok\n",i,j);
        //         tot++;
        //     }
        // }

        // pre_b = s
        // 区间 x \in [0,j-k]
        // s[j] - s[x] >= k
        // s[x] <= s[j] - k
        // s[x] 是单调增加的
        // 求s[x] 数组上 <= s[j] -k 的数量

        //找到 第一个 >(s[j] -k) 的位置
        tot += ( std::upper_bound(pre_b, pre_b+ j-k+1, pre_b[j] - k)  - pre_b );
    }
    //debug: 
    // printf("check val: %d -> tot: %d\n",val,tot);
    // 在右侧就是成功
    return tot < m;
}

// 第一个失败的位置
int bs_find(int l,int r) {
    while( l < r) {
        int m = mid(l,r);
        if( check(m)) //成立
            r = m;
        else //不成立,抛弃左半边
            l = m+1;
    }
    return l ;
}


signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    int T;
    scanf("%d",&T);
    while (T--) {
        init();

        // for(int i = 1;i <= 4 ;++i ) // i: 1->4
        // {
        //     int t = check(i);
        //     printf("[%d] succ: %d\n\n\n",i,t);
        //
        // }
        int ans = bs_find(0, 1e9+1);
        std::cout << ans-1 << "\n";
        
    }
    
    return 0;
}
