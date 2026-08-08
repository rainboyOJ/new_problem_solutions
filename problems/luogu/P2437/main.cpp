/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

int m, n;
char a[300], b[300], c[300];

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
    cin >> m >> n;
    int d = n - m;
    strcpy(a, "1");
    strcpy(b, "1");
    for (int i = 0; i < d; i++) {
        add(c, a, b);
        strcpy(a, b);
        strcpy(b, c);
    }
    cout << a << endl;
    return 0;
}
