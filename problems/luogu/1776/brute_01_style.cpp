// brute_01_style.cpp：选择序列风格暴力，每一层决定当前种宝物取几件。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, capacity;
int value[MAXN], weight[MAXN], item_count[MAXN];
int answer;

// dfs_choose(pos)：正在决定第 pos 种宝物取 0..item_count[pos] 件。
void dfs_choose(int pos, int used_weight, int total_value) {
    if (used_weight > capacity) {
        return;
    }

    if (pos == n + 1) {
        answer = max(answer, total_value);
        return;
    }

    for (int take = 0; take <= item_count[pos]; take++) {
        int next_weight = used_weight + take * weight[pos];
        int next_value = total_value + take * value[pos];
        if (next_weight > capacity) {
            break;
        }
        dfs_choose(pos + 1, next_weight, next_value);
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
    dfs_choose(1, 0, 0);

    cout << answer << '\n';
    return 0;
}
