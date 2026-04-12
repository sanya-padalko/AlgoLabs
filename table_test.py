import random

def generate_test(filename, size, p_insert=0.33, p_search=0.33):
	arr = [0 for i in range(size)]
	with open('tests/tests_int.txt', 'r') as f:
		i = 0
		for line in f:
			arr[i] = int(line)
			i += 1

	i = 0
	with open(filename, 'w') as f:
		for i in range(size):
			r = random.random()
			key = arr[i]
			i += 1

			if r < p_insert:
				op = 'i'
			elif r < p_insert + p_search:
				op = 's'
			else:
				op = 'r'
		
			f.write(f"{op} {key}\n")

generate_test('table_tests/test1', int(1e6))
generate_test('table_tests/test2', int(1e6), 0.5, 0.25)
