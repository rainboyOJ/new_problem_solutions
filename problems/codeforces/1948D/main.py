"""
很容易想到 n^3 的算法


采用思维转化:

问题: f[i] 表示第i个元素为结尾的时候, 定长为q, (i前面的每个元素j 都和j+q想等的)连续的最大长度是多少

f[i] = f[i - 1] + 1 if a[i] == a[i - q]
f[i] = 0 if a[i] != a[i - q]

然后发现一重要的数学性质: 

    if f[i] == q: 

  [i-q+1] [] [i] q=3

  则 i-q+1 对应  i-q+1+q = i+1

    则正好从i-q+1 -> i+q 是一个 Tandem Repeats

当定长为q的时候

f[i] = 
"""

import sys

def check(s:str,q):
    same = lambda a,b : a == b or b == '?' or a == '?'
    # 转化成new array b 
    b = [ 1 if same(s[i], s[i+q]) else 0  for i in range(0,len(s)-q)]
    # print(b)
    c = [0] * len(b)
    for i in range(len(b)):
        if b[i] == 0:
            c[i] = 0
        else:
            c[i] = c[i-1] + 1
            if c[i] >= q:
                return q
    return 0


def solve(data):


    for s in data:
        # print(s,len(s)//2)
        t =  [check(s,q) for q in range(1,len(s)//2+1)]
        # print(t)
        ans = max(t)
        print(ans*2)



if __name__ == "__main__":
    n,*data = sys.stdin.buffer.read().decode().split()
    solve(data)
