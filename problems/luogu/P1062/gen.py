import sys
from cyaron import IO, randint

def generate():
    io = IO(input_file=sys.stdout, disable_output=True)

    k = randint(3, 15)
    n = randint(1, 1000)

    io.input_writeln(f"{k} {n}")

if __name__ == "__main__":
    generate()
