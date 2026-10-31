import sys
from cyaron import IO, randint

def main():
    io = IO(input_file=sys.stdout, disable_output=True)
    c = 0
    t = randint(2, 5)
    io.input_writeln(c, t)
    for _ in range(t):
        n = randint(3, 15)
        d = randint(1, 20)
        io.input_writeln(n, d)
        # 生成递增序列
        coords = []
        cur = randint(-100, 100)
        coords.append(cur)
        for _ in range(n - 1):
            cur += randint(1, 5)
            coords.append(cur)
        io.input_writeln(coords)

if __name__ == '__main__':
    main()
