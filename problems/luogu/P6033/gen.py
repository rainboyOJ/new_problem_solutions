import sys
from cyaron import IO, randint, Vector

def generate():
    io = IO(input_file=sys.stdout, disable_output=True)

    n = randint(2, 20)
    io.input_writeln(n)

    weights = [randint(1, 100) for _ in range(n)]
    io.input_writeln(" ".join(map(str, weights)))

if __name__ == "__main__":
    generate()
