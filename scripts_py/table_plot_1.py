import matplotlib.pyplot as plt

def draw_plots():
    files = ["res1_2h", "res1_cep", "res1_kuk", "res1_lin", "res1_sq"]
    labels = ["Double Hashing", "Chaining", "Kukushka", "Linear", "Quadratic"]

    plt.figure(figsize=(10, 6))

    for i in range(len(files)):
        filename = files[i]
        label_name = labels[i]

        with open(f"table_tests/{filename}", "r") as f:
            times = list(map(float, f))

        lf_axis = [10000 + j * 10000 for j in range(len(times))]

        plt.plot(lf_axis, times, label=label_name, marker='.', markersize=4)

    plt.title("Hash Table Comparison (equal p)")
    plt.xlabel("Operation's count")
    plt.ylabel("Execution Time (ms)")
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.legend()
    
    plt.savefig("plots/table_plot_1.svg")

draw_plots()