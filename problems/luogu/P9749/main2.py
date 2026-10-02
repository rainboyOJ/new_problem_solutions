import sys
from itertools import accumulate


def main():
    # 输入用迭代器顺序读：一个 next() 取一个数，不用自己记下标
    it = iter(map(int, sys.stdin.buffer.read().split()))
    n, d = next(it), next(it)
    v = [next(it) for _ in range(n - 1)]  # 站点 i 到 i+1 的距离
    a = [next(it) for _ in range(n)]      # 各站点油价

    # 到各站的累计公里数（前缀和，pos[0] = 0）与前缀最低价（单调不增）
    pos = list(accumulate(v, initial=0))
    prefix_min = list(accumulate(a, min))  # prefix_min[i] = min(a[:i+1])

    # 找“新低”站点（0 基下标）：前缀最低价刷新的位置。
    # 这里必须用 filter 而不是 takewhile——谓词失败后 filter 还会继续看后面的元素，
    # 价格回升（非新低）不影响，后面再创新低仍然记进来；这是子序列，不是连续下降段。
    lows = [0] + list(filter(
        lambda i: prefix_min[i] < prefix_min[i - 1], range(1, n)
    ))

    # 贪心：只在这几个新低站点加油——比它们贵的站，油都能用更低价买在前面。
    # 每段的终点是下一个新低站（最后一段是终点站），途中没有更便宜的站，
    # 所以缺口必须在本段起点用它的价格买够；整升向上取整，多出的油带进后面。
    ans = 0
    tank = 0                      # 油箱已有油还能跑多少公里
    for idx, nxt in zip(lows, lows[1:] + [n - 1]):
        seg = pos[nxt] - pos[idx]  # 本段要走的公里数
        lack = seg - tank
        if lack > 0:
            liter = (lack + d - 1) // d   # 只能整升买，向上取整
            ans += liter * a[idx]
            tank += liter * d - seg       # 剩余油量结转下一段
        else:
            tank -= seg                   # 现有油够用，一分钱不花

    print(ans)


if __name__ == "__main__":
    main()
