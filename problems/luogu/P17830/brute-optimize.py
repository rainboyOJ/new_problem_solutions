import sys


# 桌面（栈底 = 桌面最左端，栈顶 = 桌面最右端）
class Stack(list):
    push = list.append
    empty = lambda self: not self
    size = lambda self: len(self)

# 全局变量：少写字，函数里只读/只改内容就不用写 global
n = m = 0
a = []          # 点数序列，0-based
nxt = []        # nxt[i]：从 i 开始这一局的下一站，-1 表示没有下一站
ans = []        # ans[v]：点数 v 在所有局结束时留在桌面上的次数
st = Stack()


# 从 i 开始一局，沿跳跃链走到底，把这一局留下的点数压栈
# 只读 nxt / a，原地改 st，所以不用 global
def calc(i):
    while i != -1:
        st.push(a[i])       # 这一局最左端就是 a[i]，它会一直留下
        i = nxt[i]          # i+1 .. nxt[i]-1 整段被收走，直接从 nxt[i] 继续


def solve():
    global n, m, a, nxt, ans, data

    data = iter(map(int, sys.stdin.buffer.read().split()))
    n, m = next(data), next(data)
    a = [next(data) for _ in range(n)]

    # last[v]：点数 v 在序列中最后一次出现的位置
    last = [0] * (m + 1)
    for i, v in enumerate(a):
        last[v] = i

    nxt = [-1] * n
    for i, v in enumerate(a):
        j = last[v] + 1                     # 下一局开始的位置
        nxt[i] = j if j < n else -1         # -1 表示没有下一站

    ans = [0] * (m + 1)
    for i in range(n):                      # 第 i 局：从 a[i] 开始
        st.clear()                          # 清空桌面
        calc(i)
        for v in st:                        # 栈里就是本局结束时桌上的点数
            ans[v] += 1

    print(*ans[1:])                         # 点数从 1 开始输出


if __name__ == "__main__":
    solve()
