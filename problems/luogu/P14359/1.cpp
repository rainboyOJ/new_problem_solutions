// 60 分做法：O(n²) 贪心扫描
// 枚举每个位置 i 作为区间右端点，从 i 向前（倒着）累加异或值，
// 检查是否存在以 i 结尾的合法区间
// P1803 贪心：优先选结束最早的区间
//
// 复杂度 O(n²)，n 较大时会超时
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,k;
int a[maxn];

void init(){
    std::cin >> n; 
    std::cin >> k;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    }

}

// 计算区间 [l, r] 的异或和（直接累加，O(区间长度)）
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
    int start = 1; // 当前未分配区间的起点

    for(int i = 1;i <= n ;++i ) // 枚举区间右端点 i
    {
        bool flag = 0;
        int ans = 0;
        // 从 i 向前倒着累加异或，检查 [j, i] 的异或和是否等于 k
        for(int j = i;j>=start;j--) {
            ans = ans ^ a[j];
            if( ans == k) {
                flag = 1;
                start = i+1; // 找到就跳到下一个位置
                break;
            }
        }

        if( flag == 1) {
            tot++;
        }
    }
    std::cout << tot << "\n";
    
    return 0;
}
