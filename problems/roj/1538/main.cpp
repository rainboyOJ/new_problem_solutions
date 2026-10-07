/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:42
 * update_at: 2026-10-06 00:42
 */

#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;

const int MAXN = 500005; // 车厢数上限

ll cnt[MAXN]; // 未走过车厢的净人数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    char op;
    int m, p;
    int pos = 0;    // 主任已走到第几节车厢
    ll total = 0;   // 前 pos 节车厢的人数和
    for (int i = 0; i < k; ++i) {
        cin >> op >> m;
        if (op == 'A') {
            // 询问：把指针一站一站推进到 m，累计新经过车厢的人数
            while (pos < m) {
                ++pos;
                total += cnt[pos];
            }
            cout << total << '\n';
        } else {
            cin >> p;
            ll delta = (op == 'B') ? p : -p;
            if (m <= pos) {
                // 车厢已被走过：直接修正已统计的前缀和
                total += delta;
            } else {
                // 还没走到：先记在车厢上，等指针经过时再累加
                cnt[m] += delta;
            }
        }
    }
    return 0;
}
