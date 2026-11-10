/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:11
 * update_at: 2026-11-11 00:11
 */
// brute.cpp：结构体数组结合稳定排序实现
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string name;
    int money;
    int id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<Student> a(n);
    int total = 0;

    for (int i = 0; i < n; ++i) {
        string name;
        int score, class_score;
        char is_cadre, is_west;
        int papers;

        cin >> name >> score >> class_score >> is_cadre >> is_west >> papers;

        int cur = 0;
        if (score > 80 && papers >= 1) cur += 8000;
        if (score > 85 && class_score > 80) cur += 4000;
        if (score > 90) cur += 2000;
        if (score > 85 && is_west == 'Y') cur += 1000;
        if (class_score > 80 && is_cadre == 'Y') cur += 850;

        total += cur;
        a[i] = {name, cur, i};
    }

    // 稳定排序：按奖金降序，相同时按输入下标升序
    stable_sort(a.begin(), a.end(), [](const Student& x, const Student& y) {
        if (x.money != y.money) return x.money > y.money;
        return x.id < y.id;
    });

    cout << a[0].name << "\n";
    cout << a[0].money << "\n";
    cout << total << "\n";

    return 0;
}
