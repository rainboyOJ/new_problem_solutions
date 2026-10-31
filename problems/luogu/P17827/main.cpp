/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 18:55
 * update_at: 2026-10-31 19:20
 */
// main.cpp：把座位字母换算成「过道的哪一边 + 这一边从左数第几个」，
// 再按题目的四个条件从外到内逐层判断。
#include <bits/stdc++.h>
using namespace std;

// 座位在这一侧序列里从左数的位置，从 0 开始
// 过道左边是 A B C，分别对应 0 1 2；过道右边是 D F，分别对应 0 1
int seat_pos(char c) {
    if (c == 'A') return 0;
    if (c == 'B') return 1;
    if (c == 'C') return 2;
    if (c == 'D') return 0;
    return 1;   // 剩下的只可能是 'F'
}

// 座位在过道的哪一边：左边是 0，右边是 1
int seat_side(char c) {
    if (c == 'D' || c == 'F') return 1;
    return 0;
}

int main() {
    string car1, seat1, car2, seat2;   // 两张车票：车厢号、座位号
    cin >> car1 >> seat1 >> car2 >> seat2;

    char ch1 = seat1[2];   // 小 R 的座位字母，比如 01A 里的 'A'
    char ch2 = seat2[2];   // 小 X 的座位字母

    // 第 1 问：车厢号是否相同
    bool same_car = (car1 == car2);
    // 第 2 问：车厢相同，并且排号（座位号的前两位）也相同
    bool same_row = same_car && seat1[0] == seat2[0] && seat1[1] == seat2[1];
    // 第 3 问：同一排，并且在过道的同一边
    bool same_side = same_row && seat_side(ch1) == seat_side(ch2);
    // 第 4 问：同一边，并且在这一边的序列里挨着（位置只差 1）
    int p1 = seat_pos(ch1);
    int p2 = seat_pos(ch2);
    bool near_seat = same_side && (p1 + 1 == p2 || p2 + 1 == p1);

    if (same_car) cout << 1; else cout << 0;
    if (same_row) cout << 1; else cout << 0;
    if (same_side) cout << 1; else cout << 0;
    if (near_seat) cout << 1; else cout << 0;
    cout << '\n';
    return 0;
}
