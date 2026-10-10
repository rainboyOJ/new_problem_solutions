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

const int INF = 1 << 30;

// 左部：横向极大非墙壁段；右部：纵向极大非墙壁段
vector<int> adj[10005];   // 左部点的邻接表（右部点编号）
int match_l[10005];       // 横向段 -> 纵向段，-1 未配
int match_r[10005];       // 纵向段 -> 横向段
int distl[10005];         // 左部点层号

// BFS 分层，返回最短增广路长度，没有则返回 INF
int bfs_layers(int lefts) {
    queue<int> q;
    for (int u = 0; u < lefts; u++) {
        if (match_l[u] < 0) { distl[u] = 0; q.push(u); }
        else distl[u] = INF;
    }
    int shortest = INF;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (distl[u] >= shortest) continue;
        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            int w = match_r[v];
            if (w < 0) shortest = distl[u] + 1;
            else if (distl[w] == INF) {
                distl[w] = distl[u] + 1;
                q.push(w);
            }
        }
    }
    return shortest;
}

// 沿分层方向找一条长度恰为 shortest 的增广路并翻转
bool augment(int root, int shortest) {
    // 显式栈：帧 [当前横向段, 下一个待试邻居下标]
    vector<pair<int, int> > stack;
    stack.push_back(make_pair(root, 0));
    vector<pair<int, int> > path;   // 交替路上的未匹配边 (横向段, 纵向段)
    while (!stack.empty()) {
        int u = stack.back().first;
        int& fi = stack.back().second;
        if (fi == (int)adj[u].size()) {
            distl[u] = INF;
            stack.pop_back();
            if (!path.empty()) path.pop_back();
            continue;
        }
        int v = adj[u][fi];
        fi++;
        int w = match_r[v];
        if (w < 0) {
            if (distl[u] + 1 != shortest) continue;
            match_l[u] = v;
            match_r[v] = u;
            for (size_t i = 0; i < path.size(); i++) {
                match_l[path[i].first] = path[i].second;
                match_r[path[i].second] = path[i].first;
            }
            return true;
        }
        if (distl[w] == distl[u] + 1) {
            path.push_back(make_pair(u, v));
            stack.push_back(make_pair(w, 0));
        }
    }
    return false;
}

int hopcroft_karp(int lefts, int rights) {
    for (int i = 0; i < lefts; i++) match_l[i] = -1;
    for (int i = 0; i < rights; i++) match_r[i] = -1;
    int matched = 0;
    while (true) {
        int shortest = bfs_layers(lefts);
        if (shortest == INF) return matched;
        for (int root = 0; root < lefts; root++) {
            if (match_l[root] < 0 && augment(root, shortest)) matched++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int case_no = 1; case_no <= T; case_no++) {
        int rows, cols;
        cin >> rows >> cols;
        vector<string> grid(rows);
        for (int i = 0; i < rows; i++) cin >> grid[i];

        // 每格所属的横向极大非墙段编号（墙 = -1）
        vector<vector<int> > table(rows, vector<int>(cols));
        int lefts = 0;
        for (int r = 0; r < rows; r++) {
            int seg = -1;
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '#') seg = -1;
                else if (seg < 0) { seg = lefts; lefts++; }
                table[r][c] = seg;
            }
        }
        for (int i = 0; i < lefts; i++) adj[i].clear();

        // 纵向段：每段内每个空地格所在的横向段就是它的邻居
        int vertical_cnt = 0;
        for (int c = 0; c < cols; c++) {
            int r = 0;
            while (r < rows) {
                if (grid[r][c] == '#') { r++; continue; }
                int start = r;
                while (r < rows && grid[r][c] != '#') r++;
                for (int i = start; i < r; i++) {
                    if (grid[i][c] == 'o')
                        adj[table[i][c]].push_back(vertical_cnt);
                }
                vertical_cnt++;
            }
        }

        int ans = hopcroft_karp(lefts, vertical_cnt);
        cout << "Case :" << case_no << "\n" << ans << "\n";
    }
    return 0;
}
