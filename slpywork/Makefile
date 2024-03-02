slpy: slpy-lex.obj slpy-parse.obj slpy.obj slpy-ast.obj slpy-util.obj
	cl slpy-util.obj slpy-lex.obj slpy-ast.obj slpy-parse.obj slpy.obj

slpy-ast.obj: slpy-ast.cc
	cl slpy-ast.cc

slpy-lex.obj: slpy-lex.cc
	cl slpy-lex.cc

slpy-util.obj: slpy-util.cc
	cl slpy-util.cc

slpy-parse.obj: slpy-parse.cc
	cl slpy-parse.cc

slpy.obj: slpy.cc
	cl slpy.cc

slpy-lex.cc: slpy-lex.hh slpy-util.hh
slpy-parse.cc: slpy-parse.hh slpy-ast.hh slpy-util.hh
slpy.cc: slpy-lex.hh slpy-ast.hh slpy-parse.hh slpy-util.hh
slpy-ast.cc: slpy-ast.hh slpy-util.hh
slpy-util.cc: slpy-util.hh

clean:
	rm *~ *.obj slpy
