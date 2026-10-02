"""借教室（NOIP2012 提高组）：二分第一个无法满足的订单 + 差分数组 O((n+m)log m) 判定。"""
import sys

def main() -> None:
    data = sys.stdin.buffer.read().split()
    it = iter(map(int, data))
    n, m = next(it), next(it)
    r = [next(it) for _ in range(n)]  # 每天可租教室数
    d = [0] * m  # 订单 j 需要的教室数
    s = [0] * m  # 订单 j 的起始天
    t = [0] * m  # 订单 j 的结束天
    for j in range(m):
        d[j], s[j], t[j] = next(it), next(it), next(it)

    def ok(k: int) -> bool:
        """前 k 份订单是否都能满足：差分累计每天总需求，与 r 比较。"""
        diff = [0] * (n + 1)
        for j in range(k):
            diff[s[j] - 1] += d[j]
            diff[t[j]] -= d[j]
        cur = 0  # 当前天被占用的教室总数（前缀和）
        for i in range(n):
            cur += diff[i]
            if cur > r[i]:
                return False
        return True

    lo, hi = 0, m  # ok(lo)=True（空集必满足），ok(hi)=False 之外即答案位置
    # 二分最大的 k 使前 k 份订单全部满足；答案为 k+1，全部满足输出 0
    while lo < hi:
        mid = (lo + hi + 1) // 2
        if ok(mid):
            lo = mid
        else:
            hi = mid - 1
    print(0 if lo == m else -1)
    if lo != m:
        print(lo + 1)

if __name__ == "__main__":
    main()
