/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:16
 * update_at: 2026-10-05 02:18
 */
// main.cpp：质数方阵。
// 行/列/两条对角线都是“位和为 S”的五位素数，左上角固定为 corner。
// 做法：枚举第 0 列素数 c0 与主对角线素数 dg，二者把第 1..4 行各钉死两位，
// 每行只需在 (首位, 第 i 位) 的素数桶里选；第 0 行最后由四个列和反推；
// 副对角线（左下→右上）与列 4 的位和式联立，把第 3 行变成差值过滤；
// 行 0、副对角线、列 1..4 结尾统一查素数表确认。

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ll; // 题目数据默认 long long；本题数值都在 5 位以内，实际用 int 足够

const int MAXV = 100000; // 五位数上界，筛法与素数表都开到它

int S;      // 各数位之和
int corner; // 左上角数字

bool composite[MAXV]; // composite[x] = true 表示 x 是合数
bool in_pset[MAXV];   // in_pset[x] = true 表示 x 是位和为 S 的五位素数
vector<int> first_list; // 首位等于 corner 的候选素数（第 0 行 / 第 0 列 / 主对角线）

// 行候选桶，装的是“位和为 S 的五位素数”。
// b1[a][b]：首位为 a、第 1 位为 b，供第 1 行使用；b2/b3/b4 同理对应第 2/3/4 位。
vector<int> b1[10][10];
vector<int> b2[10][10];
vector<int> b3[10][10];
vector<int> b4[10][10];

vector<string> ans; // 每个方案拼成 25 位串（5 行数字用换行连接）

// 取 x 的第 pos 位数字：pos = 0 是万位，pos = 4 是个位
int digit_at(int x, int pos) {
    if (pos == 0) return x / 10000;
    if (pos == 1) return x / 1000 % 10;
    if (pos == 2) return x / 100 % 10;
    if (pos == 3) return x / 10 % 10;
    return x % 10;
}

