/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-19 11:59
 * update_at: 2026-07-19 11:59
 */
#include <bits/stdc++.h>
using namespace std;

const int MOD = 666623333;
const int MAX_LENGTH = 1000005;
const int MAX_PRIME = 1000005;

bool composite[MAX_PRIME];
int primes[MAX_PRIME];
int prime_count;
long long remaining[MAX_LENGTH];
long long phi_value[MAX_LENGTH];

void build_primes(int limit) {
    for (int i = 2; i <= limit; i++) {
        if (!composite[i]) primes[prime_count++] = i;
        for (int j = 0; j < prime_count; j++) {
            long long multiple = 1LL * i * primes[j];
            if (multiple > limit) break;
            composite[multiple] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long left, right;
    cin >> left >> right;

    int length = (int)(right - left + 1);
    for (int i = 0; i < length; i++) {
        remaining[i] = left + i;
        phi_value[i] = left + i;
    }

    long long square_root = sqrt((long double)right);
    while ((square_root + 1) * (square_root + 1) <= right) square_root++;
    while (square_root * square_root > right) square_root--;
    build_primes((int)square_root);

    for (int i = 0; i < prime_count; i++) {
        long long prime = primes[i];
        long long first = (left + prime - 1) / prime * prime;

        for (long long multiple = first; multiple <= right; multiple += prime) {
            int index = (int)(multiple - left);
            phi_value[index] = phi_value[index] / prime * (prime - 1);
            while (remaining[index] % prime == 0) {
                remaining[index] /= prime;
            }
        }
    }

    long long answer = 0;
    for (int i = 0; i < length; i++) {
        if (remaining[i] > 1) {
            long long prime = remaining[i];
            phi_value[i] = phi_value[i] / prime * (prime - 1);
        }

        long long value = left + i;
        answer += (value - phi_value[i]) % MOD;
        if (answer >= MOD) answer -= MOD;
    }

    cout << answer << '\n';
    return 0;
}
