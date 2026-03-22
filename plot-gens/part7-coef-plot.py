import matplotlib.pyplot as plt
import numpy as np

def plot_sorting_times():
    n_values = np.arange(0, 1000000, 10000)
    
    algorithms = {
        'Heap sort after deep = log n': 'intro-heap-1',
        'Heap sort after deep = 2logn': 'intro-heap-2',
        'Heap sort after deep = 4log n': 'intro-heap-4',
        'Heap sort after deep = 8log n': 'intro-heap-8',
        'Heap sort after deep = 16log n': 'intro-heap-16'
    }

    plt.figure(figsize=(12, 8))
    
    for algo_name, filename in algorithms.items():
        try:
            with open(filename, 'r') as file:
                times = [float(line.strip()) for line in file.readlines()]
            
            if len(times) != len(n_values):
                print(f"Предупреждение: в файле {filename} {len(times)} значений, ожидалось {len(n_values)}")

                min_len = min(len(times), len(n_values))
                plot_n_values = n_values[:min_len]
                plot_times = times[:min_len]
            else:
                plot_n_values = n_values
                plot_times = times
            
            plt.plot(plot_n_values, plot_times, marker='o', linewidth=2, 
                    markersize=6, label=algo_name)
            
            print(f"Данные из файла {filename} успешно загружены")
            
        except FileNotFoundError:
            print(f"Ошибка: файл {filename} не найден")
        except Exception as e:
            print(f"Ошибка при чтении файла {filename}: {e}")

    plt.xlabel('Количество элементов', fontsize=12, fontweight='bold')
    plt.ylabel('Время выполнения (миллисекунды)', fontsize=12, fontweight='bold')
    plt.title('Сравнение времени выполнения алгоритмов пирамидальной сортировки с разными кучами', 
              fontsize=14, fontweight='bold')
    plt.grid(True, alpha=0.3)
    plt.legend(loc='upper left', fontsize=10)
    
    plt.text(0.28, 0.98, 'Количество элементов: от 0 до 1e6 (шаг 1e4)',
             transform=plt.gca().transAxes, fontsize=9, 
             verticalalignment='top', bbox=dict(boxstyle='round', facecolor='wheat', alpha=0.5))
    
    plt.tight_layout()

    plt.savefig('7-coef-graph.png', dpi=300, bbox_inches='tight')
    print("График сохранен как '7-coef-graph.png'")
    
    plt.close()

if __name__ == "__main__":
    plot_sorting_times()