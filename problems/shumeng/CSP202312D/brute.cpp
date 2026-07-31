/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 22:10
 */
// brute.cpp：小数据暴力解，直接用链表模拟区间内的双端队列。
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

struct Matrix {
    long long a[2][2];
};

struct Operation {
    int type;
    Matrix matrix;
};

Matrix identity_matrix() {
    Matrix result = {{{1, 0}, {0, 1}}};
    return result;
}

Matrix multiply(const Matrix &left, const Matrix &right) {
    Matrix result = {};
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                result.a[i][j] = (result.a[i][j] + left.a[i][k] * right.a[k][j]) % MOD;
            }
        }
    }
    return result;
}

Operation read_operation() {
    Operation result;
    cin >> result.type;
    if (result.type == 1 || result.type == 2) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) cin >> result.matrix.a[i][j];
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, event_count;
    cin >> n >> event_count;
    vector<Operation> operation(n);
    for (int i = 0; i < n; i++) operation[i] = read_operation();

    while (event_count--) {
        int event_type;
        cin >> event_type;
        if (event_type == 1) {
            int index;
            cin >> index;
            operation[index - 1] = read_operation();
            continue;
        }

        int left, right;
        cin >> left >> right;
        list<Matrix> queue;
        vector<list<Matrix>::iterator> inserted;
        for (int i = left - 1; i < right; i++) {
            if (operation[i].type == 1) {
                queue.push_front(operation[i].matrix);
                inserted.push_back(queue.begin());
            } else if (operation[i].type == 2) {
                queue.push_back(operation[i].matrix);
                list<Matrix>::iterator position = queue.end();
                --position;
                inserted.push_back(position);
            } else if (!inserted.empty()) {
                queue.erase(inserted.back());
                inserted.pop_back();
            }
        }

        Matrix answer = identity_matrix();
        for (list<Matrix>::iterator it = queue.begin(); it != queue.end(); ++it) {
            answer = multiply(answer, *it);
        }
        cout << answer.a[0][0] << ' ' << answer.a[0][1] << ' '
             << answer.a[1][0] << ' ' << answer.a[1][1] << '\n';
    }

    return 0;
}
