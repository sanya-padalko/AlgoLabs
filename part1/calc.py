import csv

def calc_results():
    filenames = ['insert.csv', 'delete.csv', 'insert_sort.csv', 'delete_sort.csv']
    output_file = 'results/_final_results.txt'
    
    with open(output_file, 'w') as out:
        out.write(f"{'Файл':<20} | {'Среднее (5 прогонов)':<20}\n")
        out.write("-" * 45 + "\n")
        
        for name in filenames:
            path = "results/" + name
            numbers = []
            
            with open(path, 'r') as f:
                content = f.read().replace(',', '.')
                words = content.replace('\n', ' ').split()
                
                for word in words:
                    numbers.append(float(word))
                    if len(numbers) == 5:
                        break
            
            if len(numbers) == 5:
                avg = sum(numbers) / 5
                out.write(f"{name:<20} | {avg:<20.6f}\n")
            else:
                out.write(f"{name:<20} | Ошибка: мало данных ({len(numbers)})\n")

    print(f"Результаты сохранены в {output_file}")

calc_results()