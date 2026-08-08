#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

struct Student {
    string name;
    int year, month, day;
    int id; // 输入顺序，后输入的编号更大
} a[MAXN];

int n;

bool cmp(const Student &x, const Student &y) {
    if (x.year != y.year) {
        return x.year < y.year;
    }
    if (x.month != y.month) {
        return x.month < y.month;
    }
    if (x.day != y.day) {
        return x.day < y.day;
    }
    return x.id > y.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].name >> a[i].year >> a[i].month >> a[i].day;
        a[i].id = i;
    }

    sort(a + 1, a + n + 1, cmp);

    for (int i = 1; i <= n; i++) {
        cout << a[i].name << '\n';
    }

    return 0;
}
