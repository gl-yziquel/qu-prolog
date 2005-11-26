'$thread_id'/1:


$1:
	pseudo_instr1(3, 0)
	proceed
end('$thread_id'/1):



'thread_symbol'/1:


$1:
	pseudo_instr1(68, 1)
	pseudo_instr2(82, 1, 0)
	proceed
end('thread_symbol'/1):



'thread_fork'/2:


$1:
	put_constant('[]', 2)
	execute_predicate('thread_fork', 3)
end('thread_fork'/2):



'thread_fork'/3:


$1:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(3, 2)
	put_y_variable(0, 19)
	call_predicate('$thread_fork_ok', 1, 4)
	put_y_value(3, 0)
	put_y_value(0, 1)
	call_predicate('$thread_decode_sizes', 2, 3)
	pseudo_instr3(56, 22, 21, 20)
	deallocate
	proceed
end('thread_fork'/3):



'$thread_fork_ok/1$0'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'self':$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_constant('self', 1)
	get_x_value(0, 1)
	neck_cut
	fail

$2:
	proceed
end('$thread_fork_ok/1$0'/1):



'$thread_fork_ok/1$1'/1:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'elvin':$4])

$4:
	try(1, $1)
	trust($2)

$5:
	try(1, $1)
	trust($2)

$1:
	put_constant('elvin', 1)
	get_x_value(0, 1)
	neck_cut
	fail

$2:
	proceed
end('$thread_fork_ok/1$1'/1):



'$thread_fork_ok'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	proceed

