import random

random.seed(42)

def test_int_gen(filename, cnt = 1000000):
    with open(filename, 'w') as f:
        for i in range(cnt):
            f.write(f"{random.randint(0, 4294967295)}\n")

def test_float_gen(filename, cnt = 1000000):
    with open(filename, 'w') as f:
        for i in range(cnt):
            f.write(f"{random.uniform(-10, 10):.6f}\n")

def test_string_gen(filename, cnt = 1000000):
    with open(filename, 'w') as f:
        for i in range(cnt):
            len = random.randint(5, 20)
            alp_str = [chr(ord('a') + random.randint(0, 25)) for j in range(len)]
            res_str = ''.join(alp_str)
            f.write(f"{res_str}\n")

print("Test generating...")
test_int_gen("tests_int.txt")
print("Tests for int generated...")
test_float_gen("tests_float.txt")
print("Tests for float generated...")
test_string_gen("tests_string.txt")
print("Tests for strings generated...")
print("Done, tests created :)")