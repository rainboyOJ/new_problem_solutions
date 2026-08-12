/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 07:37
 * update_at: 2026-08-12 14:07
 */
// main.cpp：正式主解，用树状数组维护每个原位置是否存活，kth 查询定位当前第 k 个元素。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n;
int a[MAXN];        // 原数组，a[i] 存第 i 个位置的元素值
int tree_array[MAXN]; // 树状数组：对每个原位置维护存活标记（1 存活、0 已删除），前缀和 = 当前位置之前的存活个数

int lowbit(int x) {
    return x & -x;
}

void add(int pos, int val) {
    for (int i = pos; i <= n; i += lowbit(i)) tree_array[i] += val;
}

// 找到当前剩余序列中排名第 k 的元素对应的原数组下标。
// 利用树状数组前缀和单调性，二分倍增跳过大段。
int kth_alive(int k) {
    int pos = 0;
    int sum = 0;
    for (int step = 1 << 20; step > 0; step >>= 1) {
        int next_pos = pos + step;
        if (next_pos <= n && sum + tree_array[next_pos] < k) {
            pos = next_pos;
            sum += tree_array[next_pos];
        }
    }
    return pos + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    // 初始时所有位置都存活，树状数组第 i 个位置的值直接等于 lowbit(i)。
    for (int i = 1; i <= n; i++) tree_array[i] = lowbit(i);

    vector<vector<int> > rounds;
    int len = n; // 当前剩余序列的长度
    while (len > 0) {
        // 第一阶段：只定位本轮要删除的位置，不改树状数组，保证"同时删除"。
        vector<int> deleted_pos;
        for (long long x = 1; x * x * x <= len; x++) {
            int rank_pos = (int)(x * x * x);
            deleted_pos.push_back(kth_alive(rank_pos));
        }

        // 排名递增，查出的原下标也递增，直接按顺序输出即为本轮删除序列。
        vector<int> values;
        for (int i = 0; i < (int)deleted_pos.size(); i++) {
            values.push_back(a[deleted_pos[i]]);
        }
        rounds.push_back(values);

        // 第二阶段：统一把本轮删除的位置标记为 0。
        for (int i = 0; i < (int)deleted_pos.size(); i++) {
            add(deleted_pos[i], -1);
        }
        len -= (int)deleted_pos.size();
    }

    cout << rounds.size() << '\n';
    for (int i = 0; i < (int)rounds.size(); i++) {
        for (int j = 0; j < (int)rounds[i].size(); j++) {
            if (j) cout << ' ';
            cout << rounds[i][j];
        }
        cout << '\n';
    }
    return 0;
}
