"""
Copyright (c) 2015, Xenomorphales
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of Aversive++ nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
"""

from kinematics import *
import sympy
import json
import subprocess
import os

def call_blender_export(path):
    python_script = os.path.abspath(os.path.dirname(__file__)) + "/../scripts/blender_export.py"
    command = ["blender", path, "--background", "--python", python_script]
    subprocess.call(command)

def read_json(path):
    f = open(path, "r")
    ret = json.loads(f.read())
    f.close()
    return ret

def list2dict(json_data):
    ret = {}
    for e in json_data:
        ret[e['name']] = e
    return ret

def extract_chain(json_data, endpoint):
    json_dict = list2dict(json_data)
    elems = []
    cur = endpoint
    while cur != None:
        edata = json_dict[cur]
        if edata['is_variable']:
            e = VariableMatrixChainElement(edata['name'], edata['parent'], edata['matrix'], [sympy.Symbol('x')])
            elems = [e] + elems
        else:
            e = ConstantMatrixChainElement(edata['name'], edata['parent'], edata['matrix'])
            elems = [e] + elems
        cur = edata['parent']
    return Chain(endpoint, elems)
