// 100 分做法：前缀异或 + 时间戳桶（最优解法）
//
// 利用前缀异或 + 贪心思想：
//   区间 [l, r] 异或和 = pre[r] ^ pre[l-1]，
//   条件 pre[r] ^ pre[l-1] = k 等价于 pre[l-1] = pre[r] ^ k。
// 从左到右扫描，用时间戳数组 vis[] 记录当前段中出现过的前缀异或值，
// 每找到一个合法区间就递增时间戳（等价于清空 vis），
// 无需 memset，O(1) 清空，总复杂度 O(n)。
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 1 << 20; // 2^20 = 1048576，a[i] 和 k 的上界
int vis[MAXV]; // 时间戳数组，vis[x] 记录 x 被标记的时间戳
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
    int ans = 0; // 最多不相交区间数
    vis[0] = cur; // 初始前缀异或 0 已出现

    for (int i = 1; i <= n; ++i) {
        pre ^= a[i];                     // 计算前缀异或
        int target = pre ^ k;            // 需要的前缀异或值
        if (vis[target] == cur) {        // 在当前段中曾经出现过
            ++ans;                       // 找到一个合法区间
            ++cur;                       // 时间戳 +1 = 清空 vis
            pre = 0;                     // 新段前缀异或重置
            vis[0] = cur;                // 新段初始前缀异或
        } else {
            vis[pre] = cur;              // 标记当前前缀异或出现过
        }
    }

    cout << ans << "\n";
    return 0;
}
