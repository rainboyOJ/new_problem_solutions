/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:48
 * update_at: 2026-10-01 22:48
 */
// main.cpp：把每辆车能被测出超速的测速仪压成区间，再按右端点贪心求最少保留测速仪。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int T;
int n, m;
ll L, V;                      // L 道路长度，V 限速
ll d[MAXN], v[MAXN], a[MAXN]; // 每辆车的驶入位置、初速度、加速度
ll p[MAXN];                   // 测速仪位置，保证严格递增

int speeding_cars;            // 超速车数量，也就是产生了区间的车辆数
int max_left[MAXN];           // max_left[r]：右端点为 r 的区间里最大的左端点

// 判断从 start_pos 以 start_speed 驶入、加速度为 acc 的车在位置 pos 处是否超速。
// 直接比较速度平方 v^2 + 2*acc*(pos - start_pos) 与 V^2，避免开方和浮点误差。
bool is_speeding(ll start_pos, ll start_speed, ll acc, ll pos) {
    ll speed_square = start_speed * start_speed + 2 * acc * (pos - start_pos);
    return speed_square > V * V;
}

// 记录一个测速仪下标区间 [left, right]。
// 后面的贪心只关心“同一个右端点上最大的左端点”，所以只保留这个值，不落地存整张区间表。
void record_interval(int left, int right) {
    if (max_left[right] < left) {
        max_left[right] = left;
    }
    speeding_cars++;
}

// 求出这辆车会在哪些测速仪处超速，把对应的连续下标区间记下来。
void add_interval(ll start_pos, ll start_speed, ll acc) {
    // 测速仪位置递增，先找第一台不早于驶入位置的测速仪。
    // 测速仪都在道路内（p[j] <= L），所以不用再按 L 截断。
    int start = lower_bound(p + 1, p + m + 1, start_pos) - p;
    if (start > m) {
        return;
    }

    if (acc == 0) {
        // 匀速车：速度一直不变，要么全程超速，要么全程不超速。
        if (start_speed > V) {
            record_interval(start, m);
        }
        return;
    }

    if (acc > 0) {
        // 加速车：速度随位置单调变大，超速测速仪构成一个后缀，二分第一个超速的。
        int left = start, right = m;
        int first = m + 1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (is_speeding(start_pos, start_speed, acc, p[mid])) {
                first = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        if (first <= m) {
            record_interval(first, m);
        }
        return;
    }

    // 减速车：速度随位置单调变小，超速测速仪构成一个前缀。
    // 先确认起点处就已超速，再二分最后一个超速的测速仪。
    if (start_speed <= V || !is_speeding(start_pos, start_speed, acc, p[start])) {
        return;
    }

    int left = start, right = m;
    int last = start;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (is_speeding(start_pos, start_speed, acc, p[mid])) {
            last = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    record_interval(start, last);
}

// 最少保留多少台测速仪，才能让每辆超速车至少被测到一次。
// 标准区间贪心是按右端点排序后选右端点；这里右端点本身就是 [1, m] 的测速仪下标，
// 按右端点分桶后直接从小到大扫，省掉排序。
int min_required_sensors() {
    int selected = 0;
    int last_pos = 0;

    for (int r = 1; r <= m; r++) {
        // 右端点为 r 的区间里只要有一个还没被覆盖，就必须选 r。
        // 选 r 最靠右，最有机会把后面的区间一起盖住。
        if (max_left[r] > last_pos) {
            selected++;
            last_pos = r;
        }
    }

    return selected;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n >> m >> L >> V;

        speeding_cars = 0;
        for (int i = 1; i <= m; i++) {
            max_left[i] = 0;
        }

        for (int i = 1; i <= n; i++) {
            cin >> d[i] >> v[i] >> a[i];
        }
        for (int i = 1; i <= m; i++) {
            cin >> p[i];
        }

        for (int i = 1; i <= n; i++) {
            add_interval(d[i], v[i], a[i]);
        }

        int required = min_required_sensors();

        cout << speeding_cars << ' ' << m - required << '\n';
    }

    return 0;
}
