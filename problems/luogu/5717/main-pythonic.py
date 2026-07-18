a, b, c = sorted(map(int, input().split()))

match True:
    case _ if a + b <= c:
        print("Not triangle", end="")
    case _:
        left = a * a + b * b
        right = c * c
        result = []

        match True:
            case _ if left == right:
                result.append("Right triangle")
            case _ if left > right:
                result.append("Acute triangle")
            case _:
                result.append("Obtuse triangle")

        match (a == b or b == c, a == c):
            case (True, True):
                result.append("Isosceles triangle")
                result.append("Equilateral triangle")
            case (True, False):
                result.append("Isosceles triangle")
            case _:
                pass

        print("\n".join(result), end="")
