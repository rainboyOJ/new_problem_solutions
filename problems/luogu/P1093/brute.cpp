// brute.cpp：每次从剩余同学里线性找出当前最应该排在前面的那一个。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;

struct Student {
    int id;
    int chinese;
    int total;
};

int n;
Student stu[MAXN];
int used[MAXN];

bool better(const Student &a, const Student &b) {
    if (a.total != b.total) {
        return a.total > b.total;
    }
    if (a.chinese != b.chinese) {
        return a.chinese > b.chinese;
    }
    return a.id < b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        int chinese, math, english;
        cin >> chinese >> math >> english;
        stu[i].id = i;
        stu[i].chinese = chinese;
        stu[i].total = chinese + math + english;
    }

    int limit = min(n, 5);
    for (int rank = 1; rank <= limit; rank++) {
        int best = 0;
        for (int i = 1; i <= n; i++) {
            if (used[i]) {
                continue;
            }
            if (best == 0 || better(stu[i], stu[best])) {
                best = i;
            }
        }
        used[best] = 1;
        cout << stu[best].id << ' ' << stu[best].total << '\n';
    }

    return 0;
}
