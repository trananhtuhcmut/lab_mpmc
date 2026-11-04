import re
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

# 1. Dữ liệu Log copy từ Virtual Terminal của Proteus
raw_log = """
[     0 ms] STARTING SCHEDULER
[   300 ms] >>> OneShot A fired at 300ms! <<<
[   500 ms] Task 1 (0.5s) -> Toggle LED1
[  1000 ms] Task 2 (1.0s) -> Toggle LED2
[  1000 ms] Task 1 (0.5s) -> Toggle LED1
[  1200 ms] >>> OneShot B fired at 1200ms! <<<
[  1500 ms] Task 3 (1.5s) -> Toggle LED3
[  1500 ms] Task 1 (0.5s) -> Toggle LED1
[  2000 ms] Task 4 (2.0s) -> Toggle LED4
[  2000 ms] Task 2 (1.0s) -> Toggle LED2
[  2000 ms] Task 1 (0.5s) -> Toggle LED1
[  2500 ms] Task 5 (2.5s) -> Toggle LED5
[  2500 ms] Task 1 (0.5s) -> Toggle LED1
[  3000 ms] Task 3 (1.5s) -> Toggle LED3
[  3000 ms] Task 2 (1.0s) -> Toggle LED2
[  3000 ms] Task 1 (0.5s) -> Toggle LED1
[  3500 ms] Task 1 (0.5s) -> Toggle LED1
[  4000 ms] Task 4 (2.0s) -> Toggle LED4
[  4000 ms] Task 2 (1.0s) -> Toggle LED2
[  4000 ms] Task 1 (0.5s) -> Toggle LED1
[  4500 ms] Task 3 (1.5s) -> Toggle LED3
[  4500 ms] Task 1 (0.5s) -> Toggle LED1
[  5000 ms] Task 5 (2.5s) -> Toggle LED5
[  5000 ms] Task 2 (1.0s) -> Toggle LED2
[  5000 ms] Task 1 (0.5s) -> Toggle LED1
"""

INCLUDE_ONESHOT_IN_GANTT = True
PLOT_GPIO_VOLTAGE_LEVEL = False

# 2. Khởi tạo cấu trúc dữ liệu cho 5 Tasks / 5 LEDs
tasks_info = [
    ("Task 1", "LED1", "Task 1 / LED1 (0.5s)", "#2ecc71"),
    ("Task 2", "LED2", "Task 2 / LED2 (1.0s)", "#3498db"),
    ("Task 3", "LED3", "Task 3 / LED3 (1.5s)", "#9b59b6"),
    ("Task 4", "LED4", "Task 4 / LED4 (2.0s)", "#e67e22"),
    ("Task 5", "LED5", "Task 5 / LED5 (2.5s)", "#e74c3c"),
]

if INCLUDE_ONESHOT_IN_GANTT:
    gantt_labels = ["One-Shot A (0.3s)", "One-Shot B (1.2s)"] + [t[2] for t in tasks_info]
    gantt_colors = {"One-Shot A (0.3s)": "#34495e", "One-Shot B (1.2s)": "#7f8c8d"}
else:
    gantt_labels = [t[2] for t in tasks_info]
    gantt_colors = {}

for _, _, label, color in tasks_info:
    gantt_colors[label] = color

init_val = 1 if PLOT_GPIO_VOLTAGE_LEVEL else 0
led_history = {t[1]: [(0, init_val)] for t in tasks_info}
led_state = {t[1]: init_val for t in tasks_info}
gantt_events = {label: [] for label in gantt_labels}

# 3. Quét dữ liệu Log
pattern = re.compile(r"\[\s*(\d+)\s*ms\]\s*(.*)")
max_time = 5000

for line in raw_log.strip().split("\n"):
    match = pattern.search(line)
    if not match:
        continue
    t = int(match.group(1))
    desc = match.group(2).strip()
    max_time = max(max_time, t)

    for task_key, led_key, label, _ in tasks_info:
        if task_key in desc:
            gantt_events[label].append(t)
            led_state[led_key] = 1 - led_state[led_key]
            led_history[led_key].append((t, led_state[led_key]))

    if INCLUDE_ONESHOT_IN_GANTT:
        if "OneShot A" in desc or "One-Shot A" in desc:
            gantt_events["One-Shot A (0.3s)"].append(t)
        elif "OneShot B" in desc or "One-Shot B" in desc:
            gantt_events["One-Shot B (1.2s)"].append(t)

