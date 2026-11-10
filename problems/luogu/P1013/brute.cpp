/**
 * Problem: luogu P1013 - [NOIP 1998 提高组] 进制位 (Brute Force)
 * Author: rainboy
 * Date: 2026-11-10 22:50
 * Description: 全排列枚举验证暴力解
 */
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int n;
string table[15][15];
int letter_val[256];
bool in_set[256];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> table[i][j];
        }
    }

    int base = n - 1;
    vector<char> letters;
    for (int i = 2; i <= n; ++i) {
        letters.push_back(table[1][i][0]);
        in_set[static_cast<unsigned char>(table[1][i][0])] = true;
    }

    // 检查是否有非法字符混入，以及长度是否合法（进制下两位数不得有前导零，且长度不得超过 2）
    for (int i = 2; i <= n; ++i) {
        for (int j = 2; j <= n; ++j) {
            if (table[i][j].length() > 2) {
                cout << "ERROR!\n";
                return 0;
            }
            for (char ch : table[i][j]) {
                if (!in_set[static_cast<unsigned char>(ch)]) {
                    cout << "ERROR!\n";
                    return 0;
                }
            }
        }
    }

    vector<int> p(base);
    iota(p.begin(), p.end(), 0);

    vector<int> ans;
    int solutions = 0;

    do {
        for (int i = 0; i < base; ++i) {
            letter_val[static_cast<unsigned char>(letters[i])] = p[i];
        }

        bool ok = true;
        for (int i = 2; i <= n && ok; ++i) {
            for (int j = 2; j <= n && ok; ++j) {
                const string &s = table[i][j];
                // 多位数不能有前导零，且 0 必须表示为单个数字
                if (s.length() >= 2 && letter_val[static_cast<unsigned char>(s[0])] == 0) {
                    ok = false;
                    break;
                }
                int expected_sum = letter_val[static_cast<unsigned char>(table[i][1][0])] +
                                   letter_val[static_cast<unsigned char>(table[1][j][0])];
                int actual_sum = 0;
                for (char ch : s) {
                    actual_sum = actual_sum * base + letter_val[static_cast<unsigned char>(ch)];
                }
                if (expected_sum != actual_sum) {
                    ok = false;
                    break;
                }
            }
        }

        if (ok) {
            solutions++;
            ans = p;
            if (solutions > 1) break;
        }
    } while (next_permutation(p.begin(), p.end()));

    if (solutions != 1) {
        cout << "ERROR!\n";
    } else {
        for (int i = 0; i < base; ++i) {
            cout << letters[i] << "=" << ans[i] << (i == base - 1 ? "" : " ");
        }
        cout << "\n" << base << "\n";
    }

    return 0;
}
