/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

// 一个 45 度反射面，由两个整数端点确定，方向为斜率 ±1
struct Segment {
    long long x1, y1, x2, y2; // 两个端点
    double loss;              // 反射折损系数 a
    int slope;                // 斜率：1 或 -1
    vector<pair<long long, long long> > point; // 线段内部所有整点
};

int operation_count;
vector<Segment> segment;                                    // 线段表，下标对应操作编号
map<long long, set<pair<long long, int> > > horizontal;     // 按 y 分组，保存 (x, 线段编号)
map<long long, set<pair<long long, int> > > vertical;       // 按 x 分组，保存 (y, 线段编号)

// 把线段内部的所有整点插入水平线和竖直线
void insert_segment(int id) {
    Segment &now = segment[id];
    long long length = llabs(now.x2 - now.x1);  // 线段内部点的个数 = 长度 - 1
    long long dx = now.x2 > now.x1 ? 1 : -1;
    long long dy = now.y2 > now.y1 ? 1 : -1;
    for (long long i = 1; i < length; i++) {
        long long px = now.x1 + dx * i;
        long long py = now.y1 + dy * i;
        now.point.push_back({px, py});
        horizontal[py].insert({px, id});
        vertical[px].insert({py, id});
    }
}

// 删除线段时，把它维护的所有内部整点从两条线上移除
void erase_segment(int id) {
    Segment &now = segment[id];
    for (int i = 0; i < (int)now.point.size(); i++) {
        horizontal[now.point[i].second].erase({now.point[i].first, id});
        vertical[now.point[i].first].erase({now.point[i].second, id});
    }
}

// 在方向 direction 上找从 (x,y) 出发最近的碰撞点。
// direction: 0 向右, 1 向上, 2 向左, 3 向下。找到返回 true 并回传距离和线段编号。
bool find_next(long long x, long long y, int direction, long long &distance, int &id) {
    if (direction == 0) {
        map<long long, set<pair<long long, int> > >::iterator line = horizontal.find(y);
        if (line == horizontal.end()) return false;
        set<pair<long long, int> >::iterator it = line->second.upper_bound({x, INT_MAX});
        if (it == line->second.end()) return false;
        distance = it->first - x;
        id = it->second;
        return true;
    }
    if (direction == 2) {
        map<long long, set<pair<long long, int> > >::iterator line = horizontal.find(y);
        if (line == horizontal.end()) return false;
        set<pair<long long, int> >::iterator it = line->second.lower_bound({x, -1});
        if (it == line->second.begin()) return false;
        --it;
        distance = x - it->first;
        id = it->second;
        return true;
    }
    if (direction == 1) {
        map<long long, set<pair<long long, int> > >::iterator line = vertical.find(x);
        if (line == vertical.end()) return false;
        set<pair<long long, int> >::iterator it = line->second.upper_bound({y, INT_MAX});
        if (it == line->second.end()) return false;
        distance = it->first - y;
        id = it->second;
        return true;
    }
    map<long long, set<pair<long long, int> > >::iterator line = vertical.find(x);
    if (line == vertical.end()) return false;
    set<pair<long long, int> >::iterator it = line->second.lower_bound({y, -1});
    if (it == line->second.begin()) return false;
    --it;
    distance = y - it->first;
    id = it->second;
    return true;
}

// 根据斜率计算反射后的新方向
int reflected_direction(int direction, int slope) {
    if (slope == 1) {
        int change[4] = {1, 0, 3, 2}; // 斜率 +1：左右互换，上下互换
        return change[direction];
    }
    int change[4] = {3, 2, 1, 0};     // 斜率 -1：水平变反向，垂直变反向
    return change[direction];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> operation_count;
    segment.resize(operation_count + 1);
    for (int operation = 1; operation <= operation_count; operation++) {
        int type;
        cin >> type;
        if (type == 1) {
            Segment now;
            cin >> now.x1 >> now.y1 >> now.x2 >> now.y2 >> now.loss;
            now.slope = (now.x2 - now.x1) * (now.y2 - now.y1) > 0 ? 1 : -1;
            segment[operation] = now;
            insert_segment(operation);
        } else if (type == 2) {
            int deleted;
            cin >> deleted;
            erase_segment(deleted);
        } else {
            long long x, y, time;
            double intensity;
            int direction;
            cin >> x >> y >> direction >> intensity >> time;
            // 逐次找最近碰撞点，直到时间用完或强度耗尽
            while (time > 0 && intensity >= 1) {
                long long distance;
                int id;
                if (!find_next(x, y, direction, distance, id) || distance > time) {
                    // 本次剩余时间内不再有碰撞，直线走完
                    if (direction == 0) x += time;
                    if (direction == 1) y += time;
                    if (direction == 2) x -= time;
                    if (direction == 3) y -= time;
                    time = 0;
                    break;
                }
                // 移动到碰撞点，消耗对应时间
                if (direction == 0) x += distance;
                if (direction == 1) y += distance;
                if (direction == 2) x -= distance;
                if (direction == 3) y -= distance;
                time -= distance;
                intensity *= segment[id].loss;      // 反射折损
                direction = reflected_direction(direction, segment[id].slope);
            }
            if (intensity < 1) cout << "0 0 0\n";   // 已耗散
            else cout << x << ' ' << y << ' ' << (long long)floor(intensity) << '\n';
        }
    }

    return 0;
}