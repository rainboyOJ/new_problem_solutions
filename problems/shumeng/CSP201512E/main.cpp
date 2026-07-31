/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 16:21
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 1005;
const int MAXP = 2010;

int m;
bitset<MAXM> matrix_row[MAXM];
bitset<MAXM> linear_basis[MAXM];
bitset<MAXM> linear_expression[MAXM];
bitset<MAXM> state[MAXM];
bitset<MAXP> relation;

bitset<MAXM> multiply_vector(const bitset<MAXM> &vector_value) {
    bitset<MAXM> result;
    for (int i = 0; i < m; i++) result[i] = (matrix_row[i] & vector_value).count() % 2;
    return result;
}

bitset<MAXP> multiply_polynomial(const bitset<MAXP> &left, const bitset<MAXP> &right,
                                 int degree) {
    bitset<MAXP> result;
    for (int i = 0; i < degree; i++) if (left[i]) result ^= right << i;
    for (int i = 2 * degree - 2; i >= degree; i--) {
        if (result[i]) result ^= relation << (i - degree);
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m;
    for (int i = 0; i < m; i++) {
        string line;
        cin >> line;
        for (int j = 0; j < m; j++) matrix_row[i][j] = line[j] == '1';
    }
    string initial;
    cin >> initial;
    bitset<MAXM> current;
    for (int i = 0; i < m; i++) current[i] = initial[i] == '1';

    int degree = 0;
    for (int step = 0; step <= m; step++) {
        bitset<MAXM> value = current;
        bitset<MAXM> expression;
        expression[step] = 1;
        for (int bit = m - 1; bit >= 0; bit--) {
            if (!value[bit]) continue;
            if (linear_basis[bit].none()) {
                linear_basis[bit] = value;
                linear_expression[bit] = expression;
                state[step] = current;
                degree = step + 1;
                break;
            }
            value ^= linear_basis[bit];
            expression ^= linear_expression[bit];
        }
        if (value.none()) {
            degree = step;
            for (int i = 0; i < degree; i++) relation[i] = expression[i];
            relation[degree] = 1;
            break;
        }
        current = multiply_vector(current);
    }

    int q;
    cin >> q;
    while (q--) {
        long long k;
        cin >> k;
        bitset<MAXP> result, power;
        result[0] = 1;
        if (degree == 1) power[0] = relation[0];
        else power[1] = 1;
        while (k > 0) {
            if (k & 1) result = multiply_polynomial(result, power, degree);
            power = multiply_polynomial(power, power, degree);
            k >>= 1;
        }
        bitset<MAXM> answer;
        for (int i = 0; i < degree; i++) if (result[i]) answer ^= state[i];
        for (int i = 0; i < m; i++) cout << answer[i];
        cout << '\n';
    }
    return 0;
}
