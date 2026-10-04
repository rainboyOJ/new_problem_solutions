/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-29 19:38
 * update_at: 2026-10-05 02:31
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

ll n, i, j;

// 输出同一行、列或对角线上的所有坐标，格式为 (x,y)，相邻坐标间一个空格
void print_line(const vector<pair<ll, ll> > &cells) {
    for (ll k = 0; k < (ll)cells.size(); k++) {
        if (k > 0) cout << ' ';
        cout << '(' << cells[k].first << ',' << cells[k].second << ')';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> i >> j;

    vector<pair<ll, ll> > row, col, diag1, diag2;

    // 同行：第 i 行，列号从左到右 1..n
    for (ll c = 1; c <= n; c++) row.push_back(make_pair(i, c));
    // 同列：第 j 列，行号从上到下 1..n
    for (ll r = 1; r <= n; r++) col.push_back(make_pair(r, j));

    // 主对角线（左上到右下）：行号 - 列号 = i - j
    ll d = i - j;
    ll r1 = max(1LL, 1 + d);
    ll r2 = min(n, n + d);
    for (ll r = r1; r <= r2; r++) diag1.push_back(make_pair(r, r - d));

    // 副对角线（左下到右上）：行号 + 列号 = i + j
    ll s = i + j;
    ll r3 = max(1LL, s - n);
    ll r4 = min(n, s - 1);
    for (ll r = r4; r >= r3; r--) diag2.push_back(make_pair(r, s - r));

    print_line(row);
    print_line(col);
    print_line(diag1);
    print_line(diag2);

    return 0;
}
