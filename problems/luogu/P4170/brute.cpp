// 小数据暴力：直接模拟"反复选区间涂色"的过程，不做任何区间 DP 推导。
// 状态是一块木板（'.' 表示还没涂过的位置），从全 '.' 出发，每次挑一段连续区间
// 涂上一个颜色，广度优先搜索最少需要几步才能把每个位置都涂成目标颜色。
// 已经和目标一致的位置允许继续被覆盖，最后再被更正回来，这正是题目允许的操作。
#include <bits/stdc++.h>
using namespace std;

static string target;

// 状态编码：每位一个字符，'.' 表示未涂。用字符串哈希表去重。
int bfs() {
    int n = (int)target.size();
    string start(n, '.');

    unordered_map<string, int> dist;
    queue<string> q;
    dist[start] = 0;
    q.push(start);

    auto done = [&](const string &state) {
        for (int i = 0; i < n; ++i) {
            if (state[i] != target[i]) {
                return false;
            }
        }
        return true;
    };

    while (!q.empty()) {
        string cur = q.front();
        q.pop();
        int d = dist[cur];
        if (done(cur)) {
            return d;
        }

        // 枚举所有区间 [l, r] 和所有颜色，暴力扩展。
        for (int l = 0; l < n; ++l) {
            for (int r = l; r < n; ++r) {
                for (char c : target) {
                    string nxt = cur;
                    bool changed = false;
                    for (int i = l; i <= r; ++i) {
                        if (nxt[i] != c) {
                            changed = true;
                        }
                        nxt[i] = c;
                    }
                    if (!changed) {
                        continue;
                    }
                    if (dist.count(nxt)) {
                        continue;
                    }
                    dist[nxt] = d + 1;
                    q.push(nxt);
                }
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> target;
    // 去重相邻相同字符不影响答案（一次涂色可以顺手带上），但这里连这一步都不做，
    // 保证暴力完全独立于正解的推理。
    cout << bfs() << '\n';
    return 0;
}
