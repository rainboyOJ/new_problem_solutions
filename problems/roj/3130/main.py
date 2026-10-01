import sys

def main():
    data = sys.stdin.buffer.read().split()
    S, W = int(data[0]), int(data[1])
    ptr = 2  # S 保证为 0，无需处理

    # 每个询问 (x1,y1,x2,y2) 拆成 4 个前缀角点询问 f(X,Y)=时间更早的修改中
    # 满足 x<=X 且 y<=Y 的权值和：f(x2,y2)-f(x1-1,y2)-f(x2,y1-1)+f(x1-1,y1-1)。
    # 这样问题变成三维偏序（时间, x, y）：CDQ 分治时间维，x 排序后树状数组维护 y。
    ev = []  # (x, y, w, qid, sgn)；修改 qid=-1，询问角点带 qid 与符号 sgn
    cnt = 0
    while data[ptr] != b'3':
        if data[ptr] == b'1':
            ev.append((int(data[ptr + 1]), int(data[ptr + 2]), int(data[ptr + 3]), -1, 0))
            ptr += 4
        else:
            x1, y1, x2, y2 = (int(v) for v in data[ptr + 1:ptr + 5])
            ev.append((x1 - 1, y1 - 1, 0, cnt, 1))
            ev.append((x2, y2, 0, cnt, 1))
            ev.append((x1 - 1, y2, 0, cnt, -1))
            ev.append((x2, y1 - 1, 0, cnt, -1))
            cnt += 1
            ptr += 5

    m = len(ev)
    ans = [0] * cnt
    tree = [0] * (W + 1)  # 树状数组按下标 y 维护
    stamp = [0] * (W + 1)  # 时间戳清零，免去每层回滚
    cur = 0

    def solve(l, r):
        nonlocal cur
        if r - l <= 1:
            return
        mid = (l + r) >> 1
        solve(l, mid)
        solve(mid, r)
        # 递归保证两半各自按 x 有序；左半修改（时间早）贡献给右半询问
        cur += 1
        i = l
        for j in range(mid, r):
            qx, qy, _, qid, sgn = ev[j]
            if qid == -1:
                continue
            while i < mid and ev[i][0] <= qx:
                ex, ey, ew, eq, _ = ev[i]
                if eq == -1:
                    k = ey
                    while k <= W:
                        if stamp[k] != cur:
                            stamp[k] = cur
                            tree[k] = 0
                        tree[k] += ew
                        k += k & -k
                i += 1
            if sgn:
                s = 0
                k = qy
                while k:
                    if stamp[k] == cur:
                        s += tree[k]
                    k -= k & -k
                ans[qid] += sgn * s
        # 归并两半按 x 有序，维持不变式
        tmp = []
        a, b = l, mid
        while a < mid and b < r:
            if ev[a][0] <= ev[b][0]:
                tmp.append(ev[a]); a += 1
            else:
                tmp.append(ev[b]); b += 1
        tmp.extend(ev[a:mid]); tmp.extend(ev[b:r])
        ev[l:r] = tmp

    solve(0, m)
    sys.stdout.write('\n'.join(map(str, ans)) + '\n')

main()
