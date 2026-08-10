/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-10 14:12
 * update_at: 2026-08-10 14:12
 */
#include <bits/stdc++.h>
using namespace std;

// 单点加、前缀和、区间和。下标必须从 1 开始。
// 模板来自 rbook fenwick。
template <typename T>
struct Fenwick {
    int n = 0;
    vector<T> tree;

    Fenwick(int n = 0) { init(n); }

    void init(int size) {
        n = size;
        tree.assign(n + 1, 0);
    }

    static int lowbit(int x) { return x & -x; }

    void add(int pos, T value) {
        for (int i = pos; i <= n; i += lowbit(i)) {
            tree[i] += value;
        }
    }

    T prefix_sum(int pos) const {
        T answer = 0;
        for (int i = pos; i > 0; i -= lowbit(i)) {
            answer += tree[i];
        }
        return answer;
    }

    T range_sum(int left, int right) const {
        return prefix_sum(right) - prefix_sum(left - 1);
    }
};

const int MAXN = 300005;
const int MAXM = 300005;

struct Point {
    int first;
    int second;
};

struct Query {
    int left;
    int right;
    int identity;
};

int n, m;
long long a[MAXN];       // 原数组
int ordered[MAXN];       // 按值从小到大排列的原下标
Point points[2 * MAXN];  // 好配对转成的点 (max(x,y), min(x,y))
int point_cnt;
Query queries[MAXM];

// 按值排序原下标
bool cmp_value(int x, int y) {
    return a[x] < a[y];
}

bool cmp_point(const Point &p, const Point &q) {
    if (p.first != q.first) return p.first < q.first;
    return p.second < q.second;
}

bool cmp_query(const Query &p, const Query &q) {
    if (p.right != q.right) return p.right < q.right;
    return p.left < q.left;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> queries[i].left >> queries[i].right;
        queries[i].identity = i;
    }

    // 找每个位置的值最近邻居：按值排序后，最近值只可能是前驱或后继。
    for (int i = 1; i <= n; i++) ordered[i] = i;
    sort(ordered + 1, ordered + n + 1, cmp_value);

    for (int pos = 1; pos <= n; pos++) {
        int index = ordered[pos];
        long long left_gap = LLONG_MAX;
        long long right_gap = LLONG_MAX;
        if (pos > 1) left_gap = a[index] - a[ordered[pos - 1]];
        if (pos < n) right_gap = a[ordered[pos + 1]] - a[index];

        // 前驱距离更近（或相等）：与前驱组成好配对
        if (pos > 1 && left_gap <= right_gap) {
            int other = ordered[pos - 1];
            point_cnt++;
            points[point_cnt].first = max(index, other);
            points[point_cnt].second = min(index, other);
        }
        // 后继距离更近（或相等）：与后继组成好配对
        if (pos < n && right_gap <= left_gap) {
            int other = ordered[pos + 1];
            point_cnt++;
            points[point_cnt].first = max(index, other);
            points[point_cnt].second = min(index, other);
        }
    }

    // 重复的二维点不能去重：两个相反方向是两组有序配对。
    sort(points + 1, points + point_cnt + 1, cmp_point);
    sort(queries + 1, queries + m + 1, cmp_query);

    Fenwick<int> bit(n); // 标记第二坐标（min）已加入的点
    int pointer = 0;     // 已加入的点数
    long long answer = 0;

    for (int i = 1; i <= m; i++) {
        // 右端点递增：加入所有第一坐标 <= r 的点
        while (pointer < point_cnt && points[pointer + 1].first <= queries[i].right) {
            pointer++;
            bit.add(points[pointer].second, 1);
        }
        // 总数去掉第二坐标 < l 的部分，就是两个坐标都在 [l,r] 内的配对
        long long count = pointer - bit.prefix_sum(queries[i].left - 1);
        answer += count * queries[i].identity;
    }

    cout << answer << '\n';
    return 0;
}
