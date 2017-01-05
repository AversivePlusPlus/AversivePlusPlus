from kinematics import *
from generator import *
import numpy as np
import sympy

x = sympy.Symbol("x")
y = sympy.Symbol("y")
z = sympy.Symbol("z")

e1 = ConstantMatrixChainElement("e1", None,
                                [[0,1,0],[1,0,0],[0,0,1]])

e2 = VariableMatrixChainElement("e1", None,
                                [[x,0,0],[0,y,0],[0,0,1]], [x,y])

chain = Chain("my_chain", [e1, e2])

gen = CppProjectGenerator()
add_ik_module(gen, chain)
print(gen)
