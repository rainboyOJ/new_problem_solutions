/**
 * Problem: luogu P1013 - [NOIP 1998 提高组] 进制位
 * Author: rainboy
 * Date: 2026-11-10 22:50
 * Description: 进位统计求值与全表检验
 */
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int n;
string table[15][15];
int val[15];          // 每个字母（对应输入第 2 ~ n 项）对应的数值
int letter_val[256];  // ASCII 到数值的映射
bool in_set[256];     // 表头中出现的字符集合
bool vis[15];

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

    // 0. 登记表头给出的所有字母，并检查单元格字符合法性与长度限制
    for (int i = 2; i <= n; ++i) {
        in_set[static_cast<unsigned char>(table[1][i][0])] = true;
    }
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

    // 1. 统计第 i 行中两位数的数量，作为该字母的值
    for (int i = 2; i <= n; ++i) {
        int carry_count = 0;
        for (int j = 2; j <= n; ++j) {
            if (table[i][j].length() >= 2) {
                carry_count++;
            }
        }
        val[i] = carry_count;
    }

    // 2. 检查数值是否构成 0 ~ base-1 的互不相同排列
    for (int i = 0; i < base; ++i) vis[i] = false;
    for (int i = 2; i <= n; ++i) {
        if (val[i] < 0 || val[i] >= base || vis[val[i]]) {
            cout << "ERROR!\n";
            return 0;
        }
        vis[val[i]] = true;
        char ch = table[i][1][0];
        letter_val[static_cast<unsigned char>(ch)] = val[i];
    }

    // 3. 全表代入验算加法运算在 base 进制下是否完全成立
    for (int i = 2; i <= n; ++i) {
        for (int j = 2; j <= n; ++j) {
            const string &s = table[i][j];
            // 两位数前导位不能为 0
            if (s.length() >= 2 && letter_val[static_cast<unsigned char>(s[0])] == 0) {
                cout << "ERROR!\n";
                return 0;
            }
            int expected_sum = val[i] + val[j];
            int actual_sum = 0;
            for (char ch : s) {
                actual_sum = actual_sum * base + letter_val[static_cast<unsigned char>(ch)];
            }
            if (expected_sum != actual_sum) {
                cout << "ERROR!\n";
                return 0;
            }
        }
    }

    // 4. 输出每个字母的值及进制
    for (int i = 2; i <= n; ++i) {
        cout << table[1][i] << "=" << val[i] << (i == n ? "" : " ");
    }
    cout << "\n" << base << "\n";

    return 0;
}
