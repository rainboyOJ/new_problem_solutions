#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

struct Dwarf {
    int a, b;
} d[MAXN], ord[MAXN];

int n, H;
int best_answer;
int total_a;

bool cmp_dwarf(const Dwarf &lhs, const Dwarf &rhs) {
    return lhs.a + lhs.b < rhs.a + rhs.b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
    // 做法是枚举所有子集，把选中的人按 a+b 排序，
    // 再逐个检查“已逃走肩高前缀 <= T+a_i+b_i-H”是否始终成立。
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> d[i].a >> d[i].b;
        total_a += d[i].a;
    }
    cin >> H;

    best_answer = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                ord[cnt++] = d[i];
            }
        }

        sort(ord, ord + cnt, cmp_dwarf);

        bool ok = true;
        int prefix_escape = 0;
        for (int i = 0; i < cnt; i++) {
            prefix_escape += ord[i].a;
            if (prefix_escape > total_a + ord[i].a + ord[i].b - H) {
                ok = false;
                break;
            }
        }

        if (ok) {
            best_answer = max(best_answer, cnt);
        }
    }

    cout << best_answer << '\n';
    return 0;
}
