'catch'/3:


$1:
	get_x_variable(4, 0)
	get_x_variable(0, 1)
	pseudo_instr1(21, 1)
	get_x_variable(3, 1)
	put_x_value(4, 1)
	execute_predicate('$enter_catch', 4)
end('catch'/3):



'$enter_catch/4$0/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	allocate(1)
	get_y_level(0)
	put_structure(2, 0)
	set_constant('$throw_pattern')
	set_x_value(1)
	set_void(1)
	put_constant('true', 1)
	call_predicate('clause', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('$enter_catch/4$0/3$0'/1):



'$enter_catch/4$0'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$enter_catch/4$0/3$0', 1, 1)
	cut(0)
	fail

$2:
	get_x_variable(3, 0)
	allocate(2)
	get_y_variable(0, 2)
	get_y_level(1)
	put_structure(2, 0)
	set_constant('$throw_pattern')
	set_x_value(3)
	set_x_value(1)
	put_constant('true', 1)
	call_predicate('$retract', 2, 2)
	cut(1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call_predicate', 1)

$3:
	pseudo_instr0(1)
	fail
end('$enter_catch/4$0'/3):



'$enter_catch'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_variable(0, 1)
	allocate(2)
	get_y_variable(1, 3)
	pseudo_instr0(0)
	pseudo_instr1(21, 1)
	get_y_variable(0, 1)
	call_predicate('call_predicate', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$exit_catch', 2)

$2:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 2)
	get_y_variable(3, 3)
	put_y_variable(0, 0)
	call_predicate('thread_symbol', 1, 4)
	pseudo_instr1(22, 23)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$enter_catch/4$0', 3)
end('$enter_catch'/4):



'$exit_catch'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(22, 0)
	proceed

$2:
	pseudo_instr1(22, 1)
	fail
end('$exit_catch'/2):



'throw'/1:


$1:
	allocate(2)
	get_y_variable(1, 0)
	put_y_variable(0, 0)
	call_predicate('thread_symbol', 1, 2)
	put_structure(2, 0)
	set_constant('$throw_pattern')
	set_y_value(0)
	set_y_value(1)
	call_predicate('asserta', 1, 0)
	pseudo_instr0(1)
	fail
end('throw'/1):



