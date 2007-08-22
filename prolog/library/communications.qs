'??'/2:


$1:
	proceed
end('??'/2):



'->>'/2:


$1:
	allocate(2)
	get_y_variable(1, 0)
	get_x_variable(0, 1)
	put_y_variable(0, 1)
	call_predicate('$full_handle', 2, 2)
	pseudo_instr1(90, 0)
	get_x_variable(1, 0)
	put_structure(3, 0)
	set_constant('p2pmsg')
	set_y_value(0)
	set_x_value(1)
	set_y_value(1)
	deallocate
	execute_predicate('$pedro_p2p', 1)
end('->>'/2):



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



'$same_host/2$1'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'localhost':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	put_constant('localhost', 2)
	get_x_value(0, 2)
	neck_cut
	put_constant('127.0.0.1', 0)
	get_x_value(1, 0)
	proceed

$2:
	execute_predicate('$same_host', 2)
end('$same_host/2$1'/2):



'$same_host/2$2'/1:

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
end('$same_host/2$2'/1):



'$same_host/2$3'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'localhost':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	put_constant('localhost', 2)
	get_x_value(0, 2)
	neck_cut
	put_constant('127.0.0.1', 0)
	get_x_value(1, 0)
	proceed

$2:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_x_value(2, 1)
	execute_predicate('$same_host', 2)
end('$same_host/2$3'/2):



