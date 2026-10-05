/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:19
 * update_at: 2026-10-06 00:19
 */

#include <algorithm>
#include <iostream>
#include <string>

typedef long long ll;

const int MAXN = 1e4 + 5; // 每组数据最多 1e4 个数字串

std::string word[MAXN]; // word[1..n] 保存当前这组的数字串

// 判断 a 是否为 b 的前缀（两串相等也算）
bool is_prefix(const std::string &a, const std::string &b) {
    if (a.size() > b.size()) return false;
    return b.compare(0, a.size(), a) == 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        int n;
        std::cin >> n;
        for (int i = 1; i <= n; ++i) std::cin >> word[i];

        // 关键结论：若存在前缀对，排序后它们一定相邻，所以只需检查 n-1 个相邻对
        std::sort(word + 1, word + n + 1);

        bool found = false; // found = 是否存在一对前缀关系
        for (int i = 1; i < n; ++i) {
            if (is_prefix(word[i], word[i + 1])) {
                found = true;
                break;
            }
        }

        // 题面的反直觉对应：有前缀对输出 NO，否则输出 YES
        std::cout << (found ? "NO" : "YES") << "\n";
    }
    return 0;
}
