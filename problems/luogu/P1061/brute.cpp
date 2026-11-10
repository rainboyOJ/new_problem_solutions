/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:16
 * update_at: 2026-11-11 00:16
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int s_idx, t_idx, w;
string initial_str;
vector<string> all_combinations;

void dfs(int cur_char_idx, string& current) {
    if ((int)current.size() == w) {
        all_combinations.push_back(current);
        return;
    }

    for (int idx = cur_char_idx; idx <= t_idx; ++idx) {
        current.push_back(static_cast<char>('a' + idx - 1));
        dfs(idx + 1, current);
        current.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> s_idx >> t_idx >> w)) return 0;
    if (!(cin >> initial_str)) return 0;

    string cur = "";
    dfs(s_idx, cur);

    // 在所有生成的递增序列中找到 initial_str 的位置
    auto it = upper_bound(all_combinations.begin(), all_combinations.end(), initial_str);

    int output_count = 0;
    while (it != all_combinations.end() && output_count < 5) {
        cout << *it << "\n";
        ++it;
        ++output_count;
    }

    return 0;
}
