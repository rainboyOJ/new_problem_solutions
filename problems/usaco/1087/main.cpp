/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 20:07
 * update_at: 2026-07-11 20:08
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, q;
string s;
int prefix_cnt[MAXN]; // prefix_cnt[i] 表示前 i 段栅栏最少需要多少笔
int suffix_cnt[MAXN]; // suffix_cnt[i] 表示第 i..n 段栅栏最少需要多少笔

// 把颜色 c 加入当前扫描段，必要时开启一笔新的颜色。
void add_color(stack<char> &st, char c, int &cnt) {
    while (!st.empty() && st.top() > c) {
        st.pop();
    }
    if (st.empty() || st.top() < c) {
        st.push(c);
        cnt++;
    }
}

void build_prefix() {
    stack<char> st;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        add_color(st, s[i], cnt);
        prefix_cnt[i] = cnt;
    }
}

void build_suffix() {
    stack<char> st;
    int cnt = 0;
    for (int i = n; i >= 1; i--) {
        add_color(st, s[i], cnt);
        suffix_cnt[i] = cnt;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    cin >> s;
    s = " " + s;

    build_prefix();
    build_suffix();

    for (int i = 1; i <= q; i++) {
        int a, b;
        cin >> a >> b;
        cout << prefix_cnt[a - 1] + suffix_cnt[b + 1] << '\n';
    }

    return 0;
}
