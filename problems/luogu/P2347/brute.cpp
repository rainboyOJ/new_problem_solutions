// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int TYPE_CNT = 6;
const int weight_value[TYPE_CNT + 1] = {0, 1, 2, 3, 5, 10, 20};
const int MAXW = 1005;

int cnt[TYPE_CNT + 1];     // 每种砝码的数量
bool reachable[MAXW];      // reachable[w] = 是否能称出重量 w
int total_weight;          // 所有砝码总重量

void dfs(int type_id, int current_sum) {
    if (type_id > TYPE_CNT) {
        if (current_sum > 0) {
            reachable[current_sum] = true;
        }
        return;
    }

    for (int use_cnt = 0; use_cnt <= cnt[type_id]; use_cnt++) {
        dfs(type_id + 1, current_sum + use_cnt * weight_value[type_id]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    total_weight = 0;
    for (int i = 1; i <= TYPE_CNT; i++) {
        cin >> cnt[i];
        total_weight += cnt[i] * weight_value[i];
    }

    memset(reachable, 0, sizeof(reachable));
    dfs(1, 0);

    int answer = 0;
    for (int w = 1; w <= total_weight; w++) {
        if (reachable[w]) {
            answer++;
        }
    }

    cout << "Total=" << answer << '\n';
    return 0;
}
