# gen.py：生成随机小数据用于对拍。
import random, sys

def gen(n, m):
    ops = []
    for i in range(2, n + 1):
        k = random.randint(1, i - 1)
        p = random.randint(0, 1)
        ops.append((k, p))
    dels = []
    if m > 0:
        dels = random.sample(range(1, n + 1), min(m, n))
    return n, ops, dels

def main():
    random.seed(int(sys.argv[1]) if len(sys.argv) > 1 else 0)
    n = random.randint(3, 15)
    m = random.randint(0, min(5, n))
    n, ops, dels = gen(n, m)

    print(n)
    for k, p in ops:
        print(k, p)
    print(m)
    for x in dels:
        print(x)

if __name__ == "__main__":
    main()
