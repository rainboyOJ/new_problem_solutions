import sys
from cyaron import IO, randint, Vector

def generate():
    io = IO(input_file=sys.stdout, disable_output=True)

    # 暴力能承受的规模：(m+1)^n 约 6^5 = 7776
    n = randint(1, 5)
    m = randint(0, 4)
    k = randint(1, n)

    io.input_writeln(f"{n} {m} {k}")

    v = Vector.random(m + 1, [1, 20])
    io.input_writeln(v)

if __name__ == "__main__":
    generate()
