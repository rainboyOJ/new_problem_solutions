#include <bits/stdc++.h>
using namespace std;

int n, k;
int answer;

// 暴力 DFS：
// 按非递减顺序枚举每一份的大小，这样天然不会把不同排列重复统计。
void dfs(int left_sum, int left_cnt, int last_part) {
    if (left_cnt == 0) {
        if (left_sum == 0) {
            answer++;
        }
        return;
    }

    // 至少还要留下 left_cnt - 1 个数，每个数都不小于当前选择的 x。
    for (int x = last_part; x <= left_sum; x++) {
        if (left_sum - x < left_cnt - 1) {
            break;
        }
        dfs(left_sum - x, left_cnt - 1, x);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    dfs(n, k, 1);
    cout << answer << '\n';
    return 0;
}
