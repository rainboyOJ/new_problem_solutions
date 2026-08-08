#include <bits/stdc++.h>
using namespace std;

const int MAXM = 1005;

struct Node {
    int id;     // 这条缝的位置编号
    int cnt;    // 有多少对同学会被这条缝隔开
};

int m, n, k, l, d;
int row_cnt[MAXM], col_cnt[MAXM];
Node row_gap[MAXM], col_gap[MAXM];

bool cmp_node(const Node &a, const Node &b) {
    if (a.cnt != b.cnt) {
        return a.cnt > b.cnt;
    }
    return a.id < b.id;
}

bool cmp_int(int a, int b) {
    return a < b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n >> k >> l >> d;

    for (int i = 1; i <= d; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        // 两人上下相邻，只会被某一条横向通道隔开。
        if (x1 != x2) {
            int gap = min(x1, x2);
            row_cnt[gap]++;
        }
        // 两人左右相邻，只会被某一条纵向通道隔开。
        else {
            int gap = min(y1, y2);
            col_cnt[gap]++;
        }
    }

    for (int i = 1; i < m; i++) {
        row_gap[i].id = i;
        row_gap[i].cnt = row_cnt[i];
    }
    for (int i = 1; i < n; i++) {
        col_gap[i].id = i;
        col_gap[i].cnt = col_cnt[i];
    }

    sort(row_gap + 1, row_gap + m, cmp_node);
    sort(col_gap + 1, col_gap + n, cmp_node);

    vector<int> ans_row, ans_col;
    for (int i = 1; i <= k; i++) {
        ans_row.push_back(row_gap[i].id);
    }
    for (int i = 1; i <= l; i++) {
        ans_col.push_back(col_gap[i].id);
    }

    sort(ans_row.begin(), ans_row.end(), cmp_int);
    sort(ans_col.begin(), ans_col.end(), cmp_int);

    for (int i = 0; i < (int) ans_row.size(); i++) {
        if (i) {
            cout << ' ';
        }
        cout << ans_row[i];
    }
    cout << '\n';

    for (int i = 0; i < (int) ans_col.size(); i++) {
        if (i) {
            cout << ' ';
        }
        cout << ans_col[i];
    }
    cout << '\n';

    return 0;
}
