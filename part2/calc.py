import matplotlib.pyplot as plt

def calc_results():
	input_dir	= 'results/'
	output_plot	= 'results/performance_plot.svg'
	filenames	= ['insert', 'delete', 'sort_insert', 'sort_delete']
	
	plt.figure(figsize=(10, 6))
	
	for name in filenames:
		path = input_dir + name + '.csv'
		numbers = []
		with open(path, 'r') as f:
			content = f.read().replace(',', '.')
			words = content.replace('\n', ' ').split()
			for word in words:
				numbers.append(float(word))
		
		plt.plot(range(1, 11), numbers, marker='o', label=name)
		

	plt.title('Производительность AVL-дерева')
	plt.xlabel('Номер замера (прогон)')
	plt.ylabel('Время (мс)')
	plt.legend()
	plt.grid(True)
	plt.savefig(output_plot)
	
	print(f"График сохранен в {output_plot}")

calc_results()