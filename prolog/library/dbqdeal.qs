'$qdeal/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	put_constant('true', 1)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	allocate(1)
	get_y_variable(0, 1)
	cut(0)
	deallocate
	proceed
end('$qdeal/2$0'/2):



'$qdeal'/2:


$1:
	get_structure('/', 2, 0)
	unify_x_variable(2)
	unify_x_variable(3)
	allocate(5)
	get_y_variable(2, 1)
	get_y_level(1)
	put_x_variable(0, 0)
	pseudo_instr3(0, 0, 2, 3)
	put_y_variable(4, 1)
	call_predicate('$correct_name', 2, 5)
	pseudo_instr3(66, 24, 0, 1)
	get_x_variable(2, 1)
	put_y_variable(3, 1)
	put_y_variable(0, 3)
	call_predicate('$get_clause_ref', 4, 4)
	pseudo_instr3(26, 0, 23, 1)
	put_y_value(2, 1)
	call_predicate('$get_instructions', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$qdeal/2$0', 2)
end('$qdeal'/2):



'$get_instructions/2$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(0, 1)
	get_y_level(1)
	call_predicate('$last_clause_instruction', 1, 2)
	cut(1)
	put_y_value(0, 0)
	get_constant('[]', 0)
	deallocate
	proceed

$2:
	get_x_variable(0, 2)
	execute_predicate('$get_instructions', 2)
end('$get_instructions/2$0'/3):



'$get_instructions'/2:


$1:
	allocate(8)
	get_y_variable(7, 0)
	get_list(1)
	unify_x_ref(0)
	unify_y_variable(2)
	get_structure('-', 2, 0)
	unify_y_value(7)
	unify_y_variable(5)
	put_integer(0, 1)
	pseudo_instr3(20, 0, 27, 1)
	get_x_variable(1, 0)
	put_y_variable(1, 0)
	put_y_variable(4, 2)
	call_predicate('$opcode', 3, 8)
	put_integer(1, 1)
	pseudo_instr3(2, 27, 1, 0)
	get_y_variable(3, 0)
	put_y_value(4, 0)
	put_y_variable(6, 2)
	put_integer(0, 1)
	call_predicate('$length', 3, 7)
	pseudo_instr3(0, 25, 21, 26)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_variable(0, 2)
	put_y_value(5, 4)
	put_integer(1, 3)
	call_predicate('$get_inst_args', 5, 3)
	put_y_value(1, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$get_instructions/2$0', 3)
end('$get_instructions'/2):



'$last_clause_instruction'/1:

	switch_on_term(0, $7, 'fail', 'fail', 'fail', 'fail', $6)

$6:
	switch_on_constant(0, 16, ['default':'fail', 'db_try_dec_ref':$1, 'proceed':$2, 'execute_predicate':$3, 'execute_address':$4, 'fail':$5])

$7:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_constant('db_try_dec_ref', 0)
	proceed

$2:
	get_constant('proceed', 0)
	proceed

$3:
	get_constant('execute_predicate', 0)
	proceed

$4:
	get_constant('execute_address', 0)
	proceed

$5:
	get_constant('fail', 0)
	proceed
end('$last_clause_instruction'/1):



'$get_inst_args'/5:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(5, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_value(1, 2)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(7)
	unify_y_variable(3)
	get_x_variable(5, 1)
	get_y_variable(2, 2)
	get_y_variable(4, 3)
	get_y_variable(1, 4)
	pseudo_instr3(1, 24, 21, 1)
	get_y_variable(6, 1)
	put_y_variable(5, 1)
	put_x_value(5, 2)
	put_y_variable(0, 3)
	call_predicate('$get_instr_arg', 4, 7)
	put_y_value(6, 0)
	get_y_value(5, 0)
	put_integer(1, 1)
	pseudo_instr3(2, 24, 1, 0)
	get_x_variable(3, 0)
	put_y_value(3, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$get_inst_args', 5)
end('$get_inst_args'/5):



'$get_instr_arg'/4:

	switch_on_term(0, $9, 'fail', 'fail', 'fail', 'fail', $8)

$8:
	switch_on_constant(0, 16, ['default':'fail', 'register':$1, 'constant':$2, 'integer':$3, 'number':$4, 'predatom':$5, 'address':$6, 'offset':$7])

$9:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	trust($7)

$1:
	get_constant('register', 0)
	put_integer(0, 4)
	pseudo_instr3(20, 0, 2, 4)
	get_x_value(1, 0)
	put_integer(1, 1)
	pseudo_instr3(2, 2, 1, 0)
	get_x_value(3, 0)
	proceed

$2:
	get_constant('constant', 0)
	put_integer(0, 4)
	pseudo_instr3(21, 0, 2, 4)
	get_x_value(1, 0)
	put_integer(4, 1)
	pseudo_instr3(2, 2, 1, 0)
	get_x_value(3, 0)
	proceed

$3:
	get_constant('integer', 0)
	put_integer(0, 4)
	pseudo_instr3(67, 0, 2, 4)
	get_x_value(1, 0)
	put_integer(4, 1)
	pseudo_instr3(2, 2, 1, 0)
	get_x_value(3, 0)
	proceed

$4:
	get_constant('number', 0)
	put_integer(0, 4)
	pseudo_instr3(22, 0, 2, 4)
	get_x_value(1, 0)
	put_integer(1, 1)
	pseudo_instr3(2, 2, 1, 0)
	get_x_value(3, 0)
	proceed

$5:
	get_constant('predatom', 0)
	put_integer(0, 4)
	pseudo_instr3(25, 0, 2, 4)
	get_x_value(1, 0)
	put_integer(4, 1)
	pseudo_instr3(2, 2, 1, 0)
	get_x_value(3, 0)
	proceed

$6:
	get_constant('address', 0)
	put_integer(0, 4)
	pseudo_instr3(23, 0, 2, 4)
	get_x_value(1, 0)
	put_integer(4, 1)
	pseudo_instr3(2, 2, 1, 0)
	get_x_value(3, 0)
	proceed

$7:
	get_constant('offset', 0)
	put_integer(0, 4)
	pseudo_instr3(24, 0, 2, 4)
	get_x_value(1, 0)
	put_integer(2, 1)
	pseudo_instr3(2, 2, 1, 0)
	get_x_value(3, 0)
	proceed
end('$get_instr_arg'/4):



'$display_list'/1:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(1, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(1)
	unify_y_variable(0)
	call_predicate('write', 1, 1)
	call_predicate('nl', 0, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$display_list', 1)
end('$display_list'/1):



