/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:57
 * update_at: 2026-07-11 15:59
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n;
long long m;
string str;
char s[MAXN];
long long a[MAXN];
bool loss_left[MAXN];  // loss_left[i]：i 是一段 R 链右端的亏损点
bool loss_right[MAXN]; // loss_right[i]：i 是一段 L 链左端的亏损点

int pre_pos(int x) {
    if (x == 1) return n;
    return x - 1;
}

int next_pos(int x) {
    if (x == n) return 1;
    return x + 1;
}

long long calc_left_chain(int pos) {
    long long sum = 0;
    int j = pre_pos(pos);
    while (s[j] == 'R') {
        sum += a[j];
        j = pre_pos(j);
    }
    return sum;
}

long long calc_right_chain(int pos) {
    long long sum = 0;
    int j = next_pos(pos);
    while (s[j] == 'L') {
        sum += a[j];
        j = next_pos(j);
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    cin >> str;
    for (int i = 1; i <= n; i++) {
        s[i] = str[i - 1];
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ans += a[i];
        loss_left[i] = false;
        loss_right[i] = false;
    }

    // 相邻的 R L 会形成两个可能溢出的点。
    for (int i = 1; i <= n; i++) {
        int j = next_pos(i);
        if (s[i] == 'R' && s[j] == 'L') {
            loss_left[i] = true;
            loss_right[j] = true;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (loss_left[i]) {
            long long sum = calc_left_chain(i);
            ans -= min(sum, m);
        }
        if (loss_right[i]) {
            long long sum = calc_right_chain(i);
            ans -= min(sum, m);
        }
    }

    cout << ans << '\n';

    return 0;
}
