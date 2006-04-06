'current_atom'/1:


$1:
	put_constant('fail', 1)
	execute_predicate('$current_atom', 2)
end('current_atom'/1):



'$current_atom/2$0'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'fail':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_constant('fail', 1)
	get_x_value(2, 1)
	neck_cut
	execute_predicate('$external', 1)

$2:
	proceed
end('$current_atom/2$0'/2):



'$current_atom'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	proceed

$2:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	pseudo_instr1(1, 21)
	put_y_value(1, 1)
	put_integer(-1, 0)
	call_predicate('$search_atom_table', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$current_atom/2$0', 2)
end('$current_atom'/2):



'$search_atom_table/2$0'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	proceed

$2:
	get_x_variable(3, 0)
	get_x_variable(0, 2)
	put_x_value(3, 1)
	execute_predicate('$search_atom_table', 2)
end('$search_atom_table/2$0'/3):



'$search_atom_table'/2:


$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_x_variable(1, 1)
	pseudo_instr3(32, 2, 1, 3)
	get_x_variable(2, 3)
	execute_predicate('$search_atom_table/2$0', 3)
end('$search_atom_table'/2):



'current_predicate'/1:


$1:
	put_constant('fail', 1)
	execute_predicate('$current_predicate', 2)
end('current_predicate'/1):



'$current_predicate/2$0'/1:

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
end('$current_predicate/2$0'/1):



'$current_predicate/2$1'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(1, 0)
	pseudo_instr1(1, 1)
	proceed

$2:
	pseudo_instr1(1, 0)
	pseudo_instr1(3, 1)
	proceed

$3:
	pseudo_instr1(2, 0)
	pseudo_instr1(1, 1)
	proceed
end('$current_predicate/2$1'/2):



'$current_predicate/2$2'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'fail':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_constant('fail', 1)
	get_x_value(2, 1)
	neck_cut
	execute_predicate('$external', 1)

$2:
	proceed
end('$current_predicate/2$2'/2):



'$current_predicate'/2:

	switch_on_term(0, $6, 'fail', 'fail', $3, 'fail', 'fail')

$3:
	switch_on_structure(0, 4, ['$default':'fail', '$'/0:$4, '/'/2:$5])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$6:
	try(2, $1)
	trust($2)

$1:
	get_structure('/', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	pseudo_instr1(2, 0)
	pseudo_instr1(3, 2)
	neck_cut
	put_x_value(2, 1)
	allocate(2)
	put_y_variable(1, 2)
	put_y_variable(0, 3)
	call_predicate('$correct_pred_arity', 4, 2)
	pseudo_instr3(33, 21, 20, 0)
	deallocate
	execute_predicate('$current_predicate/2$0', 1)

$2:
	get_structure('/', 2, 0)
	allocate(8)
	unify_y_variable(3)
	unify_y_variable(1)
	get_y_variable(6, 1)
	get_y_level(7)
	put_y_variable(5, 19)
	put_y_variable(4, 19)
	put_y_variable(2, 19)
	put_y_variable(0, 19)
	put_y_value(3, 0)
	put_y_value(1, 1)
	call_predicate('$current_predicate/2$1', 2, 8)
	cut(7)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_integer(-1, 0)
	call_predicate('$search_pred_table', 3, 7)
	put_y_value(6, 0)
	put_y_value(5, 1)
	call_predicate('$current_predicate/2$2', 2, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(2, 2)
	put_y_value(0, 3)
	call_predicate('$decompile_pred_arity', 4, 4)
	put_y_value(3, 0)
	get_y_value(2, 0)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$current_predicate'/2):



'$search_pred_table/3$0'/5:

	try(5, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	get_x_value(2, 3)
	proceed

$2:
	get_x_variable(5, 0)
	get_x_variable(0, 4)
	put_x_value(5, 1)
	execute_predicate('$search_pred_table', 3)
end('$search_pred_table/3$0'/5):



'$search_pred_table'/3:


$1:
	get_x_variable(3, 0)
	get_x_variable(0, 1)
	pseudo_instr4(5, 3, 1, 4, 5)
	get_x_variable(3, 4)
	get_x_variable(4, 5)
	execute_predicate('$search_pred_table/3$0', 5)
end('$search_pred_table'/3):



'$decompile_pred_arity/4$0'/2:

	try(2, $1)
	trust($2)

$1:
	put_constant('$', 3)
	pseudo_instr4(1, 0, 1, 3, 2)
	neck_cut
	fail

$2:
	proceed
end('$decompile_pred_arity/4$0'/2):



'$decompile_pred_arity'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(6)
	get_y_variable(2, 0)
	get_x_variable(0, 1)
	get_y_variable(4, 2)
	get_y_variable(0, 3)
	get_y_level(5)
	put_y_variable(3, 19)
	put_y_variable(1, 19)
	call_predicate('$last_x_reg', 1, 6)
	put_integer(1, 1)
	put_constant('/', 2)
	pseudo_instr4(1, 22, 1, 2, 0)
	get_y_value(3, 0)
	put_integer(1, 1)
	pseudo_instr3(2, 23, 1, 0)
	get_y_value(1, 0)
	put_y_value(2, 0)
	put_y_value(1, 1)
	call_predicate('$decompile_pred_arity/4$0', 2, 6)
	cut(5)
	put_integer(1, 1)
	pseudo_instr3(3, 23, 1, 0)
	put_integer(1, 2)
	pseudo_instr4(2, 22, 2, 0, 1)
	get_y_value(4, 1)
	pseudo_instr2(30, 22, 0)
	pseudo_instr3(3, 0, 23, 1)
	get_x_variable(0, 1)
	pseudo_instr4(2, 22, 21, 0, 1)
	get_x_variable(0, 1)
	pseudo_instr2(32, 0, 1)
	get_x_variable(0, 1)
	pseudo_instr2(39, 0, 1)
	get_y_value(0, 1)
	deallocate
	proceed

$2:
	get_x_value(0, 2)
	get_x_value(1, 3)
	proceed
end('$decompile_pred_arity'/4):



'predicate_property'/2:


$1:
	put_constant('fail', 2)
	execute_predicate('$predicate_property', 3)
end('predicate_property'/2):



'$predicate_property/3$0'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'fail':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	put_constant('fail', 1)
	get_x_value(2, 1)
	neck_cut
	execute_predicate('$external', 1)

$2:
	proceed
end('$predicate_property/3$0'/2):



'$predicate_property'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(7)
	get_y_variable(5, 0)
	get_y_variable(2, 1)
	get_y_variable(6, 2)
	pseudo_instr1(1, 25)
	neck_cut
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	put_integer(-1, 0)
	call_predicate('$search_pred_table', 3, 7)
	put_y_value(6, 0)
	put_y_value(1, 1)
	call_predicate('$predicate_property/3$0', 2, 6)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	call_predicate('$decompile_pred_arity', 4, 6)
	pseudo_instr3(0, 25, 24, 23)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('$obtain_predicate_property', 3)

$2:
	get_x_variable(3, 0)
	allocate(3)
	get_y_variable(2, 1)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 3, 0, 1)
	put_y_variable(1, 2)
	put_y_variable(0, 3)
	call_predicate('$correct_pred_arity', 4, 3)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('$obtain_predicate_property', 3)
end('$predicate_property'/3):



'$obtain_predicate_property'/3:

	try(3, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant('built_in', 2)
	allocate(1)
	get_y_level(0)
	call_predicate('$builtin', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_constant('dynamic', 2)
	pseudo_instr3(33, 0, 1, 2)
	put_integer(1, 0)
	get_x_value(2, 0)
	neck_cut
	proceed

$3:
	get_constant('static', 2)
	pseudo_instr3(33, 0, 1, 2)
	put_integer(2, 0)
	get_x_value(2, 0)
	neck_cut
	proceed

$4:
	get_constant('foreign', 2)
	pseudo_instr3(33, 0, 1, 2)
	put_integer(3, 0)
	get_x_value(2, 0)
	neck_cut
	proceed
end('$obtain_predicate_property'/3):



'$external/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$internal', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('$external/1$0'/1):



'$external'/1:


$1:
	execute_predicate('$external/1$0', 1)
end('$external'/1):



'$internal'/1:


$1:
	put_integer(1, 2)
	put_constant('$', 3)
	pseudo_instr4(1, 0, 2, 3, 1)
	proceed
end('$internal'/1):



