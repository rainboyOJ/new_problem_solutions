/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 18:55
 * update_at: 2026-10-31 18:57
 */
// brute.cpp：把两张车票都拆成 (车厢号, 排号, 侧, 侧内下标) 四元组，
// 再逐位对照题目定义给出四个答案，用于和 main.cpp 对拍。
#include <bits/stdc++.h>
using namespace std;

struct Seat {
    int car;    // 车厢号
    int row;    // 排号
    int side;   // 0 过道左侧，1 过道右侧
    int idx;    // 侧内下标，从 0 开始
};

Seat parse(const string &car_str, const string &seat_str) {
    Seat s;
    s.car = stoi(car_str);
    s.row = stoi(seat_str.substr(0, 2));
    char ch = seat_str[2];
    if (ch == 'A') { s.side = 0; s.idx = 0; }
    else if (ch == 'B') { s.side = 0; s.idx = 1; }
    else if (ch == 'C') { s.side = 0; s.idx = 2; }
    else if (ch == 'D') { s.side = 1; s.idx = 0; }
    else { s.side = 1; s.idx = 1; }   // 'F'
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string c1, s1, c2, s2;
    cin >> c1 >> s1 >> c2 >> s2;
    Seat a = parse(c1, s1);
    Seat b = parse(c2, s2);

    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    if (a.car == b.car) {
        q1 = 1;
        if (a.row == b.row) {
            q2 = 1;
            if (a.side == b.side) {
                q3 = 1;
                if (a.idx + 1 == b.idx || b.idx + 1 == a.idx) q4 = 1;
            }
        }
    }
    cout << q1 << q2 << q3 << q4 << '\n';
    return 0;
}
