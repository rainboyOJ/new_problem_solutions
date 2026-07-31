/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 23:29
 */
#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int ROOT = 3;

int ntt_limit;
int ntt_log;
vector<int> ntt_root;
vector<int> ntt_reverse;
int reduction_ntt_size;
vector<int> characteristic_transform;
vector<int> inverse_reversed_transform;

int power_mod(long long base, int exponent) {
    long long result = 1;
    while (exponent > 0) {
        if (exponent & 1) result = result * base % MOD;
        base = base * base % MOD;
        exponent >>= 1;
    }
    return (int)result;
}

void prepare_ntt(int minimum_limit) {
    ntt_limit = 1;
    ntt_log = 0;
    while (ntt_limit < minimum_limit) {
        ntt_limit <<= 1;
        ntt_log++;
    }

    ntt_root.assign(ntt_limit, 1);
    int primitive = power_mod(ROOT, (MOD - 1) / ntt_limit);
    for (int i = 1; i < ntt_limit; i++) {
        ntt_root[i] = (int)(ntt_root[i - 1] * 1LL * primitive % MOD);
    }

    ntt_reverse.assign(ntt_limit, 0);
    for (int i = 1; i < ntt_limit; i++) {
        ntt_reverse[i] = (ntt_reverse[i >> 1] >> 1) | ((i & 1) << (ntt_log - 1));
    }
}

void ntt(vector<int> &value, bool inverse) {
    int n = (int)value.size();
    int current_log = __builtin_ctz((unsigned int)n);
    int reverse_shift = ntt_log - current_log;
    for (int i = 1; i < n; i++) {
        int j = ntt_reverse[i] >> reverse_shift;
        if (i < j) swap(value[i], value[j]);
    }
    for (int half = 1; half < n; half <<= 1) {
        int step = ntt_limit / (half << 1);
        for (int start = 0; start < n; start += half << 1) {
            for (int i = 0; i < half; i++) {
                int left = value[start + i];
                int root_index = i * step;
                if (inverse && root_index != 0) root_index = ntt_limit - root_index;
                int right = (int)(value[start + i + half] * 1LL * ntt_root[root_index] % MOD);
                value[start + i] = left + right < MOD ? left + right : left + right - MOD;
                value[start + i + half] = left - right < 0 ? left - right + MOD : left - right;
            }
        }
    }
    if (inverse) {
        int inv_n = power_mod(n, MOD - 2);
        for (int i = 0; i < n; i++) value[i] = (int)(value[i] * 1LL * inv_n % MOD);
    }
}

vector<int> multiply(const vector<int> &left, const vector<int> &right) {
    if (left.empty() || right.empty()) return vector<int>();
    if ((int)left.size() * (int)right.size() <= 4096) {
        vector<int> result(left.size() + right.size() - 1, 0);
        for (int i = 0; i < (int)left.size(); i++) {
            for (int j = 0; j < (int)right.size(); j++) {
                result[i + j] = (result[i + j] + left[i] * 1LL * right[j]) % MOD;
            }
        }
        return result;
    }
    int size = 1;
    int need = (int)left.size() + (int)right.size() - 1;
    while (size < need) size <<= 1;
    vector<int> first(left), second(right);
    first.resize(size);
    second.resize(size);
    ntt(first, false);
    ntt(second, false);
    for (int i = 0; i < size; i++) first[i] = (int)(first[i] * 1LL * second[i] % MOD);
    ntt(first, true);
    first.resize(need);
    return first;
}

vector<int> multiply_with_fixed_right(const vector<int> &left, int right_size,
                                      const vector<int> &right_transform) {
    int need = (int)left.size() + right_size - 1;
    // 右侧多项式已经完成 NTT，只需变换左侧并做一次逆变换。
    vector<int> value(left);
    value.resize(reduction_ntt_size);
    ntt(value, false);
    for (int i = 0; i < reduction_ntt_size; i++) {
        value[i] = (int)(value[i] * 1LL * right_transform[i] % MOD);
    }
    ntt(value, true);
    value.resize(need);
    return value;
}

