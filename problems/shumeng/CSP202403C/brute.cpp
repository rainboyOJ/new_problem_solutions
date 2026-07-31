/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 22:55
 */
// brute.cpp：小数据基准，显式构造元素计数矩阵并消元求秩。
#include <bits/stdc++.h>
using namespace std;

map<string, int> parse_formula(const string &formula) {
    map<string, int> result;
    int position = 0;
    while (position < (int)formula.size()) {
        string element;
        while (position < (int)formula.size() && islower(formula[position])) {
            element += formula[position++];
        }
        int number = 0;
        while (position < (int)formula.size() && isdigit(formula[position])) {
            number = number * 10 + formula[position++] - '0';
        }
        result[element] = number;
    }
    return result;
}

int matrix_rank(vector<vector<double> > matrix) {
    int rows = matrix.size();
    int columns = matrix[0].size();
    int rank = 0;
    for (int column = 0; column < columns && rank < rows; column++) {
        int pivot = rank;
        while (pivot < rows && fabs(matrix[pivot][column]) < 1e-10) pivot++;
        if (pivot == rows) continue;
        swap(matrix[pivot], matrix[rank]);
        for (int row = rank + 1; row < rows; row++) {
            double ratio = matrix[row][column] / matrix[rank][column];
            for (int next = column; next < columns; next++) {
                matrix[row][next] -= ratio * matrix[rank][next];
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
        int substance_count;
        cin >> substance_count;
        vector<map<string, int> > substance(substance_count);
        map<string, int> element_id;
        for (int i = 0; i < substance_count; i++) {
            string formula;
            cin >> formula;
            substance[i] = parse_formula(formula);
            for (map<string, int>::iterator it = substance[i].begin();
                    it != substance[i].end(); ++it) {
                if (!element_id.count(it->first)) element_id[it->first] = element_id.size();
            }
        }
        vector<vector<double> > matrix(element_id.size(),
                vector<double>(substance_count, 0));
        for (int column = 0; column < substance_count; column++) {
            for (map<string, int>::iterator it = substance[column].begin();
                    it != substance[column].end(); ++it) {
                matrix[element_id[it->first]][column] = it->second;
            }
        }
        cout << (matrix_rank(matrix) < substance_count ? 'Y' : 'N') << '\n';
    }

    return 0;
}
