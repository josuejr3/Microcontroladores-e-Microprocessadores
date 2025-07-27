#  SCRIPT PARA A QUESTÃO 2 - PROVA 2 - MICRO

def python_list_to_c_array(name, data, values_per_line=10):
    c_code = f"uint16_t {name}[{len(data)}] = {{\n"
    for i in range(0, len(data), values_per_line):
        line = data[i:i+values_per_line]
        line_str = ', '.join(str(x) for x in line)
        c_code += f"    {line_str},\n"
    c_code += "};"
    return c_code

from math import pi, sin
import matplotlib.pyplot as plt
from math import pi, sin
import numpy as np


VM = int((1.6/3.3) * 4095)
Vpp = int((2/3.3) * 4095)
A = int(Vpp/2)
Vref= 3.3
n_amostras = 500



vector = []
tempo = []
tensao_volts = []

T = 20e-6

for i in range(500):
    t = i * T
    v = int(A * sin(2 * pi * i * 100 * T) + VM)
    vector.append(v)
    tempo.append(t * 1000)
    valor_em_volts = (v * Vref) / 4095
    tensao_volts.append(valor_em_volts)

a = python_list_to_c_array("samples", vector, 10)
print(a)

# Ticks do eixo Y de 0.05 em 0.05 V
min_v = np.floor(min(tensao_volts) / 0.05) * 0.05
max_v = np.ceil(max(tensao_volts) / 0.05) * 0.05
y_ticks = np.arange(min_v, max_v + 0.05, 0.05)

# Plot
plt.figure(figsize=(15, 10))
plt.plot(tempo, tensao_volts, color='blue', linewidth=1)
plt.title('Senoide de 100 Hz - Eixo Y com variação de 0.05 V')
plt.xlabel('Tempo (ms)')
plt.ylabel('Tensão (V)')
plt.yticks(y_ticks)
plt.grid(True)
plt.tight_layout()
plt.show()


