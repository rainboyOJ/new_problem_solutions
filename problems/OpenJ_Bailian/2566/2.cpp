/**
 * Corrected Solution for "Bound Found" (POJ 2566 / UVA)
 */
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
typedef long long ll;

const int maxn = 100005;

struct Node {
    ll sum;
    int id;
    // 排序规则：按前缀和大小升序
    bool operator<(const Node &other) const {
        return sum < other.sum;
    }
};

Node pre[maxn];
int n, k;
ll t;

ll _abs(ll v) {
    return v < 0 ? -v : v;
}

void solve() {
    // 读取 N 和 K，如果都为0则结束。
    // 注意：这里采用了更稳健的读取方式放在 main 中，solve 只处理一次查询逻辑
    
    // 输入由 main 函数控制，这里只处理 queries
    for (int q = 0; q < k; ++q) {
        cin >> t;
        
        ll min_diff = 2e18; // 初始化为足够大的值 (long long max)
        ll ans_sum = 0;
        int ans_l = 0, ans_r = 0;

        // 双指针算法 O(N)
        // l: 左指针, r: 右指针
        int l = 0;
        int r = 1;
        
        while (r <= n && l < r) {
            // 计算当前两个前缀和的差值（即区间和）
            ll current_sum = pre[r].sum - pre[l].sum;
            ll diff = _abs(current_sum - t);

            // 如果找到了更优解（更接近 t）
            if (diff < min_diff) {
                min_diff = diff;
                ans_sum = current_sum;
                ans_l = pre[l].id;
                ans_r = pre[r].id;
            }

            // 移动指针策略
            if (current_sum < t) {
                // 如果当前和小于目标，需要增大和，右指针右移
                r++;
            } else if (current_sum > t) {
                // 如果当前和大于目标，需要减小和，左指针右移
                l++;
                // 保证区间非空，如果 l 追上了 r，r 必须也前进
                if (l == r) {
                    r++;
                }
            } else {
                // 如果相等，已经是最近了（距离为0），直接跳出
                break;
            }
        }

        // 恢复原始下标顺序
        // 前缀和 pre[i] 和 pre[j] 定义的区间是 (min_id + 1) 到 max_id
        int final_l = ans_l;
        int final_r = ans_r;
        if (final_l > final_r) swap(final_l, final_r);
        
        cout << ans_sum << " " << final_l + 1 << " " << final_r << "\n";
    }
}

int main() {
    // 优化 I/O
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> n >> k && (n != 0 || k != 0)) {
        pre[0].sum = 0;
        pre[0].id = 0;

        // 计算前缀和
        for (int i = 1; i <= n; ++i) {
            int val;
            cin >> val;
            pre[i].sum = pre[i - 1].sum + val;
            pre[i].id = i;
        }

        // 排序前缀和数组
        sort(pre, pre + 1 + n);

        // 处理 K 个查询
        solve();
    }

    return 0;
}
