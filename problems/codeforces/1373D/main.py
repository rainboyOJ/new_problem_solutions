"""
1. 设定反转的区间为从 [i,j]
2. 那么这个区间的长度一定是偶数长度 否则翻转完之后 奇数位还是奇数位 偶数位还是偶数位
3 4 5
5 4 3


2 3 4 5
5 4 3 2


固定结尾 J 那么我们能得到的最大反转区间是什么呢？

tot +Odd(i,j) - Eeven(i,j)  

所以这里我们要找到一个最大的 i ,是的 Odd(i,j) - Eeven(i,j) 最大

Odd(i,j) = prefix_odd[j] - prefix_odd[i-1]
Eeven(i,j) = prefix_even[j] - prefix_even[i-1]


我又简单地思考了一下

发现无论是以偶数的 J 是以奇数的 J  结尾
翻转完之后 总是把偶数的位置减去 奇数的位置增加
"""

import sys
from functools import reduce
from itertools import accumulate

a = []

# 得到区间最大和
def dp(a:list[int]):
    if len(a) == 0:
        return 0
    f = accumulate(a,lambda x,y :max(x+y,y))
    return max(list(f))

def solve(data):
    global a
    T = next(data)
    while T > 0:
        T-=1
        n = next(data)

        a = [next(data) for _ in range(n)]
        # 所有偶数位置的和
        tot = sum(a[0::2])

        c = [ a[i] if i & 1  else -a[i] for i in range(n)]

        # end pos is Even
        t = [c[i]  + c[i-1] for i in range(2,n,2)]
        g1 = dp(t)


        # end pos is Odd
        t= [c[i]  + c[i-1] for i in range(1,n,2)]
        g2 = dp(t)
        ans = tot + max(0,g1,g2)

        
        print(ans)

    


if __name__ == "__main__":
    data = iter(map(int, sys.stdin.buffer.read().split()))
    solve(data)
