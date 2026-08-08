/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-19 11:49
 * update_at: 2026-07-19 11:49
 */
// main3.cpp：使用 sort + unique 保序去重的教学写法。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

struct Node {
    int value; // 数字本身
    int index; // 第一次输入时的原始位置
};

int n;
Node a[MAXN];

bool cmp_value_index(const Node &x, const Node &y) {
    if (x.value != y.value) {
        return x.value < y.value;
    }
    return x.index < y.index;
}

bool same_value(const Node &x, const Node &y) {
    return x.value == y.value;
}

bool cmp_index(const Node &x, const Node &y) {
    return x.index < y.index;
}

void solve_one() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].value;
        a[i].index = i;
    }

    // 先按 value 排，相同 value 按 index 排，让第一次出现的留在最前面。
    sort(a + 1, a + n + 1, cmp_value_index);

    // unique 只比较 value，相同数字只保留最早出现的那个。
    int new_n = unique(a + 1, a + n + 1, same_value) - (a + 1);

    // 再按原始位置排回去，恢复“第一次出现”的输出顺序。
    sort(a + 1, a + new_n + 1, cmp_index);

    for (int i = 1; i <= new_n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << a[i].value;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve_one();
    }

    return 0;
}
