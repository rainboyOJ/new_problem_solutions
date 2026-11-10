/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-09 17:35
 * update_at: 2026-11-09 22:39
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105;
const int INF = 1e9;

// 区间结构体：记录字符串匹配出的一个可用线段
struct Segment {
    int l;   // 区间左端点（0-indexed）
    int r;   // 区间右端点（0-indexed）
    int id;  // 对应第几个字符串（1-indexed）
    int pos; // 在原串 t 中的起始位置（1-indexed）
};

// 状态前驱记录：用于回溯最优方案
struct Step {
    int prev_idx; // 上一个状态位置
    int id;       // 本次使用的字符串编号
    int pos;      // 本次使用的起始位置
};

int n;
string t;
string s[MAXN];

int dp[MAXN];          // dp[i] 表示完全覆盖前缀 t[0..i-1] 所需的最少操作次数
Step pre[MAXN];        // pre[i] 记录 dp[i] 是从哪个状态转移而来的
vector<Segment> segs;  // 存储所有匹配出来的区间

void read_input() {
    cin >> t >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }
}

// 预处理：利用 string::find 找出所有字符串在文本 t 中的所有出现区间（允许重叠）
void build_segments() {
    segs.clear();
    for (int i = 1; i <= n; i++) {
        int len_s = s[i].size();
        size_t p = t.find(s[i], 0);
        while (p != string::npos) {
            int left = p;
            int right = left + len_s - 1;
            segs.push_back({left, right, i, left + 1});
            p = t.find(s[i], p + 1); // 允许重叠，从 p + 1 继续寻找下一个出现位置
        }
    }
}

void solve() {
    build_segments();

    int len_t = t.size();
    for (int i = 0; i <= len_t; i++) {
        dp[i] = INF;
    }
    dp[0] = 0;

    // dp[i]：前缀 [0..i-1] 已经全部覆盖
    for (int i = 0; i < len_t; i++) {
        if (dp[i] == INF) continue;

        // 枚举所有可以接在当前前缀后面的区间（要求区间的左端点落在已覆盖区域内，即 seg.l <= i）
        for (const auto &seg : segs) {
            if (seg.l <= i) {
                int next_idx = max(i, seg.r + 1); // 新覆盖到达的前缀边界
                if (dp[next_idx] > dp[i] + 1) {
                    dp[next_idx] = dp[i] + 1;
                    pre[next_idx] = {i, seg.id, seg.pos};
                }
            }
        }
    }

    // 无法覆盖整串
    if (dp[len_t] == INF) {
        cout << -1 << "\n";
        return;
    }

    // 从终点向前回溯提取方案
    vector<pair<int, int>> ans;
    int cur = len_t;
    while (cur > 0) {
        ans.push_back({pre[cur].id, pre[cur].pos});
        cur = pre[cur].prev_idx;
    }

    // 倒序恢复成从前到后的操作序列
    reverse(ans.begin(), ans.end());

    cout << ans.size() << "\n";
    for (const auto &op : ans) {
        cout << op.first << " " << op.second << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    if (cin >> q) {
        while (q--) {
            read_input();
            solve();
        }
    }
    return 0;
}
