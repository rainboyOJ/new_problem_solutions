from itertools import accumulate
import sys


def solve():
    it = iter(map(int, sys.stdin.buffer.read().split()))
    n, d = next(it), next(it)
    v = [next(it) for _ in range(n - 1)]  # 站点 i 到 i+1 的距离
    a = [next(it) for _ in range(n)]      # 各站点油价

    pos = list(accumulate(v,initial=0))
    prefix_min = list(accumulate(a,min))

    print(pos)
    print(prefix_min)

    # 存基点
    lows = [0] + list( filter( lambda i : prefix_min[i] < prefix_min[i-1],range(1,n)))
    print(lows)

    ans = 0
    tank = 0 # 这一段路程 已经走了多少

    for idx,nxt in zip(lows,lows[1:] + [n-1]):
        seg = pos[nxt] - pos[idx]
        lack = seg - tank
        if lack > 0:
            L = (lack + d - 1)//d # how many purchase
            ans += L * a[idx];  # money
            tank = tank + L*d - seg 
        else:
            tank -= seg
    print(ans)






if __name__ == "__main__":
    solve()
