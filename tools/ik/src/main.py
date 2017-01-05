from kinematics import *
from generator import *
import blender_utils
import sympy
import sys

def main(argv):
    if len(argv) < 2:
        print("usage : " + argv[0] + " <blend_file> [<endpoint>]")
        exit()

    x = sympy.Symbol("x")
    y = sympy.Symbol("y")
    z = sympy.Symbol("z")

    blender_utils.call_blender_export(argv[1])

    if len(argv) == 2:
        l = blender_utils.read_json("blender.out.json")
        for e in l:
            print(e["name"])
    elif len(argv) == 3:
        endpoint = argv[2].replace("/", "_")
        chain = blender_utils.extract_chain(
            blender_utils.read_json("blender.out.json"),
            argv[2]
        )
        chain.name = chain.name.replace("/", "_")
        gen = CppProjectGenerator()
        add_ik_module(gen, chain)
        for fname in gen:
            with open(fname, "w+") as f:
                f.write(str(gen[fname]))

