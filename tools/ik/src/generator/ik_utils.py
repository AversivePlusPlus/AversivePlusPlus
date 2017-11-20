from cpp import *

import sympy
import numpy

class IkMatrixType:
    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
    def __str__(self):
        return "matrix<{r}, {c}>".format(
            r=self.rows,
            c=self.cols
        )

def get_cse(matrix):
    rows = len(matrix)
    cols = len(matrix[0])
    expr_list = []
    coord_list = {}
    for row in range(0, rows):
        for col in range(0, cols):
            scase = sympy.sympify(matrix[row][col])
            coord_list[(row,col)] = len(expr_list)
            expr_list.append(scase)
    cse = sympy.cse(expr_list, sympy.numbered_symbols('tmp'))
    tmp_list = cse[0]
    expr_list = cse[1]
    expr_mat = []
    for row in range(0, rows):
        row_list = []
        for col in range(0, cols):
            i = coord_list[(row,col)]
            e = expr_list[i]
            row_list.append(expr_list[i])
        expr_mat.append(row_list)
    return (tmp_list, expr_mat)

def get_transposed_jacobian(mat, sym):
    flat = []
    for row in mat:
        for case in row:
            flat.append(case)
    t_jacobian = []
    for s in sym:
        t_jacobian.append(list(map(lambda e: e.diff(s), flat)))
    return t_jacobian

def matrix_type(r, c):
    return IkMatrixType(r,c)

def get_chain_symbols(chain):
    ids = range(0, chain.get_num_params())
    pnames = list(map(lambda i: "q"+str(i)+"_io", ids))
    return list(map(lambda i: sympy.Symbol(i), pnames))

def get_matrix_mult(m1, m2):
    ret = sympy.Matrix(m1) * sympy.Matrix(m2)
    return list(map(lambda e: [e], list(ret)))

def get_matrix_from_name(gen, name, rows, cols):
    ret = []
    for row in range(0, rows):
        ret_row = []
        for col in range(0, cols):
            ret_row.append(
                sympy.Symbol(gen.matrix_get(name, matrix_type(rows, cols), row, col))
            )
        ret.append(ret_row)
    return ret

def get_column_matrix(matrix):
    ret = []
    rows = len(matrix)
    cols = len(matrix[0])
    for row in range(0, rows):
        for col in range(0, cols):
            ret.append([matrix[row][col]])
    return ret

def get_flat_matrix(matrix):
    ret = []
    rows = len(matrix)
    cols = len(matrix[0])
    for row in range(0, rows):
        for col in range(0, cols):
            ret.append(matrix[row][col])
    return ret

