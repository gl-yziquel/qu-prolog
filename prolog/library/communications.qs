'->>'/2:

	try(2, $1)
	trust($2)

$1:
	get_structure('reply_to', 2, 1)
	unify_x_variable(1)
	unify_x_variable(2)
	neck_cut
	put_structure(1, 4)
	set_constant('remember_names')
	set_constant('false')
	put_list(3)
	set_x_value(4)
	set_constant('[]')
	execute_predicate('ipc_send', 4)

$2:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	put_y_variable(0, 0)
	call_predicate('icm_thread_handle', 1, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	put_structure(1, 4)
	set_constant('remember_names')
	set_constant('false')
	put_list(3)
	set_x_value(4)
	set_constant('[]')
	deallocate
	execute_predicate('ipc_send', 4)
end('->>'/2):



'+>>'/2:

	try(2, $1)
	trust($2)

$1:
	get_structure('reply_to', 2, 1)
	unify_x_variable(1)
	unify_x_variable(2)
	neck_cut
	put_structure(1, 4)
	set_constant('encode')
	set_constant('false')
	put_list(3)
	set_x_value(4)
	set_constant('[]')
	execute_predicate('ipc_send', 4)

$2:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	put_y_value(1, 0)
	put_x_variable(1, 1)
	call_predicate('symbolic_address_to_icm_handle', 2, 3)
	put_y_variable(0, 0)
	call_predicate('icm_thread_handle', 1, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	put_structure(1, 4)
	set_constant('encode')
	set_constant('false')
	put_list(3)
	set_x_value(4)
	set_constant('[]')
	deallocate
	execute_predicate('ipc_send', 4)
end('+>>'/2):



'symbolic_address_to_icm_handle/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	put_constant('localhost', 2)
	get_x_value(0, 2)
	neck_cut
	put_structure(2, 2)
	set_constant(':')
	set_void(2)
	put_structure(2, 0)
	set_constant('@')
	set_x_value(2)
	set_x_value(1)
	execute_predicate('icm_thread_handle', 1)

$2:
	pseudo_instr2(79, 0, 2)
	get_x_variable(0, 2)
	pseudo_instr2(80, 2, 0)
	get_x_value(1, 2)
	proceed
end('symbolic_address_to_icm_handle/2$0'/2):



'symbolic_address_to_icm_handle/2$1'/2:

	try(2, $1)
	trust($2)

$1:
	put_constant('localhost', 2)
	get_x_value(0, 2)
	neck_cut
	put_structure(2, 2)
	set_constant(':')
	set_void(2)
	put_structure(2, 0)
	set_constant('@')
	set_x_value(2)
	set_x_value(1)
	execute_predicate('icm_thread_handle', 1)

$2:
	pseudo_instr2(79, 0, 2)
	get_x_variable(0, 2)
	pseudo_instr2(80, 2, 0)
	get_x_value(1, 2)
	proceed
end('symbolic_address_to_icm_handle/2$1'/2):



'symbolic_address_to_icm_handle'/2:

	switch_on_term(0, $15, $14, $14, $7, $14, $12)

$7:
	switch_on_structure(0, 8, ['default':$14, '$'/0:$8, ':'/2:$9, '@'/2:$10, '/'/2:$11])

$8:
	try(2, $1)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$9:
	try(2, $1)
	retry($3)
	trust($4)

$10:
	try(2, $1)
	retry($3)
	trust($5)

$11:
	try(2, $1)
	retry($3)
	trust($6)

$12:
	switch_on_constant(0, 4, ['default':$14, 'self':$13])

$13:
	try(2, $1)
	retry($2)
	trust($3)

$14:
	try(2, $1)
	trust($3)

$15:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('symbolic_address_to_icm_handle')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('compound')
	put_structure(1, 2)
	set_constant('?')
	set_constant('compound')
	put_structure(2, 3)
	set_constant('symbolic_address_to_icm_handle')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_constant('self', 0)
	get_x_variable(0, 1)
	neck_cut
	execute_predicate('icm_thread_handle', 1)

$3:
	allocate(5)
	get_y_variable(4, 0)
	get_y_variable(3, 1)
	pseudo_instr1(43, 24)
	neck_cut
	put_structure(2, 0)
	set_constant(':')
	set_void(1)
	set_y_variable(2)
	put_structure(2, 1)
	set_constant('@')
	set_x_value(0)
	set_y_variable(1)
	put_structure(2, 0)
	set_constant('/')
	set_x_value(1)
	set_y_variable(0)
	call_predicate('icm_thread_handle', 1, 5)
	put_y_value(3, 0)
	get_structure('/', 2, 0)
	unify_x_ref(0)
	unify_y_value(0)
	get_structure('@', 2, 0)
	unify_x_ref(0)
	unify_y_value(1)
	get_structure(':', 2, 0)
	unify_y_value(4)
	unify_y_value(2)
	deallocate
	proceed

$4:
	get_structure(':', 2, 0)
	allocate(5)
	unify_y_variable(4)
	unify_y_variable(3)
	get_y_variable(2, 1)
	pseudo_instr1(43, 24)
	pseudo_instr1(2, 23)
	neck_cut
	put_structure(2, 0)
	set_constant(':')
	set_void(2)
	put_structure(2, 1)
	set_constant('@')
	set_x_value(0)
	set_y_variable(1)
	put_structure(2, 0)
	set_constant('/')
	set_x_value(1)
	set_y_variable(0)
	call_predicate('icm_thread_handle', 1, 5)
	put_y_value(2, 0)
	get_structure('/', 2, 0)
	unify_x_ref(0)
	unify_y_value(0)
	get_structure('@', 2, 0)
	unify_x_ref(0)
	unify_y_value(1)
	get_structure(':', 2, 0)
	unify_y_value(4)
	unify_y_value(3)
	deallocate
	proceed

$5:
	get_structure('@', 2, 0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure(':', 2, 2)
	allocate(4)
	unify_y_variable(3)
	unify_y_variable(2)
	get_y_variable(1, 1)
	pseudo_instr1(43, 23)
	pseudo_instr1(2, 22)
	pseudo_instr1(2, 0)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('symbolic_address_to_icm_handle/2$0', 2, 4)
	put_y_value(1, 0)
	get_structure('/', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('@', 2, 0)
	unify_x_ref(0)
	unify_y_value(0)
	get_structure(':', 2, 0)
	unify_y_value(3)
	unify_y_value(2)
	get_list(1)
	unify_y_value(0)
	unify_constant('[]')
	deallocate
	proceed

$6:
	get_structure('/', 2, 0)
	unify_x_ref(0)
	allocate(6)
	unify_y_variable(5)
	get_structure('@', 2, 0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure(':', 2, 2)
	unify_y_variable(4)
	unify_y_variable(3)
	get_y_variable(2, 1)
	pseudo_instr1(43, 24)
	pseudo_instr1(2, 23)
	pseudo_instr1(2, 0)
	neck_cut
	put_y_variable(1, 1)
	call_predicate('symbolic_address_to_icm_handle/2$1', 2, 6)
	put_y_value(5, 0)
	put_y_variable(0, 1)
	call_predicate('$process_locations', 2, 5)
	put_y_value(2, 0)
	get_structure('/', 2, 0)
	unify_x_ref(0)
	unify_y_value(0)
	get_structure('@', 2, 0)
	unify_x_ref(0)
	unify_y_value(1)
	get_structure(':', 2, 0)
	unify_y_value(4)
	unify_y_value(3)
	deallocate
	proceed
end('symbolic_address_to_icm_handle'/2):



'$symbolic_address_to_handle'/2:


$1:
	allocate(5)
	get_y_variable(0, 1)
	put_structure(2, 1)
	set_constant(':')
	set_y_variable(4)
	set_y_variable(3)
	put_structure(2, 2)
	set_constant('@')
	set_x_value(1)
	set_y_variable(2)
	put_structure(2, 1)
	set_constant('/')
	set_x_value(2)
	set_y_variable(1)
	call_predicate('symbolic_address_to_icm_handle', 2, 5)
	pseudo_instr5(2, 24, 23, 22, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$symbolic_address_to_handle'/2):



'icm_handle_to_components'/5:


$1:
	get_structure('/', 2, 4)
	unify_x_ref(4)
	unify_x_value(3)
	get_structure('@', 2, 4)
	unify_x_ref(3)
	unify_x_value(2)
	get_structure(':', 2, 3)
	unify_x_value(0)
	unify_x_value(1)
	proceed
end('icm_handle_to_components'/5):



'$process_locations/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	put_constant('localhost', 2)
	get_x_value(0, 2)
	neck_cut
	put_structure(2, 2)
	set_constant(':')
	set_void(2)
	put_structure(2, 0)
	set_constant('@')
	set_x_value(2)
	set_x_value(1)
	execute_predicate('icm_thread_handle', 1)

$2:
	pseudo_instr2(79, 0, 2)
	get_x_variable(0, 2)
	pseudo_instr2(80, 2, 0)
	get_x_value(1, 2)
	proceed
end('$process_locations/2$0'/2):



'$process_locations'/2:

	switch_on_term(0, $7, $1, $4, $1, $1, $5)

$4:
	try(2, $1)
	trust($3)

$5:
	switch_on_constant(0, 4, ['default':$1, '[]':$6])

$6:
	try(2, $1)
	trust($2)

$7:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	fail

$2:
	get_constant('[]', 0)
	get_constant('[]', 1)
	proceed

$3:
	get_list(0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(0)
	pseudo_instr1(2, 0)
	call_predicate('$process_locations/2$0', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$process_locations', 2)
end('$process_locations'/2):



'icm_handle_to_symbolic_address'/2:

	switch_on_term(0, $8, $7, $7, $4, $7, $7)

$4:
	switch_on_structure(0, 4, ['default':$7, '$'/0:$5, '/'/2:$6])

$5:
	try(2, $1)
	retry($2)
	trust($3)

$6:
	try(2, $1)
	retry($2)
	trust($3)

$7:
	try(2, $1)
	trust($2)

$8:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('icm_handle_to_symbolic_address')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('compound')
	put_structure(1, 2)
	set_constant('?')
	set_constant('compound')
	put_structure(2, 3)
	set_constant('icm_handle_to_symbolic_address')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	pseudo_instr1(1, 1)
	get_x_value(1, 0)
	neck_cut
	proceed

$3:
	get_structure('/', 2, 0)
	unify_x_ref(0)
	allocate(6)
	unify_y_variable(1)
	get_structure('@', 2, 0)
	unify_x_ref(0)
	unify_y_variable(2)
	get_structure(':', 2, 0)
	unify_y_variable(4)
	unify_y_variable(3)
	get_y_variable(0, 1)
	put_y_variable(5, 0)
	call_predicate('icm_thread_handle', 1, 6)
	put_y_value(5, 0)
	get_structure('/', 2, 0)
	unify_x_ref(0)
	unify_void(1)
	get_structure('@', 2, 0)
	unify_x_ref(0)
	unify_x_variable(6)
	get_structure(':', 2, 0)
	unify_x_variable(4)
	unify_x_variable(5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	put_y_value(0, 7)
	deallocate
	execute_predicate('$build_handle', 8)
end('icm_handle_to_symbolic_address'/2):



'$build_handle/8$0'/2:

	try(2, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_variable(0)
	unify_constant('[]')
	pseudo_instr2(79, 1, 2)
	get_x_variable(1, 2)
	pseudo_instr2(79, 0, 2)
	get_x_value(1, 2)
	neck_cut
	fail

$2:
	proceed
end('$build_handle/8$0'/2):



'$build_handle'/8:

	try(8, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	allocate(6)
	get_y_variable(5, 0)
	get_y_variable(4, 1)
	get_y_variable(1, 2)
	get_y_variable(3, 3)
	get_y_variable(2, 7)
	get_y_level(0)
	put_y_value(3, 0)
	put_y_value(1, 1)
	call_predicate('$build_handle/8$0', 2, 6)
	put_y_value(2, 0)
	get_structure('/', 2, 0)
	unify_x_ref(0)
	unify_y_value(3)
	get_structure('@', 2, 0)
	unify_x_ref(0)
	unify_x_variable(1)
	get_structure(':', 2, 0)
	unify_y_value(5)
	unify_y_value(4)
	put_y_value(1, 0)
	call_predicate('$same_host', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_x_variable(8, 0)
	get_x_variable(0, 2)
	get_x_value(8, 4)
	get_x_value(1, 5)
	get_x_variable(1, 6)
	allocate(2)
	get_y_variable(1, 7)
	get_y_level(0)
	call_predicate('$same_host', 2, 2)
	put_y_value(1, 0)
	get_constant('self', 0)
	cut(0)
	deallocate
	proceed

$3:
	get_x_variable(8, 0)
	get_x_variable(0, 2)
	get_x_value(1, 5)
	get_x_variable(1, 6)
	get_x_value(8, 7)
	allocate(1)
	get_y_level(0)
	call_predicate('$same_host', 2, 1)
	cut(0)
	deallocate
	proceed

$4:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_x_variable(0, 2)
	get_x_variable(1, 6)
	get_y_variable(1, 7)
	get_y_level(0)
	call_predicate('$same_host', 2, 4)
	put_y_value(1, 0)
	get_structure(':', 2, 0)
	unify_y_value(3)
	unify_y_value(2)
	cut(0)
	deallocate
	proceed

$5:
	get_x_variable(8, 0)
	get_x_variable(9, 1)
	get_x_variable(0, 2)
	put_x_value(7, 1)
	get_structure('@', 2, 1)
	unify_x_ref(2)
	unify_x_variable(1)
	get_structure(':', 2, 2)
	unify_x_value(8)
	unify_x_value(9)
	allocate(1)
	get_y_level(0)
	call_predicate('$same_host', 2, 1)
	cut(0)
	deallocate
	proceed

$6:
	get_x_variable(8, 0)
	get_x_variable(9, 1)
	get_x_variable(0, 2)
	allocate(2)
	get_y_variable(1, 3)
	put_x_value(7, 1)
	get_structure('/', 2, 1)
	unify_x_ref(1)
	unify_y_variable(0)
	get_structure('@', 2, 1)
	unify_x_ref(2)
	unify_x_variable(1)
	get_structure(':', 2, 2)
	unify_x_value(8)
	unify_x_value(9)
	call_predicate('$same_host', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$same_locs', 2)
end('$build_handle'/8):



'$same_host/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	put_constant('localhost', 1)
	pseudo_instr2(110, 0, 1)
	proceed

$2:
	put_constant('LOCALHOST', 1)
	pseudo_instr2(110, 0, 1)
	proceed
end('$same_host/2$0'/1):



'$same_host/2$1'/1:

	try(1, $1)
	trust($2)

$1:
	put_constant('localhost', 1)
	pseudo_instr2(110, 0, 1)
	proceed

$2:
	put_constant('LOCALHOST', 1)
	pseudo_instr2(110, 0, 1)
	proceed
end('$same_host/2$1'/1):



'$same_host'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	call_predicate('$same_host/2$0', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant(':')
	set_void(2)
	put_structure(2, 1)
	set_constant('@')
	set_x_value(0)
	set_y_variable(0)
	put_structure(2, 0)
	set_constant('/')
	set_x_value(1)
	set_void(1)
	call_predicate('icm_thread_handle', 1, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$same_host', 2)

$2:
	allocate(3)
	get_y_variable(1, 0)
	get_x_variable(0, 1)
	get_y_level(2)
	call_predicate('$same_host/2$1', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant(':')
	set_void(2)
	put_structure(2, 1)
	set_constant('@')
	set_x_value(0)
	set_y_variable(0)
	put_structure(2, 0)
	set_constant('/')
	set_x_value(1)
	set_void(1)
	call_predicate('icm_thread_handle', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$same_host', 2)

$3:
	get_x_value(0, 1)
	neck_cut
	proceed

$4:
	pseudo_instr2(79, 0, 2)
	get_x_variable(0, 2)
	pseudo_instr2(79, 1, 2)
	get_x_value(0, 2)
	proceed
end('$same_host'/2):



'$same_locs'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('[]', 1)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(0)
	call_predicate('$same_host', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$same_locs', 2)
end('$same_locs'/2):



'same_handle'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	pseudo_instr2(67, 2, 0)
	get_list(0)
	unify_void(2)
	neck_cut
	put_structure(2, 0)
	set_constant('same_handle')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('term')
	put_structure(1, 2)
	set_constant('?')
	set_constant('term')
	put_structure(2, 3)
	set_constant('same_handle')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(2)
	get_y_variable(1, 1)
	put_y_variable(0, 1)
	call_predicate('symbolic_address_to_icm_handle', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('icm_handle_to_symbolic_address', 2)
end('same_handle'/2):



'$same_handle'/2:


$1:
	get_structure('$icm_handle', 4, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	unify_x_variable(3)
	unify_x_variable(4)
	put_structure(2, 5)
	set_constant(':')
	set_x_value(0)
	set_x_value(2)
	put_structure(2, 2)
	set_constant('@')
	set_x_value(5)
	set_x_value(3)
	put_structure(2, 0)
	set_constant('/')
	set_x_value(2)
	set_x_value(4)
	execute_predicate('same_handle', 2)
end('$same_handle'/2):



'<<-/2$0/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	get_structure('reply_to', 2, 0)
	unify_void(2)
	neck_cut
	fail

$2:
	proceed
end('<<-/2$0/1$0'/1):



'<<-/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	proceed

$2:
	execute_predicate('<<-/2$0/1$0', 1)
end('<<-/2$0'/1):



'<<-'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(5)
	get_y_variable(1, 0)
	get_y_variable(3, 1)
	get_y_level(4)
	put_y_value(3, 0)
	call_predicate('<<-/2$0', 1, 5)
	cut(4)
	put_y_variable(0, 0)
	put_y_variable(2, 1)
	put_x_variable(2, 2)
	put_structure(1, 4)
	set_constant('remember_names')
	set_constant('false')
	put_list(3)
	set_x_value(4)
	set_constant('[]')
	call_predicate('ipc_recv', 4, 4)
	put_y_value(2, 0)
	put_y_value(3, 1)
	call_predicate('same_handle', 2, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	allocate(7)
	get_y_variable(1, 0)
	get_structure('reply_to', 2, 1)
	unify_y_variable(5)
	unify_y_variable(3)
	get_y_level(6)
	put_y_variable(0, 0)
	put_y_variable(4, 1)
	put_y_variable(2, 2)
	put_structure(1, 4)
	set_constant('remember_names')
	set_constant('false')
	put_list(3)
	set_x_value(4)
	set_constant('[]')
	call_predicate('ipc_recv', 4, 7)
	cut(6)
	put_y_value(4, 0)
	put_y_value(5, 1)
	call_predicate('same_handle', 2, 4)
	put_y_value(2, 0)
	put_y_value(3, 1)
	call_predicate('same_handle', 2, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('<<-'/2):



'<<=/2$0/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	get_structure('reply_to', 2, 0)
	unify_void(2)
	neck_cut
	fail

$2:
	proceed
end('<<=/2$0/1$0'/1):



'<<=/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	proceed

$2:
	execute_predicate('<<=/2$0/1$0', 1)
end('<<=/2$0'/1):



'<<='/2:

	try(2, $1)
	trust($2)

$1:
	allocate(5)
	get_y_variable(3, 0)
	get_y_variable(4, 1)
	get_y_level(0)
	put_y_value(4, 0)
	call_predicate('<<=/2$0', 1, 5)
	cut(0)
	put_y_variable(2, 0)
	put_y_variable(1, 1)
	put_y_value(4, 2)
	put_x_variable(3, 3)
	put_constant('block', 4)
	put_constant('false', 5)
	call_predicate('$ipc_peek', 6, 4)
	put_y_value(3, 0)
	get_y_value(2, 0)
	pseudo_instr1(55, 21)
	cut(0)
	deallocate
	proceed

$2:
	allocate(4)
	get_y_variable(3, 0)
	get_structure('reply_to', 2, 1)
	unify_x_variable(2)
	unify_x_variable(3)
	get_y_level(0)
	put_y_variable(2, 0)
	put_y_variable(1, 1)
	put_constant('block', 4)
	put_constant('false', 5)
	call_predicate('$ipc_peek', 6, 4)
	put_y_value(3, 0)
	get_y_value(2, 0)
	pseudo_instr1(55, 21)
	cut(0)
	deallocate
	proceed
end('<<='/2):



'$mc_inline/2$0'/8:

	try(8, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_x_value(1, 0)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_x_value(6)
	get_structure('$ipc_peek', 6, 0)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	unify_x_value(5)
	unify_constant('block')
	unify_constant('false')
	proceed

$2:
	get_structure(';', 2, 1)
	unify_x_ref(1)
	unify_x_value(7)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_value(6)
	get_structure('$ipc_peek', 6, 1)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	unify_x_value(5)
	unify_x_value(0)
	unify_constant('false')
	proceed
end('$mc_inline/2$0'/8):



'$mc_inline'/2:


$1:
	allocate(8)
	get_y_variable(7, 1)
	put_y_variable(6, 1)
	put_y_variable(5, 2)
	put_y_variable(4, 3)
	put_y_variable(3, 4)
	put_y_variable(2, 5)
	put_y_variable(1, 6)
	put_y_variable(0, 7)
	call_predicate('$mc_gen_choices', 8, 8)
	put_y_value(1, 0)
	put_y_value(7, 1)
	put_y_value(5, 2)
	put_y_value(4, 3)
	put_y_value(3, 4)
	put_y_value(2, 5)
	put_y_value(6, 6)
	put_y_value(0, 7)
	deallocate
	execute_predicate('$mc_inline/2$0', 8)
end('$mc_inline'/2):



'$mc_gen_choices'/8:

	switch_on_term(0, $9, $4, $4, $5, $4, $4)

$5:
	switch_on_structure(0, 8, ['default':$4, '$'/0:$6, ';'/2:$7, '->'/2:$8])

$6:
	try(8, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(8, $1)
	retry($2)
	trust($4)

$8:
	try(8, $3)
	trust($4)

$9:
	try(8, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant('fail', 1)
	get_structure(';', 2, 0)
	unify_x_ref(0)
	unify_void(1)
	get_structure('->', 2, 0)
	unify_x_ref(0)
	unify_x_variable(1)
	get_structure('timeout', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 6)
	get_x_value(1, 7)
	neck_cut
	proceed

$2:
	get_structure(';', 2, 0)
	unify_x_variable(0)
	allocate(8)
	unify_y_variable(7)
	get_structure(';', 2, 1)
	unify_x_variable(1)
	unify_y_variable(6)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	get_y_variable(3, 4)
	get_y_variable(2, 5)
	get_y_variable(1, 6)
	get_y_variable(0, 7)
	neck_cut
	call_predicate('$mc_choice_to_code', 6, 8)
	put_y_value(7, 0)
	put_y_value(6, 1)
	put_y_value(5, 2)
	put_y_value(4, 3)
	put_y_value(3, 4)
	put_y_value(2, 5)
	put_y_value(1, 6)
	put_y_value(0, 7)
	deallocate
	execute_predicate('$mc_gen_choices', 8)

$3:
	get_constant('fail', 1)
	get_structure('->', 2, 0)
	unify_x_ref(0)
	unify_x_variable(1)
	get_structure('timeout', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 6)
	get_x_value(1, 7)
	neck_cut
	proceed

$4:
	get_structure(';', 2, 1)
	unify_x_variable(1)
	unify_constant('fail')
	neck_cut
	execute_predicate('$mc_choice_to_code', 6)
end('$mc_gen_choices'/8):



'$mc_choice_to_code'/6:

	switch_on_term(0, $6, 'fail', 'fail', $3, 'fail', 'fail')

$3:
	switch_on_structure(0, 4, ['default':'fail', '$'/0:$4, '->'/2:$5])

$4:
	try(6, $1)
	trust($2)

$5:
	try(6, $1)
	trust($2)

$6:
	try(6, $1)
	trust($2)

$1:
	get_structure('->', 2, 0)
	unify_x_ref(0)
	allocate(5)
	unify_y_variable(3)
	get_structure('::', 2, 0)
	unify_x_variable(0)
	unify_y_variable(4)
	get_y_variable(2, 1)
	get_y_variable(1, 3)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$mc_get_msg_addr_code', 6, 5)
	put_y_value(2, 0)
	get_structure('->', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure(',', 2, 0)
	unify_y_value(0)
	unify_y_value(4)
	get_structure(',', 2, 1)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('$ipc_commit', 1, 0)
	unify_y_value(1)
	get_structure(',', 2, 1)
	unify_constant('!')
	unify_y_value(3)
	deallocate
	proceed

$2:
	get_structure('->', 2, 0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(3)
	get_y_variable(2, 1)
	get_y_variable(1, 3)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$mc_get_msg_addr_code', 6, 4)
	put_y_value(2, 0)
	get_structure('->', 2, 0)
	unify_y_value(0)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('$ipc_commit', 1, 0)
	unify_y_value(1)
	get_structure(',', 2, 1)
	unify_constant('!')
	unify_y_value(3)
	deallocate
	proceed
end('$mc_choice_to_code'/6):



'$mc_get_msg_addr_code/6$0'/6:

	try(6, $1)
	trust($2)

$1:
	pseudo_instr1(46, 0)
	get_structure('reply_to', 2, 0)
	unify_x_variable(0)
	unify_x_variable(6)
	neck_cut
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_ref(7)
	get_structure('same_handle', 2, 1)
	unify_x_value(2)
	unify_x_value(0)
	get_structure(',', 2, 7)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('same_handle', 2, 0)
	unify_x_value(3)
	unify_x_value(6)
	get_structure('=', 2, 1)
	unify_x_value(4)
	unify_x_value(5)
	proceed

$2:
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_ref(3)
	get_structure('same_handle', 2, 1)
	unify_x_value(2)
	unify_x_value(0)
	get_structure('=', 2, 3)
	unify_x_value(4)
	unify_x_value(5)
	proceed
end('$mc_get_msg_addr_code/6$0'/6):



'$mc_get_msg_addr_code'/6:


$1:
	get_structure('<<-', 2, 0)
	unify_x_variable(6)
	unify_x_variable(0)
	get_x_variable(7, 2)
	get_x_variable(2, 4)
	get_x_variable(3, 5)
	put_x_value(6, 4)
	put_x_value(7, 5)
	execute_predicate('$mc_get_msg_addr_code/6$0', 6)
end('$mc_get_msg_addr_code'/6):



'$query_communications2002_9_26_11_20_10_158/0$0'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(452, 0)
	put_constant('xfx', 1)
	put_constant('->>', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications2002_9_26_11_20_10_158/0$0'/0):



'$query_communications2002_9_26_11_20_10_158/0$1'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(452, 0)
	put_constant('xfx', 1)
	put_constant('+>>', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications2002_9_26_11_20_10_158/0$1'/0):



'$query_communications2002_9_26_11_20_10_158/0$2'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(452, 0)
	put_constant('xfx', 1)
	put_constant('<<-', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications2002_9_26_11_20_10_158/0$2'/0):



'$query_communications2002_9_26_11_20_10_158/0$3'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(452, 0)
	put_constant('xfx', 1)
	put_constant('<<=', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications2002_9_26_11_20_10_158/0$3'/0):



'$query_communications2002_9_26_11_20_10_158/0$4'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(451, 0)
	put_constant('xfx', 1)
	put_constant('reply_to', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications2002_9_26_11_20_10_158/0$4'/0):



'$query_communications2002_9_26_11_20_10_158/0$5'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(500, 0)
	put_constant('fy', 1)
	put_constant('message_choice', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications2002_9_26_11_20_10_158/0$5'/0):



'$query_communications2002_9_26_11_20_10_158/0$6'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(50, 0)
	put_constant('xfx', 1)
	put_constant(':', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications2002_9_26_11_20_10_158/0$6'/0):



'$query_communications2002_9_26_11_20_10_158/0$7'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(1024, 0)
	put_constant('xfx', 1)
	put_constant('::', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications2002_9_26_11_20_10_158/0$7'/0):



'$query_communications2002_9_26_11_20_10_158/0$8'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(100, 0)
	put_constant('xfx', 1)
	put_constant('@', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications2002_9_26_11_20_10_158/0$8'/0):



'$query_communications2002_9_26_11_20_10_158/0$9'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_structure(1, 0)
	set_constant('message_choice')
	set_x_variable(3)
	put_x_variable(4, 1)
	put_structure(2, 2)
	set_constant('$mc_inline')
	set_x_value(3)
	set_x_value(4)
	call_predicate('inline', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications2002_9_26_11_20_10_158/0$9'/0):



'$query_communications2002_9_26_11_20_10_158'/0:

	try(0, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	retry($10)
	trust($11)

$1:
	allocate(0)
	call_predicate('$query_communications2002_9_26_11_20_10_158/0$0', 0, 0)
	fail

$2:
	allocate(0)
	call_predicate('$query_communications2002_9_26_11_20_10_158/0$1', 0, 0)
	fail

$3:
	allocate(0)
	call_predicate('$query_communications2002_9_26_11_20_10_158/0$2', 0, 0)
	fail

$4:
	allocate(0)
	call_predicate('$query_communications2002_9_26_11_20_10_158/0$3', 0, 0)
	fail

$5:
	allocate(0)
	call_predicate('$query_communications2002_9_26_11_20_10_158/0$4', 0, 0)
	fail

$6:
	allocate(0)
	call_predicate('$query_communications2002_9_26_11_20_10_158/0$5', 0, 0)
	fail

$7:
	allocate(0)
	call_predicate('$query_communications2002_9_26_11_20_10_158/0$6', 0, 0)
	fail

$8:
	allocate(0)
	call_predicate('$query_communications2002_9_26_11_20_10_158/0$7', 0, 0)
	fail

$9:
	allocate(0)
	call_predicate('$query_communications2002_9_26_11_20_10_158/0$8', 0, 0)
	fail

$10:
	allocate(0)
	call_predicate('$query_communications2002_9_26_11_20_10_158/0$9', 0, 0)
	fail

$11:
	proceed
end('$query_communications2002_9_26_11_20_10_158'/0):



'$query'/0:


$1:
	execute_predicate('$query_communications2002_9_26_11_20_10_158', 0)
end('$query'/0):



