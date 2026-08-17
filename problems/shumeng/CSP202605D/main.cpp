/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

const int LOG = 21; // 2^21 > 1e6

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    // 奇数下标与偶数下标各自的异或前缀和
    vector<unsigned int> prefix_odd(n + 1, 0);
    vector<unsigned int> prefix_even(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        unsigned int value;
        cin >> value;
        prefix_odd[i] = prefix_odd[i - 1];
        prefix_even[i] = prefix_even[i - 1];
        if (i & 1) prefix_odd[i] ^= value;
        else prefix_even[i] ^= value;
    }

    // 逆序扫描后，latest 保存当前后缀中每种前缀异或值的最小位置。
    // 键带一个奇数/偶数标记位，避免两类前缀异或互相串扰。
    unordered_map<unsigned long long, int> latest;
    latest.reserve((n + 1) * 4);
    vector<int> first_good_end(n + 1, n + 1);
    for (int left = n; left >= 1; left--) {
        unsigned long long odd_key =
            (static_cast<unsigned long long>(prefix_odd[left]) << 1) | 1ULL;
        unsigned long long even_key =
            (static_cast<unsigned long long>(prefix_even[left]) << 1);
        latest[odd_key] = left;
        latest[even_key] = left;

        unsigned long long target_key;
        if (left & 1) {
            target_key =
                (static_cast<unsigned long long>(prefix_odd[left - 1]) << 1) | 1ULL;
        } else {
            target_key =
                (static_cast<unsigned long long>(prefix_even[left - 1]) << 1);
        }
        unordered_map<unsigned long long, int>::iterator it =
            latest.find(target_key);
        if (it != latest.end()) first_good_end[left] = it->second;
    }

    // 选择起点不小于 left 的所有必胜区间中，结束位置最靠前的一个。
    // jump[left] 是选完一次最优区间后的下一个起点（结束位置 + 1）。
    vector<int> jump(n + 3, n + 2);
    int best_end = n + 1;
    for (int left = n; left >= 1; left--) {
        best_end = min(best_end, first_good_end[left]);
        if (best_end <= n) jump[left] = best_end + 1;
    }
    jump[n + 1] = n + 2;

    // 对跳转关系做倍增，询问时用二进制拆分快速计数
    vector<vector<int>> up(LOG, vector<int>(n + 3, n + 2));
    for (int i = 1; i <= n + 1; i++) up[0][i] = jump[i];
    for (int level = 1; level < LOG; level++) {
        for (int i = 1; i <= n + 1; i++) {
            up[level][i] = up[level - 1][up[level - 1][i]];
        }
    }

    // 对每个询问做贪心区间调度：从 left 开始，只要下一个区间还落在 [L,R] 内就选择
    for (int query = 0; query < q; query++) {
        int left, right;
        cin >> left >> right;
        int current = left;
        int answer = 0;
        for (int level = LOG - 1; level >= 0; level--) {
            int next_position = up[level][current];
            if (next_position <= right + 1) { // 选择 2^level 个区间后仍不越界
                current = next_position;
                answer += 1 << level;
            }
        }
        cout << answer << '\n';
    }
    return 0;
}
