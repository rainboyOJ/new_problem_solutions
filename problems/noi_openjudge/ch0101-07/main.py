def format_exponent(text):
    """把 Python 的 e+01 形式改成题目样例要求的 e+001。"""
    if "e" not in text:
        return text
    mantissa, exponent = text.split("e")
    return f"{mantissa}e{exponent[0]}{int(exponent[1:]):03d}"


value = float(input())
print(f"{value:.6f}")
print(f"{value:.5f}")
print(format_exponent(f"{value:.6e}"))
print(format_exponent(f"{value:.6g}"))
