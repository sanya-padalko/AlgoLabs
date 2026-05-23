import sys
from random import randint

size = int(sys.argv[1])
max_value = int(sys.argv[2])
print(*[randint(0, max_value) for i in range(size)])