'$same_host'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	allocate(2)
	get_y_variable(0, 1)
	get_y_level(1)
	call_predicate('$same_host/2$0', 1, 2)
	cut(1)
	pseudo_instr1(90, 0)
	get_structure('@', 2, 0)
	unify_void(1)
	unify_x_variable(0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$same_host/2$1', 2)

$2:
	allocate(2)
	get_y_variable(0, 0)
	get_x_variable(0, 1)
	get_y_level(1)
	call_predicate('$same_host/2$2', 1, 2)
	cut(1)
	pseudo_instr1(90, 0)
	get_structure('@', 2, 0)
	unify_void(1)
	unify_x_variable(0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$same_host/2$3', 2)

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



'same_handle'/2:

	switch_on_term(0, $7, $6, $6, $6, $6, $4)

$4:
	switch_on_constant(0, 4, ['$default':$6, 'pedro':$5])

$5:
	try(2, $1)
	retry($2)
	trust($3)

$6:
	try(2, $1)
	trust($3)

$7:
	try(2, $1)
	retry($2)
	trust($3)

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
	get_constant('pedro', 0)
	get_constant('pedro', 1)
	neck_cut
	proceed

$3:
	allocate(2)
	get_y_variable(1, 1)
	put_y_variable(0, 1)
	call_predicate('$full_handle', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$full_handle', 2)
end('same_handle'/2):



'$full_handle'/2:

	switch_on_term(0, $15, $14, $14, $8, $14, $12)

$8:
	switch_on_structure(0, 8, ['$default':$14, '$'/0:$9, ':'/2:$10, '@'/2:$11])

$9:
	try(2, $1)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$10:
	try(2, $1)
	retry($3)
	trust($4)

$11:
	try(2, $1)
	retry($3)
	retry($5)
	retry($6)
	trust($7)

$12:
	switch_on_constant(0, 4, ['$default':$14, 'self':$13])

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
	retry($6)
	trust($7)

$1:
	put_constant('pedro', 1)
	pseudo_instr2(110, 0, 1)
	neck_cut
	fail

$2:
	get_constant('self', 0)
	neck_cut
	pseudo_instr1(90, 0)
	get_x_value(1, 0)
	proceed

$3:
	get_structure('@', 2, 1)
	unify_x_ref(1)
	unify_x_variable(2)
	get_structure(':', 2, 1)
	unify_x_value(0)
	unify_x_variable(1)
	pseudo_instr1(2, 0)
	neck_cut
	pseudo_instr1(90, 0)
	get_structure('@', 2, 0)
	unify_x_ref(0)
	unify_x_value(2)
	get_structure(':', 2, 0)
	unify_void(1)
	unify_x_value(1)
	proceed

$4:
	get_structure(':', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_structure('@', 2, 1)
	unify_x_ref(1)
	unify_x_variable(3)
	get_structure(':', 2, 1)
	unify_x_value(0)
	unify_x_value(2)
	pseudo_instr1(90, 0)
	get_structure('@', 2, 0)
	unify_x_ref(0)
	unify_x_value(3)
	get_structure(':', 2, 0)
	unify_void(2)
	proceed

$5:
	get_structure('@', 2, 0)
	unify_x_variable(2)
	unify_x_variable(0)
	get_structure('@', 2, 1)
	unify_x_value(2)
	unify_x_variable(1)
	pseudo_instr1(2, 2)
	neck_cut
	execute_predicate('$same_host', 2)

$6:
	get_structure('@', 2, 0)
	unify_x_variable(2)
	unify_x_variable(0)
	get_structure('@', 2, 1)
	unify_x_value(2)
	unify_x_variable(1)
	pseudo_instr1(1, 2)
	neck_cut
	execute_predicate('$same_host', 2)

$7:
	get_structure('@', 2, 0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure(':', 2, 2)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('@', 2, 1)
	unify_x_ref(4)
	unify_x_variable(1)
	get_structure(':', 2, 4)
	unify_x_value(2)
	unify_x_value(3)
	execute_predicate('$same_host', 2)
end('$full_handle'/2):



'$same_handle_from'/2:

	switch_on_term(0, $13, $12, $12, $7, $12, $10)

$7:
	switch_on_structure(0, 4, ['$default':$12, '$'/0:$8, '@'/2:$9])

$8:
	try(2, $1)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$9:
	try(2, $1)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$10:
	switch_on_constant(0, 4, ['$default':$12, 'pedro':$11])

$11:
	try(2, $1)
	retry($2)
	trust($3)

$12:
	try(2, $1)
	trust($3)

$13:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	pseudo_instr1(1, 1)
	neck_cut
	get_x_value(0, 1)
	proceed

$2:
	get_constant('pedro', 0)
	neck_cut
	put_constant('pedro', 0)
	get_x_value(1, 0)
	proceed

$3:
	get_constant('self', 1)
	pseudo_instr1(90, 1)
	get_x_value(0, 1)
	proceed

$4:
	get_structure('@', 2, 0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure(':', 2, 2)
	unify_x_variable(2)
	unify_x_variable(3)
	get_x_value(2, 1)
	pseudo_instr1(2, 2)
	neck_cut
	pseudo_instr1(90, 1)
	get_structure('@', 2, 1)
	unify_x_ref(2)
	unify_x_variable(1)
	get_structure(':', 2, 2)
	unify_void(1)
	unify_x_value(3)
	execute_predicate('$same_host', 2)

$5:
	get_structure('@', 2, 0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure(':', 2, 2)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure(':', 2, 1)
	unify_x_value(2)
	unify_x_value(3)
	pseudo_instr1(90, 1)
	get_structure('@', 2, 1)
	unify_x_ref(2)
	unify_x_variable(1)
	get_structure(':', 2, 2)
	unify_void(2)
	execute_predicate('$same_host', 2)

$6:
	get_structure('@', 2, 0)
	unify_x_ref(2)
	unify_x_variable(0)
	get_structure(':', 2, 2)
	unify_x_variable(2)
	unify_x_variable(3)
	get_structure('@', 2, 1)
	unify_x_ref(4)
	unify_x_variable(1)
	get_structure(':', 2, 4)
	unify_x_value(2)
	unify_x_value(3)
	execute_predicate('$same_host', 2)
end('$same_handle_from'/2):



'<<-'/2:


$1:
	allocate(6)
	get_y_variable(1, 0)
	get_y_variable(3, 1)
	get_y_level(4)
	put_y_variable(0, 0)
	put_y_variable(5, 1)
	put_y_variable(2, 2)
	put_constant('block', 3)
	put_constant('false', 4)
	call_predicate('$ipc_peek', 5, 6)
	pseudo_instr1(55, 25)
	cut(4)
	put_y_value(2, 0)
	put_y_value(3, 1)
	call_predicate('$same_handle_from', 2, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('<<-'/2):



'<<='/2:


$1:
	allocate(6)
	get_y_variable(3, 0)
	get_y_variable(5, 1)
	get_y_level(0)
	put_y_variable(2, 0)
	put_y_variable(1, 1)
	put_y_variable(4, 2)
	put_constant('block', 3)
	put_constant('false', 4)
	call_predicate('$ipc_peek', 5, 6)
	put_y_value(4, 0)
	put_y_value(5, 1)
	call_predicate('$same_handle_from', 2, 4)
	put_y_value(3, 0)
	get_y_value(2, 0)
	pseudo_instr1(55, 21)
	cut(0)
	deallocate
	proceed
end('<<='/2):



'$is_not_timeout/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	put_constant('$$ipc_timeout$$', 1)
	pseudo_instr2(110, 0, 1)
	neck_cut
	fail

$2:
	proceed
end('$is_not_timeout/1$0'/1):



'$is_not_timeout'/1:


$1:
	execute_predicate('$is_not_timeout/1$0', 1)
end('$is_not_timeout'/1):



'$mc_inline/2$0'/6:

	try(6, $1)
	trust($2)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_x_value(1, 0)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_x_value(5)
	get_structure('$ipc_peek', 5, 0)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	unify_constant('block')
	unify_constant('false')
	proceed

$2:
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_value(5)
	get_structure('$ipc_peek', 5, 1)
	unify_x_value(2)
	unify_x_value(3)
	unify_x_value(4)
	unify_x_value(0)
	unify_constant('false')
	proceed
end('$mc_inline/2$0'/6):



'$mc_inline'/2:


$1:
	allocate(6)
	get_y_variable(5, 1)
	put_y_variable(4, 1)
	put_y_variable(3, 2)
	put_y_variable(2, 3)
	put_y_variable(1, 4)
	put_y_variable(0, 5)
	call_predicate('$mc_gen_choices', 6, 6)
	put_y_value(0, 0)
	put_y_value(5, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_y_value(4, 5)
	deallocate
	execute_predicate('$mc_inline/2$0', 6)
end('$mc_inline'/2):



'$mc_gen_choices'/6:

	switch_on_term(0, $9, $4, $4, $5, $4, $4)

$5:
	switch_on_structure(0, 8, ['$default':$4, '$'/0:$6, ';'/2:$7, '->'/2:$8])

$6:
	try(6, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(6, $1)
	retry($2)
	trust($4)

$8:
	try(6, $3)
	trust($4)

$9:
	try(6, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_structure(';', 2, 0)
	unify_x_ref(0)
	unify_void(1)
	get_structure('->', 2, 0)
	unify_x_ref(0)
	unify_x_variable(6)
	get_structure('timeout', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 5)
	get_x_value(1, 6)
	neck_cut
	proceed

$2:
	get_structure(';', 2, 0)
	unify_x_variable(0)
	allocate(6)
	unify_y_variable(5)
	get_structure(';', 2, 1)
	unify_x_variable(1)
	unify_y_variable(4)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_y_variable(0, 5)
	neck_cut
	call_predicate('$mc_choice_to_code', 5, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_y_value(0, 5)
	deallocate
	execute_predicate('$mc_gen_choices', 6)

$3:
	get_structure('->', 2, 0)
	unify_x_ref(0)
	unify_x_variable(6)
	get_structure('timeout', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 5)
	get_x_value(1, 6)
	neck_cut
	proceed

$4:
	get_structure(';', 2, 1)
	unify_x_variable(1)
	unify_constant('fail')
	neck_cut
	execute_predicate('$mc_choice_to_code', 5)
end('$mc_gen_choices'/6):



'$mc_choice_to_code'/5:

	switch_on_term(0, $7, 'fail', 'fail', $4, 'fail', 'fail')

$4:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$5, '->'/2:$6])

$5:
	try(5, $1)
	retry($2)
	trust($3)

$6:
	try(5, $1)
	retry($2)
	trust($3)

$7:
	try(5, $1)
	retry($2)
	trust($3)

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
	call_predicate('$mc_get_msg_addr_code', 5, 5)
	put_y_value(2, 0)
	get_structure('->', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure(',', 2, 0)
	unify_y_value(0)
	unify_y_value(4)
	get_structure(',', 2, 1)
	unify_x_ref(0)
	unify_y_value(3)
	get_structure('$ipc_commit', 1, 0)
	unify_y_value(1)
	deallocate
	proceed

$2:
	get_structure('->', 2, 0)
	unify_x_ref(0)
	allocate(5)
	unify_y_variable(3)
	get_structure('??', 2, 0)
	unify_x_variable(0)
	unify_y_variable(4)
	get_y_variable(2, 1)
	get_y_variable(1, 3)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$mc_get_msg_addr_code', 5, 5)
	put_y_value(2, 0)
	get_structure('->', 2, 0)
	unify_x_ref(0)
	unify_x_ref(1)
	get_structure(',', 2, 0)
	unify_y_value(0)
	unify_y_value(4)
	get_structure(',', 2, 1)
	unify_x_ref(0)
	unify_y_value(3)
	get_structure('$ipc_commit', 1, 0)
	unify_y_value(1)
	deallocate
	proceed

$3:
	get_structure('->', 2, 0)
	unify_x_variable(0)
	allocate(4)
	unify_y_variable(3)
	get_y_variable(2, 1)
	get_y_variable(1, 3)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$mc_get_msg_addr_code', 5, 4)
	put_y_value(2, 0)
	get_structure('->', 2, 0)
	unify_y_value(0)
	unify_x_ref(0)
	get_structure(',', 2, 0)
	unify_x_ref(0)
	unify_y_value(3)
	get_structure('$ipc_commit', 1, 0)
	unify_y_value(1)
	deallocate
	proceed
end('$mc_choice_to_code'/5):



'$mc_get_msg_addr_code'/5:


$1:
	get_structure('<<-', 2, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	get_structure(',', 2, 1)
	unify_x_ref(1)
	unify_x_ref(3)
	get_structure('$is_not_timeout', 1, 1)
	unify_x_value(2)
	get_structure(',', 2, 3)
	unify_x_ref(1)
	unify_x_ref(3)
	get_structure('$same_handle_from', 2, 1)
	unify_x_value(4)
	unify_x_value(5)
	get_structure('=', 2, 3)
	unify_x_value(0)
	unify_x_value(2)
	proceed
end('$mc_get_msg_addr_code'/5):



'$query_communications2007_8_22_10_22_48_600/0$0'/0:


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
end('$query_communications2007_8_22_10_22_48_600/0$0'/0):



'$query_communications2007_8_22_10_22_48_600/0$1'/0:


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
end('$query_communications2007_8_22_10_22_48_600/0$1'/0):



'$query_communications2007_8_22_10_22_48_600/0$2'/0:


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
end('$query_communications2007_8_22_10_22_48_600/0$2'/0):



'$query_communications2007_8_22_10_22_48_600/0$3'/0:


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
end('$query_communications2007_8_22_10_22_48_600/0$3'/0):



'$query_communications2007_8_22_10_22_48_600/0$4'/0:


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
end('$query_communications2007_8_22_10_22_48_600/0$4'/0):



'$query_communications2007_8_22_10_22_48_600/0$5'/0:


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
end('$query_communications2007_8_22_10_22_48_600/0$5'/0):



'$query_communications2007_8_22_10_22_48_600/0$6'/0:


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
end('$query_communications2007_8_22_10_22_48_600/0$6'/0):



'$query_communications2007_8_22_10_22_48_600/0$7'/0:


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
end('$query_communications2007_8_22_10_22_48_600/0$7'/0):



'$query_communications2007_8_22_10_22_48_600/0$8'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(1024, 0)
	put_constant('xfx', 1)
	put_constant('??', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_communications2007_8_22_10_22_48_600/0$8'/0):



'$query_communications2007_8_22_10_22_48_600/0$9'/0:


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
end('$query_communications2007_8_22_10_22_48_600/0$9'/0):



'$query_communications2007_8_22_10_22_48_600'/0:

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
	call_predicate('$query_communications2007_8_22_10_22_48_600/0$0', 0, 0)
	fail

$2:
	allocate(0)
	call_predicate('$query_communications2007_8_22_10_22_48_600/0$1', 0, 0)
	fail

$3:
	allocate(0)
	call_predicate('$query_communications2007_8_22_10_22_48_600/0$2', 0, 0)
	fail

$4:
	allocate(0)
	call_predicate('$query_communications2007_8_22_10_22_48_600/0$3', 0, 0)
	fail

$5:
	allocate(0)
	call_predicate('$query_communications2007_8_22_10_22_48_600/0$4', 0, 0)
	fail

$6:
	allocate(0)
	call_predicate('$query_communications2007_8_22_10_22_48_600/0$5', 0, 0)
	fail

$7:
	allocate(0)
	call_predicate('$query_communications2007_8_22_10_22_48_600/0$6', 0, 0)
	fail

$8:
	allocate(0)
	call_predicate('$query_communications2007_8_22_10_22_48_600/0$7', 0, 0)
	fail

$9:
	allocate(0)
	call_predicate('$query_communications2007_8_22_10_22_48_600/0$8', 0, 0)
	fail

$10:
	allocate(0)
	call_predicate('$query_communications2007_8_22_10_22_48_600/0$9', 0, 0)
	fail

$11:
	proceed
end('$query_communications2007_8_22_10_22_48_600'/0):



'$query'/0:


$1:
	execute_predicate('$query_communications2007_8_22_10_22_48_600', 0)
end('$query'/0):



