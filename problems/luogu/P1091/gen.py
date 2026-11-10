import sys
from cyaron import IO, randint, Vector

def generate():
    io = IO(input_file=sys.stdout, disable_output=True)

    n = randint(2, 20)
    io.input_writeln(n)

    # 身高在 130 到 230 之间
    heights = Vector.random(n, [130, 230])
    io.input_writeln(heights)

if __name__ == "__main__":
    generate()
