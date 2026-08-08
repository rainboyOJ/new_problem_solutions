#include <bits/stdc++.h>
using namespace std;

const int MAXD = 1005;

struct Talk {
    int x1, y1, x2, y2;
};

int m, n, k, l, d;
Talk a[MAXD];
vector<int> choose_row, choose_col;
vector<int> best_row, best_col;
int best_blocked = -1;

// 判断某一对同学是否会被当前通道方案隔开。
bool is_blocked(const Talk &t) {
    if (t.x1 != t.x2) {
        int gap = min(t.x1, t.x2);
        for (int i = 0; i < (int) choose_row.size(); i++) {
            if (choose_row[i] == gap) {
                return true;
            }
        }
        return false;
    }
    else {
        int gap = min(t.y1, t.y2);
        for (int i = 0; i < (int) choose_col.size(); i++) {
            if (choose_col[i] == gap) {
                return true;
            }
        }
        return false;
    }
}

// 比较两个方案的字典序，便于在小数据对拍时固定输出。
bool better_lexicographically(const vector<int> &row1, const vector<int> &col1,
                              const vector<int> &row2, const vector<int> &col2) {
    if (row1 != row2) {
        return row1 < row2;
    }
    return col1 < col2;
}

void evaluate() {
    int blocked = 0;
    for (int i = 1; i <= d; i++) {
        if (is_blocked(a[i])) {
            blocked++;
        }
    }

    if (blocked > best_blocked ||
        (blocked == best_blocked &&
         better_lexicographically(choose_row, choose_col, best_row, best_col))) {
        best_blocked = blocked;
        best_row = choose_row;
        best_col = choose_col;
    }
}

void dfs_col(int pos, int need) {
    if (need == 0) {
        evaluate();
        return;
    }
    if (pos >= n) {
        return;
    }
    if (n - pos < need) {
        return;
    }

    choose_col.push_back(pos);
    dfs_col(pos + 1, need - 1);
    choose_col.pop_back();

    dfs_col(pos + 1, need);
}

void dfs_row(int pos, int need) {
    if (need == 0) {
        dfs_col(1, l);
        return;
    }
    if (pos >= m) {
        return;
    }
    if (m - pos < need) {
        return;
    }

    choose_row.push_back(pos);
    dfs_row(pos + 1, need - 1);
    choose_row.pop_back();

    dfs_row(pos + 1, need);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n >> k >> l >> d;
    for (int i = 1; i <= d; i++) {
        cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
    }

    dfs_row(1, k);

    for (int i = 0; i < (int) best_row.size(); i++) {
        if (i) {
            cout << ' ';
        }
        cout << best_row[i];
    }
    cout << '\n';

    for (int i = 0; i < (int) best_col.size(); i++) {
        if (i) {
            cout << ' ';
        }
        cout << best_col[i];
    }
    cout << '\n';

    return 0;
}
