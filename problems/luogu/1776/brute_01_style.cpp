// brute_01_style.cpp：选择序列风格暴力，每一层决定当前种宝物取几件。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, capacity;
int value[MAXN], weight[MAXN], item_count[MAXN];
int choose_take[MAXN]; // choose_take[i] 表示第 i 种宝物取几件
int answer;

bool check() {
    int total_weight = 0;
    for (int i = 1; i <= n; i++) {
        total_weight += choose_take[i] * weight[i];
    }
    return total_weight <= capacity;
}

int calc_answer() {
    int total_value = 0;
    for (int i = 1; i <= n; i++) {
        total_value += choose_take[i] * value[i];
    }
    return total_value;
}

// dfs_choose(pos)：只负责决定第 pos 种宝物取 0..item_count[pos] 件。
void dfs_choose(int pos) {
    if (pos == n + 1) {
        if (check()) {
            int current_value = calc_answer();
            if (answer < current_value) answer = current_value;
        }
        return;
    }

    for (int take = 0; take <= item_count[pos]; take++) {
        choose_take[pos] = take;
        dfs_choose(pos + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> capacity;
    for (int i = 1; i <= n; i++) {
        cin >> value[i] >> weight[i] >> item_count[i];
    }

    answer = 0;
    dfs_choose(1);

    cout << answer << '\n';
    return 0;
}
