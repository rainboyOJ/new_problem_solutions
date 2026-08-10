/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-10 21:22
 * update_at: 2026-08-10 21:22
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 500005;

int n;
int a[MAXN];          // 原序列
int sorted_value[MAXN]; // 排序后的值，用来离散化
int tree[MAXN];       // Fenwick：tree 中维护值排名出现次数

int lowbit(int x) {
    return x & -x;
}

void add(int pos, int value) {
    for (int i = pos; i <= n; i += lowbit(i)) {
        tree[i] += value;
    }
}

int prefix_sum(int pos) {
    int answer = 0;
    for (int i = pos; i > 0; i -= lowbit(i)) {
        answer += tree[i];
    }
    return answer;
}

int get_rank(int value, int value_cnt) {
    return (int)(lower_bound(sorted_value + 1, sorted_value + value_cnt + 1, value) - sorted_value);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sorted_value[i] = a[i];
    }

    sort(sorted_value + 1, sorted_value + n + 1);
    int value_cnt = unique(sorted_value + 1, sorted_value + n + 1) - (sorted_value + 1);

    ll answer = 0;
    int seen = 0; // 已经扫描过的元素个数

    for (int i = 1; i <= n; i++) {
        int rank = get_rank(a[i], value_cnt);

        // prefix 表示左边 <= 当前值的个数。
        int prefix = prefix_sum(rank);
        answer += (ll)(seen - prefix); // 左边 > 当前值的个数，就是新产生的逆序对数

        add(rank, 1); // 当前值加入“值排名桶”
        seen++;
    }

    cout << answer << '\n';
    return 0;
}
