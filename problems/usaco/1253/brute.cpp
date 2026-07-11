/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:21
 * update_at: 2026-07-11 17:23
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 105;
const int MAXC = 15;

int n, m;
string input_value[MAXM];
char output_value[MAXM];

int cond_cnt;
int rule_cnt;
int rule_bit[MAXC], rule_val[MAXC], rule_ret[MAXC];
bool used_cond[MAXC];
bool found_program;

int run_program(string s, int default_ret) {
    for (int i = 1; i <= rule_cnt; i++) {
        if (s[rule_bit[i]] == char('0' + rule_val[i])) {
            return rule_ret[i];
        }
    }
    return default_ret;
}

bool current_program_matches(int default_ret) {
    for (int i = 1; i <= m; i++) {
        int ret = run_program(input_value[i], default_ret);
        if (ret != output_value[i] - '0') {
            return false;
        }
    }
    return true;
}

void dfs_program() {
    if (found_program) {
        return;
    }

    if (current_program_matches(0) || current_program_matches(1)) {
        found_program = true;
        return;
    }

    if (rule_cnt == cond_cnt) {
        return;
    }

    // 枚举下一条 if 语句：检查某个变量是否等于 0/1，并返回 0/1。
    for (int c = 0; c < cond_cnt; c++) {
        if (used_cond[c]) {
            continue;
        }
        used_cond[c] = true;

        for (int ret = 0; ret <= 1; ret++) {
            rule_cnt++;
            rule_bit[rule_cnt] = c / 2;
            rule_val[rule_cnt] = c % 2;
            rule_ret[rule_cnt] = ret;

            dfs_program();

            rule_cnt--;
            if (found_program) {
                break;
            }
        }

        used_cond[c] = false;
        if (found_program) {
            break;
        }
    }
}

bool solve_case() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> input_value[i] >> output_value[i];
    }

    cond_cnt = 2 * n;
    rule_cnt = 0;
    found_program = false;
    for (int i = 0; i < cond_cnt; i++) {
        used_cond[i] = false;
    }

    dfs_program();
    return found_program;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        if (solve_case()) {
            cout << "OK\n";
        } else {
            cout << "LIE\n";
        }
    }

    return 0;
}
