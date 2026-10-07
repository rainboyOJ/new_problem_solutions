/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:40
 * update_at: 2026-10-07 15:48
 */
// main.cpp：正确答案。
// n 个人各写一份长度 m 的 N/Y 答案，其中恰有 p 人满分（答案 == 标准答案）、
// q 人零分（答案 == 标准答案逐位取反），求字典序最小的标准答案，无解输出 -1。
// 关键观察：满分人数就是"标准答案"这个串在输入中的出现次数，
// 零分人数就是"标准答案的反串"的出现次数；于是候选串可以由出现次数直接反推，
// 只有 p = q = 0 时候选有无穷多个，改用"前缀计数"贪心构造。
// 与 main.py 同一算法。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n, m, p, q;                      // 题面数据（人数、判断题数、满分人数、零分人数）
vector<string> forbid;              // p = q = 0 的禁止集合 A ∪ comp(A)，排序去重后使用
unordered_map<string, int> appear;  // 每个答案串被多少个人写出（只统计出现次数）

string ans;                         // 找到的标准答案
bool found;                         // 是否找到解

// 逐位取反：N 变 Y、Y 变 N。因为 m >= 1，comp(s) 永远不等于 s。
string comp(const string &s) {
    string t = s;
    for (size_t i = 0; i < t.size(); i++) {
        t[i] = (t[i] == 'N') ? 'Y' : 'N';
    }
    return t;
}

// 串 s 在输入中的出现次数，没出现过就是 0
int count_of(const string &s) {
    auto it = appear.find(s);
    if (it == appear.end()) return 0;
    return it->second;
}

// p + q > 0：标准答案 s 必须满足 cnt[s] == p 且 cnt[comp(s)] == q。
// 输入中每个出现过的串 x 都贡献两个候选：s = x（对应 p > 0，s 自己出现过）
// 和 s = comp(x)（对应 p == 0 < q，此时 cnt[comp(s)] == cnt[x] == q）。
// 任何合法 s 至少满足 cnt[s] > 0 或 cnt[comp(s)] > 0 之一，所以这样枚举一定不漏。
bool solve_by_counts() {
    bool ok = false;
    for (auto it = appear.begin(); it != appear.end(); ++it) {
        for (ll k = 0; k < 2; k++) {
            string s = (k == 0) ? it->first : comp(it->first);
            if (count_of(s) != p) continue;             // 满分人数必须正好是 p
            if (count_of(comp(s)) != q) continue;       // 零分人数必须正好是 q
            if (!ok || s < ans) {                       // 多解时取字典序最小
                ans = s;
                ok = true;
            }
        }
    }
    return ok;
}

// p == q == 0：标准答案和它的反串都不得出现在输入中，候选有无穷多个，
// 用前缀计数贪心逐位构造字典序最小的合法串。
// 前缀 pref 之下共有 2^rem 个长度 m 的串；只要 forbid 中以 pref 为前缀的串
// 少于 2^rem 个，就必定存在一条不受禁的延伸，这一位就可以定下来。
// 每次都在"当前前缀对应的区间"里二分，所以区间只会越缩越窄。
bool solve_free() {
    string s;                        // 已经确定下来的前缀
    ll lo = 0, hi = forbid.size();   // forbid[lo, hi) 是以 s 为前缀的那一段
    for (ll d = 0; d < m; d++) {
        ll rem = m - d - 1;          // 定下这一位后还剩多少位
        // 禁止串总数至多 6e4 个，rem >= 20 时 2^rem 必然更大，用大常数代替避免溢出
        ll limit = (rem >= 20) ? 1000000000000000000LL : (1LL << rem);
        bool picked = false;
        for (ll k = 0; k < 2 && !picked; k++) {
            char ch = (k == 0) ? 'N' : 'Y';   // 先试 N，保证字典序最小
            string pref = s + ch;
            string up = pref;
            up.append(rem, 'Z');              // 'Z' > 'Y'，pref 后面补满 Z 就是该前缀的上界
            ll nlo = lower_bound(forbid.begin() + lo, forbid.begin() + hi, pref) - forbid.begin();
            ll nhi = upper_bound(forbid.begin() + lo, forbid.begin() + hi, up) - forbid.begin();
            ll blocked = nhi - nlo;           // 这个前缀下被禁掉的串数
            if (blocked < limit) {            // 还留着不受禁的延伸，这一位就定成 ch
                s = pref;
                lo = nlo;
                hi = nhi;
                picked = true;
            }
        }
        if (!picked) return false;            // 两位都走不通，说明这一层无路可走
    }
    ans = s;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> p >> q;

    string s;
    if (p > 0 || q > 0) {
        // 只需要"每个答案串出现了几次"：满分人数与零分人数都由此读出
        for (ll i = 0; i < n; i++) {
            cin >> s;
            appear[s]++;
        }
    } else {
        // p = q = 0：只需要禁止集合 A ∪ comp(A)，不必统计次数
        for (ll i = 0; i < n; i++) {
            cin >> s;
            forbid.push_back(s);
            forbid.push_back(comp(s));
        }
        sort(forbid.begin(), forbid.end());
        forbid.erase(unique(forbid.begin(), forbid.end()), forbid.end());
    }

    if (p > 0 || q > 0) found = solve_by_counts();
    else found = solve_free();

    if (found) cout << ans << "\n";
    else cout << "-1\n";

    return 0;
}
