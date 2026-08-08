#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const int INF = -2e9; // 初始化负无穷

int dp[MAXN];
int a[MAXN];
int n, l, r; // 这里定义的是小写的 l, r

int main() {
    // 优化 I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n >> l >> r)) return 0; // 输入小写 l, r

    // 读入 A_i，注意题目说第 i 个数是编号 i-1
    // 其实就是从 0 到 N 输入
    for (int i = 0; i <= n; i++) {
        cin >> a[i];
    }

    // 初始化 DP 数组
    for (int i = 0; i <= n; i++) dp[i] = INF;
    dp[0] = 0; // 起点

    // 单调队列，存储下标
    deque<int> q;
    
    // 最终答案，初始化为很小的数
    int ans = INF;

    // DP 过程
    // 【修正】这里原来的 L 改为 l
    for (int i = l; i <= n; i++) {
        // 1. 新的候选下标进入视野： j = i - L
        // 【修正】这里原来的 L 改为 l
        int candidate = i - l;
        
        // 只有当 candidate 是可达的时候，才有资格进入队列
        if (dp[candidate] != INF) {
            // 维护单调递减队列 (如果新来的比队尾优，删队尾)
            while (!q.empty() && dp[q.back()] <= dp[candidate]) {
                q.pop_back();
            }
            q.push_back(candidate);
        }

        // 2. 移除过期元素
        // 能跳到 i 的最远位置是 i - R
        // 【修正】这里原来的 R 改为 r
        if (!q.empty() && q.front() < i - r) {
            q.pop_front();
        }

        // 3. 转移状态
        // 如果队列不为空，队头就是当前窗口 [i-R, i-L] 内的最优解
        if (!q.empty()) {
            dp[i] = dp[q.front()] + a[i];
        }

        // 4. 更新最终答案
        // 如果从当前位置 i 再跳一步(最小l，最大r)能超过 N，则 i 是合法的最后一步
        // 【修正】这里原来的 R 改为 r
        if (i + r > n) {
            ans = max(ans, dp[i]);
        }
    }

    cout << ans << endl;

    return 0;
}
