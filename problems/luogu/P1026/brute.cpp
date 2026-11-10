/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:06
 * update_at: 2026-11-11 00:06
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 暴力版本：DFS 搜索所有可能的 k-1 个切分点
int p, k_parts, word_cnt;
string total_str;
vector<string> dict;
int n;
int best_ans = 0;

int calc_interval(int l, int r) {
    int cnt = 0;
    for (int i = l; i <= r; ++i) {
        for (const string& w : dict) {
            int len = w.size();
            if (i + len - 1 <= r && total_str.substr(i, len) == w) {
                cnt++;
                break; // 同一起点只算一次
            }
        }
    }
    return cnt;
}

void dfs(int last_cut, int parts_done, int cur_sum) {
    if (parts_done == k_parts - 1) {
        cur_sum += calc_interval(last_cut + 1, n);
        best_ans = max(best_ans, cur_sum);
        return;
    }

    // 枚举下一个切分点
    for (int cut = last_cut + 1; cut <= n - (k_parts - parts_done); ++cut) {
        dfs(cut, parts_done + 1, cur_sum + calc_interval(last_cut + 1, cut));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> p >> k_parts)) return 0;

    total_str = " ";
    for (int i = 0; i < p; ++i) {
        string line;
        cin >> line;
        total_str += line;
    }

    cin >> word_cnt;
    dict.resize(word_cnt);
    for (int i = 0; i < word_cnt; ++i) {
        cin >> dict[i];
    }

    n = total_str.size() - 1;
    best_ans = 0;
    dfs(0, 0, 0);

    cout << best_ans << "\n";

    return 0;
}
