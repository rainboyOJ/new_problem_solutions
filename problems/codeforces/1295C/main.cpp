/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-04 19:35
 * update_at: 2026-11-04 19:42
 */
/*
 * 思路(与 main.py 一致)：
 *   一趟 append 相当于「沿着 t 往下走，同时在 s 里只向右跳」，
 *   所以答案就是最少需要几趟。
 *
 * 关键优化：
 *   对每个字符维护它在 s 中的出现位置列表(天然有序)，
 *   用 upper_bound 找严格大于当前位置的第一个出现位置，
 *   把「线性扫描找下一个字符」换成 O(log |s|) 跳转。
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;

const int maxn = 2e5+5;
string s, t;
vector<int> pos[26];    // pos[c] = 字符 c 在 s 中出现的所有位置

void sol(){
    cin >> s >> t;

    for (int c = 0; c < 26; c++)
        pos[c].clear();
    for (int i = 0; i < (int)s.size(); i++)
        pos[s[i] - 'a'].push_back(i);

    int ans = 1;
    int cur = -1;                   // s 中已经用到的位置，-1 表示还没开始
    for (char ch : t) {
        vector<int> &p = pos[ch - 'a'];
        if (p.empty()) {            // t 里有 s 没有的字符，永远做不到
            ans = -1;
            break;
        }
        auto it = upper_bound(p.begin(), p.end(), cur);  // 严格大于 cur 的第一个位置
        if (it == p.end()) {        // s 后面没有这个字符了，只能重开一趟
            ans++;
            cur = p[0];
        } else {
            cur = *it;
        }
    }
    cout << ans << "\n";
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    int T;
    cin >> T;
    while (T--)
        sol();
    return 0;
}
