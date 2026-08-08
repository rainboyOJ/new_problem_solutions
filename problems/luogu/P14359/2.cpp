// 90 分做法：前缀异或 + 桶数组（memset 清空导致 TLE）
//
// 利用前缀异或性质：区间 [l, r] 的异或和 = pre[r] ^ pre[l-1]
// 条件 pre[r] ^ pre[l-1] = k 等价于 pre[l-1] = pre[r] ^ k
// 用一个大小为 2^20 的桶数组记录当前段中出现过的前缀异或值
// 每找到一个区间就用 memset 清空整个桶，代价 O(2^20)，多次操作会超时
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,k;
int a[maxn];
int b[(1<<20)+1]; // 桶数组，记录前缀异或值是否在当前段出现过

void init(){
    std::cin >> n; 
    std::cin >> k;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    }

}

int xor_sum(int l,int r){
    int ans = 0;
    for(int i = l;i <= r ;++i ) // i: l->r
    {
        ans = ans ^ a[i];
    }
    return ans;
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();

    int tot = 0;
    int start = 1;

    b[0] = 1;             // 初始前缀异或 0 出现过
    int pre_sum = 0;      // 当前段内的前缀异或
    for(int i = 1;i <= n ;++i )
    {
        pre_sum = pre_sum ^ a[i];            // 更新到 i 的前缀异或
        int target = pre_sum ^ k;            // 需要的之前出现过的前缀异或值
        if( b[target] == 1) {
            // 找到了一个异或和为 k 的区间
            pre_sum = 0;
            memset(b,0,sizeof(b));            // 清空整个桶（O(2^20)，很慢）
            b[0]=1;                           // 新段初始前缀异或
            tot++;
        }
        else {
            b[pre_sum] = 1;                   // 标记当前前缀异或出现过
        }
    }
    std::cout << tot << "\n";
    
    return 0;
}
