'call'/1:


$1:
	pseudo_instr1(7, 1)
	execute_predicate('$call_2', 2)
end('call'/1):



'$call_2'/2:

	switch_on_term(0, $20, $19, $11, $12, $19, $16)

$11:
	try(2, $1)
	retry($2)
	retry($7)
	retry($9)
	trust($10)

$12:
	switch_on_structure(0, 8, ['$default':$19, '$'/0:$13, ','/2:$14, ';'/2:$15])

$13:
	try(2, $1)
	retry($3)
	retry($4)
	retry($5)
	retry($7)
	retry($9)
	trust($10)

$14:
	try(2, $1)
	retry($3)
	retry($7)
	retry($9)
	trust($10)

$15:
	try(2, $1)
	retry($4)
	retry($5)
	retry($7)
	retry($9)
	trust($10)

$16:
	switch_on_constant(0, 4, ['$default':$19, '!':$17, 'trace':$18])

$17:
	try(2, $1)
	retry($6)
	retry($7)
	retry($9)
	trust($10)

$18:
	try(2, $1)
	retry($7)
	retry($8)
	retry($9)
	trust($10)

$19:
	try(2, $1)
	retry($7)
	retry($9)
	trust($10)

$20:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	trust($10)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(1, 0)
	set_constant('call')
	set_x_value(2)
	put_structure(1, 1)
	set_constant('+')
	set_constant('nonvar')
	put_structure(1, 3)
	set_constant('call')
	set_x_value(1)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(1)
	unify_y_variable(0)
	neck_cut
	call_predicate('consult', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('consult', 1)

$3:
	get_structure(',', 2, 0)
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_y_variable(0, 1)
	neck_cut
	call_predicate('$call_2', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$call_2', 2)

$4:
	get_structure(';', 2, 0)
	unify_x_variable(0)
	unify_x_variable(2)
	get_x_variable(3, 1)
	pseudo_instr1(46, 0)
	get_structure('->', 2, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	neck_cut
	execute_predicate('$ite_call', 4)

$5:
	get_structure(';', 2, 0)
	unify_x_variable(0)
	unify_x_variable(3)
	get_x_variable(2, 1)
	neck_cut
	put_x_value(3, 1)
	execute_predicate('$or_call', 3)

$6:
	get_constant('!', 0)
	neck_cut
	pseudo_instr1(9, 1)
	proceed

$7:
	put_constant('$debugger_status', 2)
	pseudo_instr2(73, 2, 1)
	put_constant('off', 2)
	get_x_value(1, 2)
	neck_cut
	execute_predicate('call_predicate', 1)

$8:
	get_constant('trace', 0)
	neck_cut
	put_constant('trace', 0)
	execute_predicate('call_predicate', 1)

$9:
	allocate(2)
	get_y_variable(0, 0)
	pseudo_instr1(68, 0)
	get_y_level(1)
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	call_predicate('$thread_debug_set', 3, 2)
	cut(1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('$debug_call', 1)

$10:
	execute_predicate('call_predicate', 1)
end('$call_2'/2):



'$ite_call'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 1)
	get_y_variable(0, 3)
	get_y_level(2)
	put_y_value(0, 1)
	call_predicate('$call_2', 2, 3)
	cut(2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$call_2', 2)

$2:
	get_x_variable(0, 2)
	get_x_variable(1, 3)
	execute_predicate('$call_2', 2)
end('$ite_call'/4):



'$or_call'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_variable(1, 2)
	execute_predicate('$call_2', 2)

$2:
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	execute_predicate('$call_2', 2)
end('$or_call'/3):



','/2:


$1:
	allocate(1)
	get_y_variable(0, 1)
	call_predicate('call', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call', 1)
end(','/2):



';'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 1)
	pseudo_instr1(46, 0)
	get_structure('->', 2, 0)
	unify_x_variable(0)
	unify_x_variable(1)
	neck_cut
	execute_predicate('$$if_then_else', 3)

$2:
	pseudo_instr1(7, 2)
	execute_predicate('$call_or', 3)
end(';'/2):



'$$if_then_else'/3:


$1:
	get_x_variable(3, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	pseudo_instr1(7, 2)
	put_structure(2, 4)
	set_constant(',')
	set_constant('!')
	set_x_value(0)
	put_structure(2, 0)
	set_constant(',')
	set_x_value(3)
	set_x_value(4)
	execute_predicate('$call_or', 3)
end('$$if_then_else'/3):



'$call_or'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_variable(1, 2)
	execute_predicate('$call_2', 2)

$2:
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	execute_predicate('$call_2', 2)
end('$call_or'/3):



'call_with_inlining'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr2(92, 0, 1)
	get_x_variable(2, 1)
	allocate(2)
	get_y_level(1)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	put_y_variable(0, 3)
	call_predicate('$inline', 4, 2)
	cut(1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('call_with_inlining', 1)

$2:
	execute_predicate('call_predicate', 1)
end('call_with_inlining'/1):



'call_predicate'/1:


$1:
	pseudo_instr1(19, 0)
	proceed
end('call_predicate'/1):



'call_predicate'/2:


$1:
	pseudo_instr2(68, 0, 1)
	proceed
end('call_predicate'/2):



'call_predicate'/3:


$1:
	pseudo_instr3(37, 0, 1, 2)
	proceed
end('call_predicate'/3):



'call_predicate'/4:


$1:
	pseudo_instr4(8, 0, 1, 2, 3)
	proceed
end('call_predicate'/4):



'call_predicate'/5:


$1:
	pseudo_instr5(1, 0, 1, 2, 3, 4)
	proceed
end('call_predicate'/5):



'$call_clause'/2:


$1:
	execute_predicate('$call_clause_psi', 2)
end('$call_clause'/2):



