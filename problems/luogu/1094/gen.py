# gen.py：生成随机小数据用于对拍。
import random, sys

def main():
    random.seed(int(sys.argv[1]) if len(sys.argv) > 1 else 0)
    w = random.randint(80, 200)
    n = random.randint(3, 15)
    print(w)
    print(n)
    for i in range(n):
        print(random.randint(5, w))

if __name__ == "__main__":
    main()
