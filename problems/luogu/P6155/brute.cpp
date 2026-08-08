#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

const int MAXN = 12;

int n;
int a_arr[MAXN];
int b_arr[MAXN];
int order_arr[MAXN];
bool used[MAXN];
ull best_ans;

void dfs(int step, int cur_time) {
    if (step > n) {
        int wait_arr[MAXN];
        for (int i = 1; i <= n; i++) {
            wait_arr[i] = order_arr[i];
        }

        sort(wait_arr + 1, wait_arr + n + 1, greater<int>());
        ull cur = 0;
        for (int i = 1; i <= n; i++) {
            cur += (ull)wait_arr[i] * (ull)b_arr[i];
        }
        best_ans = min(best_ans, cur);
        return;
    }

    bool has_avail = false;
    for (int i = 1; i <= n; i++) {
        if (!used[i] && a_arr[i] <= cur_time) {
            has_avail = true;
            used[i] = true;
            order_arr[step] = cur_time - a_arr[i];
            dfs(step + 1, cur_time + 1);
            used[i] = false;
        }
    }

    if (!has_avail) {
        int next_time = INT_MAX;
        for (int i = 1; i <= n; i++) {
            if (!used[i]) {
                next_time = min(next_time, a_arr[i]);
            }
        }
        dfs(step, next_time);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a_arr[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b_arr[i];
    }

    sort(b_arr + 1, b_arr + n + 1);
    best_ans = numeric_limits<ull>::max();
    memset(used, 0, sizeof(used));

    int start_time = a_arr[1];
    for (int i = 2; i <= n; i++) {
        start_time = min(start_time, a_arr[i]);
    }

    dfs(1, start_time);
    cout << best_ans << '\n';
    return 0;
}
