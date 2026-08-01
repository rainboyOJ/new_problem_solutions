/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-07-31 16:22
 */
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353LL;

long long limit_n;
vector<int> primes;
vector<int> small_id;
vector<int> large_id;
vector<long long> quotient_values;
vector<vector<long long>> prime_sieve_sum;
vector<array<long long, 6>> prime_prefix;
vector<vector<array<long long, 6>>> local_values;
unordered_map<unsigned long long, array<long long, 6>> memo;

long long normalize(long long value) {
    value %= MOD;
    if (value < 0) value += MOD;
    return value;
}

int quotient_id(long long value) {
    if (value <= (long long)small_id.size() - 1) return small_id[value];
    return large_id[limit_n / value];
}

array<long long, 6> prime_sum(long long value) {
    array<long long, 6> result{};
    if (value < 2) return result;
    int id = quotient_id(value);
    long long p0 = prime_sieve_sum[0][id];
    long long p1 = prime_sieve_sum[1][id];
    long long p2 = prime_sieve_sum[2][id];
    long long p3 = prime_sieve_sum[3][id];
    result[0] = normalize(p3 + 2 * p2 + 3 * p1 + 2 * p0);
    result[1] = normalize(p2 + p1 + p0);
    result[2] = normalize(p3 + p1);
    result[3] = normalize(3 * p1);
    result[4] = p1;
    result[5] = p1;
    return result;
}

