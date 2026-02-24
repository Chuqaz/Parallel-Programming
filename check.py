import numpy as np

def load_matrix(filename):
    with open(filename,"r",encoding="utf-8") as file:
        size=int(file.readline().strip())
        matrix=[]
        for i in range(size):
            numbers=file.readline().strip().split()
            row=[]
            for j in range(size):
                row.append(float(numbers[j]))
            matrix.append(row)
    return matrix

def multiply(matrix_a, matrix_b):
    result=np.dot(matrix_a,matrix_b)
    result = np.round(result, 2)
    return result

def main():
    matrix_a=load_matrix("matrix_1.txt")
    matrix_b=load_matrix("matrix_2.txt")
    matrix_cpp=load_matrix("matrix_c++.txt")
    result=multiply(matrix_a,matrix_b)
    if(np.array_equal(matrix_cpp, result)):
        print("Verification complete.The matrices are equal")
    else:
        print("Verification complete.The matrices are not equal")

if __name__=="__main__":
    main()