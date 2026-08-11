/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 07:37
 * update_at: 2026-08-11 10:05
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n;
int a[MAXN];
int tree_array[MAXN]; // 树状数组维护每个原位置是否仍存在

int lowbit(int x) {
    return x & -x;
}

void add(int pos, int val) {
    for (int i = pos; i <= n; i += lowbit(i)) tree_array[i] += val;
}

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
    for (int i = 1; i <= n; i++) tree_array[i] = lowbit(i);

    vector<vector<int> > rounds;
    int len = n;
    while (len > 0) {
        vector<int> deleted_pos;
        for (long long x = 1; x * x * x <= len; x++) {
            int rank_pos = (int)(x * x * x);
            deleted_pos.push_back(kth_alive(rank_pos));
        }

        vector<int> values;
        for (int i = 0; i < (int)deleted_pos.size(); i++) {
            values.push_back(a[deleted_pos[i]]);
        }
        rounds.push_back(values);

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