// 埃氏筛标记合数，并把位和恰好为 S 的五位素数分装进各个桶
void build_tables() {
    composite[0] = true;
    composite[1] = true;
    for (int i = 2; i * i < MAXV; i++) {
        if (composite[i]) continue;
        for (int j = i * i; j < MAXV; j += i) composite[j] = true;
    }

    for (int x = 10000; x < MAXV; x++) {
        if (composite[x]) continue;
        int sum = 0;
        for (int pos = 0; pos < 5; pos++) sum += digit_at(x, pos);
        if (sum != S) continue;

        in_pset[x] = true;
        int d0 = digit_at(x, 0);
        if (d0 == corner) first_list.push_back(x);
        b1[d0][digit_at(x, 1)].push_back(x);
        b2[d0][digit_at(x, 2)].push_back(x);
        b3[d0][digit_at(x, 3)].push_back(x);
        b4[d0][digit_at(x, 4)].push_back(x);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> S >> corner;

    build_tables();

    for (size_t ci = 0; ci < first_list.size(); ci++) {
        int c0 = first_list[ci]; // 第 0 列（素数），c0 的第 i 位就是第 i 行首位
        int c01 = digit_at(c0, 1);
        int c02 = digit_at(c0, 2);
        int c03 = digit_at(c0, 3);
        int c04 = digit_at(c0, 4);

        for (size_t di = 0; di < first_list.size(); di++) {
            int dg = first_list[di]; // 主对角线（素数），dg 的第 i 位是第 i 行第 i 位
            int dg1 = digit_at(dg, 1);
            int dg2 = digit_at(dg, 2);
            int dg3 = digit_at(dg, 3);
            int dg4 = digit_at(dg, 4);

            vector<int>& L1 = b1[c01][dg1]; // 第 1 行的候选素数
            vector<int>& L2 = b2[c02][dg2]; // 第 2 行的候选素数
            vector<int>& L3 = b3[c03][dg3]; // 第 3 行的候选素数（还要过滤 第1位-第4位）
            vector<int>& L4 = b4[c04][dg4]; // 第 4 行的候选素数

            for (size_t i1 = 0; i1 < L1.size(); i1++) {
                int r1 = L1[i1];
                int x11 = digit_at(r1, 1);
                int x12 = digit_at(r1, 2);
                int x13 = digit_at(r1, 3);
                int x14 = digit_at(r1, 4);

                for (size_t i2 = 0; i2 < L2.size(); i2++) {
                    int r2 = L2[i2];
                    int x21 = digit_at(r2, 1);
                    int x22 = digit_at(r2, 2);
                    int x23 = digit_at(r2, 3);
                    int x24 = digit_at(r2, 4);

                    // 列 3、列 4 只剩第 4、第 3 行各一个自由格，其和与行 0 的数字都在 [0,9]
                    if (x13 + x23 < S - 18 - dg3) continue;
                    if (x13 + x23 > S - dg3) continue;
                    if (x14 + x24 < S - 18 - dg4) continue;
                    if (x14 + x24 > S - dg4) continue;

                    // 副对角线位和 c04+r31+dg2+x13+d04=S 与列 4 位和消去 d04，
                    // 得到第 3 行必须满足：第 1 位 - 第 4 位 = delta
                    int delta = dg4 + x14 + x24 - c04 - dg2 - x13;

                    for (size_t i3 = 0; i3 < L3.size(); i3++) {
                        int r3 = L3[i3];
                        int x31 = digit_at(r3, 1);
                        int x32 = digit_at(r3, 2);
                        int x33 = digit_at(r3, 3);
                        int x34 = digit_at(r3, 4);
                        if (x31 - x34 != delta) continue;

                        // 列 2、列 1 同样只剩一个自由格，做窗口剪枝
                        if (x12 + x32 < S - 18 - dg2) continue;
                        if (x12 + x32 > S - dg2) continue;
                        if (x21 + x31 < S - 18 - dg1) continue;
                        if (x21 + x31 > S - dg1) continue;

                        for (size_t i4 = 0; i4 < L4.size(); i4++) {
                            int r4 = L4[i4];
                            int x41 = digit_at(r4, 1);
                            int x42 = digit_at(r4, 2);
                            int x43 = digit_at(r4, 3);
                            int x44 = digit_at(r4, 4);

                            // 四个列和反推第 0 行的四个数字（第 0 列、主对角线已由 c0、dg 保证）
                            int d01 = S - dg1 - x21 - x31 - x41;
                            int d02 = S - dg2 - x12 - x32 - x42;
                            int d03 = S - dg3 - x13 - x23 - x43;
                            int d04 = S - dg4 - x14 - x24 - x34;
                            if (d01 < 0 || d01 > 9) continue;
                            if (d02 < 0 || d02 > 9) continue;
                            if (d03 < 0 || d03 > 9) continue;
                            if (d04 < 0 || d04 > 9) continue;

                            int r0 = corner * 10000 + d01 * 1000 + d02 * 100 + d03 * 10 + d04;
                            if (!in_pset[r0]) continue;

                            // 副对角线从左下 (4,0) 读到右上 (0,4)，即 c04, r31, dg2, r13, d04
                            int anti = c04 * 10000 + x31 * 1000 + dg2 * 100 + x13 * 10 + d04;
                            if (!in_pset[anti]) continue;

                            // 列 1..4 从上往下读
                            int col1 = d01 * 10000 + x11 * 1000 + x21 * 100 + x31 * 10 + x41;
                            int col2 = d02 * 10000 + x12 * 1000 + x22 * 100 + x32 * 10 + x42;
                            int col3 = d03 * 10000 + x13 * 1000 + x23 * 100 + x33 * 10 + x43;
                            int col4 = d04 * 10000 + x14 * 1000 + x24 * 100 + x34 * 10 + x44;
                            if (!in_pset[col1]) continue;
                            if (!in_pset[col2]) continue;
                            if (!in_pset[col3]) continue;
                            if (!in_pset[col4]) continue;

                            string s = to_string(r0);
                            s += "\n" + to_string(r1);
                            s += "\n" + to_string(r2);
                            s += "\n" + to_string(r3);
                            s += "\n" + to_string(r4);
                            ans.push_back(s);
                        }
                    }
                }
            }
        }
    }

    // 所有方案都是等长的 25 位串，按字典序排就是按 25 位数大小排
    sort(ans.begin(), ans.end());

    if (ans.empty()) {
        cout << "NONE\n";
    } else {
        for (size_t i = 0; i < ans.size(); i++) {
            if (i > 0) cout << "\n"; // 两组方案之间空一行
            cout << ans[i] << "\n";
        }
    }

    return 0;
}
