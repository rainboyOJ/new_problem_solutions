#include <bits/stdc++.h>
using namespace std;

int r, c;
vector<string> grid_data;
vector<int> border_rows, border_cols;

// 把一个窗口图案编码成字符串，方便放进 set 去重。
string encode_pattern(const vector<string> &mat) {
    string res = "";
    int h = (int)mat.size();
    int w = (int)mat[0].size();
    res += to_string(h);
    res += "x";
    res += to_string(w);
    res += "|";
    for (int i = 0; i < h; i++) {
        res += mat[i];
        res += "/";
    }
    return res;
}

// 顺时针旋转 90 度。
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

// 取一个窗口在允许旋转下的最小表示。
string canonical(const vector<string> &mat) {
    vector<string> cur = mat;
    string best = encode_pattern(cur);

    // 180 度旋转总是和原窗口同尺寸，因此一定要考虑。
    cur = rotate90(cur);
    if ((int)mat.size() == (int)mat[0].size()) {
        best = min(best, encode_pattern(cur));
    }

    cur = rotate90(cur);
    best = min(best, encode_pattern(cur));

    cur = rotate90(cur);
    if ((int)mat.size() == (int)mat[0].size()) {
        best = min(best, encode_pattern(cur));
    }

    return best;
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

    set<string> kinds;

    for (int i = 0; i < row_cnt; i++) {
        for (int j = 0; j < col_cnt; j++) {
            int sr = border_rows[i] + 1;
            int sc = border_cols[j] + 1;
            vector<string> mat(win_h);
            for (int x = 0; x < win_h; x++) {
                mat[x] = grid_data[sr + x].substr(sc, win_w);
            }
            kinds.insert(canonical(mat));
        }
    }

    cout << kinds.size() << '\n';

    return 0;
}
