import numpy as np
import time

def load_matrix(filename):
    with open(filename,"r",encoding="utf-8") as file:
        quantity=int(file.readline().strip())
        size=int(file.readline().strip())
        matrices_list=[]
        matrix=[]
        for i in range(size*quantity+(quantity-1)):
            line=file.readline()
            if not line:
                break
            while line.strip()=="":
                line=file.readline()
                if not line:
                    break
            numbers=line.strip().split()
            if len(numbers)!=size:
                continue
            row=[]
            for j in range(size):
                row.append(float(numbers[j]))
            matrix.append(row)
            if(len(matrix)==size):
                matrices_list.append(matrix.copy())
                matrix.clear()
    return matrices_list

def multiply(matrix_a, matrix_b):
    start_time = time.perf_counter()
    result = np.dot(matrix_a, matrix_b)
    end_time = time.perf_counter()
    execution_time = end_time - start_time
    print(f"Execution time: {execution_time*(10**6)} microseconds")
    result = np.round(result, 2)
    return result

def main():
    print("Code in Python")
    matrix_a=load_matrix("matrix_1.txt")
    matrix_b=load_matrix("matrix_2.txt")
    result=[]
    for i in range(len(matrix_a)):
        print(f"Pair number {i}")
        result.append(multiply(matrix_a[i],matrix_b[i]))
    matrix_cpp=load_matrix("matrix_c++.txt")
    for i in range(len(matrix_a)):
        if(np.array_equal(matrix_cpp[i], result[i])):
            print("Verification complete.The matrices are equal")
        else:
            print("Verification complete.The matrices are not equal")

if __name__=="__main__":
    main()
