
from functools import reduce
from itertools import accumulate

a = [1,2,3,4]

b = reduce(lambda x,y :x +y,a,0)

print(b)

