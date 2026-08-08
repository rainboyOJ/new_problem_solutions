/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-19 22:27
 * update_at: 2026-07-12 16:35
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 8000 + 5;

struct Node {
    int value;
    int id;
};

int n, q;
int a[MAXN];          // a[i] 表示原下标 i 的元素当前值
int rank_pos[MAXN];   // rank_pos[i] 表示元素 i 稳定排序后的当前排名
Node nodes[MAXN];     // 初始化时用于按 (值, 原下标) 排序

bool node_less(const Node &x, const Node &y) {
    if (x.value != y.value) {
        return x.value < y.value;
    }
    return x.id < y.id;
}

// 初始化每个原下标对应的稳定排序排名。
void init_rank() {
    sort(nodes + 1, nodes + n + 1, node_less);
    for (int i = 1; i <= n; i++) {
        rank_pos[nodes[i].id] = i;
    }
}

// 把元素 x 从旧排名中删除，再按新值插入到正确排名。
void modify_value(int x, int value) {
    int old_rank = rank_pos[x];

    // 删除旧元素后，排在它后面的元素都向前移动一位。
    for (int i = 1; i <= n; i++) {
        if (i != x && rank_pos[i] > old_rank) {
            rank_pos[i]--;
        }
    }

    a[x] = value;
    rank_pos[x] = 1;

    // 按 (值, 原下标) 比较，确定新元素的排名并调整后继元素。
    for (int i = 1; i <= n; i++) {
        if (i == x) {
            continue;
        }

        if (a[i] < a[x] || (a[i] == a[x] && i < x)) {
            rank_pos[x]++;
        } else {
            rank_pos[i]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        nodes[i].value = a[i];
        nodes[i].id = i;
    }
    init_rank();

    while (q--) {
        int op, x;
        cin >> op >> x;

        if (op == 1) {
            int value;
            cin >> value;
            modify_value(x, value);
        } else {
            cout << rank_pos[x] << '\n';
        }
    }

    return 0;
}
