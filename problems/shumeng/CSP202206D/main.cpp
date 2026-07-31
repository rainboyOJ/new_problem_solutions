/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 23:04
 */
#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

struct Segment {
    long long x1, y1, x2, y2;
    double loss;
    int slope;
    bool active;
    vector<Point> point;
};

int operation_count;
vector<Segment> segment;
map<long long, set<pair<long long, int> > > horizontal, vertical;

void insert_segment(int id) {
    Segment &now = segment[id];
    long long length = llabs(now.x2 - now.x1);
    long long dx = now.x2 > now.x1 ? 1 : -1;
    long long dy = now.y2 > now.y1 ? 1 : -1;
    for (long long i = 1; i < length; i++) {
        Point point = {now.x1 + dx * i, now.y1 + dy * i};
        now.point.push_back(point);
        horizontal[point.y].insert({point.x, id});
        vertical[point.x].insert({point.y, id});
    }
    now.active = true;
}

void erase_segment(int id) {
    Segment &now = segment[id];
    for (int i = 0; i < (int)now.point.size(); i++) {
        horizontal[now.point[i].y].erase({now.point[i].x, id});
        vertical[now.point[i].x].erase({now.point[i].y, id});
    }
    now.active = false;
}

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

int reflected_direction(int direction, int slope) {
    if (slope == 1) {
        int change[4] = {1, 0, 3, 2};
        return change[direction];
    }
    int change[4] = {3, 2, 1, 0};
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
            now.active = false;
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
            while (time > 0 && intensity >= 1) {
                long long distance;
                int id;
                if (!find_next(x, y, direction, distance, id) || distance > time) {
                    if (direction == 0) x += time;
                    if (direction == 1) y += time;
                    if (direction == 2) x -= time;
                    if (direction == 3) y -= time;
                    time = 0;
                    break;
                }
                if (direction == 0) x += distance;
                if (direction == 1) y += distance;
                if (direction == 2) x -= distance;
                if (direction == 3) y -= distance;
                time -= distance;
                intensity *= segment[id].loss;
                direction = reflected_direction(direction, segment[id].slope);
            }
            if (intensity < 1) cout << "0 0 0\n";
            else cout << x << ' ' << y << ' ' << (long long)floor(intensity) << '\n';
        }
    }

    return 0;
}
