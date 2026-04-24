import numpy as np
import time


def get_matrix(filename: str) -> np.ndarray:
    with open(filename, "r", encoding="utf-8") as file:
        size = int(file.readline().strip())
        matrix = []
        for _ in range(size):
            row = list(map(float, file.readline().split()))
            matrix.append(row)
    return np.array(matrix)


def matrix_miltiplier(
    matrix_1: np.ndarray, matrix_2: np.ndarray
) -> tuple[np.ndarray, float]:
    start = time.perf_counter()
    result = np.dot(matrix_1, matrix_2)
    stop = time.perf_counter()
    execution_time = (stop - start) * (10**6)
    return result, execution_time


def make_report(filename: str, execution_time: float, status: bool) -> None:
    with open(filename, "a", encoding="utf-8") as f:
        f.write(f"NumPy Execution time: {execution_time:.2f} microseconds\n")
        f.write(f"Verification: {status}\n")
        f.write("-----------------------------------\n")


def main():
    matrix_1 = get_matrix("matrix_1.txt")
    matrix_2 = get_matrix("matrix_2.txt")
    result_matrix = get_matrix("result.txt")
    py_result, execution_time = matrix_miltiplier(matrix_1, matrix_2)
    if np.allclose(result_matrix, py_result, atol=1e-3):
        make_report("report.txt", execution_time, True)
    else:
        make_report("report.txt", execution_time, False)


if __name__ == "__main__":
    main()
