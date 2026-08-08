#include <bits/stdc++.h>
using namespace std;

int r, c;
vector<string> grid_data;
vector<int> border_rows, border_cols;

vector<string> rotate90(const vector<string> &mat) {
    int h = (int)mat.size();
    int w = (int)mat[0].size();
    vector<string> res(w, string(h, '.'));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            res[j][h - 1 - i] = mat[i][j];
        }
    }
    return res;
}

// 直接判断两个窗口是否能通过旋转匹配。
bool same_pattern(vector<string> a, const vector<string> &b) {
    if ((int)a.size() == (int)b.size() && (int)a[0].size() == (int)b[0].size() && a == b) {
        return true;
    }
    for (int t = 1; t <= 3; t++) {
        a = rotate90(a);
        if ((int)a.size() == (int)b.size() && (int)a[0].size() == (int)b[0].size() && a == b) {
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> r >> c;
    grid_data.resize(r);
    for (int i = 0; i < r; i++) {
        cin >> grid_data[i];
    }

    for (int i = 0; i < r; i++) {
        bool all_hash = true;
        for (int j = 0; j < c; j++) {
            if (grid_data[i][j] != '#') {
                all_hash = false;
                break;
            }
        }
        if (all_hash) {
            border_rows.push_back(i);
        }
    }
    for (int j = 0; j < c; j++) {
        bool all_hash = true;
        for (int i = 0; i < r; i++) {
            if (grid_data[i][j] != '#') {
                all_hash = false;
                break;
            }
        }
        if (all_hash) {
            border_cols.push_back(j);
        }
    }

    int win_h = border_rows[1] - border_rows[0] - 1;
    int win_w = border_cols[1] - border_cols[0] - 1;
    int row_cnt = (int)border_rows.size() - 1;
    int col_cnt = (int)border_cols.size() - 1;

    // brute.cpp：把所有窗口都拆出来，逐个和已有代表图案比较，直接判断旋转等价。
    vector<vector<string>> kinds;
    for (int i = 0; i < row_cnt; i++) {
        for (int j = 0; j < col_cnt; j++) {
            int sr = border_rows[i] + 1;
            int sc = border_cols[j] + 1;
            vector<string> mat(win_h);
            for (int x = 0; x < win_h; x++) {
                mat[x] = grid_data[sr + x].substr(sc, win_w);
            }

            bool found = false;
            for (int id = 0; id < (int)kinds.size(); id++) {
                if (same_pattern(mat, kinds[id])) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                kinds.push_back(mat);
            }
        }
    }

    cout << kinds.size() << '\n';

    return 0;
}
