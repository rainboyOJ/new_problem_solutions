/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

struct Moment {
    // 区间内点的数量、一次矩和二次矩。
    long double count, sx, sy, sxx, syy, sxy;
};

struct Affine {
    // (x,y) -> M(x,y) + v。
    long double m00, m01, m10, m11, vx, vy;
};

struct Node {
    Moment data;
    Affine lazy;
};

int n, query_count, base;
vector<Node> tree;

Affine identity() {
    return {1, 0, 0, 1, 0, 0};
}

Affine compose(const Affine &first, const Affine &second) {
    // 先执行 second，再执行 first。
    return {
        first.m00 * second.m00 + first.m01 * second.m10,
        first.m00 * second.m01 + first.m01 * second.m11,
        first.m10 * second.m00 + first.m11 * second.m10,
        first.m10 * second.m01 + first.m11 * second.m11,
        first.m00 * second.vx + first.m01 * second.vy + first.vx,
        first.m10 * second.vx + first.m11 * second.vy + first.vy,
    };
}

Moment merge_moment(const Moment &left, const Moment &right) {
    return {left.count + right.count, left.sx + right.sx, left.sy + right.sy,
            left.sxx + right.sxx, left.syy + right.syy, left.sxy + right.sxy};
}

void apply_node(int node, const Affine &transform) {
    Moment old = tree[node].data;
    long double nx = transform.m00 * old.sx + transform.m01 * old.sy + old.count * transform.vx;
    long double ny = transform.m10 * old.sx + transform.m11 * old.sy + old.count * transform.vy;
    long double nxx = transform.m00 * transform.m00 * old.sxx
        + transform.m01 * transform.m01 * old.syy
        + 2 * transform.m00 * transform.m01 * old.sxy
        + 2 * transform.vx * (transform.m00 * old.sx + transform.m01 * old.sy)
        + old.count * transform.vx * transform.vx;
    long double nyy = transform.m10 * transform.m10 * old.sxx
        + transform.m11 * transform.m11 * old.syy
        + 2 * transform.m10 * transform.m11 * old.sxy
        + 2 * transform.vy * (transform.m10 * old.sx + transform.m11 * old.sy)
        + old.count * transform.vy * transform.vy;
    long double nxy = transform.m00 * transform.m10 * old.sxx
        + (transform.m00 * transform.m11 + transform.m01 * transform.m10) * old.sxy
        + transform.m01 * transform.m11 * old.syy
        + transform.vx * (transform.m10 * old.sx + transform.m11 * old.sy)
        + transform.vy * (transform.m00 * old.sx + transform.m01 * old.sy)
        + old.count * transform.vx * transform.vy;
    tree[node].data.sx = nx;
    tree[node].data.sy = ny;
    tree[node].data.sxx = nxx;
    tree[node].data.syy = nyy;
    tree[node].data.sxy = nxy;
    tree[node].lazy = compose(transform, tree[node].lazy);
}

void pull(int node) {
    tree[node].data = merge_moment(tree[node << 1].data, tree[node << 1 | 1].data);
}

void push(int node) {
    Affine lazy = tree[node].lazy;
    if (lazy.m00 == 1 && lazy.m01 == 0 && lazy.m10 == 0 && lazy.m11 == 1
            && lazy.vx == 0 && lazy.vy == 0) return;
    apply_node(node << 1, lazy);
    apply_node(node << 1 | 1, lazy);
    tree[node].lazy = identity();
}

void update(int node, int left, int right, int ql, int qr, const Affine &transform) {
    if (ql <= left && right <= qr) {
        apply_node(node, transform);
        return;
    }
    push(node);
    int middle = (left + right) >> 1;
    if (ql <= middle) update(node << 1, left, middle, ql, qr, transform);
    if (qr > middle) update(node << 1 | 1, middle + 1, right, ql, qr, transform);
    pull(node);
}

Moment query(int node, int left, int right, int ql, int qr) {
    if (ql <= left && right <= qr) return tree[node].data;
    push(node);
    int middle = (left + right) >> 1;
    Moment result = {};
    if (ql <= middle) result = merge_moment(result, query(node << 1, left, middle, ql, qr));
    if (qr > middle) result = merge_moment(result, query(node << 1 | 1, middle + 1, right, ql, qr));
    return result;
}

Affine transform_line(long double theta, long double y0, bool projection) {
    long double c = cos(theta), s = sin(theta);
    Affine result;
    if (projection) result = {c * c, c * s, c * s, s * s, 0, 0};
    else result = {c * c - s * s, 2 * c * s, 2 * c * s, s * s - c * c, 0, 0};
    result.vx = -result.m01 * y0;
    result.vy = y0 - result.m11 * y0;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> query_count;
    base = 1;
    while (base < n) base <<= 1;
    tree.resize(base << 1);
    for (int i = 1; i < (base << 1); i++) tree[i].lazy = identity();
    for (int i = 1; i <= n; i++) {
        long double x, y;
        cin >> x >> y;
        tree[base + i - 1].data = {1, x, y, x * x, y * y, x * y};
    }
    for (int i = base - 1; i >= 1; i--) pull(i);

    cout << fixed << setprecision(6);
    while (query_count--) {
        int type, left, right;
        cin >> type >> left >> right;
        if (type <= 5) {
            long double a, b, theta, lambda;
            Affine transform;
            if (type == 1) {
                cin >> a >> b;
                transform = {1, 0, 0, 1, a, b};
            } else if (type == 2) {
                cin >> a >> b >> theta;
                long double c = cos(theta), s = sin(theta);
                transform = {c, -s, s, c, a - c * a + s * b, b - s * a - c * b};
            } else if (type == 3) {
                cin >> a >> b >> lambda;
                transform = {lambda, 0, 0, lambda, a * (1 - lambda), b * (1 - lambda)};
            } else {
                cin >> theta >> b;
                transform = transform_line(theta, b, type == 5);
            }
            update(1, 1, base, left, right, transform);
        } else if (type == 6) {
            Moment result = query(1, 1, base, left, right);
            cout << result.sx / result.count << ' ' << result.sy / result.count << '\n';
        } else {
            long double a, b;
            cin >> a >> b;
            Moment result = query(1, 1, base, left, right);
            long double answer = result.sxx + result.syy - 2 * a * result.sx - 2 * b * result.sy
                + result.count * (a * a + b * b);
            cout << answer << '\n';
        }
    }

    return 0;
}
