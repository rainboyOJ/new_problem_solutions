/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50;

int substance_count;          // 一个方程中物质的个数（矩阵列数）
int element_count;            // 一个方程中出现的元素种类数（矩阵行数）
map<string, int> element_id;  // 元素名称 -> 矩阵行号
long double matrix[MAXN][MAXN]; // matrix[i][j]：第 j 个物质中含元素 i 的原子个数

// 解析化学式：连续小写字母为元素名，其后紧跟的数字为该元素的原子个数
map<string, int> parse_formula(const string &formula) {
    map<string, int> result;
    int position = 0;
    while (position < (int)formula.size()) {
        string element;
        while (position < (int)formula.size()
                && 'a' <= formula[position] && formula[position] <= 'z') {
            element += formula[position++];
        }
        int number = 0;
        while (position < (int)formula.size()
                && '0' <= formula[position] && formula[position] <= '9') {
            number = number * 10 + formula[position++] - '0';
        }
        result[element] = number;
    }
    return result;
}

// 读入一个方程的各个物质，构造元素-物质计数矩阵
void read_equation() {
    cin >> substance_count;
    element_id.clear();
    memset(matrix, 0, sizeof(matrix));

    for (int column = 0; column < substance_count; column++) {
        string formula;
        cin >> formula;
        map<string, int> counts = parse_formula(formula);
        for (map<string, int>::iterator it = counts.begin(); it != counts.end(); ++it) {
            int row;
            if (element_id.count(it->first)) {
                row = element_id[it->first];
            } else {
                row = (int)element_id.size();
                element_id[it->first] = row;
            }
            matrix[row][column] = it->second;
        }
    }
    element_count = (int)element_id.size();
}

// 高斯消元（列主元）求矩阵的秩，返回非零行数
int matrix_rank() {
    int rank = 0;
    for (int column = 0; column < substance_count && rank < element_count; column++) {
        // 在当前列选择绝对值最大的行作为主元，提高数值稳定性
        int pivot = rank;
        for (int row = rank + 1; row < element_count; row++) {
            if (fabsl(matrix[row][column]) > fabsl(matrix[pivot][column])) pivot = row;
        }
        // 主元为 0 说明该列已是自由列，直接跳过
        if (fabsl(matrix[pivot][column]) < 1e-12L) continue;

        // 把主元行换到当前行
        for (int j = column; j < substance_count; j++) {
            swap(matrix[pivot][j], matrix[rank][j]);
        }
        // 用当前行消去下面各行的当前列
        for (int row = rank + 1; row < element_count; row++) {
            if (fabsl(matrix[row][column]) < 1e-12L) continue;
            long double ratio = matrix[row][column] / matrix[rank][column];
            for (int j = column; j < substance_count; j++) {
                matrix[row][j] -= ratio * matrix[rank][j];
            }
        }
        rank++;
    }
    return rank;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int equation_count;
    cin >> equation_count;
    while (equation_count--) {
        read_equation();
        // 齐次方程组 AX=0 有非零解当且仅当矩阵秩小于未知数个数
        cout << (matrix_rank() < substance_count ? 'Y' : 'N') << '\n';
    }

    return 0;
}