/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:00
 */
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;
const int MAX_STATE = 1 << 7;

int width;
long long transition_count[MAX_STATE][MAX_STATE];

void fill_row(int start_mask, int current_mask, int next_mask, int column) {
    while (column < width && (current_mask & (1 << column)) != 0) {
        column++;
    }
    if (column == width) {
        transition_count[start_mask][next_mask]++;
        return;
    }

    // 当前行占连续两格，下一行占其中一格。
    if (column + 1 < width && (current_mask & (1 << (column + 1))) == 0) {
        int filled = current_mask | (1 << column) | (1 << (column + 1));
        if ((next_mask & (1 << column)) == 0) {
            fill_row(start_mask, filled, next_mask | (1 << column), column + 1);
        }
        if ((next_mask & (1 << (column + 1))) == 0) {
            fill_row(start_mask, filled, next_mask | (1 << (column + 1)), column + 1);
        }
    }

    // 当前行占一格，下一行占 column 和 column+1 两格。
    if (column + 1 < width
            && (next_mask & (1 << column)) == 0
            && (next_mask & (1 << (column + 1))) == 0) {
        fill_row(start_mask, current_mask | (1 << column),
                 next_mask | (1 << column) | (1 << (column + 1)), column + 1);
    }

    // 当前行占一格，下一行占 column-1 和 column 两格。
    if (column > 0
            && (next_mask & (1 << (column - 1))) == 0
            && (next_mask & (1 << column)) == 0) {
        fill_row(start_mask, current_mask | (1 << column),
                 next_mask | (1 << (column - 1)) | (1 << column), column + 1);
    }
}

typedef vector<vector<long long> > Matrix;

Matrix multiply(const Matrix &left, const Matrix &right) {
    int size = (int)left.size();
    Matrix result(size, vector<long long>(size, 0));
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++) {
            if (left[i][k] == 0) {
                continue;
            }
            for (int j = 0; j < size; j++) {
                if (right[k][j] == 0) {
                    continue;
                }
                result[i][j] = (result[i][j] + left[i][k] * right[k][j]) % MOD;
            }
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n >> width;

    if ((n % 3) * (width % 3) % 3 != 0) {
        cout << 0 << '\n';
        return 0;
    }

    int state_count = 1 << width;
    for (int mask = 0; mask < state_count; mask++) {
        fill_row(mask, mask, 0, 0);
    }

    Matrix result(state_count, vector<long long>(state_count, 0));
    Matrix base(state_count, vector<long long>(state_count, 0));
    for (int i = 0; i < state_count; i++) {
        result[i][i] = 1;
        for (int j = 0; j < state_count; j++) {
            base[i][j] = transition_count[i][j] % MOD;
        }
    }

    while (n > 0) {
        if (n & 1) {
            result = multiply(result, base);
        }
        base = multiply(base, base);
        n >>= 1;
    }

    cout << result[0][0] << '\n';
    return 0;
}
