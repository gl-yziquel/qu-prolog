'os/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	pseudo_instr2(46, 0, 1)
	proceed

$2:
	put_structure(1, 1)
	set_constant('system')
	set_x_value(0)
	put_structure(1, 0)
	set_constant('os')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('+')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('os')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('os/1$0'/1):



'os/1$1'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	pseudo_instr2(46, 0, 2)
	get_x_value(1, 2)
	proceed

$2:
	put_structure(2, 2)
	set_constant('system')
	set_x_value(0)
	set_x_value(1)
	put_structure(1, 0)
	set_constant('os')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('+')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('os')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('os/1$1'/2):



'os'/1:

	switch_on_term(0, $18, $17, $17, $9, $17, $17)

$9:
	switch_on_structure(0, 16, ['$default':$17, '$'/0:$10, 'access'/2:$11, 'argv'/1:$12, 'exit'/1:$13, 'mktemp'/2:$14, 'system'/1:$15, 'system'/2:$16])

$10:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$11:
	try(1, $1)
	retry($2)
	trust($8)

$12:
	try(1, $1)
	retry($3)
	trust($8)

$13:
	try(1, $1)
	retry($4)
	trust($8)

$14:
	try(1, $1)
	retry($5)
	trust($8)

$15:
	try(1, $1)
	retry($6)
	trust($8)

$16:
	try(1, $1)
	retry($7)
	trust($8)

$17:
	try(1, $1)
	trust($8)

$18:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('os')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('+')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('os')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_structure('access', 2, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	neck_cut
	put_integer(0, 2)
	execute_predicate('access', 3)

$3:
	get_structure('argv', 1, 0)
	unify_x_variable(0)
	neck_cut
	pseudo_instr1(11, 1)
	get_x_value(0, 1)
	proceed

$4:
	get_structure('exit', 1, 0)
	unify_x_variable(0)
	neck_cut
	execute_predicate('halt', 1)

$5:
	get_structure('mktemp', 2, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	neck_cut
	pseudo_instr2(47, 0, 2)
	get_x_variable(0, 2)
	get_x_value(1, 0)
	proceed

$6:
	get_structure('system', 1, 0)
	unify_x_variable(0)
	neck_cut
	execute_predicate('os/1$0', 1)

$7:
	get_structure('system', 2, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	neck_cut
	execute_predicate('os/1$1', 2)

$8:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('os')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('+')
	set_constant('gcomp')
	put_structure(1, 3)
	set_constant('os')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('os'/1):



'access/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('access/3$0'/1):



'access'/3:

	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	pseudo_instr1(2, 0)
	pseudo_instr1(3, 1)
	neck_cut
	pseudo_instr3(34, 0, 1, 3)
	get_x_value(2, 3)
	proceed

$2:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('access')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('access')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(3, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(3, 0)
	set_constant('access')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('access')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	call_predicate('access/3$0', 1, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('access')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('access')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)

$5:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('access')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(3, 4)
	set_constant('access')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	put_constant('integer', 3)
	execute_predicate('type_exception', 4)
end('access'/3):



'halt'/0:


$1:
	put_integer(0, 0)
	execute_predicate('halt', 1)
end('halt'/0):



'halt'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	allocate(1)
	get_y_variable(0, 0)
	pseudo_instr1(3, 20)
	neck_cut
	call_predicate('exit_all_thread_guis', 0, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$halt', 1)

$2:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('halt')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('halt')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('halt')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('halt')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	put_constant('integer', 3)
	execute_predicate('type_exception', 4)
end('halt'/1):



'abort'/0:


$1:
	put_list(1)
	set_constant('execution aborted')
	set_constant('[]')
	put_structure(3, 0)
	set_constant('abort')
	set_constant('fatal')
	set_constant('abort')
	set_x_value(1)
	execute_predicate('exception', 1)
end('abort'/0):



