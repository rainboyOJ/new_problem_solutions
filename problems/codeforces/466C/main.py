from collections import defaultdict
import sys
from itertools import accumulate


def solve():
    n,*data = map(int, sys.stdin.buffer.read().split())

    # pre sum
    p = list(accumulate(data))
    # print(list(p))

    # 桶
    d = defaultdict(int)
    ans = 0
    for i in range(n-2,-1,-1):
        val = p[i]
        if 3*val == p[n-1]:
            ans += d[2*val]
        d[val] += 1
    print(ans)

    


if __name__ == "__main__":
    solve()
