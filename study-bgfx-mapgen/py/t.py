import matplotlib.pyplot as plt

points = [
    (178, 48.4858, 51.9549),
    (198, 46.7457, 60.1442),
    (257, 51.4789, 56.6929),
    (247, 42.1071, 53.6253)
]

labels, x_vals, y_vals = zip(*[(p[0], p[1], p[2]) for p in points])

plt.figure(figsize=(9, 7))
plt.scatter(x_vals, y_vals, color='blue', s=120, zorder=5)

# 使用不同偏移避免重叠
offsets = [(0.6, 0.6), (-1.0, 0.6), (0.6, -0.6), (-1.2, -0.6)]
for i, label in enumerate(labels):
    dx, dy = offsets[i]
    plt.text(x_vals[i] + dx, y_vals[i] + dy, str(label), fontsize=13, weight='bold')

plt.grid(True, linestyle='--', alpha=0.7)
plt.xlabel('X', fontsize=12)
plt.ylabel('Y', fontsize=12)
plt.title('Coordinates with Labels: 178, 198, 257, 247', fontsize=14)
plt.xlim(40, 54)
plt.ylim(50, 62)
plt.tight_layout()
plt.show()