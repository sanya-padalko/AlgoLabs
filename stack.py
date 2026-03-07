#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import subprocess
import sys
from pathlib import Path

def main():
    print("Компиляция проекта с solve.c...")
    
    # Команда компиляции
    cmd = "gcc -o stack.exe solve.c list/list.c vector/vector.c stack_list/stack_list.c stack_vector/stack_vector.c -I./list -I./vector -I./stack_list -I./stack_vector"
    
    # Добавляем tests если есть
    if Path("tests/tests.c").exists():
        cmd += " tests/tests.c -I./tests"
        print("Добавлен tests.c")
    
    # Запускаем компиляцию
    result = subprocess.run(cmd, shell=True)
    
    if result.returncode == 0:
        print("✅ Компиляция успешна!")
        
        # Запускаем программу
        print("\nЗапуск stack.exe...")
        subprocess.run("stack.exe", shell=True)
        
        # Запускаем скрипт для графиков
        if Path("tests/plot-res.py").exists():
            print("\nЗапуск построения графиков...")
            subprocess.run(["python", "tests/plot-res.py"], shell=True)
    else:
        print("❌ Ошибка компиляции!")

if __name__ == "__main__":
    main()