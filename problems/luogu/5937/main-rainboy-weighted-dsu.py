# 带权dsu-by-rainboy
input = sys.stdin.buffer.readline

n = int(input()) # 长度
m =  int(input()) # 数据量

# ----------- dsu ---------
parent = {}
size = {}
parity = {}


def init(x):
    """ 初始化 """
    if x not in parent:
        parent[x] = x
        size[x] = 1
        parity[x] = 0

def find(x):
    """ 查找 并路径压缩 ,并更新 parity """
    if parent[x] != x:
        old_parent = parent [x]
        parent[x] = find(old_parent)
        parity[x] ^= parity[old_parent]
    return parent[x]

def unite(x,y,expected):
    rootx = find(x)
    rooty = find(y)

    if rootx == rooty: # 在同一个集合
        return (parity[x] ^ parity[y] ^ expected) ==0
        # 相同 ^ expected 会得到0

    # 不在同一个集合,需要合并
    if size[rootx] < size[rooty]:
        rootx ,rooty = rooty,rootx
    # 报纸rootx 是大的

    parent[rooty] = rootx # 合并
    size[rootx] += size[rooty]

    parity[rooty] = (parity[x] ^ parity[y] ^ expected)
    return True # 成功,不会冲突

# ----------- dsu end ---------


def solve():
    pass


if __name__ == "__main__":
    # 读取数据
    ans = m
    for i in range(m):
        left ,right , word = map(int,input().split())
        left -= 1
        init(left)
        init(right)
        if ans == m and not unite(left,right,word == b'odd'):
            ans = i
            break
    print(ans)
