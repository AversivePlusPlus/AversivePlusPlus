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

from chain_element import ChainElement
import numpy as np

class Chain(ChainElement):
    def __init__(self, name, elements):
        ChainElement.__init__(self, name)
        self.elements = elements

    def get_num_params(self):
        _to_num_params = lambda e: e.get_num_params()
        return sum(list(map(_to_num_params, self.elements)))

    def get_matrix(self, *params):
        if len(params) != self.get_num_params():
            return None
        first = self.elements[0]
        ret = first.get_matrix(*params[:first.get_num_params()])
        params = params[first.get_num_params():]
        for e in self.elements[1:]:
            mat = np.asarray(e.get_matrix(*params[:e.get_num_params()]))
            ret = np.dot(ret, mat)
            params = params[e.get_num_params():]
        return ret

    def forward_kinematics(self, params):
        return self.get_matrix(*params)
