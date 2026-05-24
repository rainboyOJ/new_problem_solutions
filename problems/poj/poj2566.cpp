#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long ll;

const int N = 100005; // 题目范围 1e5，稍微开大一点
const ll INF = 1e18;  // 足够大的初始值
int n, k;

struct Node {
    ll val;
    int id;
    // 重载小于号，sort 时自动调用
    bool operator<(const Node &other) const {
        return val < other.val;
    }
} p[N]; // 全局大数组

ll _abs(ll t) { return t < 0 ? -t : t;}

void work(ll t) {
    // 初始化答案状态
    ll min_gap = INF;
    ll ans_sum = 0;
    int ans_l = 0, ans_r = 0;

    // 双指针初始化
    int l = 0, r = 1;

    // 4. 双指针扫描单调数组
    // 只要 r 没越界，并且 l 也没越界 (实际上 r 会先触顶)
    while (r <= n && l <= n) {
        ll diff = p[r].val - p[l].val;
        ll gap = _abs(diff - t);

        // 尝试更新最优解
        if (gap < min_gap) {
            min_gap = gap;
            ans_sum = diff;
            ans_l = p[l].id;
            ans_r = p[r].id;
        }

        // 剪枝：如果已经完美匹配，无需继续
        if (gap == 0) break;

        // 移动策略
        if (diff < t) r++;      // 差小了 -> 扩大右边界
        else l++;               // 差大了 -> 扩大左边界

        // 撞车保护：区间长度至少为 1
        if (l == r) r++;
    }

    // 输出结果
    // 题目要求输出区间 [min_id + 1, max_id]
    if (ans_l > ans_r) swap(ans_l, ans_r);
    cout << ans_sum << " " << ans_l + 1 << " " << ans_r << "\n";
}

int main() {
    // 关流加速，竞赛必备
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> n >> k && (n || k)) {

        // 1. 初始化并构建前缀和
        // p[0] 永远是 0，代表空前缀
        p[0] = {0, 0};

        for (int i = 1; i <= n; ++i) {
            int x;
            cin >> x;
            // 直接利用上一个位置累加，不需要原数组 a[]
            p[i].val = p[i - 1].val + x;
            p[i].id = i;
        }

        // 2. 排序
        // 注意范围是 [0, n]，所以要 sort 到 p + n + 1
        sort(p, p + n + 1);

        // 3. 处理 k 次查询
        while (k--) {
            ll t;
            cin >> t;
            work(t);

        }
    }
    return 0;
}