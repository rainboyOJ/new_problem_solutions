/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:00
 */
// brute.cpp：小数据暴力解，在小棋盘上递归枚举 L 型积木放置。
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;
int n, m;
unordered_map<unsigned long long, long long> memo;

long long dfs(unsigned long long used) {
    unordered_map<unsigned long long, long long>::iterator it = memo.find(used);
    if (it != memo.end()) {
        return it->second;
    }

    int total = n * m;
    int first = -1;
    for (int i = 0; i < total; i++) {
        if ((used & (1ULL << i)) == 0) {
            first = i;
            break;
        }
    }
    if (first == -1) {
        return 1;
    }

    int row = first / m;
    int column = first % m;
    long long answer = 0;
    for (int top = row - 1; top <= row; top++) {
        for (int left = column - 1; left <= column; left++) {
            if (top < 0 || top + 1 >= n || left < 0 || left + 1 >= m) {
                continue;
            }
            for (int missing = 0; missing < 4; missing++) {
                unsigned long long placement = 0;
                bool contains_first = false;
                for (int dr = 0; dr < 2; dr++) {
                    for (int dc = 0; dc < 2; dc++) {
                        int index = dr * 2 + dc;
                        if (index == missing) {
                            continue;
                        }
                        int cell = (top + dr) * m + left + dc;
                        placement |= 1ULL << cell;
                        if (cell == first) {
                            contains_first = true;
                        }
                    }
                }
                if (!contains_first || (used & placement) != 0) {
                    continue;
                }
                answer += dfs(used | placement);
            }
        }
    }

    answer %= MOD;
    memo[used] = answer;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    if ((n * m) % 3 != 0) {
        cout << 0 << '\n';
        return 0;
    }
    cout << dfs(0) % MOD << '\n';
    return 0;
}
