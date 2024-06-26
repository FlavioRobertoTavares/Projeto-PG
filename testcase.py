import numpy as np

# Função para normalizar um vetor
def normalize(v):
    norm = np.linalg.norm(v)
    if norm == 0: 
       return v
    return v / norm

# Parâmetros
I_a = 0.2
I_d = 1.0
I_s = 1.0
k_a = 0.1
k_d = 0.7
k_s = 0.5
n = 10
L = np.array([1, 1, 1])
N = np.array([0, 0, 1])
V = np.array([0, 0, 1])

# Normalização dos vetores
L = normalize(L)
N = normalize(N)
V = normalize(V)

# Cálculos
L_dot_N = np.dot(L, N)
R = 2 * L_dot_N * N - L
R = normalize(R)
R_dot_V = np.dot(R, V)

# Equação de Phong
I = I_a * k_a + I_d * max(L_dot_N, 0) * k_d + I_s * (max(R_dot_V, 0) ** n) * k_s

print(f"Intensidade da luz resultante: {I}")
