'ipc_send'/2:


$1:
	pseudo_instr1(90, 2)
	pseudo_instr2(114, 1, 3)
	get_x_variable(1, 3)
	put_constant('[]', 3)
	pseudo_instr4(9, 0, 1, 2, 3)
	proceed
end('ipc_send'/2):



'ipc_send'/3:


$1:
	pseudo_instr2(114, 1, 3)
	get_x_variable(1, 3)
	pseudo_instr2(114, 2, 3)
	get_x_variable(2, 3)
	put_constant('[]', 3)
	pseudo_instr4(9, 0, 1, 2, 3)
	proceed
end('ipc_send'/3):



'ipc_send'/4:


$1:
	pseudo_instr2(114, 1, 4)
	get_x_variable(1, 4)
	pseudo_instr2(114, 2, 4)
	get_x_variable(2, 4)
	pseudo_instr4(9, 0, 1, 2, 3)
	proceed
end('ipc_send'/4):



'ipc_recv'/1:


$1:
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	put_constant('[]', 3)
	execute_predicate('ipc_recv', 4)
end('ipc_recv'/1):



'ipc_recv'/2:


$1:
	put_x_variable(2, 2)
	put_constant('[]', 3)
	execute_predicate('ipc_recv', 4)
end('ipc_recv'/2):



'ipc_recv'/3:


$1:
	put_constant('[]', 3)
	execute_predicate('ipc_recv', 4)
end('ipc_recv'/3):



'ipc_recv'/4:


$1:
	allocate(9)
	get_y_variable(6, 0)
	get_y_variable(5, 1)
	get_y_variable(3, 2)
	get_x_variable(0, 3)
	get_y_level(0)
	put_y_variable(4, 19)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	put_y_variable(8, 1)
	put_y_variable(7, 2)
	call_predicate('$ipc_decode_peek_options', 3, 9)
	put_y_value(6, 0)
	put_y_value(1, 1)
	put_y_value(4, 2)
	put_y_value(2, 3)
	put_y_value(8, 4)
	put_y_value(7, 5)
	call_predicate('$ipc_peek', 6, 7)
	put_y_value(6, 0)
	call_predicate('$is_not_timeout', 1, 6)
	put_y_value(4, 0)
	put_y_value(5, 1)
	call_predicate('$same_handle', 2, 4)
	put_y_value(2, 0)
	put_y_value(3, 1)
	call_predicate('$same_handle', 2, 2)
	pseudo_instr1(55, 21)
	cut(0)
	deallocate
	proceed
end('ipc_recv'/4):



'ipc_peek'/1:


$1:
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	put_constant('[]', 3)
	execute_predicate('ipc_peek', 4)
end('ipc_peek'/1):



'ipc_peek'/2:


$1:
	put_x_variable(2, 2)
	put_constant('[]', 3)
	execute_predicate('ipc_peek', 4)
end('ipc_peek'/2):



'ipc_peek'/3:


$1:
	put_constant('[]', 3)
	execute_predicate('ipc_peek', 4)
end('ipc_peek'/3):



'ipc_peek'/4:


$1:
	allocate(7)
	get_y_variable(4, 0)
	get_y_variable(3, 1)
	get_y_variable(1, 2)
	get_x_variable(0, 3)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	put_y_variable(6, 1)
	put_y_variable(5, 2)
	call_predicate('$ipc_decode_peek_options', 3, 7)
	put_y_value(4, 0)
	put_x_variable(1, 1)
	put_y_value(2, 2)
	put_y_value(0, 3)
	put_y_value(6, 4)
	put_y_value(5, 5)
	call_predicate('$ipc_peek', 6, 5)
	put_y_value(4, 0)
	call_predicate('$is_not_timeout', 1, 4)
	put_y_value(2, 0)
	put_y_value(3, 1)
	call_predicate('$same_handle', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$same_handle', 2)
end('ipc_peek'/4):



'$ipc_peek/6$0'/5:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'timeout':$4])

$4:
	try(5, $1)
	trust($2)

$5:
	try(5, $1)
	trust($2)

$1:
	put_constant('timeout', 2)
	get_x_value(0, 2)
	neck_cut
	put_constant('$$ipc_timeout$$', 0)
	get_x_value(1, 0)
	proceed

$2:
	pseudo_instr5(0, 5, 0, 6, 7, 4)
	get_x_variable(0, 5)
	get_x_value(2, 6)
	get_x_value(3, 7)
	get_x_value(1, 0)
	proceed
end('$ipc_peek/6$0'/5):



'$ipc_peek'/6:


