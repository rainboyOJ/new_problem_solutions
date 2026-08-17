/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 23:01
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 1005; // 向量/矩阵最大维数
const int MAXP = 2010; // 递推多项式最高次数（2*m 量级）

int m;
bitset<MAXM> matrix_row[MAXM];    // 矩阵 A 的每一行，用于把向量左乘 A
bitset<MAXM> linear_basis[MAXM];  // 高斯消元后的向量基（按最高位归位）
bitset<MAXM> linear_expression[MAXM]; // 基向量对应的多项式系数（列）
bitset<MAXM> state[MAXM];         // state[i] = A^i * b
bitset<MAXP> relation;            // 最小递推多项式 P(x)，满足 x^d = sum relation[i]*x^i

// 计算 A * vector_value（GF(2) 下，行向量点积取异或）。
bitset<MAXM> multiply_vector(const bitset<MAXM> &vector_value) {
    bitset<MAXM> result;
    for (int i = 0; i < m; i++) {
        result[i] = (matrix_row[i] & vector_value).count() % 2;
    }
    return result;
}

// GF(2) 多项式乘法并对 P(x) 取模（次数为 degree）。
bitset<MAXP> multiply_polynomial(const bitset<MAXP> &left, const bitset<MAXP> &right,
                                 int degree) {
    bitset<MAXP> result;
    // 先做普通多项式乘法，再对次数 >= degree 的项用 x^degree = P(x) 归约。
    for (int i = 0; i < degree; i++) {
        if (left[i]) result ^= right << i;
    }
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
    bitset<MAXM> current; // 当前状态向量 b
    for (int i = 0; i < m; i++) current[i] = initial[i] == '1';

    // 逐项生成 Krylov 序列 b, Ab, A^2b, ...，用高斯消元找第一个线性相关。
    int degree = 0;
    for (int step = 0; step <= m; step++) {
        bitset<MAXM> value = current;
        bitset<MAXM> expression;
        expression[step] = 1; // 初始表示 A^step * b = 1 * (A^step * b)
        // 按最高位从高到低消元。
        for (int bit = m - 1; bit >= 0; bit--) {
            if (!value[bit]) continue;
            if (linear_basis[bit].none()) {
                // 当前向量线性无关，加入基并记录它对应的 A 的幂次。
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
            // 找到首个线性关系：A^step * b = sum expression[i] * A^i * b。
            degree = step;
            for (int i = 0; i < degree; i++) relation[i] = expression[i];
            relation[degree] = 1; // P(x) = x^degree - sum expression[i]*x^i
            break;
        }
        current = multiply_vector(current);
    }

    int q;
    cin >> q;
    while (q--) {
        long long k;
        cin >> k;
        // 用多项式快速幂计算 x^k mod P(x)，结果系数决定 state 的线性组合。
        bitset<MAXP> result, power;
        result[0] = 1;
        if (degree == 1) power[0] = relation[0]; // 一次递推的特例：x = relation[0]
        else power[1] = 1;                        // 否则 x^1
        while (k > 0) {
            if (k & 1) result = multiply_polynomial(result, power, degree);
            power = multiply_polynomial(power, power, degree);
            k >>= 1;
        }
        // 答案 = sum result[i] * state[i]。
        bitset<MAXM> answer;
        for (int i = 0; i < degree; i++) {
            if (result[i]) answer ^= state[i];
        }
        for (int i = 0; i < m; i++) cout << answer[i];
        cout << '\n';
    }
    return 0;
}