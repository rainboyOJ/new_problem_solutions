import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 生成少于 10 个操作符的合法括号表达式
ops = ["+", "*"]

def gen_expr(depth=0):
    if depth >= 2 or randint(0, 2) == 0:
        return "" # 单个横线
    op = ops[randint(0, 1)]
    left = gen_expr(depth + 1)
    right = gen_expr(depth + 1)
    
    use_bracket_l = "(" + left + ")" if left != "" and randint(0, 1) == 0 else left
    use_bracket_r = "(" + right + ")" if right != "" and randint(0, 1) == 0 else right
    return use_bracket_l + op + use_bracket_r

expr = gen_expr()
if not expr:
    expr = "+"

io.input_writeln(len(expr))
io.input_writeln(expr)
