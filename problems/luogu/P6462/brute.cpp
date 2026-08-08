#include <bits/stdc++.h>
using namespace std;

int T;
long long h, x, y;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;

    while (T--) {
        cin >> h >> x >> y;

        // brute.cpp：小数据暴力。
        // 用集合维护“每次轮到英雄选择时，小兵可能剩下多少血”，
        // 枚举攻击/不攻击两种选择。
        set<long long> cur, nxt, seen;
        cur.insert(h);
        seen.insert(h);

        bool ok = false;

        while (!cur.empty() && !ok) {
            nxt.clear();

            for (long long hp : cur) {
                for (int atk = 0; atk <= 1; atk++) {
                    long long hp2 = hp - 1LL * atk * y;

                    if (atk == 1 && hp2 <= 0) {
                        ok = true;
                        break;
                    }

                    long long hp3 = hp2 - x;
                    if (hp3 <= 0) {
                        continue;
                    }

                    if (!seen.count(hp3)) {
                        seen.insert(hp3);
                        nxt.insert(hp3);
                    }
                }

                if (ok) {
                    break;
                }
            }

            cur.swap(nxt);
        }

        if (ok) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
