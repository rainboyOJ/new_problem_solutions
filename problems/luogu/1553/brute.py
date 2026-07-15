def rev_int(text):
    return str(int(text[::-1])) if text else "0"


def rev_decimal(text):
    value = text[::-1].rstrip("0")
    return value if value else "0"


s = input().strip()

if "." in s:
    left, right = s.split(".")
    print(f"{rev_int(left)}.{rev_decimal(right)}")
elif "/" in s:
    left, right = s.split("/")
    print(f"{rev_int(left)}/{rev_int(right)}")
elif s.endswith("%"):
    print(rev_int(s[:-1]) + "%")
else:
    print(rev_int(s))
