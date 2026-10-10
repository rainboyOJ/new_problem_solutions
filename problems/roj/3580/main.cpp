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

const int MAXM = 505;

int n, m;
int h[505][505];
bitset<MAXM> cover[505][505];   // cover[i][j]：格子 (i,j) 能被第 1 行哪些列的蓄水厂供到

struct Cell { int h, i, j; };
vector<Cell> order_;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> h[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            order_.push_back({h[i][j], i, j});
    sort(order_.begin(), order_.end(), [](const Cell& a, const Cell& b) { return a.h > b.h; });

    const int di[4] = {-1, 1, 0, 0};
    const int dj[4] = {0, 0, -1, 1};
    for (size_t idx = 0; idx < order_.size(); idx++) {
        int height = order_[idx].h, i = order_[idx].i, j = order_[idx].j;
        bitset<MAXM> bits;
        if (i == 0) bits.set(j);
        for (int d = 0; d < 4; d++) {
            int ni = i + di[d], nj = j + dj[d];
            if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
            if (h[ni][nj] > height) bits |= cover[ni][nj];
        }
        cover[i][j] = bits;
    }

    int unreachable = 0;
    for (int j = 0; j < m; j++)
        if (cover[n - 1][j].none()) unreachable++;
    if (unreachable) {
        cout << "0\n" << unreachable << "\n";
        return 0;
    }

    // 每个源点能供到的最后一行列是连续区间
    vector<int> lo(m, 0), hi(m, 0);
    bitset<MAXM> seen;
    for (int j = 0; j < m; j++) {
        bitset<MAXM> fresh = cover[n - 1][j] & ~seen;
        seen |= cover[n - 1][j];
        for (int s = 0; s < m; s++)
            if (fresh[s]) lo[s] = j;
    }
    seen.reset();
    for (int j = m - 1; j >= 0; j--) {
        bitset<MAXM> fresh = cover[n - 1][j] & ~seen;
        seen |= cover[n - 1][j];
        for (int s = 0; s < m; s++)
            if (fresh[s]) hi[s] = j;
    }

    vector<pair<int, int> > segments;
    for (int s = 0; s < m; s++)
        if (cover[n - 1][lo[s]][s])
            segments.push_back(make_pair(lo[s], hi[s]));
    sort(segments.begin(), segments.end());

    int built = 0, reach = 0, idx2 = 0;
    while (reach < m) {
        int best = reach;
        while (idx2 < (int)segments.size() && segments[idx2].first <= reach) {
            best = max(best, segments[idx2].second);
            idx2++;
        }
        built++;
        reach = best + 1;
    }
    cout << "1\n" << built << "\n";
    return 0;
}
