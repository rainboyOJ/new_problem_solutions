/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:57
 * update_at: 2026-10-01 22:57
 */
// main.cpp：把两种颜色的历史压成“另一色最后值”的 DP，用最大/次大状态 O(1) 查排除当前值后的最优转移。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005;   // n <= 2e5
const int MAXV = 1000005;  // A_i <= 1e6，值直接当 DP 下标

// 哨兵值，表示“这个状态还不存在”。取 LL 最小值的一半而不是本身，给加法留出余量。
const ll NEG_INF = LLONG_MIN / 2;

int T, n;
int a[MAXN];           // a[i]：第 i 个数，值域不超过 1e6，正好当 DP 下标用，所以用 int
bool active_state[MAXV]; // active_state[x]：状态 x 是否已经出现过
ll dp[MAXV];           // dp[x]：另一颜色最后值为 x 时的最大得分（已减去 lazy_add）
ll lazy_add;           // 所有状态共享的加分，避免逐个改 dp
vector<int> touched;   // 本组数据用到过的状态编号，方便整组清理

// 最大、次大的状态编号与 dp 值（不含 lazy_add）。
// dp[x] 只会变大，lazy_add 对所有状态一视同仁，所以两个状态就够回答“排除某值后的最大值”。
int best_key, second_key;
ll best_value, second_value;

// 取状态 x 的真实得分；状态不存在时返回哨兵。
ll get_actual(int x) {
    if (!active_state[x]) {
        return NEG_INF;
    }
    return dp[x] + lazy_add;
}

// 取“除了状态 x 之外”的最大真实得分。
ll get_max_except(int x) {
    if (best_key == -1) {
        return NEG_INF;
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

// 某个状态的 dp 值变大后，用它刷新最大、次大两个记录。
void update_best(int x) {
    ll value = dp[x];

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

// 把状态 x 的真实得分抬高到 actual_value（只有更优才写入）。
void set_state(int x, ll actual_value) {
    if (active_state[x] && actual_value <= get_actual(x)) {
        return;
    }

    if (!active_state[x]) {
        active_state[x] = true;
        touched.push_back(x);
    }
    dp[x] = actual_value - lazy_add;

    update_best(x);
}

// 每组数据结束时，只清本组真正用过的状态，避免 O(值域) 重置。
void clear_case() {
    int cnt = touched.size();
    for (int i = 0; i < cnt; i++) {
        active_state[touched[i]] = false;
        dp[touched[i]] = 0;
    }
    touched.clear();

    lazy_add = 0;
    best_key = -1;
    second_key = -1;
    best_value = NEG_INF;
    second_value = NEG_INF;
}

void solve_one() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    clear_case();

    // 开局把第一个数染成任意一种颜色，此时“另一种颜色还没出现”，用状态 0 表示。
    int last_value = a[1];
    set_state(0, 0);

    for (int i = 2; i <= n; i++) {
        int x = a[i];

        // 选择二：把当前数染到另一种颜色上。
        // 之后角色互换，“另一色最后值”变成原来的 last_value。
        ll candidate = get_max_except(x);
        if (active_state[x]) {
            candidate = max(candidate, get_actual(x) + x);
        }

        // 选择一：把当前数染成和上一个数相同的颜色。
        // 只有 x == last_value 时才贡献 x，且所有状态一起加，用 lazy_add 表示。
        if (x == last_value) {
            lazy_add += x;
        }

        // 两种选择里取更优的，写到状态 last_value 上。
        ll current = get_actual(last_value);
        if (candidate > current) {
            set_state(last_value, candidate);
        }

        last_value = x;
    }

    ll ans = NEG_INF;
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
