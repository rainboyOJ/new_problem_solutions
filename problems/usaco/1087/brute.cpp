/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 20:07
 * update_at: 2026-07-11 20:08
 */
// brute.cpp：小数据暴力解，每个询问重新扫描左右两段。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, q;
string s;

// 计算 s[l..r] 这一段单独刷成目标颜色需要的最少笔数。
int count_segment(int l, int r) {
    stack<char> st;
    int cnt = 0;
    for (int i = l; i <= r; i++) {
        char c = s[i];
        while (!st.empty() && st.top() > c) {
            st.pop();
        }
        if (st.empty() || st.top() < c) {
            st.push(c);
            cnt++;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    cin >> s;
    s = " " + s;

    for (int i = 1; i <= q; i++) {
        int a, b;
        cin >> a >> b;
        int left_need = count_segment(1, a - 1);
        int right_need = count_segment(b + 1, n);
        cout << left_need + right_need << '\n';
    }

    return 0;
}
