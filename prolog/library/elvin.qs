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
	trust($3)

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



