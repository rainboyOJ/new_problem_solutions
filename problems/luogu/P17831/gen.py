import sys
from cyaron import IO, Vector, randint

def main():
    io = IO(input_file=sys.stdout, disable_output=True)
    # 随机生成不同规模的数据
    # 测试模式可以通过环境变量或者命令行参数指定，默认生成中等随机规模
    scale = 0
    if len(sys.argv) > 1:
        scale = int(sys.argv[1])
    
    if scale == 1:
        # 小规模指数级 n <= 10
        n = randint(1, 10)
        m = randint(0, 50)
        vals = [randint(-20, 20) for _ in range(n)]
    elif scale == 2:
        # 中规模 n <= 2000
        n = randint(1, 2000)
        m = randint(0, 10**9)
        vals = [randint(-10**5, 10**5) for _ in range(n)]
    elif scale == 3:
        # 大规模极限数据 n = 500000
        n = 500000
        m = randint(0, 10**18)
        vals = [randint(-10**12, 10**12) for _ in range(n)]
    elif scale == 4:
        # 特殊性质 A: a_i = i
        n = 500000
        m = randint(0, 10**18)
        vals = list(range(1, n + 1))
    elif scale == 5:
        # 特殊性质 B: 等差数列
        n = 500000
        m = randint(0, 10**18)
        start = randint(-10**6, 10**6)
        step = randint(1, 1000)
        vals = [start + i * step for i in range(n)]
    else:
        # 默认对拍规模 (针对 brute.cpp，n <= 12)
        n = randint(1, 12)
        m = randint(0, 100)
        vals = [randint(-20, 20) for _ in range(n)]

    io.input_writeln(n, m)
    io.input_writeln(vals)

if __name__ == '__main__':
    main()
