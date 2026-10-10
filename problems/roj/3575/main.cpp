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

int weight[9][9];
const int ALL = (1 << 10) - 2;   // 数字 1..9 的位都为 1

int grid[9][9];
int rows[9], cols[9], boxes[9];
int best;
int n_empties;
vector<tuple<int, int, int> > empties;   // (行, 列, 宫)

void dfs(int k, int score) {
    if (k == n_empties) {
        best = max(best, score);
        return;
    }
    int bound = score;
    int pick = -1, pick_cand = 0, pick_cnt = 10;
    for (int i = k; i < n_empties; i++) {
        int r = get<0>(empties[i]), c = get<1>(empties[i]), b = get<2>(empties[i]);
        int cand = ALL & ~(rows[r] | cols[c] | boxes[b]);
        if (!cand) return;
        bound += weight[r][c] * (31 - __builtin_clz((unsigned)cand));
        int cnt = __builtin_popcount((unsigned)cand);
        if (cnt < pick_cnt) { pick = i; pick_cand = cand; pick_cnt = cnt; }
    }
    if (bound <= best) return;

    swap(empties[k], empties[pick]);
    int r = get<0>(empties[k]), c = get<1>(empties[k]), b = get<2>(empties[k]);
    while (pick_cand) {
        int low = pick_cand & (-pick_cand);
        pick_cand ^= low;
        int v = 31 - __builtin_clz((unsigned)low);
        rows[r] |= low; cols[c] |= low; boxes[b] |= low;
        dfs(k + 1, score + weight[r][c] * v);
        rows[r] ^= low; cols[c] ^= low; boxes[b] ^= low;
    }
    swap(empties[k], empties[pick]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int r = 0; r < 9; r++)
        for (int c = 0; c < 9; c++)
            weight[r][c] = 10 - max(abs(r - 4), abs(c - 4));

    for (int r = 0; r < 9; r++)
        for (int c = 0; c < 9; c++)
            cin >> grid[r][c];

    int base = 0;
    for (int r = 0; r < 9; r++)
        for (int c = 0; c < 9; c++) {
            int b = r / 3 * 3 + c / 3;
            if (grid[r][c]) {
                int bit = 1 << grid[r][c];
                rows[r] |= bit; cols[c] |= bit; boxes[b] |= bit;
                base += weight[r][c] * grid[r][c];
            } else {
                empties.push_back(make_tuple(r, c, b));
            }
        }
    best = -1;
    n_empties = (int)empties.size();
    dfs(0, base);
    cout << best << "\n";
    return 0;
}
