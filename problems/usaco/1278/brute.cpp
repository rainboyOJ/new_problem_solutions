/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 19:05
 * update_at: 2026-07-11 19:08
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const string ALL = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

int T;

int bfs(string s, string target) {
    if (s == target) return 0;

    bool used[256];
    memset(used, 0, sizeof(used));

    vector<char> letters;
    for (int i = 0; i < (int)s.size(); i++) {
        if (!used[(unsigned char)s[i]]) {
            used[(unsigned char)s[i]] = true;
            letters.push_back(s[i]);
        }
        if (!used[(unsigned char)target[i]]) {
            used[(unsigned char)target[i]] = true;
            letters.push_back(target[i]);
        }
    }

    // 小数据暴力额外加入一个临时字符，用来打破环。
    for (int i = 0; i < (int)ALL.size(); i++) {
        if (!used[(unsigned char)ALL[i]]) {
            letters.push_back(ALL[i]);
            break;
        }
    }

    queue<string> q;
    map<string, int> dist;
    q.push(s);
    dist[s] = 0;

    while (!q.empty()) {
        string cur = q.front();
        q.pop();
        int d = dist[cur];

        for (int i = 0; i < (int)letters.size(); i++) {
            char from = letters[i];
            bool has_from = false;
            for (int p = 0; p < (int)cur.size(); p++) {
                if (cur[p] == from) {
                    has_from = true;
                    break;
                }
            }
            if (!has_from) continue;

            for (int j = 0; j < (int)letters.size(); j++) {
                char to = letters[j];
                if (from == to) continue;

                string nxt = cur;
                for (int p = 0; p < (int)nxt.size(); p++) {
                    if (nxt[p] == from) {
                        nxt[p] = to;
                    }
                }

                if (dist.find(nxt) == dist.end()) {
                    dist[nxt] = d + 1;
                    if (nxt == target) {
                        return d + 1;
                    }
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

    cin >> T;
    while (T--) {
        string s, t;
        cin >> s >> t;
        cout << bfs(s, t) << '\n';
    }

    return 0;
}
