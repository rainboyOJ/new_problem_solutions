/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:10
 * update_at: 2026-07-11 17:11
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

char opposite_char(char c) {
    if (c == 'M') {
        return 'O';
    }
    return 'M';
}

int bfs_solve(string start) {
    queue<string> q;
    map<string, int> dis;

    q.push(start);
    dis[start] = 0;

    while (!q.empty()) {
        string cur = q.front();
        q.pop();

        int d = dis[cur];
        if (cur == "MOO") {
            return d;
        }

        int len = (int)cur.size();
        if (len == 0) {
            continue;
        }

        string nxt;

        // 操作 1：翻转第一个字符。
        nxt = cur;
        nxt[0] = opposite_char(nxt[0]);
        if (dis.find(nxt) == dis.end()) {
            dis[nxt] = d + 1;
            q.push(nxt);
        }

        // 操作 1：翻转最后一个字符。
        nxt = cur;
        nxt[len - 1] = opposite_char(nxt[len - 1]);
        if (dis.find(nxt) == dis.end()) {
            dis[nxt] = d + 1;
            q.push(nxt);
        }

        // 操作 2：删除第一个字符。
        nxt = cur.substr(1);
        if (dis.find(nxt) == dis.end()) {
            dis[nxt] = d + 1;
            q.push(nxt);
        }

        // 操作 2：删除最后一个字符。
        nxt = cur.substr(0, len - 1);
        if (dis.find(nxt) == dis.end()) {
            dis[nxt] = d + 1;
            q.push(nxt);
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        cout << bfs_solve(s) << '\n';
    }

    return 0;
}
