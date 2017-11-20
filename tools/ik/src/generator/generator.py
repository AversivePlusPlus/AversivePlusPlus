
class NotImplementedError(Exception):
    pass

class Generator:
    # TYPE
    def matrix_type(self, rows, cols):
        raise NotImplementedError()
    real_type = None
    integer_type = None
    void_type = None
    # DEFINE
    def define_module(self, name):
        raise NotImplementedError()
    def define_function(self, name, ret_type, params):
        raise NotImplementedError()
    def define_main_function(self):
        raise NotImplementedError()    
    def define_for_block(self, size):
        raise NotImplementedError()
    def define_if_block(self, cond):
        raise NotImplementedError()
    def define_else_if_block(self, cond):
        raise NotImplementedError()
    def define_else_block(self, cond):
        raise NotImplementedError()
    # ADD
    def add_constant(self, name, type, value):
        raise NotImplementedError()
    def add_variable(self, name, type, default_value = None):
        raise NotImplementedError()
    def add_instruction(self, instr):
        raise NotImplementedError()
    # Others
    def param(self, name, type, default_value = None):
        raise NotImplementedError()
    def ref_type(self, type):
        raise NotImplementedError()
    def const_type(self, type):
        raise NotImplementedError()
    def list_type(self, type):
        raise NotImplementedError()
    def call(self, name, params):
        raise NotImplementedError()
    def assign(self, var, val):
        raise NotImplementedError()
    def matrix_get(self, name, i,j):
        raise NotImplementedError()
    def list_get(self, name, i):
        raise NotImplementedError()
    def nested(self, *names):
        raise NotImplementedError()
