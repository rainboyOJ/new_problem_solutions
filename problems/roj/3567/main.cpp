/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int INF = 1000000000;

int n;
int a[1005];

// 冲突图 CSR
int deg[1005];
int start_[1006];
vector<int> edges;

// 二分染色，返回 color[1..n]；染不上返回空
vector<int> two_color(int first[]) {
    vector<int> color(n + 1, -1);
    for (int seed = 1; seed <= n; seed++) {
        if (color[seed] != -1) continue;
        color[seed] = 0;
        vector<int> q;
        q.push_back(seed);
        for (size_t qi = 0; qi < q.size(); qi++) {
            int u = q[qi];
            for (int t = start_[u]; t < start_[u + 1]; t++) {
                int v = edges[t];
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    q.push_back(v);
                } else if (color[v] == color[u]) {
                    return vector<int>();
                }
            }
        }
        // anchor：输入位置最早的成员，翻成 0
        int anchor = q[0];
        for (size_t i = 1; i < q.size(); i++)
            if (first[q[i]] < first[anchor]) anchor = q[i];
        if (color[anchor]) {
            for (size_t i = 0; i < q.size(); i++)
                color[q[i]] ^= 1;
        }
    }
    return color;
}

// 贪心产出字典序最小操作序列；凑不出 1..n 则返回空
string smallest_ops(const vector<int>& color) {
    vector<int> s1, s2;
    vector<string> ops;
    int ptr = 0, need = 1;
    while (need <= n) {
        bool b_now = !s1.empty() && s1.back() == need;
        bool d_now = !s2.empty() && s2.back() == need;
        if (ptr == n) {
            if (b_now) { s1.pop_back(); ops.push_back("b"); }
            else if (d_now) { s2.pop_back(); ops.push_back("d"); }
            else return string();
            need++;
            continue;
        }
        int v = a[ptr];
        bool push_s1 = color[v] == 0 && (s1.empty() || v < s1.back());
        bool push_s2 = color[v] == 1 && (s2.empty() || v < s2.back());
        if (push_s1) { s1.push_back(v); ops.push_back("a"); ptr++; }
        else if (b_now) { s1.pop_back(); ops.push_back("b"); need++; }
        else if (push_s2) { s2.push_back(v); ops.push_back("c"); ptr++; }
        else if (d_now) { s2.pop_back(); ops.push_back("d"); need++; }
        else return string();
    }
    string out;
    for (size_t i = 0; i < ops.size(); i++) {
        if (i) out += " ";
        out += ops[i];
    }
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> n)) { cout << "0\n"; return 0; }
    for (int i = 0; i < n; i++) cin >> a[i];
    // first[v] = 值 v 在输入里的位置
    int first[1005];
    for (int i = 0; i < n; i++) first[a[i]] = i;

    // build_conflicts
    int suf[1006];
    suf[n + 1] = INF;
    for (int i = n; i >= 1; i--) suf[i] = min(a[i - 1], suf[i + 1]);

    for (int v = 0; v <= n; v++) deg[v] = 0;
    for (int j = 1; j <= n; j++) {
        int mn = suf[j + 1];
        for (int i = 1; i < j; i++) {
            int x = a[i - 1];
            if (mn < x && x < a[j - 1]) {
                deg[x]++;
                deg[a[j - 1]]++;
            }
        }
    }
    start_[1] = 0;
    for (int u = 1; u <= n; u++) start_[u + 1] = start_[u] + deg[u];
    edges.assign(start_[n + 1], 0);
    vector<int> fill(start_, start_ + n + 2);
    for (int j = 1; j <= n; j++) {
        int mn = suf[j + 1];
        for (int i = 1; i < j; i++) {
            int x = a[i - 1];
            if (mn < x && x < a[j - 1]) {
                edges[fill[x]] = a[j - 1];
                fill[x]++;
                edges[fill[a[j - 1]]] = x;
                fill[a[j - 1]]++;
            }
        }
    }

    vector<int> color = two_color(first);
    string ans = color.empty() ? string() : smallest_ops(color);
    if (ans.empty()) cout << "0\n";
    else cout << ans << "\n";
    return 0;
}