vector<int> polynomial_inverse(const vector<int> &polynomial, int need) {
    vector<int> result(1, power_mod(polynomial[0], MOD - 2));
    while ((int)result.size() < need) {
        int length = min(need, (int)result.size() << 1);
        vector<int> prefix(polynomial.begin(), polynomial.begin() + min((int)polynomial.size(), length));
        int transform_size = 1;
        // 同一频域中还要完成 R * (2 - A * R)，长度需覆盖完整的中间乘积，避免循环卷积串入低位。
        while (transform_size < (int)prefix.size() + 2 * (int)result.size() - 1) transform_size <<= 1;
        vector<int> prefix_transform(prefix);
        vector<int> result_transform(result);
        prefix_transform.resize(transform_size);
        result_transform.resize(transform_size);
        ntt(prefix_transform, false);
        ntt(result_transform, false);
        for (int i = 0; i < transform_size; i++) {
            int product = (int)(prefix_transform[i] * 1LL * result_transform[i] % MOD);
            int correction = 2 - product;
            if (correction < 0) correction += MOD;
            result_transform[i] = (int)(result_transform[i] * 1LL * correction % MOD);
        }
        ntt(result_transform, true);
        result_transform.resize(length);
        result = result_transform;
    }
    return result;
}

vector<int> polynomial_remainder(const vector<int> &value, const vector<int> &characteristic,
                                 const vector<int> &inverse_reversed) {
    int degree = (int)characteristic.size() - 1;
    if ((int)value.size() <= degree) return value;
    int quotient_size = (int)value.size() - degree;
    vector<int> reversed_value(value.rbegin(), value.rend());
    reversed_value.resize(quotient_size);
    vector<int> reversed_quotient;
    if ((int)reversed_value.size() * (int)inverse_reversed.size() <= 4096) {
        reversed_quotient = multiply(reversed_value, inverse_reversed);
    } else {
        reversed_quotient = multiply_with_fixed_right(reversed_value, inverse_reversed.size(),
                                                      inverse_reversed_transform);
    }
    reversed_quotient.resize(quotient_size);
    vector<int> quotient(reversed_quotient.rbegin(), reversed_quotient.rend());
    vector<int> product;
    if ((int)quotient.size() * (int)characteristic.size() <= 4096) {
        product = multiply(quotient, characteristic);
    } else {
        product = multiply_with_fixed_right(quotient, characteristic.size(), characteristic_transform);
    }
    vector<int> result(degree, 0);
    for (int i = 0; i < degree; i++) {
        int subtract = i < (int)product.size() ? product[i] : 0;
        result[i] = value[i] - subtract < 0 ? value[i] - subtract + MOD : value[i] - subtract;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    long long left, right;
    cin >> m >> left >> right;
    vector<int> coefficient(m + 1, 0);
    for (int i = 1; i <= m; i++) cin >> coefficient[i];
    int count = (int)(right - left + 1);
    prepare_ntt(2 * (m + count + 5));

    // C(x)=1-k1*x-...-km*x^m，生成函数为 1/C(x)。
    vector<int> denominator(m + 1, 0);
    denominator[0] = 1;
    for (int i = 1; i <= m; i++) denominator[i] = coefficient[i] == 0 ? 0 : MOD - coefficient[i];

    // P(x)=x^m-k1*x^(m-1)-...-km 是递推的特征多项式。
    vector<int> characteristic(m + 1, 0);
    characteristic[m] = 1;
    for (int i = 0; i < m; i++) {
        characteristic[i] = coefficient[m - i] == 0 ? 0 : MOD - coefficient[m - i];
    }
    vector<int> reversed_characteristic(characteristic.rbegin(), characteristic.rend());
    vector<int> inverse_reversed = polynomial_inverse(reversed_characteristic, m);

    // 约化时反复出现的两个多项式只做一次 NTT。
    reduction_ntt_size = 1;
    while (reduction_ntt_size < 2 * m - 1) reduction_ntt_size <<= 1;
    characteristic_transform = characteristic;
    characteristic_transform.resize(reduction_ntt_size);
    ntt(characteristic_transform, false);
    inverse_reversed_transform = inverse_reversed;
    inverse_reversed_transform.resize(reduction_ntt_size);
    ntt(inverse_reversed_transform, false);

    vector<int> result(m, 0), base(m, 0);
    result[0] = 1;
    if (m == 1) base[0] = coefficient[1];
    else base[1] = 1;
    long long exponent = left;
    while (exponent > 0) {
        if (exponent & 1) {
            result = polynomial_remainder(multiply(result, base), characteristic, inverse_reversed);
        }
        exponent >>= 1;
        if (exponent > 0) {
            base = polynomial_remainder(multiply(base, base), characteristic, inverse_reversed);
        }
    }

    int prefix_length = m + count - 1;
    vector<int> sequence = polynomial_inverse(denominator, prefix_length);
    vector<int> reversed_result(result.rbegin(), result.rend());
    vector<int> convolution = multiply(reversed_result, sequence);
    for (int i = 0; i < count; i++) {
        cout << convolution[m - 1 + i] << '\n';
    }

    return 0;
}
