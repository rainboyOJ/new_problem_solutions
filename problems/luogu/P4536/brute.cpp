// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

struct Triangle {
    string code;
    Point a, b, c;
};

vector<Triangle> all_triangles;
string target_code;
int max_depth;

Point mid(Point p, Point q) {
    return {(p.x + q.x) / 2, (p.y + q.y) / 2};
}

void add_triangle(const string &code, Point a, Point b, Point c) {
    all_triangles.push_back({code, a, b, c});
}

void build_all(const string &prefix, Point a, Point b, Point c, int depth) {
    Point ab = mid(a, b);
    Point ac = mid(a, c);
    Point bc = mid(b, c);

    // 1: 顶部，2: 左下，3: 右下，4: 中间倒三角
    add_triangle(prefix + '1', ac, bc, c);
    add_triangle(prefix + '2', a, ab, ac);
    add_triangle(prefix + '3', ab, b, bc);
    add_triangle(prefix + '4', ab, ac, bc);

    if (depth == max_depth) return;

    build_all(prefix + '1', ac, bc, c, depth + 1);
    build_all(prefix + '2', a, ab, ac, depth + 1);
    build_all(prefix + '3', ab, b, bc, depth + 1);
}

bool is_prefix_noncontain_hole(const string &small, const string &big) {
    // 判断 small 是否是 big 的“包含性前缀”。
    if ((int)small.size() >= (int)big.size()) return false;
    if (big.substr(0, small.size()) != small) return false;
    if (!small.empty() && small.back() == '4') return false;
    return true;
}

bool same_point(Point p, Point q) {
    return p.x == q.x && p.y == q.y;
}

bool on_segment(Point p, Point a, Point b) {
    long long cross = (p.x - a.x) * (b.y - a.y) - (p.y - a.y) * (b.x - a.x);
    if (cross != 0) return false;
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

vector<pair<Point, Point>> edges(const Triangle &t) {
    vector<pair<Point, Point>> e;
    e.push_back({t.a, t.b});
    e.push_back({t.a, t.c});
    e.push_back({t.b, t.c});
    return e;
}

bool adjacent(const Triangle &A, const Triangle &B) {
    if (A.code == B.code) return false;
    if (is_prefix_noncontain_hole(B.code, A.code)) return false;

    vector<pair<Point, Point>> ea = edges(A);
    vector<pair<Point, Point>> eb = edges(B);

    for (int i = 0; i < (int)ea.size(); i++) {
        Point p = ea[i].first;
        Point q = ea[i].second;
        for (int j = 0; j < (int)eb.size(); j++) {
            Point u = eb[j].first;
            Point v = eb[j].second;
            if (on_segment(p, u, v) && on_segment(q, u, v)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string full_name;
    cin >> full_name;
    target_code = full_name.substr(1);
    max_depth = (int)target_code.size();

    long long scale = 1LL << max_depth;
    Point a = {0, 0};
    Point b = {scale, 0};
    Point c = {0, scale};
    build_all("", a, b, c, 1);

    Triangle target;
    for (int i = 0; i < (int)all_triangles.size(); i++) {
        if (all_triangles[i].code == target_code) {
            target = all_triangles[i];
            break;
        }
    }

    vector<string> ans;
    for (int i = 0; i < (int)all_triangles.size(); i++) {
        if (adjacent(target, all_triangles[i])) {
            ans.push_back(all_triangles[i].code);
        }
    }

    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    for (int i = 0; i < (int)ans.size(); i++) {
        cout << 'T' << ans[i] << '\n';
    }

    return 0;
}
