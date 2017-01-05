from ik_utils import *

def add_matrix_typedef(gen):
    gen.add_instruction("template<int r, int c> using matrix = {}".format(
        gen.matrix_type("r", "c")
    ))
    return gen

def add_typed_variable_list(gen, vtype, vlist):
    for v in vlist:
        gen.add_variable(v[0], vtype, v[1])
    return gen

def add_fill_matrix_instructions(gen, name, matrix):
    rows = len(matrix)
    cols = len(matrix[0])
    for row in range(0, rows):
        for col in range(0, cols):
            gen.add_instruction(
                gen.assign(
                    gen.matrix_get(
                        name,
                        matrix_type(rows, cols),
                        row, col
                    ),
                    str(matrix[row][col])
                )
            )
    return gen

def add_matrix_returning_function(gen, name, matrix, symbols):
    cse = get_cse(matrix)
    rows = len(matrix)
    cols = len(matrix[0])
    func = gen.define_function(
        name,
        gen.void_type,
        map(lambda s: gen.param(str(s), gen.real_type), symbols) +
        [gen.param("matrix_out", gen.ref_type(matrix_type(rows, cols)))]
    )
    add_typed_variable_list(func, func.real_type, cse[0])
    add_fill_matrix_instructions(func, "matrix_out", cse[1])
    return gen

def add_forward_kinematics_function(gen, chain):
    ids = range(0, chain.get_num_params())
    sym = list(map(lambda i: sympy.Symbol("q"+str(i)), ids))
    mat = chain.forward_kinematics(sym)
    add_matrix_returning_function(
        gen,
        "forward_kinematics",
        mat,
        sym
    )
    return gen

def add_transposed_jacobian_function(gen, chain):
    ids = range(0, chain.get_num_params())
    sym = list(map(lambda i: sympy.Symbol("q"+str(i)), ids))
    mat = chain.forward_kinematics(sym)
    t_jacobian = get_transposed_jacobian(mat, sym)
    add_matrix_returning_function(
        gen,
        "transposed_jacobian",
        t_jacobian,
        sym
    )
    return gen

def add_chain_distance_instructions(gen, chain_name, ret_name, target_name, sym, rows, cols):
    gen.add_instruction(
        gen.call(
            "forward_kinematics",
            map(lambda s: str(s), sym) + [ret_name]
        )
    )
    for row in range(0, rows):
        for col in range(0, cols):
            gen.add_instruction(
                gen.assign(
                    gen.matrix_get(
                        ret_name,
                        matrix_type(rows, cols),
                        row, col
                    ),
                    " - ".join([
                        gen.matrix_get(
                            target_name,
                            matrix_type(rows, cols),
                            row, col
                        ),
                        gen.matrix_get(
                            ret_name,
                            matrix_type(rows, cols),
                            row, col
                        ),
                    ])
                )
            )

def add_norm_constant(gen, ret_name, dist_name, dist_rows, dist_cols):
    dist = get_flat_matrix(
        get_matrix_from_name(gen, dist_name, dist_rows, dist_cols)
    )
    gen.add_constant(
        ret_name,
        gen.real_type,
        gen.call(
            "sqrt",
            [" + ".join(map(lambda e: "{e}*{e}".format(e=str(e)), dist))]
        )
    )
    return gen

def add_ik_return_instructions(gen, sym, delta, delta_norm, dist_norm):
    delta = get_flat_matrix(get_matrix_from_name(gen, delta, len(sym), 1))
    ifblock = gen.define_if_block("{} != 0".format(delta_norm))
    ifblock.add_constant(
        "gain",
        ifblock.real_type,
        "{}*{}/{}".format("coeff", dist_norm, delta_norm)
    )
    for (s,d) in zip(sym,delta):
        ifblock.add_instruction(
            ifblock.assign(
                s,
                "{}+({}*{})".format(s, d, "gain")
            )
        )