$2:
	allocate(1)
	get_y_variable(0, 0)
	call_predicate('$thread_fork_ok/1$0', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$thread_fork_ok/1$1', 1)
end('$thread_fork_ok'/1):



'thread_suspend'/0:


$1:
	pseudo_instr1(68, 0)
	pseudo_instr1(69, 0)
	proceed
end('thread_suspend'/0):



'thread_wait'/0:


$1:
	put_constant('[]', 0)
	execute_predicate('thread_wait', 1)
end('thread_wait'/0):



'thread_wait'/1:


$1:
	allocate(3)
	put_y_variable(2, 1)
	put_y_variable(1, 2)
	put_y_variable(0, 3)
	call_predicate('$thread_wait_conditions', 4, 3)
	put_x_variable(0, 1)
	get_structure('$thread_wait_conditions', 3, 1)
	unify_y_value(2)
	unify_y_value(1)
	unify_y_value(0)
	pseudo_instr1(71, 0)
	deallocate
	proceed
end('thread_wait'/1):



'$thread_wait_conditions/4$0'/1:

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
end('$thread_wait_conditions/4$0'/1):



'$thread_wait_conditions/4$1'/1:

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
end('$thread_wait_conditions/4$1'/1):



'$thread_wait_conditions/4$2'/1:

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
end('$thread_wait_conditions/4$2'/1):



'$thread_wait_conditions/4$3/4$0'/4:

	switch_on_term(0, $10, $4, $4, $5, $4, $4)

$5:
	switch_on_structure(0, 8, ['$default':$4, '$'/0:$6, 'db'/1:$7, 'record_db'/1:$8, 'timeout'/1:$9])

$6:
	try(4, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(4, $1)
	trust($4)

$8:
	try(4, $2)
	trust($4)

$9:
	try(4, $3)
	trust($4)

$10:
	try(4, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_structure('db', 1, 0)
	unify_x_value(1)
	proceed

$2:
	get_structure('record_db', 1, 0)
	unify_x_value(2)
	proceed

$3:
	get_structure('timeout', 1, 0)
	unify_x_value(3)
	proceed

$4:
	fail
end('$thread_wait_conditions/4$3/4$0'/4):



'$thread_wait_conditions/4$3'/4:

	try(4, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	fail

$2:
	execute_predicate('$thread_wait_conditions/4$3/4$0', 4)
end('$thread_wait_conditions/4$3'/4):



'$thread_wait_conditions'/4:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(4, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_variable(0, 1)
	allocate(2)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	neck_cut
	call_predicate('$thread_wait_conditions/4$0', 1, 2)
	put_y_value(1, 0)
	call_predicate('$thread_wait_conditions/4$1', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$thread_wait_conditions/4$2', 1)

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(5)
	unify_y_variable(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	neck_cut
	get_y_level(4)
	call_predicate('$thread_wait_conditions/4$3', 4, 5)
	cut(4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$thread_wait_conditions', 4)
end('$thread_wait_conditions'/4):



'thread_wait_on_goal/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('call', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	put_structure(1, 0)
	set_constant('record_db')
	set_constant('true')
	put_list(1)
	set_x_value(0)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('db')
	set_constant('true')
	put_list(0)
	set_x_value(2)
	set_x_value(1)
	allocate(0)
	call_predicate('thread_wait', 1, 0)
	fail
end('thread_wait_on_goal/1$0'/1):



'thread_wait_on_goal'/1:


$1:
	allocate(2)
	get_y_variable(1, 0)
	get_y_level(0)
	call_predicate('repeat', 0, 2)
	put_y_value(1, 0)
	call_predicate('thread_wait_on_goal/1$0', 1, 1)
	cut(0)
	deallocate
	proceed
end('thread_wait_on_goal'/1):



'thread_wait_on_goal/2$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 2)
	get_y_level(0)
	call_predicate('$check_pred_stamps', 2, 2)
	put_y_value(1, 0)
	call_predicate('call', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	put_structure(1, 0)
	set_constant('record_db')
	set_constant('true')
	put_list(1)
	set_x_value(0)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('db')
	set_constant('true')
	put_list(0)
	set_x_value(2)
	set_x_value(1)
	allocate(0)
	call_predicate('thread_wait', 1, 0)
	fail
end('thread_wait_on_goal/2$0'/3):



'thread_wait_on_goal'/2:


$1:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_level(0)
	put_y_value(2, 0)
	put_y_variable(1, 1)
	call_predicate('$get_pred_stamps', 2, 4)
	call_predicate('repeat', 0, 4)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(3, 2)
	call_predicate('thread_wait_on_goal/2$0', 3, 1)
	cut(0)
	deallocate
	proceed
end('thread_wait_on_goal'/2):



'$get_pred_stamps'/2:

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
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure('/', 2, 2)
	unify_x_variable(2)
	unify_x_variable(3)
	get_list(1)
	unify_x_variable(4)
	unify_x_variable(1)
	pseudo_instr1(2, 2)
	pseudo_instr1(3, 3)
	pseudo_instr3(72, 2, 3, 5)
	get_x_value(4, 5)
	execute_predicate('$get_pred_stamps', 2)
end('$get_pred_stamps'/2):



'$check_pred_stamps'/2:

	switch_on_term(0, $3, 'fail', $3, 'fail', 'fail', 'fail')

$3:
	try(2, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_ref(0)
	unify_void(1)
	get_structure('/', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_list(1)
	unify_x_variable(1)
	unify_void(1)
	pseudo_instr3(72, 0, 2, 3)
	get_x_variable(0, 3)
	pseudo_instr2(1, 1, 0)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_void(1)
	unify_x_variable(0)
	get_list(1)
	unify_void(1)
	unify_x_variable(1)
	execute_predicate('$check_pred_stamps', 2)
end('$check_pred_stamps'/2):



'thread_sleep/1$0'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('thread_sleep')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('thread_sleep')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	pseudo_instr1(3, 0)
	neck_cut
	put_structure(1, 1)
	set_constant('record_db')
	set_constant('false')
	put_list(2)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('db')
	set_constant('false')
	put_list(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('timeout')
	set_x_value(0)
	put_list(0)
	set_x_value(1)
	set_x_value(3)
	execute_predicate('thread_wait', 1)

$3:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('thread_sleep')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('thread_sleep')
	set_x_value(1)
	put_integer(1, 1)
	put_constant('integer', 3)
	execute_predicate('type_exception', 4)
end('thread_sleep/1$0'/1):



'thread_sleep'/1:


$1:
	execute_predicate('thread_sleep/1$0', 1)
end('thread_sleep'/1):



'thread_sleep_until/1$0'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(1, 0)
	set_constant('thread_sleep_until')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('thread_sleep_until')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	pseudo_instr1(3, 0)
	pseudo_instr2(1, 1, 0)
	neck_cut
	pseudo_instr3(3, 0, 1, 2)
	get_x_variable(0, 2)
	put_structure(1, 1)
	set_constant('record_db')
	set_constant('false')
	put_list(2)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('db')
	set_constant('false')
	put_list(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('timeout')
	set_x_value(0)
	put_list(0)
	set_x_value(1)
	set_x_value(3)
	execute_predicate('thread_wait', 1)

$3:
	get_x_variable(2, 0)
	put_structure(1, 0)
	set_constant('thread_sleep_until')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('thread_sleep_until')
	set_x_value(1)
	put_integer(1, 1)
	put_constant('integer', 3)
	execute_predicate('type_exception', 4)
end('thread_sleep_until/1$0'/2):



'thread_sleep_until'/1:


$1:
	pseudo_instr1(59, 1)
	execute_predicate('thread_sleep_until/1$0', 2)
end('thread_sleep_until'/1):



'thread_defaults'/1:


$1:
	get_list(0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure('heap_size', 1, 0)
	unify_x_variable(0)
	get_list(1)
	unify_x_ref(1)
	unify_x_ref(2)
	get_structure('scratchpad_size', 1, 1)
	unify_x_variable(1)
	get_list(2)
	unify_x_ref(2)
	unify_x_ref(3)
	get_structure('binding_trail_size', 1, 2)
	unify_x_variable(2)
	get_list(3)
	unify_x_ref(3)
	unify_x_ref(4)
	get_structure('object_trail_size', 1, 3)
	unify_x_variable(3)
	get_list(4)
	unify_x_ref(4)
	unify_x_ref(5)
	get_structure('ip_trail_size', 1, 4)
	unify_x_variable(4)
	get_list(5)
	unify_x_ref(5)
	unify_x_ref(6)
	get_structure('tag_trail_size', 1, 5)
	unify_x_variable(5)
	get_list(6)
	unify_x_ref(6)
	unify_x_ref(7)
	get_structure('ref_trail_size', 1, 6)
	unify_x_value(5)
	get_list(7)
	unify_x_ref(6)
	unify_x_ref(7)
	get_structure('env_size', 1, 6)
	unify_x_variable(6)
	get_list(7)
	unify_x_ref(7)
	unify_x_ref(8)
	get_structure('choice_size', 1, 7)
	unify_x_variable(7)
	get_list(8)
	unify_x_ref(8)
	unify_x_ref(9)
	get_structure('name_table_size', 1, 8)
	unify_x_variable(8)
	get_list(9)
	unify_x_ref(9)
	unify_constant('[]')
	get_structure('ip_table_size', 1, 9)
	unify_x_variable(9)
	pseudo_instr1(72, 10)
	get_structure('$thread_defaults', 11, 10)
	unify_x_value(0)
	unify_x_value(1)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	unify_x_value(5)
	unify_void(1)
	unify_x_value(6)
	unify_x_value(7)
	unify_x_value(8)
	unify_x_value(9)
	proceed
end('thread_defaults'/1):



'thread_set_defaults'/1:


$1:
	allocate(1)
	put_y_variable(0, 1)
	call_predicate('$thread_decode_sizes', 2, 1)
	pseudo_instr1(73, 20)
	deallocate
	proceed
end('thread_set_defaults'/1):



'$thread_decode_sizes'/2:


$1:
	put_x_value(1, 2)
	get_structure('$thread_defaults', 11, 2)
	unify_void(11)
	execute_predicate('$thread_decode_sizes1', 2)
end('$thread_decode_sizes'/2):



'$thread_decode_sizes1'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	pseudo_instr1(72, 0)
	get_x_variable(2, 0)
	put_integer(11, 0)
	execute_predicate('$try_unify_thread_args', 3)

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(1)
	get_y_variable(0, 1)
	put_y_variable(3, 1)
	put_y_variable(2, 2)
	call_predicate('$thread_arg_num', 3, 4)
	pseudo_instr3(1, 23, 20, 0)
	get_y_value(2, 0)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$thread_decode_sizes1', 2)
end('$thread_decode_sizes1'/2):



'$try_unify_thread_args/3$0/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	proceed

$2:
	proceed
end('$try_unify_thread_args/3$0/2$0'/2):



'$try_unify_thread_args/3$0'/2:


$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$try_unify_thread_args/3$0/2$0', 2, 1)
	cut(0)
	deallocate
	proceed
end('$try_unify_thread_args/3$0'/2):



'$try_unify_thread_args'/3:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$1:
	get_integer(0, 0)
	neck_cut
	proceed

$2:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	pseudo_instr3(1, 22, 21, 0)
	get_x_variable(1, 0)
	pseudo_instr3(1, 22, 20, 0)
	call_predicate('$try_unify_thread_args/3$0', 2, 3)
	pseudo_instr2(70, 22, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$try_unify_thread_args', 3)
end('$try_unify_thread_args'/3):



'$thread_arg_num'/3:

	switch_on_term(0, $14, 'fail', 'fail', $12, 'fail', 'fail')

$12:
	switch_on_structure(0, 32, ['$default':'fail', '$'/0:$13, 'heap_size'/1:$1, 'scratchpad_size'/1:$2, 'binding_trail_size'/1:$3, 'object_trail_size'/1:$4, 'ip_trail_size'/1:$5, 'tag_trail_size'/1:$6, 'ref_trail_size'/1:$7, 'env_size'/1:$8, 'choice_size'/1:$9, 'name_table_size'/1:$10, 'ip_table_size'/1:$11])

$13:
	try(3, $1)
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

$14:
	try(3, $1)
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
	get_integer(1, 1)
	get_structure('heap_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$2:
	get_integer(2, 1)
	get_structure('scratchpad_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$3:
	get_integer(3, 1)
	get_structure('binding_trail_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$4:
	get_integer(4, 1)
	get_structure('object_trail_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$5:
	get_integer(5, 1)
	get_structure('ip_trail_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$6:
	get_integer(6, 1)
	get_structure('tag_trail_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$7:
	get_integer(7, 1)
	get_structure('ref_trail_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$8:
	get_integer(8, 1)
	get_structure('env_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$9:
	get_integer(9, 1)
	get_structure('choice_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$10:
	get_integer(10, 1)
	get_structure('name_table_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$11:
	get_integer(11, 1)
	get_structure('ip_table_size', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed
end('$thread_arg_num'/3):



'$thread_start/0$0'/1:

	try(1, $1)
	trust($2)

$1:
	put_structure(1, 1)
	set_constant('call')
	set_x_value(0)
	put_structure(2, 0)
	set_constant(',')
	set_constant('$initialise_system_non_backtrackable')
	set_x_value(1)
	put_x_variable(3, 1)
	put_structure(1, 2)
	set_constant('$thread_exception')
	set_x_value(3)
	execute_predicate('catch', 3)

$2:
	proceed
end('$thread_start/0$0'/1):



'$thread_start'/0:

	try(0, $1)
	trust($2)

$1:
	pseudo_instr1(64, 0)
	neck_cut
	allocate(0)
	call_predicate('$thread_start/0$0', 1, 0)
	call_predicate('exit_thread_gui', 0, 0)
	call_predicate('exit_debug_thread_gui', 0, 0)
	pseudo_instr0(8)
	deallocate
	proceed

$2:
	allocate(0)
	call_predicate('exit_thread_gui', 0, 0)
	call_predicate('exit_debug_thread_gui', 0, 0)
	pseudo_instr0(8)
	deallocate
	proceed
end('$thread_start'/0):



'$thread_exception'/1:


$1:
	allocate(1)
	get_y_variable(0, 0)
	put_constant('Uncaught throw: ', 0)
	call_predicate('error', 1, 1)
	put_y_value(0, 0)
	call_predicate('errornl', 1, 0)
	call_predicate('exit_thread_gui', 0, 0)
	call_predicate('exit_debug_thread_gui', 0, 0)
	pseudo_instr0(8)
	deallocate
	proceed
end('$thread_exception'/1):



'$handle_push_goal'/2:


$1:
	get_x_variable(2, 1)
	put_x_value(0, 1)
	put_constant('$handle_push_goal_aux', 0)
	execute_predicate('call_predicate', 3)
end('$handle_push_goal'/2):



'$handle_push_goal_aux'/2:


$1:
	allocate(1)
	get_y_variable(0, 1)
	call_predicate('call_predicate', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call_predicate', 1)
end('$handle_push_goal_aux'/2):



