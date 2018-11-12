from ctypes import *
from pyglet.gl import *
from typing import Any, Optional, List
from typing import Union as Union_

class GLSLException(Exception): ...

class Shader:
    s_tag: int = ...
    name: str = ...
    prog: str = ...
    shader: int = ...
    compiling: bool = ...
    tag: int = ...
    dependencies: List[Shader] = ...
    def __init__(self, name: str, prog: str) -> None: ...
    def __del__(self) -> None: ...
    def addDependency(self, shader: Shader) -> Shader: ...
    def destroy(self) -> None: ...
    def shaderType(self) -> int: ...
    def isCompiled(self) -> bool: ...
    def attachTo(self, program: int) -> None: ...
    def attachFlat(self, program: int) -> None: ...
    def compileFlat(self) -> None: ...
    def compile(self) -> None: ...

class VertexShader(Shader):
    def shaderType(self) -> int: ...

class FragmentShader(Shader):
    def shaderType(self) -> int: ...

class ShaderProgram:
    vertex_shader: Optional[VertexShader] = ...
    fragment_shader: Optional[FragmentShader] = ...
    program: int = ...
    def __init__(self,
                 vertex_shader: Optional[VertexShader] = ...,
                 fragment_shader: Optional[FragmentShader] = ...) -> None: ...
    def __del__(self) -> None: ...
    def destroy(self) -> None: ...
    def setShader(self, shader: Union_[VertexShader, FragmentShader]) -> None: ...
    def link(self) -> int: ...
    def prog(self) -> int: ...
    def install(self) -> None: ...
    def uninstall(self) -> None: ...
    def uniformLoc(self, var: str) -> int: ...
    def uset1F(self, var: str, x: float) -> None: ...
    def uset2F(self, var: str, x: float, y: float) -> None: ...
    def uset3F(self, var: str, x: float, y: float, z: float) -> None: ...
    def uset4F(self, var: str, x: float, y: float, z: float, w: float) -> None: ...
    def uset1I(self, var: str, x: int) -> None: ...
    def uset3I(self, var: str, x: int, y: int, z: int) -> None: ...
    def usetM4F(self, var: str, m: Any) -> None: ...
    def usetTex(self, var: str, u: int, v: Any) -> None: ...