def add_distance_from_target_function(gen, chain):
    ids = range(0, chain.get_num_params())
    sym = list(map(lambda i: sympy.Symbol("q"+str(i)+"_io"), ids))
    mat = chain.forward_kinematics(sym)
    shape = sympy.Matrix(mat).shape
    rows = shape[0]
    cols = shape[1]
    t_jacobian = get_transposed_jacobian(mat, sym)
    dist = get_matrix_from_name(gen, "dist", rows, cols)
    delta = get_matrix_mult(t_jacobian, get_column_matrix(dist))
    assert(len(delta) == len(sym))
    assert(len(delta[0]) == 1)
    func = gen.define_function(
        "distance_from_target",
        gen.real_type,
        [gen.param("target", gen.const_type(gen.ref_type(matrix_type(rows, cols))))] +
        map(lambda s: gen.param(str(s), gen.real_type), sym) +
        [gen.param("dist_out", gen.ref_type(matrix_type(rows, cols)))]
    )
    add_chain_distance_instructions(func, chain.name, "dist_out", "target", sym, rows, cols)
    add_norm_constant(func, "ret", "dist_out", rows, cols)
    func.add_instruction("return ret")

def add_inverse_kinematics_step_function(gen, chain):
    ids = range(0, chain.get_num_params())
    sym = list(map(lambda i: sympy.Symbol("q"+str(i)+"_io"), ids))
    mat = chain.forward_kinematics(sym)
    shape = sympy.Matrix(mat).shape
    rows = shape[0]
    cols = shape[1]
    t_jacobian = get_transposed_jacobian(mat, sym)
    dist = get_matrix_from_name(gen, "dist", rows, cols)
    delta = get_matrix_mult(t_jacobian, get_column_matrix(dist))
    cse = get_cse(delta)
    assert(len(delta) == len(sym))
    assert(len(delta[0]) == 1)
    func = gen.define_function(
        "inverse_kinematics_step",
        gen.void_type,
        [gen.param("target", gen.const_type(gen.ref_type(matrix_type(rows, cols))))] +
        map(lambda s: gen.param(str(s), gen.ref_type(gen.real_type)), sym) +
        [gen.param("coeff", gen.real_type)]
    )
    func.add_variable("dist", matrix_type(rows, cols))
    func.add_variable(
        "dist_norm",
        func.real_type,
        func.call(
            "distance_from_target",
            ["target"] + sym + ["dist"]
        )
    )
    func.add_variable("delta", matrix_type(len(sym),1))
    add_typed_variable_list(func, func.real_type, cse[0])
    add_fill_matrix_instructions(func, "delta", cse[1])
    add_norm_constant(func, "delta_norm", "delta", len(sym), 1)
    add_ik_return_instructions(func, sym, "delta", "delta_norm", "dist_norm")
    
def add_inverse_kinematics_function(gen, chain):
    ids = range(0, chain.get_num_params())
    sym = list(map(lambda i: sympy.Symbol("q"+str(i)+"_io"), ids))
    mat = chain.forward_kinematics(sym)
    shape = sympy.Matrix(mat).shape
    rows = shape[0]
    cols = shape[1]
    func = gen.define_function(
        "inverse_kinematics",
        "bool",
        [gen.param("target", gen.const_type(gen.ref_type(matrix_type(rows, cols))))] +
        map(lambda s: gen.param(str(s), gen.ref_type(gen.real_type)), sym) +
        [
            gen.param("coeff", gen.real_type),
            gen.param("stop_dist", gen.real_type),
            gen.param("max_iter", gen.integer_type),
        ])
    func.add_variable("tmp", matrix_type(rows, cols))
    ifblock = func.define_if_block(
        "stop_dist >= " + 
        func.call(
            "distance_from_target",
            ["target"] + sym + ["tmp"]
        )
    )
    ifblock.add_instruction("return true")
    forblock = func.define_for_block("max_iter")
    forblock.add_instruction(
        func.call(
            "inverse_kinematics_step",
            ["target"] + sym + ["coeff"]
        )
    )
    ifblock = forblock.define_if_block(
        "stop_dist >= " + 
        func.call(
            "distance_from_target",
            ["target"] + sym + ["tmp"]
        )
    )
    ifblock.add_instruction("return true")
    func.add_instruction("return false")

    
def add_ik_module(gen, chain):
    mod = gen.define_module(chain.name)
    add_matrix_typedef(mod)
    add_forward_kinematics_function(mod, chain)
    add_distance_from_target_function(mod, chain)
    add_inverse_kinematics_step_function(mod, chain)
    add_inverse_kinematics_function(mod, chain)
    return gen
