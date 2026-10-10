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
const int W = 5, Hh = 7;
typedef vector<vector<int> > Board;

string encode_board(const Board &cols) {
    string s;
    for (int x = 0; x < W; x++) {
        s.push_back('|');
        for (int y = 0; y < (int)cols[x].size(); y++) {
            s += to_string(cols[x][y]); s.push_back(',');
        }
    }
    return s;
}

bool clear_once(const Board &cols, Board &out) {
    bool mark[W][Hh]; memset(mark, 0, sizeof(mark));
    int rows[Hh][W];
    for (int y = 0; y < Hh; y++) for (int x = 0; x < W; x++) rows[y][x] = y < (int)cols[x].size() ? cols[x][y] : -1;
    for (int y = 0; y < Hh; y++) {
        int x = 0;
        while (x < W) {
            int k = x;
            while (k + 1 < W && rows[y][x] != -1 && rows[y][k + 1] == rows[y][x]) k++;
            if (k - x >= 2) for (int i = x; i <= k; i++) mark[i][y] = true;
            x = k + 1;
        }
    }
    for (int x = 0; x < W; x++) {
        int y = 0;
        while (y < (int)cols[x].size()) {
            int k = y;
            while (k + 1 < (int)cols[x].size() && cols[x][k + 1] == cols[x][y]) k++;
            if (k - y >= 2) for (int i = y; i <= k; i++) mark[x][i] = true;
            y = k + 1;
        }
    }
    bool any = false;
    out.assign(W, vector<int>());
    for (int x = 0; x < W; x++) for (int y = 0; y < (int)cols[x].size(); y++) {
        if (mark[x][y]) any = true; else out[x].push_back(cols[x][y]);
    }
    return any;
}

bool slide_board(const Board &cols, int x, int y, int d, Board &res) {
    int x2 = x + d;
    if (x2 < 0 || x2 >= W || y >= (int)cols[x].size()) return false;
    Board moved = cols;
    if (y < (int)moved[x2].size()) {
        if (moved[x][y] == moved[x2][y]) return false;
        swap(moved[x][y], moved[x2][y]);
    } else {
        int color = moved[x][y];
        moved[x].erase(moved[x].begin() + y);
        moved[x2].push_back(color);
    }
    Board nxt = moved, tmp;
    while (clear_once(nxt, tmp)) nxt = tmp;
    res = nxt;
    return true;
}

bool search_board(const Board &cols, int depth, int limit, vector<set<string> > &seen, vector<array<int,3> > &path) {
    if (depth == limit) {
        for (int x = 0; x < W; x++) if (!cols[x].empty()) return false;
        return true;
    }
    string key = encode_board(cols);
    if (seen[depth].count(key)) return false;
    seen[depth].insert(key);
    for (int x = 0; x < W; x++) for (int y = 0; y < (int)cols[x].size(); y++) {
        int dirs[2] = {1, -1};
        for (int z = 0; z < 2; z++) {
            Board nxt;
            if (slide_board(cols, x, y, dirs[z], nxt) && search_board(nxt, depth + 1, limit, seen, path)) {
                path.push_back({x, y, dirs[z]});
                return true;
            }
        }
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int steps; if (!(cin >> steps)) return 0;
    Board columns(W);
    for (int x = 0; x < W; x++) { int color; while (cin >> color && color != 0) columns[x].push_back(color); }
    vector<set<string> > seen(steps);
    vector<array<int,3> > path;
    if (search_board(columns, 0, steps, seen, path)) {
        for (int i = (int)path.size() - 1; i >= 0; i--) cout << path[i][0] << ' ' << path[i][1] << ' ' << path[i][2] << '\n';
        if (path.empty()) cout << '\n';
    } else cout << -1 << '\n';
    return 0;
}
