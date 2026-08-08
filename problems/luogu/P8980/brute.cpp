#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解。
// 直接枚举 x，再模拟每轮后还有哪些候选数与它回答完全一致。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, Q;
        cin >> n >> Q;
        vector<int> a(Q + 1);
        for (int i = 1; i <= Q; i++) {
            cin >> a[i];
        }

        bool never_stop = false;
        int best = 1;

        for (int x = 1; x <= n; x++) {
            vector<int> cand;
            for (int y = 1; y <= n; y++) {
                cand.push_back(y);
            }

            int stop_round = Q + 1;

            for (int i = 1; i <= Q; i++) {
                int gx = gcd(x, a[i]);
                vector<int> next_cand;
                for (int y : cand) {
                    if (gcd(y, a[i]) == gx) {
                        next_cand.push_back(y);
                    }
                }
                cand.swap(next_cand);
                if ((int) cand.size() == 1) {
                    stop_round = i;
                    break;
                }
            }

            if (stop_round == Q + 1) {
                never_stop = true;
                break;
            }
            best = max(best, stop_round);
        }

        if (never_stop) {
            cout << "game won't stop\n";
        } else {
            cout << best << '\n';
        }
    }

    return 0;
}
