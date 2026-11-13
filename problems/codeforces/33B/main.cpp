/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 08:54
 * update_at: 2026-11-13 08:54
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 26 个小写英文字母的全源最短路距离矩阵
const long long INF = 1e15;
long long d[26][26];

int main() {
    // 提升标准流性能
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    if (!(cin >> s >> t)) return 0;

    // 长度不等无法通过纯字符替换达成一致
    if (s.length() != t.length()) {
        cout << -1 << "\n";
        return 0;
    }

    int n;
    cin >> n;

    // 1. 初始化最短路矩阵：自身到自身距离为 0，其余为无穷大
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            d[i][j] = (i == j ? 0 : INF);
        }
    }

    // 2. 读入字符变换规则，保留重边的最小花费
    for (int i = 0; i < n; ++i) {
        char u_ch, v_ch;
        long long w;
        cin >> u_ch >> v_ch >> w;
        int u = u_ch - 'a';
        int v = v_ch - 'a';
        d[u][v] = min(d[u][v], w);
    }

    // 3. Floyd-Warshall 算法求 26 个字母之间的全源最短路
    // 口诀：中转点 k 在最外层，两段都可达才相加
    for (int k = 0; k < 26; ++k) {
        for (int i = 0; i < 26; ++i) {
            if (d[i][k] == INF) continue;
            for (int j = 0; j < 26; ++j) {
                if (d[k][j] == INF) continue;
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    // 4. 逐位独立贪心匹配目标字母
    long long total_cost = 0;
    string res = "";
    int len = s.length();

    for (int i = 0; i < len; ++i) {
        int u = s[i] - 'a';
        int v = t[i] - 'a';

        long long best_cost = INF;
        int best_ch = -1;

        // 枚举汇聚目标字符 to ∈ ['a', 'z']
        for (int to = 0; to < 26; ++to) {
            if (d[u][to] < INF && d[v][to] < INF) {
                long long cur_cost = d[u][to] + d[v][to];
                if (cur_cost < best_cost) {
                    best_cost = cur_cost;
                    best_ch = to;
                }
            }
        }

        // 无法汇聚到任意一个公共字符，说明无解
        if (best_cost >= INF) {
            cout << -1 << "\n";
            return 0;
        }

        total_cost += best_cost;
        res.push_back((char)('a' + best_ch));
    }

    cout << total_cost << "\n";
    cout << res << "\n";
    return 0;
}
