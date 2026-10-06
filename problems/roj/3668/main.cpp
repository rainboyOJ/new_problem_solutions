/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:17
 * update_at: 2026-10-06 16:17
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int LIMIT = 12000000; // 筛表上界：x ≤ 1e7，答案可能略超 1e7
const int MAXN = LIMIT + 2;

char banned[MAXN]; // banned[i] = 1 表示 i 不能报出（十进制含 7 的数及其倍数）
int nxt[MAXN];     // nxt[i] = 不小于 i 的最小可报数，用于 O(1) 回答询问

// 判断 x 的十进制表示中是否含有数字 7。
bool has_seven(int x) {
    while (x > 0) {
        if (x % 10 == 7) return true;
        x /= 10;
    }
    return false;
}

// 预处理禁报标记与 nxt 表。
void build() {
    // 像埃氏筛一样，把每个含 7 的数当作筛子，标记它的全部倍数。
    for (int i = 1; i <= LIMIT; i++) {
        if (has_seven(i)) {
            for (int j = i; j <= LIMIT; j += i) {
                banned[j] = 1;
            }
        }
    }
    // 从后往前推：i 可报则 nxt[i] = i，否则继承 nxt[i + 1]。
    nxt[LIMIT + 1] = LIMIT + 1;
    for (int i = LIMIT; i >= 1; i--) {
        if (banned[i]) nxt[i] = nxt[i + 1];
        else nxt[i] = i;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build();

    ll T;
    cin >> T;
    for (ll t = 1; t <= T; t++) {
        ll x;
        cin >> x;
        if (nxt[x] != x) cout << -1 << '\n';
        else cout << nxt[x + 1] << '\n';
    }
    return 0;
}
