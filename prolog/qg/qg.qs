'main'/1:


$1:
	put_integer(3, 1)
	put_integer(1, 2)
	pseudo_instr2(10, 1, 2)
	allocate(1)
	put_y_variable(0, 1)
	call_predicate('$process_qg_options', 2, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$expandfiles', 1)
end('main'/1):



'$process_qg_options'/2:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(2, $1)
	trust($2)

$1:
	get_list(0)
	unify_constant('-R')
	unify_x_ref(0)
	get_list(0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_y_variable(0, 1)
	neck_cut
	call_predicate('$load_qg_rulefile', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$process_qg_options', 2)

$2:
	get_x_value(0, 1)
	proceed
end('$process_qg_options'/2):



'$load_qg_rulefile/1$0'/1:

	try(1, $1)
	trust($2)

$1:
	execute_predicate('load', 1)

$2:
	proceed
end('$load_qg_rulefile/1$0'/1):



'$load_qg_rulefile/1$1'/1:

	try(1, $1)
	trust($2)

$1:
	execute_predicate('consult', 1)

$2:
	proceed
end('$load_qg_rulefile/1$1'/1):



'$load_qg_rulefile'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr2(30, 0, 1)
	put_integer(2, 3)
	pseudo_instr3(3, 1, 3, 2)
	get_x_variable(1, 2)
	put_integer(3, 3)
	pseudo_instr4(2, 0, 1, 3, 2)
	get_x_variable(1, 2)
	put_constant('.qo', 2)
	get_x_value(1, 2)
	neck_cut
	allocate(1)
	get_y_level(0)
	call_predicate('$load_qg_rulefile/1$0', 1, 1)
	cut(0)
	deallocate
	proceed

$2:
	allocate(1)
	get_y_level(0)
	call_predicate('$load_qg_rulefile/1$1', 1, 1)
	cut(0)
	deallocate
	proceed
end('$load_qg_rulefile'/1):



