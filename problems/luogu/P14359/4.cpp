// 100 分做法（最优）：前缀异或 + 时间戳桶
//
// 和 2.cpp 思路相同，但用「时间戳」技巧避免 memset 清空大数组
// vis[x] 记录前缀异或值 x 最近一次被"激活"的时间戳
// 每次需要清空时只需递增时间戳 cur，而非遍历整个数组
// 时间复杂度 O(n)，空间 O(2^20)
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 1 << 20; // 2^20 = 1048576，a[i] 和 k 的上界
int vis[MAXV]; // 时间戳数组，vis[x] = 最近一次看到 x 的时间戳
int cur = 1;   // 当前时间戳，每找到一个区间就 +1

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    
    int pre = 0; // 当前段内的前缀异或和
    int ans = 0; // 答案（最多不相交区间数）
    vis[0] = cur; // 初始状态：前缀异或 0 已出现
    
    for (int i = 1; i <= n; ++i) {
        pre ^= a[i];                     // 更新前缀异或
        int target = pre ^ k;            // 需要的之前出现过的前缀异或值
        if (vis[target] == cur) {        // 在当前段内出现过 target
            ans++;                       // 找到一个合法区间
            cur++;                       // 时间戳 +1，等价于清空 vis
            pre = 0;                     // 新段的前缀异或重置
            vis[0] = cur;                // 新段初始前缀异或
        } else {
            vis[pre] = cur;              // 标记当前前缀异或已出现
        }
    }
    
    cout << ans << "\n";
    return 0;
}
