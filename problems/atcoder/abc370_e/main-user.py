from collections import defaultdict
from itertools import accumulate
import sys
MOD = 998244353



def solve():
    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, k = next(data), next(data)
    a = [ next(data) for _ in range(n) ]

    # bucket : save pre sum
    bucket = defaultdict(int)
    bucket[0] = 1

    pre = list(accumulate(a))
    # f[i] represent: count of legal divide with end pos i
    f = [0] * n
    f[0] = 1
    # presum of f[i]
    tot = 1

    for i in range(n):
        f[i] = (tot - bucket[pre[i] - k]) % MOD
        tot = (tot + f[i])  % MOD
        bucket[pre[i]] += f[i];
        bucket[pre[i]] %= MOD;

    print((f[-1] + MOD) % MOD)


if __name__ == "__main__":
    solve()
