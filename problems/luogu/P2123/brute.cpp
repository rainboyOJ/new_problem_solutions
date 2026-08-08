// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;

struct Person {
    long long left_num;
    long long right_num;
};

int n;
Person people[MAXN];
int order_id[MAXN];

long long calc_order() {
    long long prefix_left = 0;
    long long last_reward = 0;
    for (int i = 0; i < n; i++) {
        int id = order_id[i];
        prefix_left += people[id].left_num;
        last_reward = max(last_reward, prefix_left) + people[id].right_num;
    }
    return last_reward;
}

void solve_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> people[i].left_num >> people[i].right_num;
        order_id[i] = i;
    }

    long long ans = -1;
    do {
        long long now = calc_order();
        if (ans == -1 || now < ans) {
            ans = now;
        }
    } while (next_permutation(order_id, order_id + n));

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve_case();
    }

    return 0;
}
