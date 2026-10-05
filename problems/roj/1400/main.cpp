/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:53
 * update_at: 2026-10-05 12:53
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string w; // 给定单词，统一转小写
string s; // 文章

// 将字符串统一转小写
void to_lower(string &t) {
    for (ll i = 0; i < (ll)t.size(); i++) {
        if (t[i] >= 'A' && t[i] <= 'Z') t[i] = t[i] - 'A' + 'a';
    }
}

int main() {
    getline(cin, w);
    getline(cin, s);
    to_lower(w);

    ll cnt = 0;   // 出现次数
    ll first = -1; // 首次出现位置
    ll n = s.size();
    ll i = 0;
    while (i < n) {
        // 跳过连续空格
        while (i < n && s[i] == ' ') i++;
        if (i >= n) break;
        // 记录当前单词起点，并截取完整单词
        ll start = i;
        string cur;
        while (i < n && s[i] != ' ') {
            cur.push_back(s[i]);
            i++;
        }
        to_lower(cur);
        if (cur == w) {
            cnt++;
            if (first == -1) first = start;
        }
    }

    if (cnt == 0) {
        cout << -1 << "\n";
    } else {
        cout << cnt << " " << first << "\n";
    }
    return 0;
}
