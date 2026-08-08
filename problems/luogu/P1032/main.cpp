/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P1032 [NOIP 2002 提高组] 字串变换 */
/* BFS 求十步内从起始串到目标串的最少变换次数。 */

#include <bits/stdc++.h>
using namespace std;

string start_str, target;
string from[10], to[10]; // 替换规则
int rule_cnt;            // 规则数量

// BFS 状态：当前字符串
struct Node {
    string s;
    int step;
};

int bfs() {
    queue<Node> q;
    set<string> vis;
    q.push({start_str, 0});
    vis.insert(start_str);

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        if (cur.s == target) return cur.step;
        if (cur.step == 10) continue; // 超十步不考虑

        // 尝试每条规则
        for (int r = 0; r < rule_cnt; r++) {
            string& old_s = from[r];
            string& new_s = to[r];
            size_t pos = cur.s.find(old_s);

            // 一个规则可能有多个匹配位置
            while (pos != string::npos) {
                string next = cur.s;
                next.replace(pos, old_s.length(), new_s);

                if (vis.find(next) == vis.end()) {
                    vis.insert(next);
                    q.push({next, cur.step + 1});
                }

                // 继续向后查找
                pos = cur.s.find(old_s, pos + 1);
            }
        }
    }
    return -1; // 不可达
}

int main() {
    cin >> start_str >> target;
    string a, b;
    while (cin >> a >> b) {
        from[rule_cnt] = a;
        to[rule_cnt] = b;
        rule_cnt++;
    }

    int ans = bfs();
    if (ans == -1)
        cout << "NO ANSWER!\n";
    else
        cout << ans << "\n";

    return 0;
}
