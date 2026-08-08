#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

struct Query {
    int l, r, id;
};

int n, m;
int block_size;
int color[MAXN];
long long color_count[MAXN]; // 当前区间内每种颜色出现次数。
long long same_pair_count;   // 当前区间内同色无序对数量之和。
long long answer_num[MAXN], answer_den[MAXN];
Query queries[MAXN];

bool cmp_query(const Query &a, const Query &b) {
    int block_a = a.l / block_size;
    int block_b = b.l / block_size;
    if (block_a != block_b) {
        return block_a < block_b;
    }
    if (block_a & 1) {
        return a.r > b.r;
    }
    return a.r < b.r;
}

void add_pos(int pos) {
    int c = color[pos];
    // 新加入一个颜色 c，会和已有 color_count[c] 只同色袜子配成同色对。
    same_pair_count += color_count[c];
    color_count[c]++;
}

void remove_pos(int pos) {
    int c = color[pos];
    color_count[c]--;
    same_pair_count -= color_count[c];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    block_size = max(1, (int)sqrt(n));
    sort(queries + 1, queries + m + 1, cmp_query);

    int cur_l = 1, cur_r = 0;
    for (int i = 1; i <= m; i++) {
        int l = queries[i].l;
        int r = queries[i].r;
        while (cur_l > l) {
            cur_l--;
            add_pos(cur_l);
        }
        while (cur_r < r) {
            cur_r++;
            add_pos(cur_r);
        }
        while (cur_l < l) {
            remove_pos(cur_l);
            cur_l++;
        }
        while (cur_r > r) {
            remove_pos(cur_r);
            cur_r--;
        }

        long long len = r - l + 1;
        if (len == 1) {
            answer_num[queries[i].id] = 0;
            answer_den[queries[i].id] = 1;
        } else {
            long long total_pair = len * (len - 1) / 2;
            long long g = gcd(same_pair_count, total_pair);
            answer_num[queries[i].id] = same_pair_count / g;
            answer_den[queries[i].id] = total_pair / g;
        }
    }

    for (int i = 1; i <= m; i++) {
        cout << answer_num[i] << '/' << answer_den[i] << '\n';
    }

    return 0;
}
