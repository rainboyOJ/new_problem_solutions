import sys

input = sys.stdin.buffer.readline

def solve_case(n,d):
    pw2 = 1
    while d % 2 ==0:
        pw2 *= 2
        d //= 2
    return (n-1) *(pw2-1)

def solve():

    pass


if __name__ == "__main__":
    data = list(map(int, sys.stdin.buffer.read().split()))
    it = iter(data[1:])
    res = []
    for n,a,d in zip(it,it,it):
        res.append(solve_case(n,d))
    print(*res,sep="\n")
