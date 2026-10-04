/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:31
 * update_at: 2026-10-05 02:31
 */
#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

const int MAXN = 400005; // 题目给定所有字符串总长不超过 4×10^5

char s[MAXN];   // 输入串，下标从 1 开始，和题面对应
int pref[MAXN]; // pref[i] = s[1..i] 的最长真 border 长度（真 = 不等于自身）
int chain[MAXN]; // chain[1..cnt] 存当前串的全部 border 长度（回溯得到的是降序）

// 求字符串 s[1..n] 的前缀函数
void build_prefix_function(ll n) {
    pref[1] = 0;
    for (ll i = 2; i <= n; i++) {
        ll j = pref[i - 1];
        // 失配就沿 border 链回退，直到能继续匹配或退到空串
        while (j > 0 && s[i] != s[j + 1]) {
            j = pref[j];
        }
        if (s[i] == s[j + 1]) {
            j++;
        }
        pref[i] = j;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> (s + 1)) {
        ll n = 0;
        while (s[n + 1] != '\0') {
            n++;
        }
        build_prefix_function(n);

        // 全部 border：整串 n 是平凡 border，再沿 pref 链反复回退
        ll cnt = 0;
        ll j = n;
        while (j > 0) {
            cnt++;
            chain[cnt] = j;
            j = pref[j];
        }

        // 回溯顺序是降序的，倒着输出即为题目要求的递增顺序
        for (ll k = cnt; k >= 1; k--) {
            if (k < cnt) {
                cout << ' ';
            }
            cout << chain[k];
        }
        cout << '\n';
    }

    return 0;
}
