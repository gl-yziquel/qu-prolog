'sub'/3:

	switch_on_term(0, $8, 'fail', $7, 'fail', 'fail', $6)

$7:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$8:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	get_list(0)
	unify_integer(34)
	allocate(8)
	unify_y_variable(2)
	get_x_variable(0, 1)
	get_y_variable(4, 2)
	get_y_level(5)
	put_y_variable(6, 19)
	put_y_variable(3, 19)
	put_y_variable(1, 19)
	put_y_variable(0, 19)
	put_y_variable(7, 2)
	put_integer(91, 1)
	call_predicate('C', 3, 8)
	put_y_value(1, 0)
	put_y_value(7, 1)
	put_y_value(6, 2)
	call_predicate('string', 3, 7)
	put_y_value(6, 0)
	put_y_value(3, 2)
	put_integer(93, 1)
	call_predicate('C', 3, 6)
	cut(5)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(4, 2)
	call_predicate('sub', 3, 3)
	put_y_value(1, 0)
	put_list(1)
	set_integer(34)
	set_y_value(0)
	put_y_value(2, 2)
	deallocate
	execute_predicate('append', 3)

$2:
	get_list(0)
	unify_integer(33)
	unify_x_ref(0)
	get_list(0)
	unify_integer(61)
	allocate(5)
	unify_y_variable(2)
	get_x_variable(0, 1)
	get_y_variable(1, 2)
	get_y_level(3)
	put_y_variable(0, 19)
	put_y_variable(4, 2)
	put_integer(92, 1)
	call_predicate('C', 3, 5)
	put_y_value(4, 0)
	put_y_value(0, 2)
	put_integer(61, 1)
	call_predicate('C', 3, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('sub', 3)

$3:
	get_list(0)
	unify_integer(33)
	allocate(5)
	unify_y_variable(2)
	get_x_variable(0, 1)
	get_y_variable(1, 2)
	get_y_level(3)
	put_y_variable(0, 19)
	put_y_variable(4, 2)
	put_integer(92, 1)
	call_predicate('C', 3, 5)
	put_y_value(4, 0)
	put_y_value(0, 2)
	put_integer(43, 1)
	call_predicate('C', 3, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('sub', 3)

$4:
	get_list(0)
	unify_integer(37)
	allocate(6)
	unify_y_variable(2)
	get_x_variable(0, 1)
	get_y_variable(1, 2)
	get_y_level(3)
	put_y_variable(4, 19)
	put_y_variable(0, 19)
	put_y_variable(5, 2)
	put_integer(109, 1)
	call_predicate('C', 3, 6)
	put_y_value(5, 0)
	put_y_value(4, 2)
	put_integer(111, 1)
	call_predicate('C', 3, 5)
	put_y_value(4, 0)
	put_y_value(0, 2)
	put_integer(100, 1)
	call_predicate('C', 3, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('sub', 3)

$5:
	get_list(0)
	unify_x_variable(3)
	allocate(4)
	unify_y_variable(2)
	get_x_variable(0, 1)
	get_y_variable(1, 2)
	get_y_level(3)
	put_x_value(3, 1)
	put_y_variable(0, 2)
	call_predicate('C', 3, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('sub', 3)

$6:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed
end('sub'/3):



'string'/3:

	switch_on_term(0, $3, 'fail', $3, 'fail', 'fail', 'fail')

$3:
	try(3, $1)
	trust($2)

$1:
	get_list(0)
	allocate(8)
	unify_y_variable(7)
	unify_y_variable(2)
	get_y_variable(1, 2)
	get_y_level(3)
	put_y_variable(4, 19)
	put_y_variable(0, 19)
	put_y_variable(6, 0)
	put_y_variable(5, 2)
	call_predicate('digits', 3, 8)
	put_y_value(7, 0)
	put_y_value(6, 1)
	call_predicate('name', 2, 6)
	put_y_value(5, 0)
	put_y_value(4, 2)
	put_integer(44, 1)
	call_predicate('C', 3, 5)
	put_y_value(4, 0)
	put_y_value(0, 2)
	put_integer(32, 1)
	call_predicate('C', 3, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('string', 3)

$2:
	get_list(0)
	allocate(2)
	unify_y_variable(1)
	unify_constant('[]')
	put_y_variable(0, 0)
	call_predicate('digits', 3, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('name', 2)
end('string'/3):



'digits'/3:

	switch_on_term(0, $3, 'fail', $1, 'fail', 'fail', $2)

$3:
	try(3, $1)
	trust($2)

$1:
	get_list(0)
	allocate(5)
	unify_y_variable(4)
	unify_y_variable(2)
	get_x_variable(0, 1)
	get_y_variable(1, 2)
	get_y_level(3)
	put_y_value(4, 1)
	put_y_variable(0, 2)
	call_predicate('C', 3, 5)
	put_integer(48, 0)
	pseudo_instr2(2, 0, 24)
	put_integer(57, 0)
	pseudo_instr2(2, 24, 0)
	cut(3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('digits', 3)

$2:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed
end('digits'/3):



'elvin_sub_to_term'/2:


$1:
	allocate(5)
	get_y_variable(1, 1)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	put_y_variable(4, 1)
	call_predicate('name', 2, 5)
	put_structure(1, 0)
	set_constant('term')
	set_y_value(3)
	put_y_value(4, 1)
	call_predicate('phrase', 2, 4)
	put_y_value(3, 0)
	put_list(1)
	set_integer(46)
	set_constant('[]')
	put_y_value(2, 2)
	call_predicate('append', 3, 3)
	put_structure(1, 0)
	set_constant('read')
	set_y_value(2)
	put_y_value(0, 1)
	call_predicate('open_string', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('read', 2, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('close', 1)
end('elvin_sub_to_term'/2):



'term'/3:

	switch_on_term(0, $7, 'fail', $6, 'fail', 'fail', $5)

$6:
	try(3, $1)
	retry($2)
	retry($3)
	trust($4)

$7:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_list(0)
	unify_integer(92)
	unify_x_ref(0)
	get_list(0)
	unify_integer(61)
	allocate(5)
	unify_y_variable(2)
	get_x_variable(0, 1)
	get_y_variable(1, 2)
	get_y_level(3)
	put_y_variable(0, 19)
	put_y_variable(4, 2)
	put_integer(33, 1)
	call_predicate('C', 3, 5)
	put_y_value(4, 0)
	put_y_value(0, 2)
	put_integer(61, 1)
	call_predicate('C', 3, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('term', 3)

$2:
	get_list(0)
	unify_integer(92)
	unify_x_ref(0)
	get_list(0)
	unify_integer(43)
	allocate(4)
	unify_y_variable(2)
	get_x_variable(0, 1)
	get_y_variable(1, 2)
	get_y_level(3)
	put_y_variable(0, 2)
	put_integer(33, 1)
	call_predicate('C', 3, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('term', 3)

$3:
	get_list(0)
	unify_integer(109)
	unify_x_ref(0)
	get_list(0)
	unify_integer(111)
	unify_x_ref(0)
	get_list(0)
	unify_integer(100)
	allocate(6)
	unify_y_variable(2)
	get_x_variable(0, 1)
	get_y_variable(1, 2)
	get_y_level(3)
	put_y_variable(4, 19)
	put_y_variable(0, 19)
	put_y_variable(5, 2)
	put_integer(48, 1)
	call_predicate('C', 3, 6)
	put_y_value(5, 0)
	put_y_value(4, 2)
	put_integer(39, 1)
	call_predicate('C', 3, 5)
	put_y_value(4, 0)
	put_y_value(0, 2)
	put_integer(37, 1)
	call_predicate('C', 3, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('term', 3)

$4:
	get_list(0)
	unify_x_variable(3)
	allocate(4)
	unify_y_variable(2)
	get_x_variable(0, 1)
	get_y_variable(1, 2)
	get_y_level(3)
	put_x_value(3, 1)
	put_y_variable(0, 2)
	call_predicate('C', 3, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('term', 3)

$5:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed
end('term'/3):



'elvin_connect'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('elvin_connect')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('compound')
	put_structure(1, 3)
	set_constant('elvin_connect')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	call_predicate('$elvin_connect_type_check', 1, 2)
	cut(1)
	pseudo_instr1(105, 20)
	deallocate
	proceed

$3:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('elvin_connect')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('compound')
	put_structure(1, 3)
	set_constant('elvin_connect')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('elvin_connect'/1):



'$elvin_connect_type_check'/1:

	switch_on_term(0, $6, 'fail', 'fail', $4, 'fail', $1)

$4:
	switch_on_structure(0, 8, ['$default':'fail', '$'/0:$5, 'connect'/1:$2, 'discover'/1:$3])

$5:
	try(1, $2)
	trust($3)

$6:
	try(1, $1)
	retry($2)
	trust($3)

$1:
	get_constant('default', 0)
	proceed

$2:
	get_structure('connect', 1, 0)
	unify_x_variable(0)
	pseudo_instr1(2, 0)
	proceed

$3:
	get_structure('discover', 1, 0)
	unify_x_variable(0)
	pseudo_instr1(2, 0)
	proceed
end('$elvin_connect_type_check'/1):



'elvin_add_subscription'/1:

	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('elvin_add_subscription')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('elvin_add_subscription')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	pseudo_instr1(2, 0)
	neck_cut
	pseudo_instr1(106, 0)
	proceed

$3:
	allocate(6)
	get_y_variable(5, 0)
	get_y_level(1)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	put_y_variable(4, 1)
	put_constant('write', 0)
	call_predicate('open_string', 2, 6)
	put_y_value(4, 0)
	put_y_value(5, 1)
	call_predicate('write', 2, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	call_predicate('stream_to_chars', 2, 4)
	put_structure(1, 0)
	set_constant('sub')
	set_y_value(2)
	put_y_value(3, 1)
	call_predicate('phrase', 2, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	call_predicate('name', 2, 2)
	cut(1)
	pseudo_instr1(106, 20)
	deallocate
	proceed

$4:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('elvin_add_subscription')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('elvin_add_subscription')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('elvin_add_subscription'/1):



'$check_parts'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_ref(0)
	allocate(1)
	unify_y_variable(0)
	get_structure('=', 2, 0)
	unify_x_variable(1)
	unify_x_variable(0)
	pseudo_instr1(2, 1)
	call_predicate('$check_value', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$check_parts', 1)
end('$check_parts'/1):



'$check_value'/1:

	switch_on_term(0, $14, $13, $13, $7, $13, $13)

$7:
	switch_on_structure(0, 16, ['$default':$13, '$'/0:$8, 'int64'/1:$9, 'real64'/1:$10, 'opaque'/1:$11, 'qpterm'/1:$12])

$8:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$9:
	try(1, $1)
	retry($2)
	trust($3)

$10:
	try(1, $1)
	retry($2)
	trust($4)

$11:
	try(1, $1)
	retry($2)
	trust($5)

$12:
	try(1, $1)
	retry($2)
	trust($6)

$13:
	try(1, $1)
	trust($2)

$14:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	proceed

$2:
	allocate(1)
	get_y_level(0)
	call_predicate('$check_char_list', 1, 1)
	cut(0)
	deallocate
	proceed

$3:
	get_structure('int64', 1, 0)
	unify_x_variable(0)
	pseudo_instr1(2, 0)
	neck_cut
	proceed

$4:
	get_structure('real64', 1, 0)
	unify_x_variable(0)
	pseudo_instr1(2, 0)
	neck_cut
	proceed

$5:
	get_structure('opaque', 1, 0)
	unify_void(1)
	allocate(1)
	get_y_level(0)
	put_x_variable(0, 0)
	call_predicate('$check_char_list', 1, 1)
	cut(0)
	deallocate
	proceed

$6:
	get_structure('qpterm', 1, 0)
	unify_void(1)
	proceed
end('$check_value'/1):



'$check_char_list'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_variable(1)
	unify_x_variable(0)
	pseudo_instr1(3, 1)
	put_integer(0, 2)
	pseudo_instr2(2, 2, 1)
	put_integer(255, 2)
	pseudo_instr2(2, 1, 2)
	execute_predicate('$check_char_list', 1)
end('$check_char_list'/1):



'elvin_delete_subscription'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('elvin_delete_subscription')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('compound')
	put_structure(1, 3)
	set_constant('elvin_delete_subscription')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(2)
	get_y_variable(0, 0)
	pseudo_instr1(108, 0)
	get_x_variable(1, 0)
	get_y_level(1)
	put_y_value(0, 0)
	call_predicate('member', 2, 2)
	cut(1)
	pseudo_instr1(107, 20)
	deallocate
	proceed
end('elvin_delete_subscription'/1):



'delete_all_subscriptions'/0:

	try(0, $1)
	trust($2)

$1:
	pseudo_instr1(108, 0)
	get_x_variable(1, 0)
	allocate(1)
	put_y_variable(0, 0)
	call_predicate('member', 2, 1)
	put_y_value(0, 0)
	call_predicate('elvin_delete_subscription', 1, 0)
	fail

$2:
	proceed
end('delete_all_subscriptions'/0):



'elvin_add_notification'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(1, 0)
	neck_cut
	put_structure(1, 0)
	set_constant('elvin_add_notification')
	set_void(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('compound')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('elvin_add_notification')
	set_x_value(2)
	put_list(2)
	set_x_value(1)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(2)
	get_y_variable(0, 0)
	get_y_level(1)
	call_predicate('$check_parts', 1, 2)
	cut(1)
	pseudo_instr1(110, 20)
	deallocate
	proceed

$3:
	put_structure(1, 0)
	set_constant('elvin_add_notification')
	set_void(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('compound')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('elvin_add_notification')
	set_x_value(2)
	put_list(2)
	set_x_value(1)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('elvin_add_notification'/1):



'$query_elvin2004_12_24_8_55_11_457/0$0'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(800, 0)
	put_constant('xfy', 1)
	put_constant('&&', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_elvin2004_12_24_8_55_11_457/0$0'/0):



'$query_elvin2004_12_24_8_55_11_457/0$1'/0:


$1:
	allocate(1)
	get_y_level(0)
	put_integer(810, 0)
	put_constant('xfy', 1)
	put_constant('||', 2)
	call_predicate('op', 3, 1)
	cut(0)
	deallocate
	proceed
end('$query_elvin2004_12_24_8_55_11_457/0$1'/0):



'$query_elvin2004_12_24_8_55_11_457'/0:

	try(0, $1)
	retry($2)
	trust($3)

$1:
	allocate(0)
	call_predicate('$query_elvin2004_12_24_8_55_11_457/0$0', 0, 0)
	fail

$2:
	allocate(0)
	call_predicate('$query_elvin2004_12_24_8_55_11_457/0$1', 0, 0)
	fail

$3:
	proceed
end('$query_elvin2004_12_24_8_55_11_457'/0):



'$query'/0:


$1:
	execute_predicate('$query_elvin2004_12_24_8_55_11_457', 0)
end('$query'/0):



