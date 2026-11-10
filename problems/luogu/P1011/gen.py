import sys
from cyaron import IO, randint

# 数据生成器：随机生成合法的 a, n, m, x
# 为保证一定有合法解，我们先随机 a, n, x 和第 2 站上车人数 y，然后通过模拟计算出 m
def generate():
    io = IO(input_file=sys.stdout, disable_output=True)

    a = randint(1, 20)
    n = randint(4, 20)
    x = randint(1, n - 1)
    y = randint(0, 100) # 选取适当范围的 y，使得最终 m <= 20000

    u = [0] * (n + 1)
    s = [0] * (n + 1)

    u[1] = a
    s[1] = a

    u[2] = y
    s[2] = a

    for i in range(3, n):
        u[i] = u[i - 1] + u[i - 2]
        down = u[i - 1]
        s[i] = s[i - 1] + u[i] - down

    m = s[n - 1]
    # 如果 m 超过了 20000，可以通过缩小 y 重试，或者直接输出
    io.input_writeln(f"{a} {n} {m} {x}")

if __name__ == "__main__":
    generate()
