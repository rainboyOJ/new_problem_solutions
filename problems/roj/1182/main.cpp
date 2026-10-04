/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:33
 * update_at: 2026-10-05 04:33
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 45;

ll n;
double male[MAXN];   // 男桶：身高，下标从 1 开始
double female[MAXN]; // 女桶：身高，下标从 1 开始
ll male_cnt;
ll female_cnt;

// 简单冒泡：数组 a[1..len] 升序排序，身高互不相同保证稳定。
void sort_male(double a[], ll len) {
    for (ll i = 1; i <= len; i++) {
        for (ll j = 1; j <= len - i; j++) {
            if (a[j] > a[j + 1]) {
                double t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}

// 简单冒泡：数组 a[1..len] 降序排序，身高互不相同保证稳定。
void sort_female(double a[], ll len) {
    for (ll i = 1; i <= len; i++) {
        for (ll j = 1; j <= len - i; j++) {
            if (a[j] < a[j + 1]) {
                double t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    male_cnt = 0;
    female_cnt = 0;
    for (ll i = 0; i < n; i++) {
        string sex;
        double h;
        cin >> sex >> h;
        if (sex == "male") {
            male_cnt++;
            male[male_cnt] = h;
        }
        else {
            female_cnt++;
            female[female_cnt] = h;
        }
    }

    sort_male(male, male_cnt);
    sort_female(female, female_cnt);

    // 男段在前、女段在后，每个数保留两位小数，单空格分隔。
    for (ll i = 1; i <= male_cnt; i++) {
        if (i > 1) cout << ' ';
        cout << fixed << setprecision(2) << male[i];
    }
    for (ll i = 1; i <= female_cnt; i++) {
        if (male_cnt > 0 || i > 1) cout << ' ';
        cout << fixed << setprecision(2) << female[i];
    }
    cout << '\n';

    return 0;
}