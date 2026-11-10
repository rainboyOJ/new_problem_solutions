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

// 区间结构体：记录字符串匹配出的一个可用线段
struct Segment {
    int l;   // 区间左端点（0-indexed）
    int r;   // 区间右端点（0-indexed）
    int id;  // 对应第几个字符串（1-indexed）
    int pos; // 在原串 t 中的起始位置（1-indexed）
};

// 操作方案记录
struct Operation {
    int id;
    int pos;
};

int n;
string t;
string s[MAXN];

vector<Segment> segs;     // 存储所有匹配出来的区间
vector<Operation> ans;    // 存储最终选择的操作步骤

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
    ans.clear();

    int len_t = t.size();
    int covered = 0; // 当前已经连续覆盖到 [0, covered - 1]

    // 经典区间贪心覆盖：每次在所有 l <= covered 的区间里，挑选 r 最大的那一个
    while (covered < len_t) {
        int max_r = -1;
        Segment best_seg;

        for (const auto &seg : segs) {
            if (seg.l <= covered && seg.r > max_r) {
                max_r = seg.r;
                best_seg = seg;
            }
        }

        // 如果找不到任何能越过 covered 的区间，说明出现断层，无解
        if (max_r < covered) {
            cout << -1 << "\n";
            return;
        }

        ans.push_back({best_seg.id, best_seg.pos});
        covered = max_r + 1; // 覆盖边界右移
    }

    cout << ans.size() << "\n";
    for (const auto &op : ans) {
        cout << op.id << " " << op.pos << "\n";
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
