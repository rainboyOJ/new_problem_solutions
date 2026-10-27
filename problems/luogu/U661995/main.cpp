#include <bits/stdc++.h>
using namespace std;

struct Item {
    int weight, value;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int group_count, capacity;
    cin >> group_count >> capacity;
    // dp[c] 表示容量为 c 时的最大价值。
    vector<int> dp(capacity + 1, 0);
    for (int group_id = 1; group_id <= group_count; group_id++) {
        int item_count;
        cin >> item_count;
        vector<Item> group(item_count);
        for (int i = 0; i < item_count; i++) {
            cin >> group[i].weight >> group[i].value;
        }
        // 分组背包：每组最多选一个，需要用上一组的状态来转移。
        vector<int> previous = dp;
        for (int c = 0; c <= capacity; c++) {
            dp[c] = previous[c];           // 该组一个都不选
            for (const Item &item : group) {
                if (c < item.weight) continue;
                // 从上一组的状态 dp_old[c - w] 转移，避免同组内互相影响。
                dp[c] = max(dp[c], previous[c - item.weight] + item.value);
            }
        }
    }
    cout << dp[capacity] << '\n';
    return 0;
}
