'main/1$0/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	allocate(1)
	get_y_level(0)
	put_constant('dumb', 0)
	call_predicate('member', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('main/1$0/1$0'/1):



'main/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(88, 1)
	allocate(1)
	get_y_level(0)
	call_predicate('main/1$0/1$0', 1, 1)
	cut(0)
	put_constant('$gui_state', 0)
	put_constant('gui', 1)
	pseudo_instr2(74, 0, 1)
	deallocate
	execute_predicate('start_thread_gui', 0)

$2:
	put_constant('$gui_state', 0)
	put_constant('dumb', 1)
	pseudo_instr2(74, 0, 1)
	proceed
end('main/1$0'/1):



'main'/1:


$1:
	allocate(3)
	get_y_variable(2, 0)
	put_y_variable(0, 19)
	put_y_variable(1, 1)
	put_constant('version', 0)
	call_predicate('current_prolog_flag', 2, 3)
	put_y_value(2, 0)
	call_predicate('main/1$0', 1, 2)
	pseudo_instr1(28, 0)
	get_y_value(0, 0)
	put_y_value(0, 0)
	put_constant('Qu-Prolog Version ', 1)
	call_predicate('write_atom', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_constant('write', 2)
	call_predicate('$write_t', 3, 1)
	put_integer(10, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	execute_predicate('interpreter', 0)
end('main'/1):



