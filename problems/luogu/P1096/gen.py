import sys
from cyaron import IO, randint

def generate():
    io = IO(input_file=sys.stdout, disable_output=True)

    n = randint(1, 200)
    io.input_writeln(n)

if __name__ == "__main__":
    generate()
