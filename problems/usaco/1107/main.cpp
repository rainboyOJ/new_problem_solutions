/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:29
 * update_at: 2026-07-11 13:33
 */
#include <bits/stdc++.h>
using namespace std;

string animal_name[12] = {
    "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse",
    "Goat", "Monkey", "Rooster", "Dog", "Pig", "Rat"
};

map<string, int> animal_id;
map<string, int> born_year; // 相对 Bessie 的出生年份，Bessie 为 0。

int get_animal_id(int year) {
    int x = year % 12;
    if (x < 0) {
        x += 12;
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 12; i++) {
        animal_id[animal_name[i]] = i;
    }

    born_year["Bessie"] = 0;

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        string cow_a, born, in_word, relation, animal, year_word, from, cow_b;
        cin >> cow_a >> born >> in_word >> relation >> animal >> year_word >> from >> cow_b;

        int base_year = born_year[cow_b];
        int base_animal = get_animal_id(base_year);
        int target_animal = animal_id[animal];
        int diff;

        if (relation == "next") {
            diff = (target_animal - base_animal + 12) % 12;
            if (diff == 0) {
                diff = 12;
            }
            born_year[cow_a] = base_year + diff;
        } else {
            diff = (base_animal - target_animal + 12) % 12;
            if (diff == 0) {
                diff = 12;
            }
            born_year[cow_a] = base_year - diff;
        }
    }

    cout << abs(born_year["Elsie"]) << '\n';

    return 0;
}
