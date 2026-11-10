import sys
from cyaron import IO, randint

def generate():
    io = IO(input_file=sys.stdout, disable_output=True)

    n = 2
    m = randint(5, 20)
    io.input_writeln(f"{n} {m}")

    # 构造有整数根的二次方程 (x - r1)(x - r2) = x^2 - (r1+r2)x + r1*r2
    r1 = randint(1, m)
    r2 = randint(1, m)

    a0 = r1 * r2
    a1 = -(r1 + r2)
    a2 = 1

    io.input_writeln(a0)
    io.input_writeln(a1)
    io.input_writeln(a2)

if __name__ == "__main__":
    generate()
