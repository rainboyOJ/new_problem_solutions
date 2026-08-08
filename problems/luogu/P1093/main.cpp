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

bool cmp(const Student &a, const Student &b) {
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

    sort(stu + 1, stu + n + 1, cmp);

    int limit = min(n, 5);
    for (int i = 1; i <= limit; i++) {
        cout << stu[i].id << ' ' << stu[i].total << '\n';
    }

    return 0;
}
