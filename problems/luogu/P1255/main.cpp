/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

int n;
char a[2000], b[2000], c[2000];

void add(char *res, char *x, char *y) {
    int lenx = strlen(x), leny = strlen(y);
    int carry = 0, k = 0, i = lenx - 1, j = leny - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += x[i--] - '0';
        if (j >= 0) sum += y[j--] - '0';
        carry = sum / 10;
        res[k++] = sum % 10 + '0';
    }
    res[k] = '\0';
    reverse(res, res + k);
}

int main() {
    cin >> n;
    if (n == 1) { cout << 1 << endl; return 0; }
    if (n == 2) { cout << 2 << endl; return 0; }
    strcpy(a, "1");
    strcpy(b, "2");
    for (int i = 3; i <= n; i++) {
        add(c, a, b);
        strcpy(a, b);
        strcpy(b, c);
    }
    cout << b << endl;
    return 0;
}
