'$elvin_sub'/3:

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
	execute_predicate('$elvin_sub', 3)

$2:
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
	execute_predicate('$elvin_sub', 3)

$3:
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
	execute_predicate('$elvin_sub', 3)

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
	execute_predicate('$elvin_sub', 3)

$5:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed
end('$elvin_sub'/3):



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
	set_constant('$elvin_term')
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



'$elvin_term'/3:

	switch_on_term(0, $10, $4, $7, $4, $4, $8)

$7:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$8:
	switch_on_constant(0, 4, ['$default':$4, '[]':$9])

$9:
	try(3, $4)
	trust($6)

$10:
	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

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
	execute_predicate('$elvin_term', 3)

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
	execute_predicate('$elvin_term', 3)

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
	execute_predicate('$elvin_term', 3)

$4:
	allocate(4)
	get_y_variable(2, 0)
	get_x_variable(0, 1)
	get_y_variable(1, 2)
	get_y_level(3)
	put_y_variable(0, 2)
	put_integer(34, 1)
	call_predicate('C', 3, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$elvin_term', 3)

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
	execute_predicate('$elvin_term', 3)

$6:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed
end('$elvin_term'/3):



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
	get_x_variable(1, 0)
	allocate(6)
	get_y_level(1)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	put_y_variable(5, 2)
	put_constant('$elvin_subterm_transform', 0)
	call_predicate('transform_subterms', 3, 6)
	put_y_value(4, 1)
	put_constant('write', 0)
	call_predicate('open_string', 2, 6)
	put_y_value(4, 0)
	put_y_value(5, 1)
	call_predicate('write', 2, 5)
	put_y_value(4, 0)
	put_y_value(3, 1)
	call_predicate('stream_to_chars', 2, 4)
	put_structure(1, 0)
	set_constant('$elvin_sub')
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



'$elvin_subterm_transform'/2:

	switch_on_term(0, $8, $3, $3, $4, $3, $3)

$4:
	switch_on_structure(0, 8, ['$default':$3, '$'/0:$5, '=='/2:$6, '\\='/2:$7])

$5:
	try(2, $1)
	retry($2)
	trust($3)

$6:
	try(2, $1)
	trust($3)

$7:
	try(2, $2)
	trust($3)

$8:
	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_structure('==', 2, 0)
	allocate(5)
	unify_y_variable(2)
	unify_x_variable(0)
	get_y_variable(1, 1)
	pseudo_instr1(2, 0)
	neck_cut
	put_y_variable(3, 19)
	put_y_variable(0, 19)
	put_y_variable(4, 1)
	call_predicate('name', 2, 5)
	put_list(0)
	set_integer(34)
	set_y_value(4)
	put_list(1)
	set_integer(34)
	set_constant('[]')
	put_y_value(3, 2)
	call_predicate('append', 3, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	call_predicate('name', 2, 3)
	put_y_value(1, 0)
	get_structure('==', 2, 0)
	unify_y_value(2)
	unify_y_value(0)
	deallocate
	proceed

$2:
	get_structure('\\=', 2, 0)
	allocate(5)
	unify_y_variable(2)
	unify_x_variable(0)
	get_y_variable(1, 1)
	pseudo_instr1(2, 0)
	neck_cut
	put_y_variable(3, 19)
	put_y_variable(0, 19)
	put_y_variable(4, 1)
	call_predicate('name', 2, 5)
	put_list(0)
	set_integer(34)
	set_y_value(4)
	put_list(1)
	set_integer(34)
	set_constant('[]')
	put_y_value(3, 2)
	call_predicate('append', 3, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	call_predicate('name', 2, 3)
	put_y_value(1, 0)
	get_structure('\\=', 2, 0)
	unify_y_value(2)
	unify_y_value(0)
	deallocate
	proceed

$3:
	get_x_value(0, 1)
	proceed
end('$elvin_subterm_transform'/2):



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

	switch_on_term(0, $14, $13, $13, $8, $13, $13)

$8:
	switch_on_structure(0, 8, ['$default':$13, '$'/0:$9, 'int64'/1:$10, 'opaque'/1:$11, 'qpterm'/1:$12])

$9:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$10:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$11:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($6)

$12:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($7)

$13:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$14:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	proceed

$2:
	pseudo_instr1(112, 0)
	neck_cut
	proceed

$3:
	pseudo_instr1(2, 0)
	neck_cut
	proceed

$4:
	allocate(1)
	get_y_level(0)
	call_predicate('$check_char_list', 1, 1)
	cut(0)
	deallocate
	proceed

$5:
	get_structure('int64', 1, 0)
	unify_x_variable(0)
	pseudo_instr1(2, 0)
	neck_cut
	proceed

$6:
	get_structure('opaque', 1, 0)
	unify_void(1)
	allocate(1)
	get_y_level(0)
	put_x_variable(0, 0)
	call_predicate('$check_char_list', 1, 1)
	cut(0)
	deallocate
	proceed

$7:
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
	retry($2)
	trust($3)

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
	pseudo_instr1(2, 20)
	neck_cut
	get_y_level(1)
	pseudo_instr1(108, 0)
	get_x_variable(1, 0)
	put_y_value(0, 0)
	call_predicate('member', 2, 2)
	cut(1)
	pseudo_instr1(107, 20)
	deallocate
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
	pseudo_instr1(108, 0)
	get_x_variable(1, 0)
	put_y_value(0, 0)
	call_predicate('member', 2, 2)
	cut(1)
	pseudo_instr1(107, 20)
	deallocate
	proceed
end('elvin_delete_subscription'/1):



'elvin_delete_all_subscriptions'/0:

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
end('elvin_delete_all_subscriptions'/0):



'elvin_add_notification'/1:

	try(1, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(1, 0)
	set_constant('elvin_add_notification')
	set_x_value(1)
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
	pseudo_instr1(109, 20)
	deallocate
	proceed

$3:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('elvin_add_notification')
	set_x_value(1)
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



'$query_elvin2006_4_6_12_14_13_86/0$0'/0:


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
end('$query_elvin2006_4_6_12_14_13_86/0$0'/0):



'$query_elvin2006_4_6_12_14_13_86/0$1'/0:


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
end('$query_elvin2006_4_6_12_14_13_86/0$1'/0):



'$query_elvin2006_4_6_12_14_13_86'/0:

	try(0, $1)
	retry($2)
	trust($3)

$1:
	allocate(0)
	call_predicate('$query_elvin2006_4_6_12_14_13_86/0$0', 0, 0)
	fail

$2:
	allocate(0)
	call_predicate('$query_elvin2006_4_6_12_14_13_86/0$1', 0, 0)
	fail

$3:
	proceed
end('$query_elvin2006_4_6_12_14_13_86'/0):



'$query'/0:


$1:
	execute_predicate('$query_elvin2006_4_6_12_14_13_86', 0)
end('$query'/0):