array<long long, 6> solve_sum(long long value, int first_prime) {
    array<long long, 6> zero{};
    if (value < 2) return zero;
    if (first_prime >= (int)primes.size()) {
        array<long long, 6> answer = prime_sum(value);
        int count = upper_bound(primes.begin(), primes.end(), (int)value) -
            primes.begin();
        for (int type = 0; type < 6; type++) {
            answer[type] = normalize(answer[type] -
                prime_prefix[count][type]);
        }
        return answer;
    }
    if (primes[first_prime] > value) return zero;

    unsigned long long key =
        (unsigned long long)value * (primes.size() + 1ULL) + first_prime;
    unordered_map<unsigned long long, array<long long, 6>>::iterator found =
        memo.find(key);
    if (found != memo.end()) return found->second;

    array<long long, 6> answer = prime_sum(value);
    int count = upper_bound(primes.begin(), primes.end(), (int)value) -
        primes.begin();
    int prefix_count = min(first_prime, count);
    for (int i = 0; i < 6; i++) {
        answer[i] = normalize(answer[i] - prime_prefix[prefix_count][i]);
    }

    for (int prime_index = first_prime;
         prime_index < (int)primes.size() &&
         (long long)primes[prime_index] <= value / primes[prime_index];
         prime_index++) {
        array<long long, 6> child = solve_sum(value / primes[prime_index],
            prime_index + 1);
        for (int type = 0; type < 6; type++) {
            answer[type] = normalize(answer[type] +
                local_values[prime_index][0][type] * child[type]);
        }

        long long power = (long long)primes[prime_index] * primes[prime_index];
        int exponent = 1;
        while (power <= value) {
            child = solve_sum(value / power, prime_index + 1);
            for (int type = 0; type < 6; type++) {
                answer[type] = normalize(answer[type] +
                    local_values[prime_index][exponent][type] *
                    normalize(child[type] + 1));
            }
            exponent++;
            if (power > value / primes[prime_index]) break;
            power *= primes[prime_index];
        }
    }
    memo[key] = answer;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int operation;
    cin >> operation >> limit_n;
    int root = (int)sqrt((long double)limit_n);
    while ((long long)(root + 1) * (root + 1) <= limit_n) root++;
    while ((long long)root * root > limit_n) root--;

    vector<bool> composite(root + 1, false);
    for (int i = 2; i <= root; i++) {
        if (composite[i]) continue;
        primes.push_back(i);
        if ((long long)i * i <= root) {
            for (int j = i * i; j <= root; j += i) composite[j] = true;
        }
    }

    quotient_values.reserve(2 * root + 5);
    for (int i = 1; i <= root; i++) {
        quotient_values.push_back(i);
        quotient_values.push_back(limit_n / i);
    }
    sort(quotient_values.begin(), quotient_values.end());
    quotient_values.erase(unique(quotient_values.begin(), quotient_values.end()),
        quotient_values.end());
    small_id.assign(root + 1, -1);
    large_id.assign(root + 1, -1);
    for (int i = 0; i < (int)quotient_values.size(); i++) {
        long long value = quotient_values[i];
        if (value <= root) small_id[value] = i;
        else large_id[limit_n / value] = i;
    }

    prime_sieve_sum.assign(4,
        vector<long long>(quotient_values.size(), 0));
    long long inv2 = 499122177LL;
    long long inv3 = 332748118LL;
    for (int i = 0; i < (int)quotient_values.size(); i++) {
        long long value = quotient_values[i] % MOD;
        long long sum1 = value * ((quotient_values[i] + 1) % MOD) % MOD * inv2 % MOD;
        long long sum2 = sum1 * ((2 * value + 1) % MOD) % MOD * inv3 % MOD;
        long long sum3 = sum1 * sum1 % MOD;
        prime_sieve_sum[0][i] = normalize(quotient_values[i] - 1);
        prime_sieve_sum[1][i] = normalize(sum1 - 1);
        prime_sieve_sum[2][i] = normalize(sum2 - 1);
        prime_sieve_sum[3][i] = normalize(sum3 - 1);
    }

    long long before[4] = {0, 0, 0, 0};
    for (int pi = 0; pi < (int)primes.size(); pi++) {
        int p = primes[pi];
        if ((long long)p * p > limit_n) break;
        for (int i = (int)quotient_values.size() - 1; i >= 0; i--) {
            long long value = quotient_values[i];
            if (value < (long long)p * p) continue;
            int other = quotient_id(value / p);
            long long powers[4] = {1, p % MOD,
                1LL * p * p % MOD, 1LL * p * p % MOD * p % MOD};
            for (int type = 0; type < 4; type++) {
                long long delta = normalize(prime_sieve_sum[type][other] - before[type]);
                prime_sieve_sum[type][i] = normalize(
                    prime_sieve_sum[type][i] - powers[type] * delta);
            }
        }
        long long powers[4] = {1, p % MOD,
            1LL * p * p % MOD, 1LL * p * p % MOD * p % MOD};
        for (int type = 0; type < 4; type++) {
            before[type] = normalize(before[type] + powers[type]);
        }
    }

    prime_prefix.resize(primes.size() + 1);
    prime_prefix[0].fill(0);
    local_values.resize(primes.size());
    for (int pi = 0; pi < (int)primes.size(); pi++) {
        int p = primes[pi];
        long long power = 1;
        int max_exponent = 0;
        while (power <= limit_n / p) {
            power *= p;
            max_exponent++;
        }
        local_values[pi].resize(max_exponent);
        for (int exponent = 1; exponent <= max_exponent; exponent++) {
            int max_power = 3 * exponent;
            vector<long long> powers(max_power + 1, 1);
            for (int i = 1; i <= max_power; i++) {
                powers[i] = powers[i - 1] * (p % MOD) % MOD;
            }
            array<long long, 6> local{};
            for (int x = -exponent; x <= exponent; x++) {
                for (int y = -exponent; y <= exponent; y++) {
                    if (x + y <= exponent) {
                        local[0] = normalize(local[0] + powers[exponent - x - y]);
                    }
                }
            }
            for (int y = -exponent; y <= exponent; y++) {
                local[1] = normalize(local[1] + powers[exponent - y]);
            }
            for (int x = -exponent; x <= exponent; x++) {
                if (2 * x <= exponent) {
                    local[2] = normalize(local[2] + powers[exponent - 2 * x]);
                }
                local[3] = normalize(local[3] + powers[exponent]);
            }
            for (int x = -exponent; x <= exponent; x++) {
                int y = -2 * x;
                if (y >= -exponent && y <= exponent && x + y <= exponent) {
                    local[4] = normalize(local[4] + powers[exponent - x - y]);
                }
            }
            local[5] = powers[exponent];
            local_values[pi][exponent - 1] = local;
        }
        prime_prefix[pi + 1] = prime_prefix[pi];
        for (int type = 0; type < 6; type++) {
            prime_prefix[pi + 1][type] = normalize(
                prime_prefix[pi + 1][type] + local_values[pi][0][type]);
        }
    }

    memo.reserve(3000000);
    array<long long, 6> result = solve_sum(limit_n, 0);
    for (int type = 0; type < 6; type++) result[type] = normalize(result[type] + 1);
    long long perfect = normalize(result[0] - 2 * result[1] - result[2] -
        result[3] - 2 * result[4] + 5 * result[5]);
    cout << (operation == 0 ? result[0] : perfect) << '\n';
    return 0;
}