$1:
	allocate(7)
	get_y_variable(4, 0)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	get_y_variable(6, 4)
	get_y_variable(0, 5)
	pseudo_instr1(101, 0)
	put_y_value(6, 1)
	put_y_variable(5, 2)
	call_predicate('$ipc_first_timeout', 3, 7)
	put_y_value(5, 0)
	put_y_value(3, 1)
	put_y_value(6, 2)
	call_predicate('$ipc_peek1', 3, 5)
	put_y_value(3, 0)
	put_y_value(4, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_y_value(0, 4)
	deallocate
	execute_predicate('$ipc_peek/6$0', 5)
end('$ipc_peek'/6):



'$ipc_first_timeout'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_value(0, 2)
	pseudo_instr3(68, 0, 1, 2)
	get_x_value(0, 2)
	neck_cut
	proceed

$2:
	get_constant('timeout', 2)
	proceed
end('$ipc_first_timeout'/3):



'$ipc_next_timeout/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	put_x_variable(1, 2)
	get_structure('$', 1, 2)
	unify_constant('$')
	pseudo_instr2(110, 0, 1)
	neck_cut
	fail

$2:
	proceed
end('$ipc_next_timeout/3$0'/1):



'$ipc_next_timeout'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr3(42, 0, 3, 2)
	get_x_value(1, 3)
	neck_cut
	proceed

$2:
	get_constant('timeout', 1)
	execute_predicate('$ipc_next_timeout/3$0', 1)
end('$ipc_next_timeout'/3):



'$ipc_peek1/3$0'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	proceed

$2:
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	put_y_variable(0, 1)
	call_predicate('$ipc_next_timeout', 3, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$ipc_peek1', 3)
end('$ipc_peek1/3$0'/3):



'$ipc_peek1'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'timeout':$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	get_constant('timeout', 0)
	get_constant('timeout', 1)
	neck_cut
	proceed

$2:
	execute_predicate('$ipc_peek1/3$0', 3)
end('$ipc_peek1'/3):



'$ipc_decode_peek_options/3$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_constant('block', 1)
	get_x_value(0, 1)
	proceed

$2:
	proceed
end('$ipc_decode_peek_options/3$0'/1):



'$ipc_decode_peek_options/3$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_constant('true', 1)
	get_x_value(0, 1)
	proceed

$2:
	proceed
end('$ipc_decode_peek_options/3$1'/1):



'$ipc_decode_peek_options/3$2/3$0'/3:

	switch_on_term(0, $9, $4, $4, $5, $4, $4)

$5:
	switch_on_structure(0, 8, ['$default':$4, '$'/0:$6, 'timeout'/1:$7, 'remember_names'/1:$8])

$6:
	try(3, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(3, $1)
	retry($2)
	trust($4)

$8:
	try(3, $3)
	trust($4)

$9:
	try(3, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_structure('timeout', 1, 0)
	unify_x_value(1)
	pseudo_instr1(3, 1)
	proceed

$2:
	get_structure('timeout', 1, 0)
	unify_constant('poll')
	put_integer(0, 0)
	get_x_value(1, 0)
	proceed

$3:
	get_structure('remember_names', 1, 0)
	unify_x_value(2)
	proceed

$4:
	fail
end('$ipc_decode_peek_options/3$2/3$0'/3):



'$ipc_decode_peek_options/3$2'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	fail

$2:
	execute_predicate('$ipc_decode_peek_options/3$2/3$0', 3)
end('$ipc_decode_peek_options/3$2'/3):



'$ipc_decode_peek_options'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_variable(0, 1)
	allocate(1)
	get_y_variable(0, 2)
	call_predicate('$ipc_decode_peek_options/3$0', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$ipc_decode_peek_options/3$1', 1)

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(2)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	call_predicate('$ipc_decode_peek_options/3$2', 3, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$ipc_decode_peek_options', 3)
end('$ipc_decode_peek_options'/3):



'icm_register'/1:


$1:
	put_integer(0, 1)
	put_constant('', 2)
	execute_predicate('icm_register', 3)
end('icm_register'/1):



'icm_register'/3:

	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$1:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	pseudo_instr1(2, 22)
	get_y_level(3)
	put_y_value(1, 0)
	call_predicate('number', 1, 4)
	pseudo_instr1(2, 20)
	cut(3)
	pseudo_instr3(14, 22, 21, 20)
	deallocate
	proceed

$2:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('icm_register')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('number')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(3, 4)
	set_constant('icm_register')
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
	set_constant('icm_register')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('number')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(3, 4)
	set_constant('icm_register')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	get_x_variable(3, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(3, 0)
	set_constant('icm_register')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('number')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(3, 4)
	set_constant('icm_register')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(3, 1)
	execute_predicate('instantiation_exception', 3)

$5:
	get_x_variable(3, 0)
	pseudo_instr1(46, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('icm_register')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('number')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(3, 4)
	set_constant('icm_register')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)

$6:
	get_x_variable(3, 0)
	pseudo_instr1(46, 1)
	neck_cut
	put_structure(3, 0)
	set_constant('icm_register')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('number')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(3, 4)
	set_constant('icm_register')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('type_exception', 3)

$7:
	get_x_variable(3, 0)
	pseudo_instr1(46, 2)
	neck_cut
	put_structure(3, 0)
	set_constant('icm_register')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('number')
	put_structure(1, 3)
	set_constant('@')
	set_constant('atom')
	put_structure(3, 4)
	set_constant('icm_register')
	set_x_value(1)
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(3, 1)
	execute_predicate('type_exception', 3)
end('icm_register'/3):



'icm_deregister'/0:


$1:
	allocate(0)
	call_predicate('exit_thread_gui', 0, 0)
	call_predicate('exit_debug_thread_gui', 0, 0)
	pseudo_instr1(103, 0)
	call_predicate('$close_msg_streams', 1, 0)
	pseudo_instr0(12)
	deallocate
	proceed
end('icm_deregister'/0):



'$close_msg_streams'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	allocate(1)
	put_y_variable(0, 0)
	call_predicate('member', 2, 1)
	pseudo_instr2(101, 20, 0)
	get_structure('$prop', 7, 0)
	unify_void(2)
	unify_constant('msg')
	unify_void(4)
	put_y_value(0, 0)
	call_predicate('close', 1, 0)
	fail

$2:
	proceed
end('$close_msg_streams'/1):



