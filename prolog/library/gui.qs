'start_thread_gui/0$0'/0:

	try(0, $1)
	trust($2)

$1:
	pseudo_instr1(88, 0)
	neck_cut
	fail

$2:
	proceed
end('start_thread_gui/0$0'/0):



'start_thread_gui'/0:

	try(0, $1)
	retry($2)
	trust($3)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('start_thread_gui/0$0', 0, 1)
	cut(0)
	put_constant('Can''t start GUI for unnamed process', 0)
	deallocate
	execute_predicate('errornl', 1)

$2:
	allocate(1)
	get_y_level(0)
	put_x_variable(0, 0)
	call_predicate('$thread_gui_set', 1, 1)
	cut(0)
	deallocate
	proceed

$3:
	pseudo_instr1(68, 0)
	get_x_variable(1, 0)
	allocate(9)
	get_y_level(4)
	put_y_variable(8, 19)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_structure(1, 0)
	set_constant('$thread_gui_set')
	set_x_value(1)
	call_predicate('assert', 1, 9)
	put_y_value(8, 0)
	call_predicate('icm_thread_handle', 1, 9)
	put_y_value(7, 0)
	put_y_value(6, 1)
	put_x_variable(2, 2)
	put_x_variable(3, 3)
	put_y_value(8, 4)
	call_predicate('icm_handle_to_components', 5, 8)
	pseudo_instr1(98, 0)
	pseudo_instr1(99, 1)
	put_x_variable(3, 4)
	get_list(4)
	unify_constant('"')
	unify_x_ref(4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('"')
	unify_constant('[]')
	pseudo_instr2(31, 3, 2)
	get_x_variable(0, 2)
	put_x_variable(3, 4)
	get_list(4)
	unify_constant('qp_gui')
	unify_x_ref(4)
	get_list(4)
	unify_y_value(7)
	unify_x_ref(4)
	get_list(4)
	unify_y_value(6)
	unify_x_ref(4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(1)
	unify_x_ref(0)
	get_list(0)
	unify_constant('&')
	unify_constant('[]')
	put_constant(' ', 0)
	pseudo_instr3(28, 3, 0, 2)
	get_x_variable(1, 2)
	put_structure(1, 0)
	set_constant('system')
	set_x_value(1)
	call_predicate('os', 1, 6)
	put_y_value(3, 0)
	call_predicate('gui_handle', 1, 6)
	call_predicate('repeat', 0, 6)
	put_y_value(5, 0)
	put_y_value(3, 1)
	call_predicate('<<=', 2, 6)
	put_x_variable(0, 1)
	get_list(1)
	unify_integer(114)
	unify_x_ref(1)
	get_list(1)
	unify_integer(101)
	unify_x_ref(1)
	get_list(1)
	unify_integer(97)
	unify_x_ref(1)
	get_list(1)
	unify_integer(100)
	unify_x_ref(1)
	get_list(1)
	unify_integer(121)
	unify_x_ref(1)
	get_list(1)
	unify_integer(95)
	unify_x_ref(1)
	get_list(1)
	unify_integer(116)
	unify_x_ref(1)
	get_list(1)
	unify_integer(111)
	unify_x_ref(1)
	get_list(1)
	unify_integer(95)
	unify_x_ref(1)
	get_list(1)
	unify_integer(103)
	unify_x_ref(1)
	get_list(1)
	unify_integer(111)
	unify_constant('[]')
	pseudo_instr2(110, 25, 0)
	cut(4)
	put_y_value(3, 0)
	put_y_value(2, 2)
	put_constant('read', 1)
	call_predicate('open_msgstream', 3, 4)
	put_y_value(3, 0)
	put_y_value(1, 2)
	put_constant('write', 1)
	call_predicate('open_msgstream', 3, 4)
	put_y_value(3, 0)
	put_y_value(0, 2)
	put_constant('write', 1)
	call_predicate('open_msgstream', 3, 3)
	pseudo_instr1(102, 20)
	put_integer(0, 0)
	pseudo_instr2(102, 0, 22)
	put_integer(1, 0)
	pseudo_instr2(102, 0, 21)
	put_integer(2, 0)
	pseudo_instr2(102, 0, 20)
	deallocate
	proceed
end('start_thread_gui'/0):



'exit_thread_gui'/0:

	try(0, $1)
	trust($2)

$1:
	put_constant('$indent_level', 1)
	pseudo_instr2(73, 1, 0)
	put_integer(0, 1)
	get_x_value(0, 1)
	put_constant('$break_level', 1)
	pseudo_instr2(73, 1, 0)
	put_integer(0, 1)
	get_x_value(0, 1)
	pseudo_instr1(68, 0)
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	call_predicate('$thread_gui_set', 1, 2)
	cut(1)
	put_constant('$exit_gui', 0)
	put_constant('[]', 1)
	call_predicate('write_term', 2, 1)
	call_predicate('flush_output', 0, 1)
	put_integer(0, 0)
	call_predicate('reset_std_stream', 1, 1)
	put_integer(1, 0)
	call_predicate('reset_std_stream', 1, 1)
	put_integer(2, 0)
	call_predicate('reset_std_stream', 1, 1)
	put_structure(1, 0)
	set_constant('$thread_gui_set')
	set_y_value(0)
	deallocate
	execute_predicate('retract', 1)

$2:
	proceed
end('exit_thread_gui'/0):



'exit_all_thread_guis/0$0'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_integer(0, 1)
	get_x_value(0, 1)
	neck_cut
	fail

$2:
	proceed
end('exit_all_thread_guis/0$0'/1):



'exit_all_thread_guis'/0:

	try(0, $1)
	retry($2)
	trust($3)

$1:
	put_structure(1, 0)
	set_constant('$thread_gui_set')
	set_void(1)
	allocate(0)
	call_predicate('retract', 1, 0)
	put_constant('$exit_gui', 0)
	put_constant('[]', 1)
	call_predicate('write_term', 2, 0)
	call_predicate('flush_output', 0, 0)
	fail

$2:
	put_structure(3, 0)
	set_constant('$thread_debug_set')
	set_void(1)
	allocate(2)
	set_y_variable(1)
	set_y_variable(0)
	call_predicate('retract', 1, 2)
	put_y_value(1, 0)
	call_predicate('exit_all_thread_guis/0$0', 1, 2)
	put_y_value(0, 0)
	put_constant('$exit_gui', 1)
	put_constant('[]', 2)
	call_predicate('write_term', 3, 2)
	put_y_value(1, 0)
	call_predicate('close', 1, 1)
	put_y_value(0, 0)
	call_predicate('close', 1, 0)
	fail

$3:
	proceed
end('exit_all_thread_guis'/0):



'reset_std_stream'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	get_integer(0, 0)
	neck_cut
	put_integer(0, 1)
	pseudo_instr2(101, 1, 0)
	put_integer(0, 0)
	pseudo_instr1(95, 0)
	proceed

$2:
	pseudo_instr1(95, 0)
	proceed
end('reset_std_stream'/1):



'start_debug_thread_gui/0$0/0$0'/0:

	try(0, $1)
	trust($2)

$1:
	pseudo_instr1(88, 0)
	neck_cut
	fail

$2:
	proceed
end('start_debug_thread_gui/0$0/0$0'/0):



'start_debug_thread_gui/0$0'/0:

	try(0, $1)
	trust($2)

$1:
	execute_predicate('start_debug_thread_gui/0$0/0$0', 0)

$2:
	put_constant('$gui_state', 1)
	pseudo_instr2(73, 1, 0)
	put_constant('dumb', 1)
	get_x_value(0, 1)
	proceed
end('start_debug_thread_gui/0$0'/0):



'start_debug_thread_gui'/0:

	try(0, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(68, 0)
	allocate(1)
	get_y_level(0)
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	call_predicate('$thread_debug_set', 3, 1)
	cut(0)
	deallocate
	proceed

$2:
	pseudo_instr1(88, 0)
	put_constant('$gui_state', 1)
	pseudo_instr2(73, 1, 0)
	put_constant('gui', 1)
	get_x_value(0, 1)
	neck_cut
	allocate(9)
	get_y_level(4)
	pseudo_instr1(68, 0)
	get_y_variable(2, 0)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(3, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(8, 0)
	call_predicate('icm_thread_handle', 1, 9)
	put_y_value(7, 0)
	put_y_value(6, 1)
	put_x_variable(2, 2)
	put_x_variable(3, 3)
	put_y_value(8, 4)
	call_predicate('icm_handle_to_components', 5, 8)
	pseudo_instr1(98, 0)
	put_x_variable(2, 3)
	get_list(3)
	unify_constant('"')
	unify_x_ref(3)
	get_list(3)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_constant('"')
	unify_constant('[]')
	pseudo_instr2(31, 2, 1)
	get_x_variable(0, 1)
	pseudo_instr1(99, 1)
	put_x_variable(3, 4)
	get_list(4)
	unify_constant('qp_debug_gui')
	unify_x_ref(4)
	get_list(4)
	unify_y_value(7)
	unify_x_ref(4)
	get_list(4)
	unify_y_value(6)
	unify_x_ref(4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(1)
	unify_x_ref(0)
	get_list(0)
	unify_constant('&')
	unify_constant('[]')
	put_constant(' ', 0)
	pseudo_instr3(28, 3, 0, 2)
	get_x_variable(1, 2)
	put_structure(1, 0)
	set_constant('system')
	set_x_value(1)
	call_predicate('os', 1, 6)
	put_y_value(3, 0)
	call_predicate('debug_gui_handle', 1, 6)
	call_predicate('repeat', 0, 6)
	put_y_value(5, 0)
	put_y_value(3, 1)
	call_predicate('<<=', 2, 6)
	put_x_variable(0, 1)
	get_list(1)
	unify_integer(114)
	unify_x_ref(1)
	get_list(1)
	unify_integer(101)
	unify_x_ref(1)
	get_list(1)
	unify_integer(97)
	unify_x_ref(1)
	get_list(1)
	unify_integer(100)
	unify_x_ref(1)
	get_list(1)
	unify_integer(121)
	unify_x_ref(1)
	get_list(1)
	unify_integer(95)
	unify_x_ref(1)
	get_list(1)
	unify_integer(116)
	unify_x_ref(1)
	get_list(1)
	unify_integer(111)
	unify_x_ref(1)
	get_list(1)
	unify_integer(95)
	unify_x_ref(1)
	get_list(1)
	unify_integer(103)
	unify_x_ref(1)
	get_list(1)
	unify_integer(111)
	unify_constant('[]')
	pseudo_instr2(110, 25, 0)
	cut(4)
	put_y_value(3, 0)
	put_y_value(1, 2)
	put_constant('read', 1)
	call_predicate('open_msgstream', 3, 4)
	put_y_value(3, 0)
	put_y_value(0, 2)
	put_constant('write', 1)
	call_predicate('open_msgstream', 3, 3)
	pseudo_instr1(102, 20)
	put_structure(3, 0)
	set_constant('$thread_debug_set')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	deallocate
	execute_predicate('assert', 1)

$3:
	pseudo_instr1(88, 0)
	allocate(10)
	get_y_level(4)
	put_y_variable(9, 19)
	put_y_variable(8, 19)
	put_y_variable(7, 19)
	put_y_variable(6, 19)
	put_y_variable(5, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_constant('$QPHOME/bin/xqpdebug', 0)
	put_integer(0, 1)
	put_integer(0, 2)
	call_predicate('access', 3, 10)
	cut(4)
	pseudo_instr1(68, 0)
	get_y_value(2, 0)
	put_y_value(9, 0)
	call_predicate('icm_thread_handle', 1, 10)
	put_y_value(7, 0)
	put_y_value(6, 1)
	put_y_value(8, 2)
	put_x_variable(3, 3)
	put_y_value(9, 4)
	call_predicate('icm_handle_to_components', 5, 9)
	put_x_variable(1, 2)
	get_list(2)
	unify_constant('"')
	unify_x_ref(2)
	get_list(2)
	unify_y_value(8)
	unify_x_ref(2)
	get_list(2)
	unify_constant('"')
	unify_constant('[]')
	pseudo_instr2(31, 1, 0)
	pseudo_instr1(99, 1)
	put_x_variable(3, 4)
	get_list(4)
	unify_constant('xqpdebug')
	unify_x_ref(4)
	get_list(4)
	unify_y_value(7)
	unify_x_ref(4)
	get_list(4)
	unify_y_value(6)
	unify_x_ref(4)
	get_list(4)
	unify_x_value(0)
	unify_x_ref(0)
	get_list(0)
	unify_x_value(1)
	unify_x_ref(0)
	get_list(0)
	unify_constant('&')
	unify_constant('[]')
	put_constant(' ', 0)
	pseudo_instr3(28, 3, 0, 2)
	get_x_variable(1, 2)
	put_structure(1, 0)
	set_constant('system')
	set_x_value(1)
	call_predicate('os', 1, 6)
	put_y_value(3, 0)
	call_predicate('debug_gui_handle', 1, 6)
	call_predicate('repeat', 0, 6)
	put_y_value(5, 0)
	put_y_value(3, 1)
	call_predicate('<<=', 2, 6)
	put_x_variable(0, 1)
	get_list(1)
	unify_integer(114)
	unify_x_ref(1)
	get_list(1)
	unify_integer(101)
	unify_x_ref(1)
	get_list(1)
	unify_integer(97)
	unify_x_ref(1)
	get_list(1)
	unify_integer(100)
	unify_x_ref(1)
	get_list(1)
	unify_integer(121)
	unify_x_ref(1)
	get_list(1)
	unify_integer(95)
	unify_x_ref(1)
	get_list(1)
	unify_integer(116)
	unify_x_ref(1)
	get_list(1)
	unify_integer(111)
	unify_x_ref(1)
	get_list(1)
	unify_integer(95)
	unify_x_ref(1)
	get_list(1)
	unify_integer(103)
	unify_x_ref(1)
	get_list(1)
	unify_integer(111)
	unify_constant('[]')
	pseudo_instr2(110, 25, 0)
	cut(4)
	put_y_value(3, 0)
	put_y_value(1, 2)
	put_constant('read', 1)
	call_predicate('open_msgstream', 3, 4)
	put_y_value(3, 0)
	put_y_value(0, 2)
	put_constant('write', 1)
	call_predicate('open_msgstream', 3, 3)
	pseudo_instr1(102, 20)
	put_structure(3, 0)
	set_constant('$thread_debug_set')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	deallocate
	execute_predicate('assert', 1)

$4:
	allocate(1)
	get_y_level(0)
	call_predicate('start_debug_thread_gui/0$0', 0, 1)
	cut(0)
	pseudo_instr1(68, 0)
	get_x_variable(1, 0)
	put_structure(3, 0)
	set_constant('$thread_debug_set')
	set_x_value(1)
	set_integer(0)
	set_integer(2)
	deallocate
	execute_predicate('assert', 1)
end('start_debug_thread_gui'/0):



'exit_debug_thread_gui/0$0'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_integer(0, 1)
	get_x_value(0, 1)
	neck_cut
	fail

$2:
	proceed
end('exit_debug_thread_gui/0$0'/1):



'exit_debug_thread_gui'/0:

	try(0, $1)
	trust($2)

$1:
	pseudo_instr1(68, 0)
	get_x_variable(1, 0)
	allocate(3)
	get_y_level(2)
	put_structure(3, 0)
	set_constant('$thread_debug_set')
	set_x_value(1)
	set_y_variable(1)
	set_y_variable(0)
	call_predicate('retract', 1, 3)
	put_y_value(1, 0)
	call_predicate('exit_debug_thread_gui/0$0', 1, 3)
	cut(2)
	put_y_value(0, 0)
	put_constant('$exit_gui', 1)
	put_constant('[]', 2)
	call_predicate('write_term', 3, 2)
	put_y_value(1, 0)
	call_predicate('close', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('close', 1)

$2:
	proceed
end('exit_debug_thread_gui'/0):



'gui_handle'/1:


$1:
	allocate(6)
	get_y_variable(0, 0)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(5, 0)
	call_predicate('icm_thread_handle', 1, 6)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_y_value(5, 4)
	call_predicate('icm_handle_to_components', 5, 5)
	put_x_variable(1, 2)
	get_list(2)
	unify_y_value(4)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(3)
	unify_x_ref(2)
	get_list(2)
	unify_constant('gui')
	unify_constant('[]')
	put_constant('_', 2)
	pseudo_instr3(28, 1, 2, 0)
	put_constant('', 2)
	pseudo_instr5(2, 2, 0, 22, 21, 1)
	get_x_variable(0, 1)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$same_handle', 2)
end('gui_handle'/1):



'debug_gui_handle'/1:


$1:
	allocate(6)
	get_y_variable(0, 0)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(5, 0)
	call_predicate('icm_thread_handle', 1, 6)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_y_value(5, 4)
	call_predicate('icm_handle_to_components', 5, 5)
	put_x_variable(1, 2)
	get_list(2)
	unify_y_value(4)
	unify_x_ref(2)
	get_list(2)
	unify_y_value(3)
	unify_x_ref(2)
	get_list(2)
	unify_constant('debug_gui')
	unify_constant('[]')
	put_constant('_', 2)
	pseudo_instr3(28, 1, 2, 0)
	put_constant('', 2)
	pseudo_instr5(2, 2, 0, 22, 21, 1)
	get_x_variable(0, 1)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$same_handle', 2)
end('debug_gui_handle'/1):



'write_debug_msg_term_list'/1:


$1:
	allocate(3)
	get_y_variable(1, 0)
	pseudo_instr1(68, 0)
	put_y_variable(0, 19)
	put_x_variable(1, 1)
	put_y_variable(2, 2)
	call_predicate('$thread_debug_set', 3, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('$streamnum', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$write_term_list', 2)
end('write_debug_msg_term_list'/1):



'write_debug_msg_term'/2:


$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	pseudo_instr1(68, 0)
	put_x_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$thread_debug_set', 3, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('write_term', 3)
end('write_debug_msg_term'/2):



'read_debug_msg_codes'/1:


$1:
	allocate(3)
	get_y_variable(1, 0)
	pseudo_instr1(68, 0)
	put_y_variable(0, 19)
	put_y_variable(2, 1)
	put_x_variable(2, 2)
	call_predicate('$thread_debug_set', 3, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('get_line', 2, 2)
	put_y_value(0, 0)
	put_list(1)
	set_integer(10)
	set_constant('[]')
	put_y_value(1, 2)
	deallocate
	execute_predicate('append', 3)
end('read_debug_msg_codes'/1):



'read_debug_msg_term'/2:


$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	pseudo_instr1(68, 0)
	put_y_variable(0, 1)
	put_x_variable(2, 2)
	call_predicate('$thread_debug_set', 3, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('read_term', 3)
end('read_debug_msg_term'/2):



