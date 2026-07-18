def rev_int(text: str) -> str:
    return text[::-1].lstrip("0") or "0"


def rev_dec(text: str) -> str:
    return text[::-1].rstrip("0") or "0"


s = input().strip()
match s:
    case _ if "." in s:
        left, right = s.split(".")
        print(f"{rev_int(left)}.{rev_dec(right)}")
    case _ if "/" in s:
        left, right = s.split("/")
        print(f"{rev_int(left)}/{rev_int(right)}")
    case _ if s.endswith("%"):
        print(f"{rev_int(s[:-1])}%")
    case _:
        print(rev_int(s))
