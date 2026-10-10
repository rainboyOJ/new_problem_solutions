/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Rect { int x1, x2, y1, y2; };
Rect rects[30];
int match[30];              // 幻灯片 -> 当前占用它的编号
vector<int> adj[30];        // 编号 i 的邻接表（能落到的幻灯片）

bool augment(int i, bool seen[]) {
    for (size_t t = 0; t < adj[i].size(); t++) {
        int s = adj[i][t];
        if (seen[s]) continue;
        seen[s] = true;
        if (match[s] == -1 || augment(match[s], seen)) {
            match[s] = i;
            return true;
        }
    }
    return false;
}

// 删掉匹配边 (i, s) 后，编号 i 能否沿交错路绕回 s 重新落位
bool can_swap(int i, int s, int n) {
    bool seen[30] = {false};
    deque<int> q;
    for (size_t t = 0; t < adj[i].size(); t++) {
        int u = adj[i][t];
        if (u != s) { seen[u] = true; q.push_back(u); }
    }
    while (!q.empty()) {
        int t = q.front(); q.pop_front();
        int j = match[t];
        for (size_t t2 = 0; t2 < adj[j].size(); t2++) {
            if (adj[j][t2] == s) return true;
            int u = adj[j][t2];
            if (!seen[u]) { seen[u] = true; q.push_back(u); }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int heap_no = 0;
    int n;
    while (cin >> n && n != 0) {
        heap_no++;
        for (int i = 0; i < n; i++)
            cin >> rects[i].x1 >> rects[i].x2 >> rects[i].y1 >> rects[i].y2;
        // 编号 i 的坐标
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            adj[i].clear();
            for (int s = 0; s < n; s++) {
                if (rects[s].x1 <= x && x <= rects[s].x2 &&
                    rects[s].y1 <= y && y <= rects[s].y2)
                    adj[i].push_back(s);
            }
        }
        // 求一个完美匹配
        for (int s = 0; s < n; s++) match[s] = -1;
        for (int i = 0; i < n; i++) {
            bool seen[30] = {false};
            augment(i, seen);
        }

        int owner[30];
        for (int s = 0; s < n; s++) owner[s] = -1;
        bool perfect = true;
        for (int s = 0; s < n; s++)
            if (match[s] == -1) { perfect = false; break; }

        if (perfect) {
            // 编号 i 的当前匹配边是否必须
            int owner_by_num[30];
            for (int i = 0; i < n; i++) owner_by_num[i] = -1;
            for (int s = 0; s < n; s++) owner_by_num[match[s]] = s;
            for (int i = 0; i < n; i++) {
                int s = owner_by_num[i];
                if (!can_swap(i, s, n)) {
                    owner[s] = i;   // 必须边：幻灯片 s 被编号 i 唯一确定
                }
            }
        }

        vector<string> parts;
        for (int s = 0; s < n; s++) {
            if (owner[s] != -1) {
                string p = "(";
                p += (char)('A' + s);
                p += "," + to_string(owner[s] + 1) + ")";
                parts.push_back(p);
            }
        }
        cout << "Heap " << heap_no << "\n";
        if (parts.empty()) cout << "none\n";
        else {
            for (size_t i = 0; i < parts.size(); i++) {
                if (i) cout << " ";
                cout << parts[i];
            }
            cout << "\n";
        }
        cout << "\n";
    }
    return 0;
}
