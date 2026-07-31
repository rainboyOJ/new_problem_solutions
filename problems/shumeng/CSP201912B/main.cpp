/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:11
 */
#include <bits/stdc++.h>
using namespace std;

bool has_point(const set<pair<long long, long long> > &points, long long x, long long y) {
    return points.find(make_pair(x, y)) != points.end();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<long long, long long> > point_list;
    set<pair<long long, long long> > points;
    for (int i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        point_list.push_back(make_pair(x, y));
        points.insert(make_pair(x, y));
    }

    int answer[5] = {};
    for (int i = 0; i < n; i++) {
        long long x = point_list[i].first;
        long long y = point_list[i].second;
        if (!has_point(points, x - 1, y) || !has_point(points, x + 1, y)
                || !has_point(points, x, y - 1) || !has_point(points, x, y + 1)) {
            continue;
        }
        int score = 0;
        score += has_point(points, x - 1, y - 1);
        score += has_point(points, x - 1, y + 1);
        score += has_point(points, x + 1, y - 1);
        score += has_point(points, x + 1, y + 1);
        answer[score]++;
    }
    for (int i = 0; i <= 4; i++) cout << answer[i] << '\n';

    return 0;
}
