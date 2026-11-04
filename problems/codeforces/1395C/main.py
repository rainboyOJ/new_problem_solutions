
"""
发现最多9位置.
不停的同高位到地位去尝试:
    能把这个位变成0吗?

    found the max 9th position.
Keep trying from the high position to the low position:
    can we make this bit 0?
"""
import sys
from itertools import product
from functools import reduce

def test(a,b,attempt,idx):
    # exist
    for ai in a:

        # for bj in b:
        #     t = ai & bj
        #     if not ( t & attempt == t):
        #         return False
        if not any(  (ai & bj) & ~attempt == 0 for bj in b):
            return False
    return True

    bb = product(b,repeat = len(a));
    check = (1<<idx) - 1
    for pick in bb:
        t = [ x &y for x,y in zip(a,pick)]
        res = reduce(lambda x,y : x |y, t,0)
        # if res | check == attempt:
        if res & attempt == res:
            return True
    return False

def sol(a,b):
    ans = (1<<10) - 1

    for i in range(9,-1,-1):
        attempt = ans ^ (1<<i) # set this bit to 0
        if test(a,b,attempt,i):
            ans = attempt

    print(ans)

def solve(data):
    data = iter(data)
    n = next(data)
    m = next(data)
    a = [next(data) for _ in range(n)]
    b = [next(data) for _ in range(m)]
    sol(a,b)



if __name__ == "__main__":
    solve(map(int, sys.stdin.buffer.read().split()))
