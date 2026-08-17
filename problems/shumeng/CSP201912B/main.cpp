/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:41
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
long long point_x[MAXN], point_y[MAXN]; // 各垃圾点坐标
set<pair<long long, long long> > points; // 坐标集合，用于 O(log n) 查询某个位置是否有垃圾

// 判断坐标 (x, y) 处是否存在垃圾。
bool has_point(long long x, long long y) {
    return points.find(make_pair(x, y)) != points.end();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> point_x[i] >> point_y[i];
        points.insert(make_pair(point_x[i], point_y[i]));
    }

    int answer[5] = {}; // 得分为 0..4 的回收站选址个数
    for (int i = 1; i <= n; i++) {
        long long x = point_x[i], y = point_y[i];
        // 上下左右四个正交邻居必须全部存在垃圾。
        if (!has_point(x - 1, y) || !has_point(x + 1, y)
                || !has_point(x, y - 1) || !has_point(x, y + 1)) {
            continue;
        }
        // 评分：四个对角位置中有几处存在垃圾。
        int score = 0;
        score += has_point(x - 1, y - 1);
        score += has_point(x - 1, y + 1);
        score += has_point(x + 1, y - 1);
        score += has_point(x + 1, y + 1);
        answer[score]++;
    }
    for (int i = 0; i <= 4; i++) cout << answer[i] << '\n';

    return 0;
}