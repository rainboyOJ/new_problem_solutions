/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:41
 * update_at: 2026-10-06 09:41
 */
#include <iostream>
using namespace std;

typedef long long ll;

ll cur[20]; // 当前长度的特殊质数
ll nxt[40]; // 下一长度的候选
int cur_cnt, nxt_cnt;

// 试除判素：合数必有一个不超过 sqrt(x) 的因子
bool is_prime(ll x) {
    if (x < 2) return false;
    for (ll d = 2; d * d <= x; ++d)
        if (x % d == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    if (!(cin >> n)) return 0;

    // 长度 1 的特殊质数，1 不算质数
    cur[0] = 2; cur[1] = 3; cur[2] = 5; cur[3] = 7;
    cur_cnt = 4;

    // 逐位生长：由长度 k 的特殊质数，末位接 {1,3,7,9} 并判素，得到长度 k+1
    for (int k = 1; k < n; ++k) {
        nxt_cnt = 0;
        for (int i = 0; i < cur_cnt; ++i) {
            for (int d = 0; d < 4; ++d) {
                ll tail = (d == 0) ? 1 : (d == 1) ? 3 : (d == 2) ? 7 : 9;
                ll x = cur[i] * 10 + tail;
                if (is_prime(x)) nxt[nxt_cnt++] = x;
            }
        }
        // 把 nxt 复制回 cur
        cur_cnt = nxt_cnt;
        for (int i = 0; i < cur_cnt; ++i) cur[i] = nxt[i];
    }

    for (int i = 0; i < cur_cnt; ++i) cout << cur[i] << '\n';
    return 0;
}
