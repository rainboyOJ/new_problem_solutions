#include <bits/stdc++.h>
using namespace std;

const int INF_NEG = -1000000000;

struct Bill {
    int value;
    int owner;
};

int x1, x2, x3;
int cnt[3][6];
int deno[6] = {100, 50, 20, 10, 5, 1};
vector<Bill> bills;
vector<int> dp, ndp;

int id(int a, int b, int lim_b) {
    return a * (lim_b + 1) + b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> x1 >> x2 >> x3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            cin >> cnt[i][j];
        }
    }

    int init_money[3] = {0, 0, 0};
    int total_value = 0;
    int total_bills = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 6; j++) {
            init_money[i] += cnt[i][j] * deno[j];
            total_value += cnt[i][j] * deno[j];
            total_bills += cnt[i][j];
            for (int t = 0; t < cnt[i][j]; t++) {
                bills.push_back({deno[j], i});
            }
        }
    }

    int target_a = init_money[0] - x1 + x3;
    int target_b = init_money[1] + x1 - x2;
    int target_c = init_money[2] + x2 - x3;

    if (target_a < 0 || target_b < 0 || target_c < 0 ||
        target_a + target_b + target_c != total_value) {
        cout << "impossible\n";
        return 0;
    }

    dp.assign((target_a + 1) * (target_b + 1), INF_NEG);
    ndp.assign((target_a + 1) * (target_b + 1), INF_NEG);
    dp[id(0, 0, target_b)] = 0;

    int processed_value = 0;

    for (size_t idx = 0; idx < bills.size(); idx++) {
        fill(ndp.begin(), ndp.end(), INF_NEG);
        int v = bills[idx].value;
        int owner = bills[idx].owner;

        int max_a = min(target_a, processed_value);
        for (int a = 0; a <= max_a; a++) {
            int low_b = processed_value - a - target_c;
            if (low_b < 0) {
                low_b = 0;
            }
            int high_b = processed_value - a;
            if (high_b > target_b) {
                high_b = target_b;
            }
            for (int b = low_b; b <= high_b; b++) {
                int cur = dp[id(a, b, target_b)];
                if (cur == INF_NEG) {
                    continue;
                }

                if (a + v <= target_a) {
                    int &ref = ndp[id(a + v, b, target_b)];
                    ref = max(ref, cur + (owner == 0));
                }

                if (b + v <= target_b) {
                    int &ref = ndp[id(a, b + v, target_b)];
                    ref = max(ref, cur + (owner == 1));
                }

                int next_c = processed_value + v - a - b;
                if (next_c <= target_c) {
                    int &ref = ndp[id(a, b, target_b)];
                    ref = max(ref, cur + (owner == 2));
                }
            }
        }

        processed_value += v;
        dp.swap(ndp);
    }

    int stay_best = dp[id(target_a, target_b, target_b)];
    if (stay_best == INF_NEG) {
        cout << "impossible\n";
    } else {
        cout << total_bills - stay_best << '\n';
    }

    return 0;
}
