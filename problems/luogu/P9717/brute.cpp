/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 17:40
 */
// P9717 暴力对拍解：直接照题意模拟，直到某个串第二次出现为止。
//
// 用哈希表记录出现过的串（这里直接把串本身当 key），每一步同时把所有 01
// 换成 10，第一次遇到重复串时，出现过的不同串个数就是答案。
//
// 只用来跑很短的串（生成器保证 n <= 12，答案不超过 O(n^2)），
// 与 n 到 1e7 的正解形成对照。
#include <bits/stdc++.h>
using namespace std;

string step(const string &s) {
    int n = (int)s.size();
    string t = s;
    for (int i = 0; i < n; i++)
        if (s[i] == '0' && s[(i + 1) % n] == '1') {
            t[i] = '1';
            t[(i + 1) % n] = '0';
        }
    return t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        unordered_set<string> seen;
        seen.insert(s);
        string cur = s;
        int cnt = 1;
        while (true) {
            cur = step(cur);
            if (seen.count(cur)) break;
            seen.insert(cur);
            cnt++;
        }
        cout << cnt << '\n';
    }
    return 0;
}
