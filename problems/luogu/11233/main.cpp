#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int MAXV = 1000005;
const long long NEG = -(long long)4e18;

int T, n;
int a[MAXN];
bool active_state[MAXV];
long long dp[MAXV]; // dp[x] 表示另一种颜色最后一个数为 x 时的最优得分，统一减去 lazy
long long lazy_add;
vector<int> touched;
int best_key, second_key;              // dp 最大、次大的状态编号
long long best_value, second_value;    // 对应的 dp[x]，不包含 lazy_add

long long get_actual(int x) {
    if (!active_state[x]) {
        return NEG;
    }
    return dp[x] + lazy_add;
}

long long get_max_except(int x) {
    if (best_key == -1) {
        return NEG;
    }
    if (best_key != x) {
        return best_value + lazy_add;
    }
    return second_value + lazy_add;
}

void swap_best() {
    swap(best_key, second_key);
    swap(best_value, second_value);
}

// 某个状态的 dp[x] 只会变大，用最大、次大两个状态就能回答“排除 x 的最大值”。
void update_best(int x) {
    long long value = dp[x];

    if (best_key == x) {
        best_value = value;
        return;
    }

    if (second_key == x) {
        second_value = value;
        if (second_value > best_value) {
            swap_best();
        }
        return;
    }

    if (value > best_value) {
        second_key = best_key;
        second_value = best_value;
        best_key = x;
        best_value = value;
    } else if (value > second_value) {
        second_key = x;
        second_value = value;
    }
}

void set_state(int x, long long actual_value) {
    if (active_state[x] && actual_value <= get_actual(x)) {
        return;
    }

    if (active_state[x]) {
        dp[x] = actual_value - lazy_add;
    } else {
        active_state[x] = true;
        touched.push_back(x);
        dp[x] = actual_value - lazy_add;
    }

    update_best(x);
}

void clear_case() {
    for (int i = 0; i < (int)touched.size(); i++) {
        active_state[touched[i]] = false;
        dp[touched[i]] = 0;
    }
    touched.clear();
    lazy_add = 0;
    best_key = -1;
    second_key = -1;
    best_value = NEG;
    second_value = NEG;
}

void solve_one() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    clear_case();

    int last_value = a[1];
    set_state(0, 0);

    for (int i = 2; i <= n; i++) {
        int x = a[i];

        // 当前数染到“另一种颜色”时，新的另一色最后值会变成 last_value。
        long long candidate = get_max_except(x);
        if (active_state[x]) {
            candidate = max(candidate, get_actual(x) + x);
        }

        // 当前数染到和上一个数相同的颜色，所有状态都会得到这一段相邻相同的贡献。
        if (x == last_value) {
            lazy_add += x;
        }

        long long current = get_actual(last_value);
        if (candidate > current) {
            set_state(last_value, candidate);
        }

        last_value = x;
    }

    long long ans = NEG;
    if (best_key != -1) {
        ans = best_value + lazy_add;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        solve_one();
    }

    return 0;
}
