'ipc_send'/2:


$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	put_y_variable(0, 0)
	call_predicate('icm_thread_handle', 1, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	put_constant('[]', 3)
	deallocate
	execute_predicate('ipc_send', 4)
end('ipc_send'/2):



'ipc_send'/3:


$1:
	put_constant('[]', 3)
	execute_predicate('ipc_send', 4)
end('ipc_send'/3):



'ipc_send'/4:


$1:
	allocate(6)
	get_y_variable(3, 0)
	get_y_variable(5, 1)
	get_y_variable(4, 2)
	get_x_variable(0, 3)
	put_y_variable(0, 1)
	call_predicate('$ipc_decode_send_options', 2, 6)
	put_y_value(5, 0)
	put_y_variable(2, 1)
	call_predicate('$symbolic_address_to_handle', 2, 5)
	put_y_value(4, 0)
	put_y_variable(1, 1)
	call_predicate('$symbolic_address_to_handle', 2, 4)
	pseudo_instr4(9, 23, 22, 21, 20)
	deallocate
	proceed
end('ipc_send'/4):



'$ipc_decode_send_options'/2:


$1:
	get_structure('$ipc_send_options', 2, 1)
	unify_x_variable(1)
	unify_x_variable(2)
	execute_predicate('$ipc_decode_send_options1', 3)
end('$ipc_decode_send_options'/2):



'$ipc_decode_send_options1/3$0'/1:

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
end('$ipc_decode_send_options1/3$0'/1):



'$ipc_decode_send_options1/3$1'/1:

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
end('$ipc_decode_send_options1/3$1'/1):



'$ipc_decode_send_options1/3$2/4$0'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(1)
	get_y_variable(0, 2)
	get_structure('remember_names', 1, 0)
	unify_x_value(1)
	cut(0)
	deallocate
	proceed

$2:
	get_structure('encode', 1, 0)
	unify_x_value(3)
	proceed
end('$ipc_decode_send_options1/3$2/4$0'/4):



'$ipc_decode_send_options1/3$2'/4:

	try(4, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	fail

$2:
	execute_predicate('$ipc_decode_send_options1/3$2/4$0', 4)
end('$ipc_decode_send_options1/3$2'/4):



'$ipc_decode_send_options1'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_variable(0, 1)
	allocate(1)
	get_y_variable(0, 2)
	call_predicate('$ipc_decode_send_options1/3$0', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$ipc_decode_send_options1/3$1', 1)

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(2)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	put_y_value(3, 2)
	put_y_value(0, 3)
	call_predicate('$ipc_decode_send_options1/3$2', 4, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$ipc_decode_send_options1', 3)
end('$ipc_decode_send_options1'/3):



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
	allocate(7)
	get_y_variable(6, 0)
	get_y_variable(5, 1)
	get_y_variable(4, 2)
	get_x_variable(0, 3)
	get_y_level(0)
	put_y_variable(3, 1)
	put_y_variable(2, 2)
	call_predicate('$ipc_decode_peek_options', 3, 7)
	put_y_value(6, 0)
	put_y_variable(1, 1)
	put_y_value(5, 2)
	put_y_value(4, 3)
	put_y_value(3, 4)
	put_y_value(2, 5)
	call_predicate('$ipc_peek', 6, 2)
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
	allocate(5)
	get_y_variable(4, 0)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_x_variable(0, 3)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$ipc_decode_peek_options', 3, 5)
	put_y_value(4, 0)
	put_x_variable(1, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_y_value(0, 5)
	deallocate
	execute_predicate('$ipc_peek', 6)
end('ipc_peek'/4):



'$ipc_peek/6$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(4)
	get_y_level(0)
	put_y_variable(2, 1)
	call_predicate('$same_handle', 2, 4)
	put_y_variable(3, 0)
	call_predicate('$msgstream_handle', 1, 4)
	put_y_value(3, 0)
	put_y_variable(1, 1)
	call_predicate('$same_handle', 2, 3)
	put_y_value(2, 0)
	get_y_value(1, 0)
	cut(0)
	fail

$2:
	proceed
end('$ipc_peek/6$0'/1):



'$ipc_peek'/6:


$1:
	allocate(8)
	get_y_variable(5, 0)
	get_y_variable(7, 1)
	get_y_variable(3, 2)
	get_y_variable(1, 3)
	get_x_variable(2, 4)
	get_y_variable(6, 5)
	pseudo_instr1(101, 0)
	pseudo_instr3(68, 0, 2, 1)
	get_x_value(0, 1)
	put_y_value(7, 1)
	call_predicate('$ipc_peek1', 3, 8)
	pseudo_instr5(0, 0, 27, 1, 2, 26)
	get_y_variable(4, 0)
	get_y_variable(2, 1)
	get_y_variable(0, 2)
	put_y_value(2, 0)
	call_predicate('$ipc_peek/6$0', 1, 6)
	put_y_value(5, 0)
	get_y_value(4, 0)
	put_y_value(2, 0)
	put_y_value(3, 1)
	call_predicate('$same_handle', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$same_handle', 2)
end('$ipc_peek'/6):



'$ipc_peek1/3$0'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	proceed

$2:
	pseudo_instr3(42, 0, 3, 2)
	get_x_variable(0, 3)
	execute_predicate('$ipc_peek1', 3)
end('$ipc_peek1/3$0'/3):



'$ipc_peek1'/3:


$1:
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

	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_structure('timeout', 1, 0)
	unify_x_value(1)
	proceed

$2:
	get_structure('remember_names', 1, 0)
	unify_x_value(2)
	proceed

$3:
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
	allocate(3)
	unify_y_variable(2)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	call_predicate('$ipc_decode_peek_options/3$2', 3, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$ipc_decode_peek_options', 3)
end('$ipc_decode_peek_options'/3):



