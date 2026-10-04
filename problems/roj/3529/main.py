import sys

def main() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    m, n, k = next(data), next(data), next(data)
    # 收集所有长花生的植株 (花生数, 行, 列)，按花生数从大到小排序
    nuts = sorted(
        [(p, i, j) for i in range(m) for j in range(n) if (p := next(data)) > 0],
        key=lambda x: -x[0],
    )
    t = ans = 0  # t: 已用时间；ans: 已采到的花生总数
    r = c = -1  # 当前位置（-1 表示还在路边）
    for p, nr, nc in nuts:
        # 从路边/上一棵植株移动到 (nr,nc) 再采摘：第一段路要 nr+1 步，其余走曼哈顿距离
        t += (nr + 1 if r < 0 else abs(nr - r) + abs(nc - c)) + 1
        if t + nr + 1 > k:  # 采完后还要 nr+1 步跳回路边，回不去就不采（后面的花生更少，直接停）
            break
        ans += p
        r, c = nr, nc
    print(ans)

main()
