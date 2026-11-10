import sys
from cyaron import IO, randint

def generate():
    io = IO(input_file=sys.stdout, disable_output=True)

    n = randint(3, 30)
    io.input_writeln(n)

    # 每个点 i 的出边 T_i 满足 T_i != i
    to = []
    for i in range(1, n + 1):
        target = randint(1, n)
        while target == i:
            target = randint(1, n)
        to.append(target)

    io.input_writeln(" ".join(map(str, to)))

if __name__ == "__main__":
    generate()
