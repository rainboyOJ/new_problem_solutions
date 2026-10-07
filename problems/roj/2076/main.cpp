/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:40
 * update_at: 2026-10-06 11:41
 */
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 10005;

typedef long long ll;

struct Point {
    double x;
    double y;
};

Point pts[MAXN];        // 输入的所有放牧点
Point lower_hull[MAXN]; // 下凸壳，从左下走到右上
Point upper_hull[MAXN]; // 上凸壳，从右上走回左下
Point hull[MAXN];       // 拼接后的逆时针凸包顶点序列

int n;

// 按 (x, y) 升序比较，排序后最左点取最下、最右点取最上。
bool cmp_point(Point a, Point b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

// 叉积 (a - o) × (b - o)：> 0 表示 o -> a -> b 左转，= 0 表示三点共线。
double cross(Point o, Point a, Point b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// 两点之间的欧氏距离。
double dist(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// 求点集凸包的周长，即围住所有放牧点的最短围栏长度。
double convex_hull_perimeter() {
    sort(pts + 1, pts + n + 1, cmp_point);

    // 下凸壳：从左往右扫，新点不能与栈顶构成左转就弹出栈顶。
    int lower_cnt = 0;
    for (int i = 1; i <= n; i++) {
        while (lower_cnt >= 2 &&
               cross(lower_hull[lower_cnt - 1], lower_hull[lower_cnt], pts[i]) <= 0) {
            lower_cnt--;
        }
        lower_hull[++lower_cnt] = pts[i];
    }

    // 上凸壳：从右往左扫，弹出条件与下凸壳完全一致。
    int upper_cnt = 0;
    for (int i = n; i >= 1; i--) {
        while (upper_cnt >= 2 &&
               cross(upper_hull[upper_cnt - 1], upper_hull[upper_cnt], pts[i]) <= 0) {
            upper_cnt--;
        }
        upper_hull[++upper_cnt] = pts[i];
    }

    // 两条链的首尾端点是同一对最左、最右点，各自去掉末顶点后拼接。
    int hull_cnt = 0;
    for (int i = 1; i <= lower_cnt - 1; i++) {
        hull[++hull_cnt] = lower_hull[i];
    }
    for (int i = 1; i <= upper_cnt - 1; i++) {
        hull[++hull_cnt] = upper_hull[i];
    }

    // 闭合折线周长：相邻顶点两两求距离，末顶点再连回首顶点。
    double ans = 0.0;
    for (int i = 1; i <= hull_cnt; i++) {
        int next_pos = i + 1;
        if (next_pos > hull_cnt) next_pos = 1;
        ans += dist(hull[i], hull[next_pos]);
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf %lf", &pts[i].x, &pts[i].y);
    }

    printf("%.2f\n", convex_hull_perimeter());
    return 0;
}
