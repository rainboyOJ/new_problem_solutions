/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:14
 * update_at: 2026-07-11 13:17
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int n;
string start_s;

int calc_score(string cur) {
    int cnt = 0;
    for (int i = 1; i < n; i += 2) {
        if (cur[i] == 'G') {
            cnt++;
        }
    }
    return cnt;
}

string do_reverse_prefix(string cur, int len) {
    reverse(cur.begin(), cur.begin() + len);
    return cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> start_s;

    queue<string> q;
    map<string, int> dist;

    q.push(start_s);
    dist[start_s] = 0;

    int best_score = -1;
    int best_steps = 0;

    while (!q.empty()) {
        string cur = q.front();
        q.pop();

        int steps = dist[cur];
        int score = calc_score(cur);
        if (score > best_score || (score == best_score && steps < best_steps)) {
            best_score = score;
            best_steps = steps;
        }

        // 枚举所有偶数长度前缀反转，遍历小数据下所有可达状态。
        for (int len = 2; len <= n; len += 2) {
            string nxt = do_reverse_prefix(cur, len);
            if (dist.count(nxt) == 0) {
                dist[nxt] = steps + 1;
                q.push(nxt);
            }
        }
    }

    cout << best_steps << '\n';

    return 0;
}
