/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-08-13 13:35
 */
/* P1032 [NOIP 2002 提高组] 字串变换 */
/* BFS：把字符串看成状态，一次替换是一条边，求十步内到目标串的最少步数。 */

#include <bits/stdc++.h>
using namespace std;

string start_str, target_str; // 起始串与目标串
string from[10], to[10];      // 变换规则：子串 from[i] 可以替换成 to[i]
int rule_cnt;                 // 规则数量

// BFS 队列元素：当前字符串和已经用的步数。
struct Node {
    string s;
    int step;
};

int bfs() {
    queue<Node> q;
    set<string> vis; // 判重：同一个字符串只需要访问一次
    q.push({start_str, 0});
    vis.insert(start_str);

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        if (cur.s == target_str)
            return cur.step; // BFS 第一次到达目标就是最少步数

        if (cur.step == 10)
            continue; // 十步以内（含十步）才允许继续变换

        // 尝试每一条规则
        for (int r = 0; r < rule_cnt; r++) {
            int flen = from[r].size();

            // 一条规则可能在当前串中出现多个位置，逐个替换
            size_t pos = cur.s.find(from[r]);
            while (pos != string::npos) {
                string next_s = cur.s.substr(0, pos) + to[r]
                              + cur.s.substr(pos + flen);

                if (vis.find(next_s) == vis.end()) {
                    vis.insert(next_s);
                    q.push({next_s, cur.step + 1});
                }

                // 从下一个位置继续找，避免漏掉重叠的出现
                pos = cur.s.find(from[r], pos + 1);
            }
        }
    }
    return -1; // 十步内不可达
}

int main() {
    cin >> start_str >> target_str;

    // 规则行读到 EOF 结束
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
