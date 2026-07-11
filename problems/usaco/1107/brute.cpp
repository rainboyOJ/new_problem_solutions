/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:29
 * update_at: 2026-07-11 13:33
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

string animal_name[12] = {
    "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse",
    "Goat", "Monkey", "Rooster", "Dog", "Pig", "Rat"
};

map<string, int> born_year;

string get_animal(int year) {
    int x = year % 12;
    if (x < 0) {
        x += 12;
    }
    return animal_name[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    born_year["Bessie"] = 0;

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        string cow_a, born, in_word, relation, animal, year_word, from, cow_b;
        cin >> cow_a >> born >> in_word >> relation >> animal >> year_word >> from >> cow_b;

        int y = born_year[cow_b];

        // 暴力逐年移动，直到遇到严格之前/之后的目标生肖年。
        do {
            if (relation == "next") {
                y++;
            } else {
                y--;
            }
        } while (get_animal(y) != animal);

        born_year[cow_a] = y;
    }

    cout << abs(born_year["Elsie"]) << '\n';

    return 0;
}
