# gen.py：生成随机小数据用于对拍。
import random, sys

def main():
    random.seed(int(sys.argv[1]) if len(sys.argv) > 1 else 0)
    n = random.randint(1, 4)
    k = random.randint(0, n * n)
    print(n, k)

if __name__ == "__main__":
    main()