end_time = max_time + 500
for led_key in led_history:
    led_history[led_key].append((end_time, led_state[led_key]))

# 4. Tạo bố cục hình: Thêm 1 hàng đệm (0.35) ở giữa gs[0] và các kênh LED để cách dòng
fig = plt.figure(figsize=(14, 10.5))
gs = fig.add_gridspec(7, 1, height_ratios=[2.7, 0.35, 1, 1, 1, 1, 1], hspace=0.25)

# --- PHẦN A: VẼ BIỂU ĐỒ GANTT CHO 5 TASKS (Nửa trên) ---
ax_gantt = fig.add_subplot(gs[0])
bar_width_ms = 65
bar_height = 0.55

for idx, label in enumerate(gantt_labels):
    times = gantt_events[label]
    bars = [(t, bar_width_ms) for t in times]
    color = gantt_colors[label]

    ax_gantt.broken_barh(
        bars,
        (idx - bar_height / 2, bar_height),
        facecolors=color,
        edgecolor="black",
        linewidth=0.8
    )

    for t in times:
        ax_gantt.text(
            t + bar_width_ms / 2,
            idx - bar_height / 2 - 0.08,
            f"{t}",
            ha="center",
            va="bottom",
            fontsize=7.5,
            color="#2c3e50"
        )

ax_gantt.set_yticks(range(len(gantt_labels)))
ax_gantt.set_yticklabels(gantt_labels, fontsize=9.5, fontweight="bold")

# Mở rộng trần trục Y lên -0.85 để khung 1 lấp trọn các chữ số của hàng đầu tiên
ax_gantt.set_ylim(len(gantt_labels) - 0.35, -0.85)

ax_gantt.set_xlim(0, end_time)
ax_gantt.set_xticks(range(0, end_time + 1, 500))
ax_gantt.set_title(
    "1. CPU Task Execution",
    fontsize=12,
    fontweight="bold",
    loc="left",
    pad=10
)
ax_gantt.grid(axis="x", linestyle="--", alpha=0.6)
ax_gantt.grid(axis="y", linestyle=":", alpha=0.4)

# --- PHẦN B: VẼ BIỂU ĐỒ XUNG VUÔNG CHO 5 ĐÈN LED (Nửa dưới, bắt đầu từ gs[2]) ---
axes_led = [fig.add_subplot(gs[i + 2], sharex=ax_gantt) for i in range(5)]

for idx, (_, led_key, label, color) in enumerate(tasks_info):
    ax = axes_led[idx]
    times = [pt[0] for pt in led_history[led_key]]
    states = [pt[1] for pt in led_history[led_key]]

    ax.step(times, states, where="post", color=color, linewidth=2.0)
    ax.fill_between(times, states, step="post", color=color, alpha=0.18)

    for t in times[1:-1]:
        ax.axvline(x=t, color=color, linestyle=":", alpha=0.5, linewidth=0.8)

    ax.set_ylim(-0.2, 1.3)
    ax.set_yticks([0, 1])
    if PLOT_GPIO_VOLTAGE_LEVEL:
        ax.set_yticklabels(["0V (ON)", "3.3V (OFF)"], fontsize=8)
    else:
        ax.set_yticklabels(["OFF (0)", "ON (1)"], fontsize=8)

    ax.set_ylabel(f"{led_key}\n({label.split('(')[1]}", fontsize=9, fontweight="bold", rotation=0, labelpad=38, va="center")
    ax.grid(axis="x", linestyle="--", alpha=0.5)
    ax.spines["top"].set_visible(False)
    ax.spines["right"].set_visible(False)

    if idx == 0:
        mode_str = "GPIO Active-Low" if PLOT_GPIO_VOLTAGE_LEVEL else "ON/OFF"
        ax.set_title(
            f"2. Logic Analyzer Chart ({mode_str})",
            fontsize=12,
            fontweight="bold",
            loc="left",
            pad=12  # Cách đường xung LED1 bên dưới một khoảng thoáng
        )

# Ẩn nhãn số trục X ở các khung giữa, chỉ hiện ở trục dưới cùng
for ax in [ax_gantt] + axes_led[:-1]:
    plt.setp(ax.get_xticklabels(), visible=False)

axes_led[-1].set_xlabel("System time (ms)", fontsize=11, fontweight="bold")

plt.tight_layout()
plt.savefig("combined_gantt_and_timing.png", dpi=300)
plt.show()