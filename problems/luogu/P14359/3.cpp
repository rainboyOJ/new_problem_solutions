// 100 分做法之一：前缀异或 + std::map
//
// 和 2.cpp 思路相同，但用 std::map 代替定长桶数组
// 每找到一个区间后调用 map::clear()，复杂度 O(当前段大小)
// 在元素值范围大但段内元素较少时效率不错，但 map 单次操作 O(log size)
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,k;
int a[maxn];
std::map<int,int> b; // 用 map 记录当前段中出现过的前缀异或值

void init(){
    std::cin >> n; 
    std::cin >> k;
    for(int i = 1;i <= n ;++i )
    {
        std::cin >> a[i];
    }
}

int xor_sum(int l,int r){
    int ans = 0;
    for(int i = l;i <= r ;++i )
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

    b[0] = 1;                // 初始前缀异或 0 出现过
    int pre_sum = 0;         // 当前段内的前缀异或
    for(int i = 1;i <= n ;++i )
    {
        pre_sum = pre_sum ^ a[i];
        int target = pre_sum ^ k;  // 需要的之前出现过的前缀异或值
        if( b[target] == 1) {
            // 找到了一个异或和为 k 的区间
            pre_sum = 0;
            b.clear();             // 清空 map（O(段大小)）
            b[0]=1;                // 新段初始前缀异或
            tot++;
        }
        else {
            b[pre_sum] = 1;        // 标记当前前缀异或出现过
        }
    }
    std::cout << tot << "\n";
    
    return 0;
}
