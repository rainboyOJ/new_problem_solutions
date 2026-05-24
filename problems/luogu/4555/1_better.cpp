/**
 * P4555 [国家集训队] 最长双回文串 - 单调队列优化版
 * * 核心思路:
 * 1. Manacher 算法求出所有本质不同的最大回文区间。
 * 2. 使用单调队列(滑动窗口)在 O(N) 时间内：
 * - 正向扫描：计算以 i 结尾的最长回文长度 (max_end)
 * - 逆向扫描：计算以 i 开头的最长回文长度 (max_start)
 */

#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

struct Interval {
    int l, c, r; // Left boundary, Center, Right boundary (在变换串 t 中的下标)
};

struct Manacher {
    string t;           // 变换后的字符串
    vector<int> p;      // 半径数组
    vector<Interval> nodes; // 存储所有最大回文区间

    void build(const char* s) {
        int n = strlen(s);
        
        // 1. 构造变换串
        t.resize(n * 2 + 3);
        int m = 0;
        t[m++] = '$'; t[m++] = '#';
        for (int i = 0; i < n; ++i) {
            t[m++] = s[i];
            t[m++] = '#';
        }
        t[m] = '^'; // 这里的 m 不含 null，只是为了标记逻辑结束
        
        // 2. 计算 P 数组并收集区间
        p.assign(m, 0);
        nodes.clear();
        int center = 0, right = 0;
        
        for (int i = 1; i < m; ++i) {
            int mirror = 2 * center - i;
            if (i < right) p[i] = min(right - i, p[mirror]);
            else p[i] = 1;

            while (t[i + p[i]] == t[i - p[i]]) p[i]++;

            if (i + p[i] > right) {
                center = i;
                right = i + p[i];
                // 记录区间 [i-p[i]+1, i+p[i]-1] -> 这里存的是右开区间的 right bound 还是闭区间?
                // 原代码逻辑：l = center-(right-i), r = right. 
                // 对应闭区间 [left, right]
                nodes.push_back({i - p[i] + 1, i, i + p[i] - 1});
            }
        }
    }
};

int max_end[MAXN * 2 + 5];   // 以 i 结尾的最长回文长度 (对应 X 部分)
int max_start[MAXN * 2 + 5]; // 以 i 开头的最长回文长度 (对应 Y 部分)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    static char s[MAXN];
    if (scanf("%s", s) != 1) return 0;

    Manacher man;
    man.build(s);
    int m = man.t.size(); // 变换串实际长度

    // ---------------------------------------------------------
    // 步骤 1: 正向扫描 (计算 X 部分)
    // 逻辑：对于分割点 i，寻找 center <= i 且 right >= i 的最优区间
    // ---------------------------------------------------------
    deque<Interval> q;
    int idx = 0;
    
    // nodes 里的区间天然是按 center 从小到大排序的
    for (int i = 1; i < m - 1; ++i) {
        if (man.t[i] != '#') continue; // 只在空隙处分割

        // 1. 入队：加入中心点在 i 左侧的区间
        while (idx < man.nodes.size() && man.nodes[idx].c <= i) {
            // 这里不需要像逆向那样做强剪枝，因为按 center 顺序加入，
            // 越晚加入的 center 越靠右，产生的长度 (i - c) 越小。
            // 我们取队首（center 最小，长度最大），只要它能覆盖到 i 即可。
            q.push_back(man.nodes[idx++]);
        }

        // 2. 出队：移除右边界够不到 i 的无效区间
        while (!q.empty() && q.front().r < i) {
            q.pop_front();
        }

        // 3. 更新答案：队首即为中心最靠左（半径最大）的有效区间
        if (!q.empty()) {
            // 长度 = (i - center) * 2? 不，变换串中距离即真实长度
            // 例子：# a # b #，center=a(2), i=#(3). len = 3-2 = 1 ('a')
            max_end[i] = i - q.front().c;
        }
    }

    // ---------------------------------------------------------
    // 步骤 2: 逆向扫描 (计算 Y 部分)
    // 逻辑：对于分割点 i，寻找 center >= i 且 left <= i 的最优区间
    // ---------------------------------------------------------
    q.clear();
    idx = man.nodes.size() - 1;

    // 从右往左扫
    for (int i = m - 2; i >= 1; --i) {
        if (man.t[i] != '#') continue;

        // 1. 入队：加入中心点在 i 右侧的区间
        while (idx >= 0 && man.nodes[idx].c >= i) {
            const auto& curr = man.nodes[idx];
            
            // [单调性优化 - 你的核心逻辑]
            // 如果新来的区间(center更小)的左边界 比 队尾(center更大)的左边界 还大，
            // 说明新区间被完全“支配”了（范围小且中心并不更远），直接丢弃。
            // 只有当 curr.l < q.back().l 时，新区间才有入队价值（因为它能覆盖更左边的 i）。
            if (!q.empty() && q.back().l <= curr.l) {
                // do nothing, skip current
            } else {
                q.push_back(curr);
            }
            idx--;
        }

        // 2. 出队：移除左边界在 i 右边的无效区间
        while (!q.empty() && q.front().l > i) {
            q.pop_front();
        }

        // 3. 更新答案：队首即为中心最靠右的有效区间
        if (!q.empty()) {
            max_start[i] = q.front().c - i;
        }
    }

    // ---------------------------------------------------------
    // 步骤 3: 合并答案
    // ---------------------------------------------------------
    int ans = 0;
    for (int i = 1; i < m - 1; ++i) {
        if (man.t[i] == '#' && max_end[i] > 0 && max_start[i] > 0) {
            ans = max(ans, max_end[i] + max_start[i]);
        }
    }

    printf("%d\n", ans);

    return 0;
}
