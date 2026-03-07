#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import os
import sys

def read_test4_data(filename):
    """
    Читает файл с данными теста 4.
    Формат: <n_elements> <time_list> <time_array>
    Время в файле уже в миллисекундах!
    """
    n_elements = []
    time_list = []    # в миллисекундах
    time_array = []   # в миллисекундах
    
    if not os.path.exists(filename):
        print(f"ОШИБКА: Файл {filename} не найден!")
        print(f"Текущая директория: {os.getcwd()}")
        return None, None, None
    
    print(f"Чтение файла {filename}...")
    print("-" * 60)
    #print(f"{'Элементов':>10} {'Список (мс)':>12} {'Массив (мс)':>12}")
    #print("-" * 60)
    
    with open(filename, 'r', encoding='utf-8') as f:
        for line_num, line in enumerate(f, 1):
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            
            try:
                parts = line.split()
                if len(parts) >= 3:
                    n = float(parts[0]) if '.' in parts[0] else int(parts[0])
                    t_list = float(parts[1])    # уже в миллисекундах
                    t_array = float(parts[2])    # уже в миллисекундах
                    
                    n_elements.append(n)
                    time_list.append(t_list)
                    time_array.append(t_array)
                    #print(f"{n:10.0f} {t_list:12.3f} {t_array:12.3f}")
            except ValueError as e:
                print(f"Предупреждение: Ошибка в строке {line_num}: {e}")
                continue
    
    #print("-" * 60)
    if not n_elements:
        print("ОШИБКА: Нет данных в файле!")
        return None, None, None
    
    print(f"Прочитано {len(n_elements)} точек")
    print(f"Диапазон элементов: от {min(n_elements):.0f} до {max(n_elements):.0f}")
    print(f"Диапазон времен (список): от {min(time_list):.3f} до {max(time_list):.3f} мс")
    print(f"Диапазон времен (массив): от {min(time_array):.3f} до {max(time_array):.3f} мс")
    
    return n_elements, time_list, time_array

def filter_data(n_elements, time_list, time_array, max_time):
    """
    Фильтрует данные, оставляя только точки, где оба значения <= max_time
    """
    filtered_n = []
    filtered_list = []
    filtered_array = []
    
    excluded_count = 0
    
    for i in range(len(n_elements)):
        if time_list[i] <= max_time and time_array[i] <= max_time:
            filtered_n.append(n_elements[i])
            filtered_list.append(time_list[i])
            filtered_array.append(time_array[i])
        else:
            excluded_count += 1
            if time_list[i] > max_time:
                print(f"  ⚠️ Исключена точка {n_elements[i]:.0f}: список = {time_list[i]:.1f} мс (>60)")
            if time_array[i] > max_time:
                print(f"  ⚠️ Исключена точка {n_elements[i]:.0f}: массив = {time_array[i]:.1f} мс (>60)")
    
    return filtered_n, filtered_list, filtered_array, excluded_count

def save_plot(n_elements, time_list, time_array, output_filename):
    """
    Создает и сохраняет график в файл с ограничением до 60 мс
    """
    # Создаем фигуру
    plt.figure(figsize=(14, 8))
    
    # Строим графики (данные уже в миллисекундах)
    plt.plot(n_elements, time_array, 
             marker='o', linestyle='-', color='#1f77b4', 
             linewidth=2, markersize=5,
             label='Стек на массиве', zorder=3)
    
    # Красная линия сплошная
    plt.plot(n_elements, time_list, 
             marker='s', linestyle='-', color='#d62728', 
             linewidth=2, markersize=5,
             label='Стек на списке', zorder=3)
    
    # Добавляем опорные линии
    #plt.axhline(y=50, color='gray', linestyle=':', alpha=0.7, 
     #           linewidth=1.5, label='50 мс', zorder=1)
    #plt.axhline(y=60, color='gray', linestyle=':', alpha=0.7, 
     #           linewidth=1.5, label='60 мс', zorder=1)
    #plt.axhline(y=150, color='gray', linestyle=':', alpha=0.7, 
    #            linewidth=1.5, label='150 мс', zorder=1)
    
    # Настройки графика
    plt.title('Тест 4: Сравнение времени выполнения операций push (до 60 мс)', 
              fontsize=16, fontweight='bold', pad=20)
    plt.xlabel('Количество элементов', fontsize=14, labelpad=10)
    plt.ylabel('Время выполнения (миллисекунды)', fontsize=14, labelpad=10)
    
    # Устанавливаем границы осей
    if n_elements:
        plt.xlim(min(n_elements) - 5000, max(n_elements) + 5000)
    
    # Ограничиваем Y до 150 мс
    plt.ylim(0, 60)  # 155 мс чтобы было немного места сверху
    
    # Настраиваем сетку
    plt.grid(True, linestyle=':', alpha=0.5, zorder=0)
    
    # Настраиваем легенду
    plt.legend(fontsize=12, framealpha=0.95, loc='upper left')
    
    # Настраиваем метки на осях
    plt.xticks(fontsize=11, rotation=45)
    plt.yticks(fontsize=11)
    
    # Форматируем ось X
    plt.gca().xaxis.set_major_formatter(plt.FuncFormatter(lambda x, p: f'{int(x/1000)}K'))
    
    # Добавляем статистику на график
    if time_array and time_list:
        avg_array = sum(time_array) / len(time_array)
        avg_list = sum(time_list) / len(time_list)
        
        stats_text = f"Среднее время:\nМассив: {avg_array:.1f} мс\nСписок: {avg_list:.1f} мс\nСписок/массив: {avg_list/avg_array:.2f}x"
        stats_text += f"\nТочек на графике: {len(n_elements)}"
        
        plt.text(0.02, 0.88, stats_text,
                transform=plt.gca().transAxes,
                verticalalignment='top',
                bbox=dict(boxstyle='round', facecolor='white', alpha=0.9),
                fontsize=10)
    
    plt.tight_layout()
    plt.savefig(output_filename, dpi=300, bbox_inches='tight', facecolor='white')
    print(f"\nГрафик сохранен в файл: {output_filename}")

def main():
    print("=" * 70)
    print("СОХРАНЕНИЕ ГРАФИКА ДЛЯ ТЕСТА 4")
    print("Масштаб по Y: 0-60 мс")
    print("=" * 70)
    
    input_file = "tests/test4.txt"
    output_file = "tests/test4_graph.png"
    
    # Читаем данные
    n, list_time, array_time = read_test4_data(input_file)
    
    if n is not None:
        # Фильтруем точки, оставляя только те, что в пределах 150 мс
        
        print("\nФильтрация точек...")
        filtered_n, filtered_list, filtered_array, excluded = filter_data(n, list_time, array_time, 60)
        
        print(f"\nРезультат фильтрации:")
        print(f"  Всего точек: {len(n)}")
        print(f"  Оставлено: {len(filtered_n)}")
        print(f"  Исключено: {excluded}")
        
        if len(filtered_n) == 0:
            print("\n❌ Нет точек в пределах 60 мс! График не может быть построен.")
            return
        
        # Строим и сохраняем график
        print("\nСоздание графика...")
        save_plot(filtered_n, filtered_list, filtered_array, output_file)
        print(f"\n✅ Готово! График сохранен как '{output_file}'")
        print(f"   На графике {len(filtered_n)} точек из {len(n)}")
    else:
        print("\n❌ Не удалось создать график")

if __name__ == "__main__":
    main()