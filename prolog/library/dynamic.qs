'dynamic'/1:


$1:
	get_structure('/', 2, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	put_integer(1, 2)
	put_integer(4, 3)
	execute_predicate('$dynamic', 4)
end('dynamic'/1):



'dynamic'/2:


$1:
	get_structure('/', 2, 0)
	unify_x_variable(0)
	unify_x_variable(3)
	get_x_variable(2, 1)
	put_x_value(3, 1)
	put_integer(4, 3)
	execute_predicate('$dynamic', 4)
end('dynamic'/2):



'dynamic'/3:


$1:
	get_structure('/', 2, 0)
	unify_x_variable(0)
	unify_x_variable(4)
	get_x_variable(5, 1)
	get_x_variable(3, 2)
	put_x_value(4, 1)
	put_x_value(5, 2)
	execute_predicate('$dynamic', 4)
end('dynamic'/3):



'$dynamic'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(5)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	get_y_level(0)
	put_y_variable(4, 2)
	put_y_variable(3, 3)
	call_predicate('$correct_pred_arity', 4, 5)
	pseudo_instr4(0, 24, 23, 22, 21)
	cut(0)
	deallocate
	proceed

$2:
	put_structure(2, 4)
	set_constant('/')
	set_x_value(0)
	set_x_value(1)
	put_structure(3, 1)
	set_constant('dynamic')
	set_x_value(4)
	set_x_value(2)
	set_x_value(3)
	put_structure(3, 0)
	set_constant('dynamic_code_error')
	set_constant('unrecoverable')
	set_x_value(1)
	set_constant('default')
	execute_predicate('exception', 1)
end('$dynamic'/4):



'is_dynamic_call'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	put_integer(0, 2)
	pseudo_instr3(33, 0, 2, 1)
	put_integer(1, 0)
	get_x_value(1, 0)
	proceed

$2:
	get_x_variable(2, 0)
	pseudo_instr1(0, 2)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 2, 0, 1)
	allocate(2)
	put_y_variable(1, 2)
	put_y_variable(0, 3)
	call_predicate('$correct_pred_arity', 4, 2)
	pseudo_instr3(33, 21, 20, 0)
	put_integer(1, 1)
	get_x_value(0, 1)
	deallocate
	proceed
end('is_dynamic_call'/1):



