/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 13:26
 * update_at: 2026-10-23 13:26
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// brute.cpp：小数据暴力解，把「每场选哪辆车」看成选择序列来递归枚举所有可能。
// 只适合小数据：枚举量是 3^n，n 稍大就跑不动；不含任何 2-SAT 内容，
// 因此可以作为 main.cpp（2-SAT + 枚举）的独立交叉验证基线。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;      // 暴力只用于 n <= 8 的小数据（3^8 = 6561 个叶子）
const int MAXM = 105;     // 小数据的规则条数上界

int n, m;
char S[MAXN + 1];         // S[p]：第 p 场地图类型，1 下标
int forb[MAXN];           // forb[p]：该地图禁用的赛车（0=A,1=B,2=C），-1 表示 x 型不禁用

int rule_i[MAXM], rule_j[MAXM];   // 规则的两个位置
int rule_ci[MAXM], rule_cj[MAXM]; // 规则要求的赛车编号

int choose[MAXN];         // choose[p]：第 p 场枚举到的赛车
int first_answer[MAXN];   // 找到的第一组合法方案
bool found;

// 检查当前 choose[] 是否满足全部规则
bool check_rules() {
    for (int e = 1; e <= m; e++) {
        if (choose[rule_i[e]] != rule_ci[e]) {
            continue;  // 前提不成立，这条规则自动满足
        }
        if (choose[rule_j[e]] != rule_cj[e]) {
            return false;
        }
    }
    return true;
}

// 这一层在选择第 dep 场用哪辆车；三层分支对应 A、B、C。
void dfs_choose(int dep) {
    if (found) {
        return;
    }
    if (dep > n) {
        if (check_rules()) {
            found = true;
            for (int p = 1; p <= n; p++) {
                first_answer[p] = choose[p];
            }
        }
        return;
    }
    for (int car = 0; car <= 2; car++) {
        if (car == forb[dep]) {
            continue;  // 这张地图不适合该赛车
        }
        choose[dep] = car;
        dfs_choose(dep + 1);
        if (found) {
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int d_ignored;
    cin >> n >> d_ignored;  // d 只用于限定 x 地图张数，暴力直接按 S 判断
    cin >> (S + 1);
    cin >> m;

    for (int p = 1; p <= n; p++) {
        forb[p] = (S[p] == 'x') ? -1 : S[p] - 'a';
    }

    for (int e = 1; e <= m; e++) {
        char hi, hj;
        cin >> rule_i[e] >> hi >> rule_j[e] >> hj;
        rule_ci[e] = hi - 'A';
        rule_cj[e] = hj - 'A';
    }

    found = false;
    dfs_choose(1);

    if (!found) {
        cout << -1 << '\n';
        return 0;
    }
    for (int p = 1; p <= n; p++) {
        cout << char('A' + first_answer[p]);
    }
    cout << '\n';

    return 0;
}
