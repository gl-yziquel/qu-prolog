'write'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(28, 0)
	put_constant('write', 2)
	put_integer(1200, 3)
	put_integer(1, 4)
	allocate(0)
	call_predicate('$write_term', 5, 0)
	fail

$2:
	proceed
end('write'/1):



'writeq'/1:

	try(1, $1)
	trust($2)

$1:
	get_x_variable(1, 0)
	pseudo_instr1(28, 0)
	put_constant('writeq', 2)
	put_integer(1200, 3)
	put_integer(1, 4)
	allocate(0)
	call_predicate('$write_term', 5, 0)
	fail

$2:
	proceed
end('writeq'/1):



'writeR'/1:


$1:
	pseudo_instr1(53, 0)
	execute_predicate('write', 1)
end('writeR'/1):



'writeRq'/1:


$1:
	pseudo_instr1(53, 0)
	execute_predicate('writeq', 1)
end('writeRq'/1):



'writeT'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	put_y_value(0, 0)
	put_structure(2, 1)
	set_constant('writeT')
	set_y_value(1)
	set_y_value(0)
	call_predicate('$legal_write_table', 2, 2)
	pseudo_instr1(28, 0)
	put_y_value(1, 1)
	put_structure(1, 2)
	set_constant('writeT')
	set_y_value(0)
	put_integer(1200, 3)
	put_integer(1, 4)
	call_predicate('$write_term', 5, 0)
	fail

$2:
	proceed
end('writeT'/2):



'writeTq'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	put_y_value(0, 0)
	put_structure(2, 1)
	set_constant('writeTq')
	set_y_value(1)
	set_y_value(0)
	call_predicate('$legal_write_table', 2, 2)
	pseudo_instr1(28, 0)
	put_y_value(1, 1)
	put_structure(1, 2)
	set_constant('writeTq')
	set_y_value(0)
	put_integer(1200, 3)
	put_integer(1, 4)
	call_predicate('$write_term', 5, 0)
	fail

$2:
	proceed
end('writeTq'/2):



'writeRT'/2:


$1:
	pseudo_instr1(53, 0)
	execute_predicate('writeT', 2)
end('writeRT'/2):



'writeRTq'/2:


$1:
	pseudo_instr1(53, 0)
	execute_predicate('writeTq', 2)
end('writeRTq'/2):



'write'/2:

	try(2, $1)
	trust($2)

$1:
	put_constant('write', 2)
	put_integer(1200, 3)
	put_integer(1, 4)
	allocate(0)
	call_predicate('$write_term', 5, 0)
	fail

$2:
	proceed
end('write'/2):



'writeq'/2:

	try(2, $1)
	trust($2)

$1:
	put_constant('writeq', 2)
	put_integer(1200, 3)
	put_integer(1, 4)
	allocate(0)
	call_predicate('$write_term', 5, 0)
	fail

$2:
	proceed
end('writeq'/2):



'writeR'/2:


$1:
	pseudo_instr1(53, 1)
	execute_predicate('write', 2)
end('writeR'/2):



'writeRq'/2:


$1:
	pseudo_instr1(53, 1)
	execute_predicate('writeq', 2)
end('writeRq'/2):



'writeT'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	put_y_value(0, 0)
	put_structure(3, 1)
	set_constant('writeT')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	call_predicate('$legal_write_table', 2, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_structure(1, 2)
	set_constant('writeT')
	set_y_value(0)
	put_integer(1200, 3)
	put_integer(1, 4)
	call_predicate('$write_term', 5, 0)
	fail

$2:
	proceed
end('writeT'/3):



'writeTq'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	put_y_value(0, 0)
	put_structure(3, 1)
	set_constant('writeTq')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	call_predicate('$legal_write_table', 2, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_structure(1, 2)
	set_constant('writeTq')
	set_y_value(0)
	put_integer(1200, 3)
	put_integer(1, 4)
	call_predicate('$write_term', 5, 0)
	fail

$2:
	proceed
end('writeTq'/3):



'writeRT'/3:


$1:
	pseudo_instr1(53, 1)
	execute_predicate('writeT', 3)
end('writeRT'/3):



'writeRTq'/3:


$1:
	pseudo_instr1(53, 1)
	execute_predicate('writeTq', 3)
end('writeRTq'/3):



'write_canonical'/1:


$1:
	get_x_variable(1, 0)
	pseudo_instr1(28, 0)
	execute_predicate('write_canonical', 2)
end('write_canonical'/1):



'write_canonical'/2:


$1:
	put_structure(1, 2)
	set_constant('ignore_ops')
	set_constant('true')
	put_list(3)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 4)
	set_constant('quoted')
	set_constant('true')
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	execute_predicate('write_term', 3)
end('write_canonical'/2):



'portray_clause'/1:


$1:
	get_x_variable(1, 0)
	pseudo_instr1(28, 0)
	execute_predicate('portray_clause', 2)
end('portray_clause'/1):



'portray_clause'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(0)
	call_predicate('$portray_clause', 2, 0)
	fail

$2:
	proceed
end('portray_clause'/2):



'$portray_clause'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	allocate(2)
	get_y_variable(1, 1)
	pseudo_instr1(1, 21)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 2)
	pseudo_instr1(53, 21)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_constant('writeq', 2)
	call_predicate('$write_t', 3, 1)
	put_integer(46, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(10, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$2:
	get_structure(':-', 2, 1)
	allocate(2)
	unify_y_variable(1)
	unify_x_variable(1)
	put_constant('true', 2)
	pseudo_instr2(110, 1, 2)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 2)
	pseudo_instr1(53, 21)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_constant('writeq', 2)
	call_predicate('$write_t', 3, 1)
	put_integer(46, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(10, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$3:
	allocate(4)
	get_y_variable(1, 0)
	get_structure(':-', 2, 1)
	unify_y_variable(3)
	unify_y_variable(0)
	neck_cut
	put_y_variable(2, 1)
	call_predicate('$streamnum', 2, 4)
	pseudo_instr1(53, 23)
	put_y_value(2, 0)
	put_y_value(3, 1)
	put_constant('writeq', 2)
	call_predicate('$write_t', 3, 3)
	put_y_value(2, 0)
	put_constant(' :- ', 1)
	call_predicate('write_atom', 2, 3)
	put_integer(10, 0)
	pseudo_instr2(8, 22, 0)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_integer(4, 2)
	put_constant('.', 3)
	deallocate
	execute_predicate('$portray_clause_body', 4)

$4:
	allocate(2)
	get_y_variable(1, 1)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 2)
	pseudo_instr1(53, 21)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_constant('writeq', 2)
	call_predicate('$write_t', 3, 1)
	put_integer(46, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(10, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed
end('$portray_clause'/2):



'$portray_clause_body'/4:

	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$1:
	allocate(4)
	get_y_variable(2, 1)
	get_y_variable(3, 2)
	get_y_variable(1, 3)
	pseudo_instr1(1, 22)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	call_predicate('$tab', 2, 3)
	pseudo_instr1(53, 22)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_constant('writeq', 2)
	call_predicate('$write_t', 3, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('write_atom', 2, 1)
	put_integer(10, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$2:
	allocate(4)
	get_y_variable(3, 0)
	get_structure(',', 2, 1)
	unify_x_variable(1)
	unify_y_variable(2)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	neck_cut
	put_constant(',', 3)
	call_predicate('$portray_clause_body', 4, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$portray_clause_body', 4)

$3:
	allocate(9)
	get_y_variable(3, 0)
	get_structure(';', 2, 1)
	unify_y_variable(7)
	unify_y_variable(5)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	pseudo_instr1(1, 27)
	neck_cut
	put_y_variable(8, 1)
	call_predicate('$streamnum', 2, 9)
	put_y_value(8, 0)
	put_y_value(2, 1)
	call_predicate('$tab', 2, 9)
	put_integer(40, 0)
	pseudo_instr2(8, 28, 0)
	put_integer(10, 0)
	pseudo_instr2(8, 28, 0)
	put_integer(2, 1)
	pseudo_instr3(2, 22, 1, 0)
	get_y_variable(4, 0)
	put_y_value(3, 0)
	put_y_value(7, 1)
	put_y_value(4, 2)
	put_constant(' ', 3)
	call_predicate('$portray_clause_body', 4, 7)
	put_y_value(3, 0)
	put_y_variable(6, 1)
	call_predicate('$streamnum', 2, 7)
	put_y_value(6, 0)
	put_y_value(2, 1)
	call_predicate('$tab', 2, 7)
	put_integer(59, 0)
	pseudo_instr2(8, 26, 0)
	put_integer(10, 0)
	pseudo_instr2(8, 26, 0)
	put_y_value(3, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_constant(' ', 3)
	call_predicate('$portray_clause_body', 4, 4)
	put_y_value(3, 0)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	call_predicate('$tab', 2, 2)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('write_atom', 2, 1)
	put_integer(10, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$4:
	allocate(11)
	get_y_variable(3, 0)
	get_structure(';', 2, 1)
	unify_x_ref(0)
	unify_y_variable(5)
	get_structure('->', 2, 0)
	unify_y_variable(10)
	unify_y_variable(8)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	neck_cut
	put_integer(2, 1)
	pseudo_instr3(2, 22, 1, 0)
	get_y_variable(7, 0)
	put_y_value(3, 0)
	put_y_variable(9, 1)
	call_predicate('$streamnum', 2, 11)
	put_y_value(9, 0)
	put_y_value(2, 1)
	call_predicate('$tab', 2, 11)
	put_y_value(9, 0)
	put_constant('( ', 1)
	call_predicate('write_atom', 2, 11)
	pseudo_instr1(53, 30)
	put_y_value(9, 0)
	put_y_value(10, 1)
	put_constant('writeq', 2)
	call_predicate('$write_t', 3, 10)
	put_integer(10, 0)
	pseudo_instr2(8, 29, 0)
	put_y_value(9, 0)
	put_y_value(7, 1)
	call_predicate('$tab', 2, 10)
	put_y_value(9, 0)
	put_constant('->', 1)
	call_predicate('write_atom', 2, 10)
	put_integer(10, 0)
	pseudo_instr2(8, 29, 0)
	put_integer(2, 1)
	pseudo_instr3(2, 27, 1, 0)
	get_y_variable(4, 0)
	put_y_value(3, 0)
	put_y_value(8, 1)
	put_y_value(4, 2)
	put_constant(' ', 3)
	call_predicate('$portray_clause_body', 4, 8)
	put_y_value(3, 0)
	put_y_variable(6, 1)
	call_predicate('$streamnum', 2, 8)
	put_y_value(6, 0)
	put_y_value(7, 1)
	call_predicate('$tab', 2, 7)
	put_integer(59, 0)
	pseudo_instr2(8, 26, 0)
	put_integer(10, 0)
	pseudo_instr2(8, 26, 0)
	put_y_value(3, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_constant(' ', 3)
	call_predicate('$portray_clause_body', 4, 4)
	put_y_value(3, 0)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	call_predicate('$tab', 2, 2)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('write_atom', 2, 1)
	put_integer(10, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$5:
	allocate(9)
	get_y_variable(3, 0)
	get_structure(';', 2, 1)
	unify_y_variable(7)
	unify_y_variable(5)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	neck_cut
	put_y_variable(8, 1)
	call_predicate('$streamnum', 2, 9)
	put_y_value(8, 0)
	put_y_value(2, 1)
	call_predicate('$tab', 2, 9)
	put_integer(40, 0)
	pseudo_instr2(8, 28, 0)
	put_integer(10, 0)
	pseudo_instr2(8, 28, 0)
	put_integer(2, 1)
	pseudo_instr3(2, 22, 1, 0)
	get_y_variable(4, 0)
	put_y_value(3, 0)
	put_y_value(7, 1)
	put_y_value(4, 2)
	put_constant(' ', 3)
	call_predicate('$portray_clause_body', 4, 7)
	put_y_value(3, 0)
	put_y_variable(6, 1)
	call_predicate('$streamnum', 2, 7)
	put_y_value(6, 0)
	put_y_value(2, 1)
	call_predicate('$tab', 2, 7)
	put_integer(59, 0)
	pseudo_instr2(8, 26, 0)
	put_integer(10, 0)
	pseudo_instr2(8, 26, 0)
	put_y_value(3, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_constant(' ', 3)
	call_predicate('$portray_clause_body', 4, 4)
	put_y_value(3, 0)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	call_predicate('$tab', 2, 2)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('write_atom', 2, 1)
	put_integer(10, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$6:
	get_structure('\\+', 1, 1)
	unify_x_variable(1)
	get_x_variable(5, 2)
	get_x_variable(4, 3)
	neck_cut
	put_x_value(1, 2)
	put_x_value(5, 3)
	put_constant('\\+', 1)
	execute_predicate('$portray_inner_goal', 5)

$7:
	get_structure('once', 1, 1)
	unify_x_variable(1)
	get_x_variable(5, 2)
	get_x_variable(4, 3)
	neck_cut
	put_x_value(1, 2)
	put_x_value(5, 3)
	put_constant('once', 1)
	execute_predicate('$portray_inner_goal', 5)

$8:
	allocate(4)
	get_y_variable(2, 1)
	get_y_variable(3, 2)
	get_y_variable(1, 3)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	call_predicate('$tab', 2, 3)
	pseudo_instr1(53, 22)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_constant('writeq', 2)
	call_predicate('$write_t', 3, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('write_atom', 2, 1)
	put_integer(10, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed
end('$portray_clause_body'/4):



'$portray_inner_goal'/5:

	try(5, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	allocate(5)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_variable(4, 3)
	get_y_variable(1, 4)
	pseudo_instr1(1, 22)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 5)
	put_y_value(0, 0)
	put_y_value(4, 1)
	call_predicate('$tab', 2, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	call_predicate('write_atom', 2, 3)
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	pseudo_instr1(53, 22)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_constant('writeq', 2)
	call_predicate('$write_t', 3, 2)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('write_atom', 2, 1)
	put_integer(10, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$2:
	allocate(8)
	get_y_variable(3, 0)
	get_y_variable(7, 1)
	get_structure(',', 2, 2)
	unify_y_variable(5)
	unify_y_variable(4)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	neck_cut
	put_y_variable(6, 1)
	call_predicate('$streamnum', 2, 8)
	put_y_value(6, 0)
	put_y_value(2, 1)
	call_predicate('$tab', 2, 8)
	put_y_value(6, 0)
	put_y_value(7, 1)
	call_predicate('write_atom', 2, 7)
	put_integer(40, 0)
	pseudo_instr2(8, 26, 0)
	put_integer(40, 0)
	pseudo_instr2(8, 26, 0)
	put_integer(10, 0)
	pseudo_instr2(8, 26, 0)
	put_integer(2, 1)
	pseudo_instr3(2, 22, 1, 0)
	get_x_variable(2, 0)
	put_y_value(3, 0)
	put_structure(2, 1)
	set_constant(',')
	set_y_value(5)
	set_y_value(4)
	put_constant(' ', 3)
	call_predicate('$portray_clause_body', 4, 4)
	put_y_value(3, 0)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	call_predicate('$tab', 2, 2)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('write_atom', 2, 1)
	put_integer(10, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$3:
	allocate(8)
	get_y_variable(3, 0)
	get_y_variable(7, 1)
	get_structure(';', 2, 2)
	unify_y_variable(5)
	unify_y_variable(4)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	neck_cut
	put_y_variable(6, 1)
	call_predicate('$streamnum', 2, 8)
	put_y_value(6, 0)
	put_y_value(2, 1)
	call_predicate('$tab', 2, 8)
	put_y_value(6, 0)
	put_y_value(7, 1)
	call_predicate('write_atom', 2, 7)
	put_integer(40, 0)
	pseudo_instr2(8, 26, 0)
	put_integer(10, 0)
	pseudo_instr2(8, 26, 0)
	put_integer(2, 1)
	pseudo_instr3(2, 22, 1, 0)
	get_x_variable(2, 0)
	put_y_value(3, 0)
	put_structure(2, 1)
	set_constant(';')
	set_y_value(5)
	set_y_value(4)
	put_constant(' ', 3)
	call_predicate('$portray_clause_body', 4, 4)
	put_y_value(3, 0)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	call_predicate('$tab', 2, 2)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('write_atom', 2, 1)
	put_integer(10, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$4:
	allocate(5)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_variable(4, 3)
	get_y_variable(1, 4)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 5)
	put_y_value(0, 0)
	put_y_value(4, 1)
	call_predicate('$tab', 2, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	call_predicate('write_atom', 2, 3)
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	pseudo_instr1(53, 22)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_constant('writeq', 2)
	call_predicate('$write_t', 3, 2)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('write_atom', 2, 1)
	put_integer(10, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed
end('$portray_inner_goal'/5):



'$legal_write_table/2$0'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_variable(4, 0)
	get_x_variable(0, 2)
	put_integer(2, 2)
	get_x_value(4, 2)
	neck_cut
	put_integer(1, 3)
	pseudo_instr3(1, 3, 1, 2)
	get_structure('@', 1, 2)
	unify_constant('term')
	put_integer(2, 3)
	pseudo_instr3(1, 3, 1, 2)
	get_structure('@', 1, 2)
	unify_constant('atom')
	put_list(2)
	set_x_value(1)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	get_x_variable(4, 0)
	get_x_variable(0, 2)
	put_integer(1, 5)
	pseudo_instr3(1, 5, 1, 2)
	get_structure('@', 1, 2)
	unify_constant('atom')
	put_integer(2, 5)
	pseudo_instr3(1, 5, 1, 2)
	get_structure('@', 1, 2)
	unify_constant('term')
	put_integer(3, 5)
	pseudo_instr3(1, 5, 1, 2)
	get_structure('@', 1, 2)
	unify_constant('atom')
	put_x_variable(2, 2)
	pseudo_instr3(0, 2, 3, 4)
	put_integer(1, 4)
	pseudo_instr3(1, 4, 2, 3)
	get_structure('@', 1, 3)
	unify_constant('gcomp')
	put_integer(2, 4)
	pseudo_instr3(1, 4, 2, 3)
	get_structure('@', 1, 3)
	unify_constant('term')
	put_integer(3, 4)
	pseudo_instr3(1, 4, 2, 3)
	get_structure('@', 1, 3)
	unify_constant('atom')
	put_list(3)
	set_x_value(2)
	set_constant('[]')
	put_list(2)
	set_x_value(1)
	set_x_value(3)
	put_integer(3, 1)
	execute_predicate('instantiation_exception', 3)
end('$legal_write_table/2$0'/4):



'$legal_write_table/2$1'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_variable(4, 0)
	get_x_variable(0, 2)
	put_integer(2, 2)
	get_x_value(4, 2)
	neck_cut
	put_integer(1, 3)
	pseudo_instr3(1, 3, 1, 2)
	get_structure('@', 1, 2)
	unify_constant('term')
	put_integer(2, 3)
	pseudo_instr3(1, 3, 1, 2)
	get_structure('@', 1, 2)
	unify_constant('atom')
	put_list(2)
	set_x_value(1)
	set_constant('[]')
	put_integer(2, 1)
	execute_predicate('type_exception', 3)

$2:
	get_x_variable(4, 0)
	get_x_variable(0, 2)
	put_integer(1, 5)
	pseudo_instr3(1, 5, 1, 2)
	get_structure('@', 1, 2)
	unify_constant('atom')
	put_integer(2, 5)
	pseudo_instr3(1, 5, 1, 2)
	get_structure('@', 1, 2)
	unify_constant('term')
	put_integer(3, 5)
	pseudo_instr3(1, 5, 1, 2)
	get_structure('@', 1, 2)
	unify_constant('atom')
	put_x_variable(2, 2)
	pseudo_instr3(0, 2, 3, 4)
	put_integer(1, 4)
	pseudo_instr3(1, 4, 2, 3)
	get_structure('@', 1, 3)
	unify_constant('gcomp')
	put_integer(2, 4)
	pseudo_instr3(1, 4, 2, 3)
	get_structure('@', 1, 3)
	unify_constant('term')
	put_integer(3, 4)
	pseudo_instr3(1, 4, 2, 3)
	get_structure('@', 1, 3)
	unify_constant('atom')
	put_list(3)
	set_x_value(2)
	set_constant('[]')
	put_list(2)
	set_x_value(1)
	set_x_value(3)
	put_integer(3, 1)
	execute_predicate('type_exception', 3)
end('$legal_write_table/2$1'/4):



'$legal_write_table'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	proceed

$2:
	get_x_variable(2, 1)
	pseudo_instr1(1, 0)
	neck_cut
	put_x_variable(3, 3)
	put_x_variable(0, 0)
	pseudo_instr3(0, 2, 3, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 1, 3, 0)
	execute_predicate('$legal_write_table/2$0', 4)

$3:
	get_x_variable(2, 1)
	put_x_variable(3, 3)
	put_x_variable(0, 0)
	pseudo_instr3(0, 2, 3, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 1, 3, 0)
	execute_predicate('$legal_write_table/2$1', 4)
end('$legal_write_table'/2):



'write_term'/2:


$1:
	get_x_variable(3, 0)
	get_x_variable(2, 1)
	pseudo_instr1(28, 0)
	put_x_value(3, 1)
	execute_predicate('write_term', 3)
end('write_term'/2):



'write_term/3$0'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(2, 0)
	allocate(2)
	get_y_variable(0, 1)
	get_y_level(1)
	put_structure(1, 0)
	set_constant('remember_name')
	set_constant('true')
	put_x_value(2, 1)
	call_predicate('member', 2, 2)
	cut(1)
	pseudo_instr1(53, 20)
	deallocate
	proceed

$2:
	proceed
end('write_term/3$0'/2):



'write_term/3$1'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(11)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	put_y_variable(0, 1)
	get_structure('wflags', 8, 1)
	unify_y_variable(10)
	unify_y_variable(9)
	unify_y_variable(8)
	unify_y_variable(7)
	unify_y_variable(6)
	unify_y_variable(5)
	unify_y_variable(4)
	unify_y_variable(3)
	put_y_value(10, 1)
	put_y_value(9, 2)
	put_y_value(8, 3)
	put_y_value(7, 4)
	put_y_value(6, 5)
	put_y_value(5, 6)
	put_y_value(4, 7)
	put_y_value(3, 8)
	call_predicate('$set_write_options', 9, 11)
	put_y_value(10, 0)
	put_constant('false', 1)
	call_predicate('$io_try_eq', 2, 10)
	put_y_value(9, 0)
	put_constant('false', 1)
	call_predicate('$io_try_eq', 2, 9)
	put_y_value(8, 0)
	put_constant('false', 1)
	call_predicate('$io_try_eq', 2, 8)
	put_y_value(7, 0)
	put_constant('false', 1)
	call_predicate('$io_try_eq', 2, 7)
	put_constant('$current_op_table', 1)
	pseudo_instr2(73, 1, 0)
	get_x_variable(1, 0)
	put_y_value(6, 0)
	call_predicate('$io_try_eq', 2, 6)
	put_y_value(5, 0)
	put_integer(0, 1)
	call_predicate('$io_try_eq', 2, 5)
	put_constant('$current_obvar_prefix_table', 1)
	pseudo_instr2(73, 1, 0)
	get_x_variable(1, 0)
	put_y_value(4, 0)
	call_predicate('$io_try_eq', 2, 4)
	put_y_value(3, 0)
	put_constant('true', 1)
	call_predicate('$io_try_eq', 2, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	put_integer(1200, 3)
	put_integer(1, 4)
	call_predicate('$write_term', 5, 0)
	fail

$2:
	proceed
end('write_term/3$1'/3):



'write_term/3$2'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('closed_list', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('write_term/3$2'/1):



'write_term'/3:

	try(3, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_x_variable(3, 0)
	pseudo_instr1(1, 3)
	neck_cut
	put_structure(3, 0)
	set_constant('write_term')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_constant('term')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('write_term')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('term')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(3, 4)
	set_constant('write_term')
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(4)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_level(3)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 4)
	pseudo_instr2(101, 20, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('output')
	unify_void(5)
	put_y_value(1, 0)
	call_predicate('closed_list', 1, 4)
	cut(3)
	put_y_value(1, 0)
	put_y_value(2, 1)
	call_predicate('write_term/3$0', 2, 3)
	put_y_value(1, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('write_term/3$1', 3)

$3:
	get_x_variable(3, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(3, 0)
	set_constant('write_term')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_constant('term')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('write_term')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('term')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(3, 4)
	set_constant('write_term')
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(3, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	put_y_value(0, 0)
	call_predicate('write_term/3$2', 1, 4)
	cut(3)
	put_structure(3, 0)
	set_constant('write_term')
	set_y_value(2)
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_constant('term')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('write_term')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('term')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(3, 4)
	set_constant('write_term')
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(3, 1)
	put_constant('stream', 3)
	deallocate
	execute_predicate('type_exception', 4)

$5:
	get_x_variable(3, 0)
	put_structure(3, 0)
	set_constant('write_term')
	set_x_value(3)
	set_x_value(1)
	set_x_value(2)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_constant('term')
	put_structure(1, 3)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('@')
	set_x_value(3)
	put_structure(3, 3)
	set_constant('write_term')
	set_x_value(1)
	set_x_value(2)
	set_x_value(4)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_constant('term')
	put_structure(1, 4)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 5)
	set_constant('@')
	set_x_value(4)
	put_structure(3, 4)
	set_constant('write_term')
	set_x_value(2)
	set_x_value(3)
	set_x_value(5)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('stream', 3)
	execute_predicate('type_exception', 4)
end('write_term'/3):



'$io_try_eq'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	proceed
end('$io_try_eq'/2):



'$set_write_options'/9:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(9, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(9)
	unify_y_variable(8)
	get_y_variable(7, 1)
	get_y_variable(6, 2)
	get_y_variable(5, 3)
	get_y_variable(4, 4)
	get_y_variable(3, 5)
	get_y_variable(2, 6)
	get_y_variable(1, 7)
	get_y_variable(0, 8)
	call_predicate('$set_write_options1', 9, 9)
	put_y_value(8, 0)
	put_y_value(7, 1)
	put_y_value(6, 2)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_y_value(3, 5)
	put_y_value(2, 6)
	put_y_value(1, 7)
	put_y_value(0, 8)
	deallocate
	execute_predicate('$set_write_options', 9)
end('$set_write_options'/9):



'$set_write_options1'/9:

	switch_on_term(0, $11, 'fail', 'fail', $9, 'fail', 'fail')

$9:
	switch_on_structure(0, 32, ['default':'fail', '$'/0:$10, 'quoted'/1:$1, 'ignore_ops'/1:$2, 'numbervars'/1:$3, 'remember_name'/1:$4, 'op_table'/1:$5, 'max_depth'/1:$6, 'obvar_prefix_table'/1:$7, '$simplify'/1:$8])

$10:
	try(9, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$11:
	try(9, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$1:
	get_structure('quoted', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	proceed

$2:
	get_structure('ignore_ops', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 2)
	proceed

$3:
	get_structure('numbervars', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 3)
	proceed

$4:
	get_structure('remember_name', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 4)
	proceed

$5:
	get_structure('op_table', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 5)
	proceed

$6:
	get_structure('max_depth', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 6)
	proceed

$7:
	get_structure('obvar_prefix_table', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 7)
	proceed

$8:
	get_structure('$simplify', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 8)
	proceed
end('$set_write_options1'/9):



'$process_option'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('member', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	put_integer(1, 3)
	pseudo_instr3(1, 3, 0, 1)
	get_x_value(2, 1)
	proceed
end('$process_option'/3):



'$get_depth'/2:

	switch_on_term(0, $13, 'fail', 'fail', $10, 'fail', $12)

$10:
	switch_on_structure(0, 16, ['default':'fail', '$'/0:$11, 'wflags'/8:$1, 'writeT'/1:$6, 'writeTq'/1:$7, 'writeRT'/1:$8, 'writeRTq'/1:$9])

$11:
	try(2, $1)
	retry($6)
	retry($7)
	retry($8)
	trust($9)

$12:
	switch_on_constant(0, 8, ['default':'fail', 'write':$2, 'writeq':$3, 'writeR':$4, 'writeRq':$5])

$13:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	trust($9)

$1:
	get_structure('wflags', 8, 0)
	unify_void(5)
	unify_x_variable(0)
	unify_void(2)
	get_x_value(0, 1)
	proceed

$2:
	get_constant('write', 0)
	get_integer(0, 1)
	proceed

$3:
	get_constant('writeq', 0)
	get_integer(0, 1)
	proceed

$4:
	get_constant('writeR', 0)
	get_integer(0, 1)
	proceed

$5:
	get_constant('writeRq', 0)
	get_integer(0, 1)
	proceed

$6:
	get_integer(0, 1)
	get_structure('writeT', 1, 0)
	unify_void(1)
	proceed

$7:
	get_integer(0, 1)
	get_structure('writeTq', 1, 0)
	unify_void(1)
	proceed

$8:
	get_integer(0, 1)
	get_structure('writeRT', 1, 0)
	unify_void(1)
	proceed

$9:
	get_integer(0, 1)
	get_structure('writeRTq', 1, 0)
	unify_void(1)
	proceed
end('$get_depth'/2):



'$do_write_simplify'/1:

	switch_on_term(0, $13, 'fail', 'fail', $10, 'fail', $12)

$10:
	switch_on_structure(0, 16, ['default':'fail', '$'/0:$11, 'wflags'/8:$1, 'writeT'/1:$6, 'writeTq'/1:$7, 'writeRT'/1:$8, 'writeRTq'/1:$9])

$11:
	try(1, $1)
	retry($6)
	retry($7)
	retry($8)
	trust($9)

$12:
	switch_on_constant(0, 8, ['default':'fail', 'write':$2, 'writeq':$3, 'writeR':$4, 'writeRq':$5])

$13:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	trust($9)

$1:
	get_structure('wflags', 8, 0)
	unify_void(7)
	unify_constant('true')
	proceed

$2:
	get_constant('write', 0)
	proceed

$3:
	get_constant('writeq', 0)
	proceed

$4:
	get_constant('writeR', 0)
	proceed

$5:
	get_constant('writeRq', 0)
	proceed

$6:
	get_structure('writeT', 1, 0)
	unify_void(1)
	proceed

$7:
	get_structure('writeTq', 1, 0)
	unify_void(1)
	proceed

$8:
	get_structure('writeRT', 1, 0)
	unify_void(1)
	proceed

$9:
	get_structure('writeRTq', 1, 0)
	unify_void(1)
	proceed
end('$do_write_simplify'/1):



'$get_optable'/2:

	switch_on_term(0, $13, 'fail', 'fail', $10, 'fail', $12)

$10:
	switch_on_structure(0, 16, ['default':'fail', '$'/0:$11, 'wflags'/8:$1, 'writeT'/1:$6, 'writeRT'/1:$7, 'writeTq'/1:$8, 'writeRTq'/1:$9])

$11:
	try(2, $1)
	retry($6)
	retry($7)
	retry($8)
	trust($9)

$12:
	switch_on_constant(0, 8, ['default':'fail', 'write':$2, 'writeq':$3, 'writeR':$4, 'writeRq':$5])

$13:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	trust($9)

$1:
	get_structure('wflags', 8, 0)
	unify_void(4)
	unify_x_variable(0)
	unify_void(3)
	get_x_value(0, 1)
	proceed

$2:
	get_constant('write', 0)
	put_constant('$current_op_table', 2)
	pseudo_instr2(73, 2, 0)
	get_x_value(1, 0)
	proceed

$3:
	get_constant('writeq', 0)
	put_constant('$current_op_table', 2)
	pseudo_instr2(73, 2, 0)
	get_x_value(1, 0)
	proceed

$4:
	get_constant('writeR', 0)
	put_constant('$current_op_table', 2)
	pseudo_instr2(73, 2, 0)
	get_x_value(1, 0)
	proceed

$5:
	get_constant('writeRq', 0)
	put_constant('$current_op_table', 2)
	pseudo_instr2(73, 2, 0)
	get_x_value(1, 0)
	proceed

$6:
	get_structure('writeT', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	proceed

$7:
	get_structure('writeRT', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	proceed

$8:
	get_structure('writeTq', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	proceed

$9:
	get_structure('writeRTq', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	proceed
end('$get_optable'/2):



'$get_obprefix'/2:

	switch_on_term(0, $13, 'fail', 'fail', $10, 'fail', $12)

$10:
	switch_on_structure(0, 16, ['default':'fail', '$'/0:$11, 'wflags'/8:$1, 'writeT'/1:$6, 'writeRT'/1:$7, 'writeTq'/1:$8, 'writeRTq'/1:$9])

$11:
	try(2, $1)
	retry($6)
	retry($7)
	retry($8)
	trust($9)

$12:
	switch_on_constant(0, 8, ['default':'fail', 'write':$2, 'writeq':$3, 'writeR':$4, 'writeRq':$5])

$13:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	trust($9)

$1:
	get_structure('wflags', 8, 0)
	unify_void(6)
	unify_x_variable(0)
	unify_void(1)
	get_x_value(0, 1)
	proceed

$2:
	get_constant('write', 0)
	put_constant('$current_obvar_prefix_table', 2)
	pseudo_instr2(73, 2, 0)
	get_x_value(1, 0)
	proceed

$3:
	get_constant('writeq', 0)
	put_constant('$current_obvar_prefix_table', 2)
	pseudo_instr2(73, 2, 0)
	get_x_value(1, 0)
	proceed

$4:
	get_constant('writeR', 0)
	put_constant('$current_obvar_prefix_table', 2)
	pseudo_instr2(73, 2, 0)
	get_x_value(1, 0)
	proceed

$5:
	get_constant('writeRq', 0)
	put_constant('$current_obvar_prefix_table', 2)
	pseudo_instr2(73, 2, 0)
	get_x_value(1, 0)
	proceed

$6:
	get_structure('writeT', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	proceed

$7:
	get_structure('writeRT', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	proceed

$8:
	get_structure('writeTq', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	proceed

$9:
	get_structure('writeRTq', 1, 0)
	unify_x_variable(0)
	get_x_value(0, 1)
	proceed
end('$get_obprefix'/2):



'$do_name_vars/1$0'/2:

	try(2, $1)
	trust($2)

$1:
	put_constant('true', 1)
	get_x_value(0, 1)
	proceed

$2:
	put_constant('true', 0)
	get_x_value(1, 0)
	proceed
end('$do_name_vars/1$0'/2):



'$do_name_vars'/1:

	switch_on_term(0, $9, 'fail', 'fail', $6, 'fail', $8)

$6:
	switch_on_structure(0, 8, ['default':'fail', '$'/0:$7, 'wflags'/8:$1, 'writeRT'/1:$4, 'writeRTq'/1:$5])

$7:
	try(1, $1)
	retry($4)
	trust($5)

$8:
	switch_on_constant(0, 4, ['default':'fail', 'writeR':$2, 'writeRq':$3])

$9:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_structure('wflags', 8, 0)
	unify_void(2)
	unify_x_variable(0)
	unify_x_variable(1)
	unify_void(4)
	execute_predicate('$do_name_vars/1$0', 2)

$2:
	get_constant('writeR', 0)
	proceed

$3:
	get_constant('writeRq', 0)
	proceed

$4:
	get_structure('writeRT', 1, 0)
	unify_void(1)
	proceed

$5:
	get_structure('writeRTq', 1, 0)
	unify_void(1)
	proceed
end('$do_name_vars'/1):



'$do_writeq_obvar'/1:

	switch_on_term(0, $9, 'fail', 'fail', $6, 'fail', $8)

$6:
	switch_on_structure(0, 8, ['default':'fail', '$'/0:$7, 'wflags'/8:$1, 'writeRTq'/1:$4, 'writeTq'/1:$5])

$7:
	try(1, $1)
	retry($4)
	trust($5)

$8:
	switch_on_constant(0, 4, ['default':'fail', 'writeq':$2, 'writeRq':$3])

$9:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_structure('wflags', 8, 0)
	unify_constant('true')
	unify_void(1)
	unify_constant('true')
	unify_void(5)
	proceed

$2:
	get_constant('writeq', 0)
	proceed

$3:
	get_constant('writeRq', 0)
	proceed

$4:
	get_structure('writeRTq', 1, 0)
	unify_void(1)
	proceed

$5:
	get_structure('writeTq', 1, 0)
	unify_void(1)
	proceed
end('$do_writeq_obvar'/1):



'$do_remember_name'/1:

	switch_on_term(0, $9, 'fail', 'fail', $6, 'fail', $8)

$6:
	switch_on_structure(0, 8, ['default':'fail', '$'/0:$7, 'wflags'/8:$1, 'writeRT'/1:$4, 'writeRTq'/1:$5])

$7:
	try(1, $1)
	retry($4)
	trust($5)

$8:
	switch_on_constant(0, 4, ['default':'fail', 'writeR':$2, 'writeRq':$3])

$9:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_structure('wflags', 8, 0)
	unify_void(3)
	unify_constant('true')
	unify_void(4)
	proceed

$2:
	get_constant('writeR', 0)
	proceed

$3:
	get_constant('writeRq', 0)
	proceed

$4:
	get_structure('writeRT', 1, 0)
	unify_void(1)
	proceed

$5:
	get_structure('writeRTq', 1, 0)
	unify_void(1)
	proceed
end('$do_remember_name'/1):



'$do_quote'/1:

	switch_on_term(0, $9, 'fail', 'fail', $6, 'fail', $8)

$6:
	switch_on_structure(0, 8, ['default':'fail', '$'/0:$7, 'wflags'/8:$1, 'writeTq'/1:$4, 'writeRTq'/1:$5])

$7:
	try(1, $1)
	retry($4)
	trust($5)

$8:
	switch_on_constant(0, 4, ['default':'fail', 'writeq':$2, 'writeRq':$3])

$9:
	try(1, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	get_structure('wflags', 8, 0)
	unify_constant('true')
	unify_void(2)
	unify_constant('true')
	unify_void(4)
	proceed

$2:
	get_constant('writeq', 0)
	proceed

$3:
	get_constant('writeRq', 0)
	proceed

$4:
	get_structure('writeTq', 1, 0)
	unify_void(1)
	proceed

$5:
	get_structure('writeRTq', 1, 0)
	unify_void(1)
	proceed
end('$do_quote'/1):



'$do_ignore_ops'/1:


$1:
	get_structure('wflags', 8, 0)
	unify_void(1)
	unify_constant('true')
	unify_void(6)
	proceed
end('$do_ignore_ops'/1):



'$write_term/5$0/5$0'/5:

	try(5, $1)
	trust($2)

$1:
	get_x_variable(5, 0)
	get_x_variable(0, 1)
	pseudo_instr1(6, 5)
	neck_cut
	put_x_value(5, 1)
	execute_predicate('$write_substitution', 4)

$2:
	get_x_variable(5, 0)
	get_x_variable(0, 1)
	get_x_variable(6, 3)
	get_x_variable(3, 4)
	put_x_value(5, 1)
	put_x_value(6, 4)
	execute_predicate('$write_term', 5)
end('$write_term/5$0/5$0'/5):



'$write_term/5$0'/5:

	try(5, $1)
	trust($2)

$1:
	allocate(7)
	get_y_variable(4, 0)
	get_y_variable(5, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_y_level(6)
	call_predicate('$do_write_simplify', 1, 7)
	cut(6)
	put_y_value(5, 0)
	put_y_variable(0, 1)
	call_predicate('$simplify_if_local', 2, 5)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(4, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$write_term/5$0/5$0', 5)

$2:
	get_x_variable(5, 0)
	get_x_variable(0, 2)
	put_x_value(5, 2)
	execute_predicate('$write_substitution', 4)
end('$write_term/5$0'/5):



'$write_term/5$1'/4:

	try(4, $1)
	trust($2)

$1:
	allocate(6)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(4, 2)
	get_y_variable(0, 3)
	put_y_variable(5, 1)
	call_predicate('$get_optable', 2, 6)
	put_y_value(5, 0)
	put_y_variable(3, 1)
	put_x_variable(2, 2)
	put_y_value(1, 3)
	call_predicate('current_op', 4, 5)
	pseudo_instr2(2, 24, 23)
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	call_predicate('$write_atom', 3, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$2:
	get_x_variable(4, 0)
	get_x_variable(0, 3)
	put_x_value(4, 2)
	execute_predicate('$write_atom', 3)
end('$write_term/5$1'/4):



'$write_term'/5:

	try(5, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	trust($9)

$1:
	allocate(5)
	get_y_variable(1, 0)
	get_y_variable(0, 2)
	get_y_variable(3, 4)
	get_y_level(2)
	put_y_value(0, 0)
	put_y_variable(4, 1)
	call_predicate('$get_depth', 2, 5)
	put_integer(0, 0)
	pseudo_instr2(1, 0, 24)
	pseudo_instr2(1, 24, 23)
	cut(2)
	put_y_value(1, 0)
	put_y_value(0, 2)
	put_constant('...', 1)
	deallocate
	execute_predicate('$write_atom', 3)

$2:
	get_x_variable(5, 0)
	get_x_variable(0, 2)
	get_x_variable(6, 3)
	get_x_variable(3, 4)
	pseudo_instr1(6, 1)
	neck_cut
	put_x_value(5, 2)
	put_x_value(6, 4)
	execute_predicate('$write_term/5$0', 5)

$3:
	pseudo_instr1(4, 1)
	neck_cut
	execute_predicate('$write_obvar', 3)

$4:
	get_x_variable(5, 2)
	get_x_variable(2, 3)
	pseudo_instr1(5, 1)
	neck_cut
	put_x_value(5, 3)
	execute_predicate('$write_quantification', 5)

$5:
	pseudo_instr1(1, 1)
	neck_cut
	execute_predicate('$write_var', 3)

$6:
	get_x_variable(5, 0)
	get_x_variable(0, 2)
	get_x_variable(2, 3)
	pseudo_instr1(2, 1)
	neck_cut
	allocate(1)
	get_y_level(0)
	put_x_value(5, 3)
	call_predicate('$write_term/5$1', 4, 1)
	cut(0)
	deallocate
	proceed

$7:
	pseudo_instr1(3, 1)
	neck_cut
	execute_predicate('write_integer', 2)

$8:
	allocate(1)
	get_y_level(0)
	call_predicate('$write_structure', 5, 1)
	cut(0)
	deallocate
	proceed

$9:
	put_constant('fail in $write_term/5', 0)
	allocate(0)
	call_predicate('errornl', 1, 0)
	fail
end('$write_term'/5):



'$locals_in_sub'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	put_integer(0, 1)
	call_predicate('$no_locals_in_sub', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('$locals_in_sub'/1):



'$no_locals_in_sub/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(35, 0)
	neck_cut
	fail

$2:
	proceed
end('$no_locals_in_sub/2$0'/1):



'$no_locals_in_sub'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr1(18, 1)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	allocate(2)
	get_y_variable(1, 0)
	pseudo_instr2(69, 1, 0)
	get_y_variable(0, 0)
	pseudo_instr3(17, 20, 21, 0)
	neck_cut
	call_predicate('$no_locals_in_sub/2$0', 1, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$no_locals_in_sub', 2)

$3:
	pseudo_instr2(26, 0, 1)
	get_x_variable(0, 1)
	put_integer(0, 1)
	execute_predicate('$no_locals_in_sub', 2)
end('$no_locals_in_sub'/2):



'$write_var'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_x_variable(0, 2)
	get_y_level(2)
	call_predicate('$do_name_vars', 1, 3)
	cut(2)
	pseudo_instr2(20, 21, 20)
	deallocate
	proceed

$2:
	pseudo_instr2(19, 0, 1)
	proceed
end('$write_var'/3):



'$write_obvar/3$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(2)
	call_predicate('$do_writeq_obvar', 1, 3)
	cut(2)
	pseudo_instr2(23, 21, 20)
	deallocate
	proceed

$2:
	pseudo_instr2(21, 1, 2)
	proceed
end('$write_obvar/3$0'/3):



'$write_obvar'/3:

	try(3, $1)
	trust($2)

$1:
	pseudo_instr1(35, 1)
	neck_cut
	put_integer(33, 1)
	pseudo_instr2(8, 0, 1)
	put_integer(108, 1)
	pseudo_instr2(8, 0, 1)
	proceed

$2:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	call_predicate('$write_obvar_escape', 3, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$write_obvar/3$0', 3)
end('$write_obvar'/3):



'$write_obvar_escape/3$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr2(62, 0, 2)
	get_x_variable(0, 2)
	neck_cut
	execute_predicate('obvar_name_to_prefix', 2)

$2:
	put_constant('x', 0)
	get_x_value(1, 0)
	proceed
end('$write_obvar_escape/3$0'/2):



'$write_obvar_escape'/3:

	try(3, $1)
	trust($2)

$1:
	get_x_variable(0, 1)
	allocate(4)
	get_y_variable(3, 2)
	get_y_level(0)
	put_y_variable(2, 1)
	call_predicate('$write_obvar_escape/3$0', 2, 4)
	put_y_value(3, 0)
	put_y_variable(1, 1)
	call_predicate('$get_obprefix', 2, 3)
	put_y_value(1, 0)
	put_y_value(2, 1)
	call_predicate('current_obvar_prefix', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	put_integer(33, 1)
	pseudo_instr2(8, 0, 1)
	proceed
end('$write_obvar_escape'/3):



'$write_atom/3$0'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(4)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(2)
	put_y_variable(3, 1)
	call_predicate('$get_obprefix', 2, 4)
	put_y_value(1, 0)
	put_y_value(3, 1)
	call_predicate('$check_obvar_syntax', 2, 3)
	cut(2)
	put_integer(39, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 1)
	call_predicate('write_atom', 2, 1)
	put_integer(39, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$2:
	get_x_variable(0, 2)
	execute_predicate('writeq_atom', 2)
end('$write_atom/3$0'/3):



'$write_atom'/3:

	try(3, $1)
	trust($2)

$1:
	allocate(4)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(3)
	put_y_value(0, 0)
	call_predicate('$do_quote', 1, 4)
	cut(3)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	deallocate
	execute_predicate('$write_atom/3$0', 3)

$2:
	pseudo_instr2(16, 0, 1)
	proceed
end('$write_atom'/3):



'$write_substitution/4$0'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_variable(5, 0)
	allocate(1)
	get_y_variable(0, 1)
	get_x_variable(4, 3)
	pseudo_instr1(50, 5)
	neck_cut
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_x_value(5, 1)
	put_integer(999, 3)
	call_predicate('$write_structure', 5, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$2:
	get_x_variable(5, 0)
	get_x_variable(0, 1)
	get_x_variable(4, 3)
	put_x_value(5, 1)
	put_integer(0, 3)
	execute_predicate('$write_term', 5)
end('$write_substitution/4$0'/4):



'$write_substitution'/4:


$1:
	allocate(4)
	get_y_variable(3, 0)
	get_x_variable(0, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	pseudo_instr2(24, 0, 1)
	pseudo_instr2(25, 0, 2)
	get_y_variable(0, 2)
	put_y_value(3, 0)
	put_y_value(2, 2)
	call_predicate('$write_subs', 4, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$write_substitution/4$0', 4)
end('$write_substitution'/4):



'$write_subs'/4:

	try(4, $1)
	retry($2)
	trust($3)

$1:
	allocate(3)
	get_y_variable(0, 0)
	get_y_variable(1, 2)
	get_x_variable(1, 3)
	get_y_level(2)
	put_y_value(1, 0)
	call_predicate('$get_depth', 2, 3)
	cut(2)
	put_integer(91, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 2)
	put_constant('...', 1)
	call_predicate('$write_atom', 3, 1)
	put_integer(93, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$2:
	pseudo_instr1(18, 0)
	get_x_value(1, 0)
	neck_cut
	proceed

$3:
	allocate(4)
	get_y_variable(0, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(3, 3)
	pseudo_instr2(26, 22, 0)
	get_x_variable(1, 0)
	put_y_value(0, 0)
	call_predicate('$write_subs', 4, 4)
	put_integer(91, 0)
	pseudo_instr2(8, 20, 0)
	pseudo_instr2(69, 23, 0)
	get_x_variable(3, 0)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	call_predicate('$write_sub', 4, 1)
	put_integer(93, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed
end('$write_subs'/4):



'$write_sub'/4:


$1:
	allocate(5)
	get_y_variable(3, 0)
	get_y_variable(4, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	put_integer(1, 1)
	pseudo_instr3(17, 1, 24, 0)
	get_y_variable(0, 0)
	neck_cut
	put_y_value(3, 0)
	put_y_value(4, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	put_integer(2, 1)
	call_predicate('$write_subrest', 5, 5)
	put_integer(1, 1)
	pseudo_instr3(18, 1, 24, 0)
	get_x_variable(1, 0)
	put_y_value(3, 0)
	put_y_value(0, 2)
	put_y_value(2, 3)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$write_subpair', 5)
end('$write_sub'/4):



'$write_subpair/5$0'/2:

	try(2, $1)
	trust($2)

$1:
	get_x_variable(5, 1)
	put_x_value(0, 1)
	put_x_variable(2, 2)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	put_constant('/', 0)
	execute_predicate('$binop_prec_assoc', 6)

$2:
	put_integer(400, 1)
	get_x_value(0, 1)
	put_integer(399, 0)
	proceed
end('$write_subpair/5$0'/2):



'$write_subpair'/5:


$1:
	allocate(7)
	get_y_variable(2, 0)
	get_y_variable(5, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	get_y_variable(4, 4)
	get_y_level(6)
	put_y_variable(3, 0)
	put_y_value(0, 1)
	call_predicate('$write_subpair/5$0', 2, 7)
	cut(6)
	put_y_value(2, 0)
	put_y_value(5, 1)
	put_y_value(0, 2)
	put_y_value(3, 3)
	put_y_value(4, 4)
	call_predicate('$write_term', 5, 3)
	put_integer(47, 0)
	pseudo_instr2(8, 22, 0)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$write_obvar', 3)
end('$write_subpair'/5):



'$write_subrest'/5:

	try(5, $1)
	trust($2)

$1:
	allocate(6)
	get_y_variable(0, 0)
	get_y_variable(5, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_y_variable(2, 4)
	pseudo_instr3(17, 25, 24, 0)
	get_y_variable(1, 0)
	neck_cut
	pseudo_instr2(69, 25, 0)
	get_x_variable(1, 0)
	put_y_value(0, 0)
	call_predicate('$write_subrest', 5, 6)
	pseudo_instr3(18, 25, 24, 0)
	get_x_variable(1, 0)
	put_y_value(0, 0)
	put_y_value(1, 2)
	put_y_value(3, 3)
	put_y_value(2, 4)
	call_predicate('$write_subpair', 5, 1)
	put_integer(44, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$2:
	proceed
end('$write_subrest'/5):



'$write_quantification/5$0/5$0'/5:

	try(5, $1)
	trust($2)

$1:
	get_x_variable(5, 1)
	allocate(2)
	get_y_variable(1, 2)
	get_x_variable(1, 3)
	get_y_variable(0, 4)
	pseudo_instr2(1, 0, 5)
	neck_cut
	put_y_value(1, 0)
	put_y_value(0, 2)
	call_predicate('$write_atom', 3, 2)
	put_integer(32, 0)
	pseudo_instr2(8, 21, 0)
	put_y_value(1, 0)
	put_y_value(0, 2)
	put_constant('...', 1)
	deallocate
	execute_predicate('$write_atom', 3)

$2:
	allocate(2)
	get_y_variable(0, 2)
	get_x_variable(1, 3)
	get_y_variable(1, 4)
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 2)
	call_predicate('$write_atom', 3, 2)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 2)
	put_constant('...', 1)
	call_predicate('$write_atom', 3, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed
end('$write_quantification/5$0/5$0'/5):



'$write_quantification/5$0'/5:

	try(5, $1)
	retry($2)
	trust($3)

$1:
	allocate(6)
	get_y_variable(4, 0)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	pseudo_instr1(2, 24)
	get_y_level(5)
	put_y_variable(0, 1)
	put_y_value(3, 2)
	call_predicate('$quantop_prec', 3, 6)
	cut(5)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(4, 3)
	put_y_value(3, 4)
	deallocate
	execute_predicate('$write_quantification/5$0/5$0', 5)

$2:
	get_x_variable(5, 0)
	allocate(2)
	get_y_variable(1, 1)
	get_y_variable(0, 3)
	put_integer(0, 0)
	pseudo_instr2(1, 0, 2)
	neck_cut
	put_integer(33, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(33, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_x_value(5, 1)
	put_y_value(1, 2)
	put_integer(0, 3)
	call_predicate('$write_term', 5, 2)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 2)
	put_constant('...', 1)
	deallocate
	execute_predicate('$write_atom', 3)

$3:
	get_x_variable(5, 0)
	allocate(2)
	get_y_variable(1, 1)
	get_y_variable(0, 3)
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(33, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(33, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_x_value(5, 1)
	put_y_value(1, 2)
	put_integer(0, 3)
	call_predicate('$write_term', 5, 2)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 2)
	put_constant('...', 1)
	call_predicate('$write_atom', 3, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed
end('$write_quantification/5$0'/5):



'$write_quantification/5$1/7$0'/8:

	try(8, $1)
	trust($2)

$1:
	allocate(6)
	get_y_variable(4, 0)
	get_x_variable(0, 1)
	get_y_variable(3, 2)
	get_x_variable(1, 3)
	get_y_variable(2, 4)
	get_y_variable(5, 5)
	get_y_variable(1, 6)
	get_y_variable(0, 7)
	pseudo_instr2(1, 24, 0)
	neck_cut
	put_y_value(3, 0)
	put_y_value(2, 2)
	call_predicate('$write_atom', 3, 6)
	put_integer(32, 0)
	pseudo_instr2(8, 23, 0)
	put_y_value(3, 0)
	put_y_value(5, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	call_predicate('$write_bvars', 4, 5)
	put_integer(32, 0)
	pseudo_instr2(8, 23, 0)
	put_y_value(3, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	put_y_value(4, 3)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$write_term', 5)

$2:
	allocate(6)
	get_y_variable(4, 0)
	get_y_variable(0, 2)
	get_x_variable(1, 3)
	get_y_variable(3, 4)
	get_y_variable(5, 5)
	get_y_variable(2, 6)
	get_y_variable(1, 7)
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(3, 2)
	call_predicate('$write_atom', 3, 6)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(5, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	call_predicate('$write_bvars', 4, 5)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(3, 2)
	put_y_value(4, 3)
	put_y_value(2, 4)
	call_predicate('$write_term', 5, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed
end('$write_quantification/5$1/7$0'/8):



'$write_quantification/5$1'/7:

	try(7, $1)
	retry($2)
	trust($3)

$1:
	allocate(9)
	get_y_variable(7, 0)
	get_y_variable(6, 1)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	get_y_variable(3, 4)
	get_y_variable(2, 5)
	get_y_variable(1, 6)
	pseudo_instr1(2, 27)
	get_y_level(8)
	put_y_variable(0, 1)
	put_y_value(6, 2)
	call_predicate('$quantop_prec', 3, 9)
	cut(8)
	put_y_value(0, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_y_value(7, 3)
	put_y_value(6, 4)
	put_y_value(3, 5)
	put_y_value(2, 6)
	put_y_value(1, 7)
	deallocate
	execute_predicate('$write_quantification/5$1/7$0', 8)

$2:
	get_x_variable(7, 0)
	allocate(5)
	get_y_variable(3, 1)
	get_y_variable(2, 3)
	get_y_variable(4, 4)
	get_y_variable(1, 5)
	get_y_variable(0, 6)
	put_integer(0, 0)
	pseudo_instr2(1, 0, 2)
	neck_cut
	put_integer(33, 0)
	pseudo_instr2(8, 22, 0)
	put_integer(33, 0)
	pseudo_instr2(8, 22, 0)
	put_y_value(2, 0)
	put_x_value(7, 1)
	put_y_value(3, 2)
	put_y_value(1, 4)
	put_integer(0, 3)
	call_predicate('$write_term', 5, 5)
	put_integer(32, 0)
	pseudo_instr2(8, 22, 0)
	put_y_value(2, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(1, 3)
	call_predicate('$write_bvars', 4, 4)
	put_integer(32, 0)
	pseudo_instr2(8, 22, 0)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(3, 2)
	put_y_value(1, 4)
	put_integer(0, 3)
	deallocate
	execute_predicate('$write_term', 5)

$3:
	get_x_variable(7, 0)
	allocate(5)
	get_y_variable(3, 1)
	get_y_variable(0, 3)
	get_y_variable(4, 4)
	get_y_variable(2, 5)
	get_y_variable(1, 6)
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(33, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(33, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_x_value(7, 1)
	put_y_value(3, 2)
	put_y_value(2, 4)
	put_integer(0, 3)
	call_predicate('$write_term', 5, 5)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	call_predicate('$write_bvars', 4, 4)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(3, 2)
	put_y_value(2, 4)
	put_integer(0, 3)
	call_predicate('$write_term', 5, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed
end('$write_quantification/5$1'/7):



'$write_quantification'/5:

	try(5, $1)
	trust($2)

$1:
	allocate(6)
	get_y_variable(3, 0)
	get_y_variable(4, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	get_y_variable(0, 4)
	get_y_level(5)
	put_y_value(1, 0)
	put_y_value(0, 1)
	call_predicate('$get_depth', 2, 6)
	cut(5)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	pseudo_instr4(7, 24, 0, 1, 2)
	put_y_value(1, 1)
	put_y_value(2, 2)
	put_y_value(3, 3)
	put_y_value(0, 4)
	deallocate
	execute_predicate('$write_quantification/5$0', 5)

$2:
	get_x_variable(7, 0)
	get_x_variable(8, 1)
	get_x_variable(1, 3)
	pseudo_instr2(69, 4, 0)
	get_x_variable(5, 0)
	put_x_variable(0, 0)
	put_x_variable(4, 4)
	put_x_variable(6, 6)
	pseudo_instr4(7, 8, 0, 4, 6)
	put_x_value(7, 3)
	execute_predicate('$write_quantification/5$1', 7)
end('$write_quantification'/5):



'$quantop_prec'/3:


$1:
	allocate(3)
	get_y_variable(2, 0)
	get_y_variable(1, 1)
	get_x_variable(0, 2)
	put_y_variable(0, 1)
	call_predicate('$get_optable', 2, 3)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(2, 3)
	put_constant('quant', 2)
	deallocate
	execute_predicate('current_op', 4)
end('$quantop_prec'/3):



'$write_bvars/4$0'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('$do_quote', 1, 1)
	cut(0)
	fail

$2:
	proceed
end('$write_bvars/4$0'/1):



'$write_bvars'/4:

	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	pseudo_instr1(1, 1)
	neck_cut
	execute_predicate('$write_var', 3)

$2:
	get_constant('[]', 1)
	put_integer(91, 1)
	pseudo_instr2(8, 0, 1)
	put_integer(93, 1)
	pseudo_instr2(8, 0, 1)
	proceed

$3:
	allocate(5)
	get_y_variable(3, 0)
	get_list(1)
	unify_y_variable(2)
	unify_x_variable(0)
	get_y_variable(1, 2)
	get_y_variable(0, 3)
	put_constant('[]', 2)
	pseudo_instr3(6, 0, 2, 1)
	put_constant('true', 0)
	get_x_value(1, 0)
	get_y_level(4)
	put_y_value(1, 0)
	call_predicate('$write_bvars/4$0', 1, 5)
	cut(4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$write_bvar', 4)

$4:
	allocate(3)
	get_y_variable(0, 0)
	get_y_variable(1, 2)
	get_x_variable(1, 3)
	get_y_level(2)
	put_y_value(1, 0)
	call_predicate('$get_depth', 2, 3)
	cut(2)
	put_integer(91, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 2)
	put_constant('...', 1)
	call_predicate('$write_atom', 3, 1)
	put_integer(93, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$5:
	allocate(4)
	get_y_variable(3, 0)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(2)
	get_y_variable(1, 2)
	pseudo_instr2(69, 3, 0)
	get_y_variable(0, 0)
	put_integer(91, 0)
	pseudo_instr2(8, 23, 0)
	put_y_value(3, 0)
	call_predicate('$write_bvar', 4, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$write_bvars_rest', 4)
end('$write_bvars'/4):



'$write_bvar/4$0'/5:

	try(5, $1)
	trust($2)

$1:
	allocate(7)
	get_y_variable(4, 0)
	get_y_variable(3, 1)
	get_y_variable(5, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_y_level(6)
	put_x_variable(1, 1)
	put_x_variable(2, 2)
	put_y_variable(0, 3)
	put_x_variable(4, 4)
	put_y_value(4, 5)
	put_constant(':', 0)
	call_predicate('$binop_prec_assoc', 6, 7)
	cut(6)
	put_y_value(3, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	call_predicate('$write_obvar', 3, 5)
	put_integer(58, 0)
	pseudo_instr2(8, 23, 0)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(4, 2)
	put_y_value(0, 3)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$write_term', 5)

$2:
	allocate(4)
	get_y_variable(3, 0)
	get_y_variable(0, 1)
	get_x_variable(1, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	put_integer(58, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(3, 2)
	call_predicate('$write_obvar', 3, 4)
	put_integer(44, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(3, 2)
	put_y_value(1, 4)
	put_integer(999, 3)
	call_predicate('$write_term', 5, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed
end('$write_bvar/4$0'/5):



'$write_bvar'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_variable(5, 0)
	get_structure(':', 2, 1)
	unify_x_variable(6)
	unify_x_variable(7)
	get_x_variable(0, 2)
	neck_cut
	pseudo_instr2(69, 3, 1)
	get_x_variable(4, 1)
	put_x_value(5, 1)
	put_x_value(6, 2)
	put_x_value(7, 3)
	execute_predicate('$write_bvar/4$0', 5)

$2:
	execute_predicate('$write_obvar', 3)
end('$write_bvar'/4):



'$write_bvars_rest'/4:

	try(4, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	allocate(3)
	get_y_variable(0, 0)
	get_y_variable(1, 2)
	get_x_variable(1, 3)
	get_y_level(2)
	put_y_value(1, 0)
	call_predicate('$get_depth', 2, 3)
	cut(2)
	put_integer(124, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 2)
	put_constant('...', 1)
	call_predicate('$write_atom', 3, 1)
	put_integer(93, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$2:
	allocate(1)
	get_y_variable(0, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_integer(124, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	call_predicate('$write_var', 3, 1)
	put_integer(93, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$3:
	allocate(4)
	get_y_variable(3, 0)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(2)
	get_y_variable(1, 2)
	neck_cut
	pseudo_instr2(69, 3, 0)
	get_y_variable(0, 0)
	put_integer(44, 0)
	pseudo_instr2(8, 23, 0)
	put_integer(32, 0)
	pseudo_instr2(8, 23, 0)
	put_y_value(3, 0)
	put_y_value(0, 3)
	call_predicate('$write_bvar', 4, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$write_bvars_rest', 4)

$4:
	get_constant('[]', 1)
	neck_cut
	put_integer(93, 1)
	pseudo_instr2(8, 0, 1)
	proceed
end('$write_bvars_rest'/4):



'$write_apply_structure'/4:


$1:
	allocate(6)
	get_y_variable(3, 0)
	get_x_variable(0, 1)
	get_y_variable(2, 2)
	get_y_variable(5, 3)
	put_y_variable(4, 1)
	put_y_variable(1, 2)
	call_predicate('apply', 3, 6)
	pseudo_instr2(69, 25, 0)
	get_y_variable(0, 0)
	put_y_value(3, 0)
	put_y_value(4, 1)
	put_y_value(2, 2)
	put_y_value(0, 4)
	put_integer(0, 3)
	call_predicate('$write_term', 5, 4)
	put_integer(64, 0)
	pseudo_instr2(8, 23, 0)
	put_y_value(3, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	put_y_value(0, 4)
	put_integer(0, 3)
	deallocate
	execute_predicate('$write_term', 5)
end('$write_apply_structure'/4):



'$write_structure'/5:

	try(5, $1)
	trust($2)

$1:
	allocate(5)
	get_y_variable(3, 0)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	get_y_variable(0, 4)
	get_y_level(4)
	put_y_value(1, 0)
	call_predicate('$do_ignore_ops', 1, 5)
	cut(4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$write_structureF', 4)

$2:
	execute_predicate('$write_structureNF', 5)
end('$write_structure'/5):



'$write_structureF'/4:


$1:
	get_x_variable(5, 3)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	pseudo_instr3(0, 1, 3, 4)
	execute_predicate('$write_function', 6)
end('$write_structureF'/4):



'$write_function'/6:

	try(6, $1)
	trust($2)

$1:
	allocate(5)
	get_y_variable(0, 0)
	get_y_variable(1, 2)
	get_y_variable(3, 3)
	get_y_variable(2, 5)
	get_y_level(4)
	put_y_value(1, 0)
	put_y_value(2, 1)
	call_predicate('$get_depth', 2, 5)
	cut(4)
	put_y_value(3, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	put_y_value(2, 3)
	call_predicate('$write_functor', 4, 2)
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 2)
	put_constant('...', 1)
	call_predicate('$write_atom', 3, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$2:
	allocate(5)
	get_y_variable(0, 0)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_x_variable(0, 3)
	get_y_variable(2, 4)
	get_x_variable(3, 5)
	pseudo_instr2(69, 3, 1)
	get_y_variable(1, 1)
	put_y_value(0, 1)
	call_predicate('$write_functor', 4, 5)
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(1, 1)
	pseudo_instr3(1, 1, 24, 0)
	get_x_variable(1, 0)
	put_y_value(0, 0)
	put_y_value(3, 2)
	put_y_value(1, 4)
	put_integer(999, 3)
	call_predicate('$write_term', 5, 5)
	put_y_value(0, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(1, 5)
	put_integer(1, 4)
	call_predicate('$write_arg', 6, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed
end('$write_function'/6):



'$write_functor'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_variable(5, 0)
	allocate(1)
	get_y_variable(0, 1)
	get_x_variable(4, 3)
	pseudo_instr1(6, 5)
	neck_cut
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_x_value(5, 1)
	put_integer(0, 3)
	call_predicate('$write_term', 5, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$2:
	get_x_variable(5, 0)
	get_x_variable(0, 1)
	get_x_variable(4, 3)
	put_x_value(5, 1)
	put_integer(0, 3)
	execute_predicate('$write_term', 5)
end('$write_functor'/4):



'$write_arg'/6:

	try(6, $1)
	trust($2)

$1:
	get_x_value(3, 4)
	neck_cut
	proceed

$2:
	allocate(6)
	get_y_variable(5, 0)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 5)
	pseudo_instr2(69, 4, 0)
	get_y_variable(0, 0)
	put_integer(44, 0)
	pseudo_instr2(8, 25, 0)
	put_integer(32, 0)
	pseudo_instr2(8, 25, 0)
	pseudo_instr3(1, 20, 24, 0)
	get_x_variable(1, 0)
	put_y_value(5, 0)
	put_y_value(1, 4)
	put_integer(999, 3)
	call_predicate('$write_term', 5, 6)
	put_y_value(5, 0)
	put_y_value(4, 1)
	put_y_value(3, 2)
	put_y_value(2, 3)
	put_y_value(0, 4)
	put_y_value(1, 5)
	deallocate
	execute_predicate('$write_arg', 6)
end('$write_arg'/6):



'$write_structureNF/5$0'/5:

	try(5, $1)
	trust($2)

$1:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 2)
	get_y_level(2)
	call_predicate('$get_depth', 2, 3)
	cut(2)
	put_integer(91, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 2)
	put_constant('...', 1)
	call_predicate('$write_atom', 3, 1)
	put_integer(93, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$2:
	allocate(4)
	get_y_variable(3, 0)
	get_x_variable(0, 1)
	get_y_variable(2, 2)
	get_x_variable(1, 3)
	get_y_variable(1, 4)
	pseudo_instr2(69, 0, 2)
	get_y_variable(0, 2)
	put_integer(91, 0)
	pseudo_instr2(8, 22, 0)
	put_y_value(2, 0)
	put_y_value(3, 2)
	put_y_value(0, 4)
	put_integer(999, 3)
	call_predicate('$write_term', 5, 4)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(3, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$write_list_tail', 4)
end('$write_structureNF/5$0'/5):



'$write_structureNF/5$1/7$0/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('$write_structureNF/5$1/7$0/2$0'/1):



'$write_structureNF/5$1/7$0'/2:

	try(2, $1)
	trust($2)

$1:
	execute_predicate('$write_structureNF/5$1/7$0/2$0', 1)

$2:
	put_integer(2, 0)
	pseudo_instr2(1, 0, 1)
	proceed
end('$write_structureNF/5$1/7$0'/2):



'$write_structureNF/5$1'/7:

	try(7, $1)
	retry($2)
	trust($3)

$1:
	allocate(7)
	get_y_variable(5, 0)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_variable(2, 3)
	get_y_variable(1, 4)
	get_y_variable(0, 5)
	get_y_level(6)
	call_predicate('$write_structureNF/5$1/7$0', 2, 7)
	cut(6)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_y_value(0, 5)
	deallocate
	execute_predicate('$write_function', 6)

$2:
	get_x_variable(7, 0)
	get_x_variable(8, 1)
	get_x_variable(0, 2)
	get_x_variable(1, 3)
	get_x_variable(2, 4)
	get_x_variable(9, 5)
	get_x_variable(5, 6)
	put_integer(1, 3)
	get_x_value(8, 3)
	neck_cut
	put_x_value(7, 3)
	put_x_value(8, 4)
	put_x_value(9, 6)
	execute_predicate('$write_uniopNF', 7)

$3:
	get_x_variable(7, 0)
	get_x_variable(8, 1)
	get_x_variable(0, 2)
	get_x_variable(1, 3)
	get_x_variable(2, 4)
	get_x_variable(9, 5)
	get_x_variable(5, 6)
	put_x_value(7, 3)
	put_x_value(8, 4)
	put_x_value(9, 6)
	execute_predicate('$write_binopNF', 7)
end('$write_structureNF/5$1'/7):



'$write_structureNF'/5:

	try(5, $1)
	trust($2)

$1:
	get_x_variable(5, 0)
	get_list(1)
	unify_x_variable(6)
	unify_x_variable(7)
	get_x_variable(0, 2)
	get_x_variable(1, 4)
	neck_cut
	put_x_value(5, 2)
	put_x_value(6, 3)
	put_x_value(7, 4)
	execute_predicate('$write_structureNF/5$0', 5)

$2:
	get_x_variable(7, 0)
	get_x_variable(8, 1)
	get_x_variable(9, 2)
	get_x_variable(6, 3)
	get_x_variable(5, 4)
	put_x_variable(0, 0)
	put_x_variable(1, 1)
	pseudo_instr3(0, 8, 0, 1)
	put_x_value(7, 2)
	put_x_value(8, 3)
	put_x_value(9, 4)
	execute_predicate('$write_structureNF/5$1', 7)
end('$write_structureNF'/5):



'$write_comma_tail'/3:

	try(3, $1)
	retry($2)
	trust($3)

$1:
	allocate(1)
	get_y_variable(0, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_integer(44, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	call_predicate('$write_var', 3, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$2:
	allocate(3)
	get_y_variable(2, 0)
	get_structure(',', 2, 1)
	unify_x_variable(1)
	unify_y_variable(1)
	get_y_variable(0, 2)
	neck_cut
	put_integer(44, 0)
	pseudo_instr2(8, 22, 0)
	put_integer(32, 0)
	pseudo_instr2(8, 22, 0)
	put_y_value(2, 0)
	put_integer(999, 3)
	call_predicate('$write_term', 4, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$write_comma_tail', 3)

$3:
	allocate(1)
	get_y_variable(0, 0)
	put_integer(44, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_integer(999, 3)
	call_predicate('$write_term', 4, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed
end('$write_comma_tail'/3):



'$write_list_tail'/4:

	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	allocate(3)
	get_y_variable(0, 0)
	get_y_variable(1, 2)
	get_x_variable(1, 3)
	get_y_level(2)
	put_y_value(1, 0)
	call_predicate('$get_depth', 2, 3)
	cut(2)
	put_integer(124, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 2)
	put_constant(' ... ', 1)
	call_predicate('$write_atom', 3, 1)
	put_integer(93, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$2:
	allocate(1)
	get_y_variable(0, 0)
	pseudo_instr1(1, 1)
	neck_cut
	pseudo_instr2(69, 3, 0)
	get_x_variable(4, 0)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(124, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_integer(999, 3)
	call_predicate('$write_term', 5, 1)
	put_integer(93, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$3:
	allocate(4)
	get_y_variable(3, 0)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(2)
	get_y_variable(1, 2)
	neck_cut
	pseudo_instr2(69, 3, 0)
	get_y_variable(0, 0)
	put_integer(44, 0)
	pseudo_instr2(8, 23, 0)
	put_integer(32, 0)
	pseudo_instr2(8, 23, 0)
	put_y_value(3, 0)
	put_y_value(0, 4)
	put_integer(999, 3)
	call_predicate('$write_term', 5, 4)
	put_y_value(3, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	put_y_value(0, 3)
	deallocate
	execute_predicate('$write_list_tail', 4)

$4:
	get_constant('[]', 1)
	neck_cut
	put_integer(93, 1)
	pseudo_instr2(8, 0, 1)
	proceed

$5:
	allocate(1)
	get_y_variable(0, 0)
	pseudo_instr2(69, 3, 0)
	get_x_variable(4, 0)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(124, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_integer(999, 3)
	call_predicate('$write_term', 5, 1)
	put_integer(93, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed
end('$write_list_tail'/4):



'$write_uniopNF/7$0/9$0'/1:

	try(1, $1)
	trust($2)

$1:
	put_constant('fx', 1)
	get_x_value(0, 1)
	proceed

$2:
	put_constant('fy', 1)
	get_x_value(0, 1)
	proceed
end('$write_uniopNF/7$0/9$0'/1):



'$write_uniopNF/7$0'/9:

	try(9, $1)
	trust($2)

$1:
	allocate(9)
	get_y_variable(7, 1)
	get_y_variable(6, 2)
	get_y_variable(5, 3)
	get_y_variable(4, 4)
	get_y_variable(3, 5)
	get_y_variable(2, 6)
	get_y_variable(1, 7)
	get_y_variable(0, 8)
	get_y_level(8)
	call_predicate('$write_uniopNF/7$0/9$0', 1, 9)
	cut(8)
	put_y_value(7, 0)
	put_y_value(6, 1)
	put_y_value(5, 2)
	put_y_value(4, 3)
	put_y_value(3, 4)
	put_y_value(2, 5)
	put_y_value(1, 6)
	put_y_value(0, 7)
	deallocate
	execute_predicate('$writepreop', 8)

$2:
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	get_x_variable(3, 4)
	get_x_variable(4, 5)
	get_x_variable(5, 6)
	get_x_variable(6, 7)
	get_x_variable(7, 8)
	execute_predicate('$writepostop', 8)
end('$write_uniopNF/7$0'/9):



'$write_uniopNF'/7:

	try(7, $1)
	trust($2)

$1:
	allocate(10)
	get_y_variable(8, 0)
	get_y_variable(7, 1)
	get_y_variable(6, 2)
	get_y_variable(5, 3)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	get_y_level(9)
	put_y_value(5, 0)
	put_y_variable(2, 1)
	put_y_variable(1, 2)
	put_y_variable(0, 3)
	put_y_value(6, 4)
	call_predicate('$uniop_prec_assoc', 5, 10)
	cut(9)
	put_y_value(0, 0)
	put_y_value(8, 1)
	put_y_value(7, 2)
	put_y_value(6, 3)
	put_y_value(5, 4)
	put_y_value(4, 5)
	put_y_value(2, 6)
	put_y_value(1, 7)
	put_y_value(3, 8)
	deallocate
	execute_predicate('$write_uniopNF/7$0', 9)

$2:
	get_x_variable(5, 6)
	execute_predicate('$write_function', 6)
end('$write_uniopNF'/7):



'$uniop_prec_assoc/5$0'/3:

	try(3, $1)
	trust($2)

$1:
	execute_predicate('$prefix_prec', 3)

$2:
	execute_predicate('$postfix_prec', 3)
end('$uniop_prec_assoc/5$0'/3):



'$uniop_prec_assoc'/5:


$1:
	allocate(6)
	get_y_variable(5, 0)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	get_x_variable(0, 4)
	get_y_level(0)
	put_y_variable(4, 1)
	call_predicate('$get_optable', 2, 6)
	put_y_value(4, 0)
	put_y_value(3, 1)
	put_y_value(1, 2)
	put_y_value(5, 3)
	call_predicate('current_op', 4, 4)
	put_y_value(1, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	call_predicate('$uniop_prec_assoc/5$0', 3, 1)
	cut(0)
	deallocate
	proceed
end('$uniop_prec_assoc'/5):



'$write_binopNF'/7:

	try(7, $1)
	trust($2)

$1:
	allocate(10)
	get_y_variable(8, 0)
	get_y_variable(7, 1)
	get_y_variable(6, 2)
	get_y_variable(5, 3)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	get_y_level(9)
	put_y_value(5, 0)
	put_y_variable(2, 1)
	put_y_variable(1, 2)
	put_y_variable(0, 3)
	put_x_variable(4, 4)
	put_y_value(6, 5)
	call_predicate('$binop_prec_assoc', 6, 10)
	cut(9)
	put_y_value(8, 0)
	put_y_value(7, 1)
	put_y_value(6, 2)
	put_y_value(5, 3)
	put_y_value(4, 4)
	put_y_value(1, 5)
	put_y_value(2, 6)
	put_y_value(0, 7)
	put_y_value(3, 8)
	deallocate
	execute_predicate('$writeinop', 9)

$2:
	get_x_variable(5, 6)
	execute_predicate('$write_function', 6)
end('$write_binopNF'/7):



'$binop_prec_assoc'/6:


$1:
	allocate(6)
	get_y_variable(5, 0)
	get_y_variable(3, 1)
	get_y_variable(2, 2)
	get_y_variable(1, 3)
	get_y_variable(0, 4)
	get_x_variable(0, 5)
	put_y_variable(4, 1)
	call_predicate('$get_optable', 2, 6)
	put_y_value(4, 0)
	put_y_value(2, 1)
	put_y_value(0, 2)
	put_y_value(5, 3)
	call_predicate('current_op', 4, 4)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(3, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$infix_prec', 4)
end('$binop_prec_assoc'/6):



'$writepreop/8$0'/6:

	try(6, $1)
	trust($2)

$1:
	allocate(5)
	get_y_variable(4, 0)
	get_y_variable(0, 2)
	get_y_variable(3, 3)
	get_y_variable(2, 4)
	get_y_variable(1, 5)
	pseudo_instr2(1, 24, 1)
	neck_cut
	put_y_value(0, 0)
	put_y_value(3, 2)
	put_constant('-', 1)
	call_predicate('$write_atom', 3, 5)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(3, 2)
	put_y_value(4, 3)
	put_y_value(1, 4)
	call_predicate('$write_term', 5, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed

$2:
	allocate(5)
	get_y_variable(4, 0)
	get_y_variable(0, 2)
	get_y_variable(3, 3)
	get_y_variable(2, 4)
	get_y_variable(1, 5)
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(3, 2)
	put_constant('-', 1)
	call_predicate('$write_atom', 3, 5)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(3, 2)
	put_y_value(4, 3)
	put_y_value(1, 4)
	call_predicate('$write_term', 5, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed
end('$writepreop/8$0'/6):



'$writepreop/8$1'/7:

	try(7, $1)
	trust($2)

$1:
	allocate(5)
	get_y_variable(4, 0)
	get_x_variable(0, 1)
	get_y_variable(3, 2)
	get_x_variable(1, 3)
	get_y_variable(2, 4)
	get_y_variable(1, 5)
	get_y_variable(0, 6)
	pseudo_instr2(1, 24, 0)
	neck_cut
	put_y_value(3, 0)
	put_y_value(2, 2)
	call_predicate('$write_atom', 3, 5)
	put_integer(32, 0)
	pseudo_instr2(8, 23, 0)
	put_y_value(3, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	put_y_value(4, 3)
	put_y_value(0, 4)
	deallocate
	execute_predicate('$write_term', 5)

$2:
	allocate(5)
	get_y_variable(4, 0)
	get_y_variable(0, 2)
	get_x_variable(1, 3)
	get_y_variable(3, 4)
	get_y_variable(2, 5)
	get_y_variable(1, 6)
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(3, 2)
	call_predicate('$write_atom', 3, 5)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(3, 2)
	put_y_value(4, 3)
	put_y_value(1, 4)
	call_predicate('$write_term', 5, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed
end('$writepreop/8$1'/7):



'$writepreop'/8:

	try(8, $1)
	trust($2)

$1:
	get_constant('-', 3)
	get_x_variable(8, 0)
	get_x_variable(9, 1)
	get_x_variable(3, 2)
	get_x_variable(1, 4)
	get_x_variable(0, 6)
	put_integer(1, 4)
	pseudo_instr3(1, 4, 9, 2)
	get_x_variable(4, 2)
	pseudo_instr1(3, 4)
	neck_cut
	pseudo_instr2(69, 7, 2)
	get_x_variable(5, 2)
	put_x_value(8, 2)
	execute_predicate('$writepreop/8$0', 6)

$2:
	get_x_variable(8, 0)
	get_x_variable(9, 1)
	get_x_variable(10, 2)
	get_x_variable(1, 4)
	get_x_variable(0, 6)
	pseudo_instr2(69, 7, 2)
	get_x_variable(6, 2)
	put_integer(1, 4)
	pseudo_instr3(1, 4, 9, 2)
	get_x_variable(5, 2)
	put_x_value(8, 2)
	put_x_value(10, 4)
	execute_predicate('$writepreop/8$1', 7)
end('$writepreop'/8):



'$writepostop/8$0'/7:

	try(7, $1)
	trust($2)

$1:
	get_x_variable(7, 0)
	get_x_variable(0, 1)
	allocate(3)
	get_y_variable(2, 2)
	get_x_variable(1, 3)
	get_y_variable(1, 4)
	get_x_variable(4, 5)
	get_y_variable(0, 6)
	pseudo_instr2(1, 7, 0)
	neck_cut
	put_y_value(2, 0)
	put_y_value(1, 2)
	put_x_value(7, 3)
	call_predicate('$write_term', 5, 3)
	put_integer(32, 0)
	pseudo_instr2(8, 22, 0)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$write_atom', 3)

$2:
	get_x_variable(7, 0)
	allocate(3)
	get_y_variable(0, 2)
	get_x_variable(1, 3)
	get_y_variable(2, 4)
	get_x_variable(4, 5)
	get_y_variable(1, 6)
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(2, 2)
	put_x_value(7, 3)
	call_predicate('$write_term', 5, 3)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(2, 2)
	call_predicate('$write_atom', 3, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed
end('$writepostop/8$0'/7):



'$writepostop'/8:


$1:
	get_x_variable(8, 0)
	get_x_variable(9, 1)
	get_x_variable(10, 2)
	get_x_variable(11, 3)
	get_x_variable(1, 4)
	get_x_variable(0, 6)
	pseudo_instr2(69, 7, 2)
	get_x_variable(5, 2)
	put_integer(1, 3)
	pseudo_instr3(1, 3, 9, 2)
	get_x_variable(3, 2)
	put_x_value(8, 2)
	put_x_value(10, 4)
	put_x_value(11, 6)
	execute_predicate('$writepostop/8$0', 7)
end('$writepostop'/8):



'$writeinop/9$0'/9:

	try(9, $1)
	trust($2)

$1:
	get_x_variable(9, 0)
	get_x_variable(0, 1)
	allocate(6)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_x_variable(1, 4)
	get_y_variable(2, 5)
	get_y_variable(1, 6)
	get_y_variable(5, 7)
	get_y_variable(0, 8)
	pseudo_instr2(1, 9, 0)
	pseudo_instr2(1, 24, 0)
	neck_cut
	put_y_value(3, 0)
	put_y_value(2, 2)
	put_x_value(9, 3)
	put_y_value(1, 4)
	call_predicate('$write_term', 5, 6)
	put_integer(32, 0)
	pseudo_instr2(8, 23, 0)
	put_y_value(3, 0)
	put_y_value(5, 1)
	put_y_value(2, 2)
	call_predicate('$write_atom', 3, 5)
	put_integer(32, 0)
	pseudo_instr2(8, 23, 0)
	put_y_value(3, 0)
	put_y_value(0, 1)
	put_y_value(2, 2)
	put_y_value(4, 3)
	put_y_value(1, 4)
	deallocate
	execute_predicate('$write_term', 5)

$2:
	get_x_variable(9, 0)
	allocate(6)
	get_y_variable(4, 2)
	get_y_variable(0, 3)
	get_x_variable(1, 4)
	get_y_variable(3, 5)
	get_y_variable(2, 6)
	get_y_variable(5, 7)
	get_y_variable(1, 8)
	put_integer(40, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(3, 2)
	put_x_value(9, 3)
	put_y_value(2, 4)
	call_predicate('$write_term', 5, 6)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(5, 1)
	put_y_value(3, 2)
	call_predicate('$write_atom', 3, 5)
	put_integer(32, 0)
	pseudo_instr2(8, 20, 0)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(3, 2)
	put_y_value(4, 3)
	put_y_value(2, 4)
	call_predicate('$write_term', 5, 1)
	put_integer(41, 0)
	pseudo_instr2(8, 20, 0)
	deallocate
	proceed
end('$writeinop/9$0'/9):



'$writeinop'/9:


$1:
	get_x_variable(9, 0)
	get_x_variable(10, 1)
	get_x_variable(11, 2)
	get_x_variable(12, 3)
	get_x_variable(1, 4)
	get_x_variable(0, 6)
	get_x_variable(2, 7)
	pseudo_instr2(69, 8, 3)
	get_x_variable(6, 3)
	put_integer(1, 4)
	pseudo_instr3(1, 4, 10, 3)
	get_x_variable(4, 3)
	put_integer(2, 5)
	pseudo_instr3(1, 5, 10, 3)
	get_x_variable(8, 3)
	put_x_value(9, 3)
	put_x_value(11, 5)
	put_x_value(12, 7)
	execute_predicate('$writeinop/9$0', 9)
end('$writeinop'/9):



'write_term_list'/1:


$1:
	get_x_variable(1, 0)
	pseudo_instr1(28, 0)
	execute_predicate('$write_term_list', 2)
end('write_term_list'/1):



'write_term_list'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	execute_predicate('$write_term_list', 2)

$2:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('write_term_list')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('stream')
	put_structure(1, 2)
	set_constant('list')
	set_constant('term')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 4)
	set_constant('write_term_list')
	set_x_value(1)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	allocate(3)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$streamnum', 2, 3)
	pseudo_instr2(101, 20, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('output')
	unify_void(5)
	cut(2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('$write_term_list', 2)

$4:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('write_term_list')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('stream')
	put_structure(1, 2)
	set_constant('list')
	set_constant('term')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 4)
	set_constant('write_term_list')
	set_x_value(1)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('write_term_list'/2):



'$write_term_list'/2:

	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 1)
	neck_cut
	proceed

$2:
	allocate(2)
	get_y_variable(1, 0)
	get_list(1)
	unify_x_variable(0)
	unify_y_variable(0)
	put_y_value(1, 1)
	call_predicate('$write_term_term', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('$write_term_list', 2)
end('$write_term_list'/2):



'$write_term_term'/2:

	switch_on_term(0, $29, $13, $13, $14, $13, $26)

$14:
	switch_on_structure(0, 32, ['default':$13, '$'/0:$15, 'tab'/1:$16, 'pc'/1:$17, 'wa'/1:$18, 'wqa'/1:$19, 'wi'/1:$20, 'q'/1:$21, 'w'/1:$22, 'wRq'/1:$23, 'wR'/1:$24, 'wl'/2:$25])

$15:
	try(2, $2)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	retry($10)
	retry($11)
	retry($12)
	trust($13)

$16:
	try(2, $2)
	trust($13)

$17:
	try(2, $4)
	trust($13)

$18:
	try(2, $5)
	trust($13)

$19:
	try(2, $6)
	trust($13)

$20:
	try(2, $7)
	trust($13)

$21:
	try(2, $8)
	trust($13)

$22:
	try(2, $9)
	trust($13)

$23:
	try(2, $10)
	trust($13)

$24:
	try(2, $11)
	trust($13)

$25:
	try(2, $12)
	trust($13)

$26:
	switch_on_constant(0, 4, ['default':$13, 'nl':$27, 'sp':$28])

$27:
	try(2, $1)
	trust($13)

$28:
	try(2, $3)
	trust($13)

$29:
	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	retry($10)
	retry($11)
	retry($12)
	trust($13)

$1:
	get_constant('nl', 0)
	neck_cut
	put_integer(10, 0)
	pseudo_instr2(8, 1, 0)
	proceed

$2:
	get_structure('tab', 1, 0)
	unify_x_variable(2)
	get_x_variable(0, 1)
	neck_cut
	put_x_value(2, 1)
	execute_predicate('$tab', 2)

$3:
	get_constant('sp', 0)
	neck_cut
	put_integer(32, 0)
	pseudo_instr2(8, 1, 0)
	proceed

$4:
	get_structure('pc', 1, 0)
	unify_x_variable(0)
	neck_cut
	pseudo_instr2(8, 1, 0)
	proceed

$5:
	get_structure('wa', 1, 0)
	unify_x_variable(2)
	get_x_variable(0, 1)
	neck_cut
	put_x_value(2, 1)
	execute_predicate('write_atom', 2)

$6:
	get_structure('wqa', 1, 0)
	unify_x_variable(2)
	get_x_variable(0, 1)
	neck_cut
	put_x_value(2, 1)
	execute_predicate('writeq_atom', 2)

$7:
	get_structure('wi', 1, 0)
	unify_x_variable(2)
	get_x_variable(0, 1)
	neck_cut
	put_x_value(2, 1)
	execute_predicate('write_integer', 2)

$8:
	get_structure('q', 1, 0)
	unify_x_variable(2)
	get_x_variable(0, 1)
	neck_cut
	put_x_value(2, 1)
	put_constant('writeq', 2)
	execute_predicate('$write_t', 3)

$9:
	get_structure('w', 1, 0)
	unify_x_variable(2)
	get_x_variable(0, 1)
	neck_cut
	put_x_value(2, 1)
	put_constant('write', 2)
	execute_predicate('$write_t', 3)

$10:
	get_structure('wRq', 1, 0)
	unify_x_variable(2)
	get_x_variable(0, 1)
	neck_cut
	pseudo_instr1(53, 2)
	put_x_value(2, 1)
	put_constant('writeq', 2)
	execute_predicate('$write_t', 3)

$11:
	get_structure('wR', 1, 0)
	unify_x_variable(2)
	get_x_variable(0, 1)
	neck_cut
	pseudo_instr1(53, 2)
	put_x_value(2, 1)
	put_constant('write', 2)
	execute_predicate('$write_t', 3)

$12:
	get_structure('wl', 2, 0)
	unify_x_variable(0)
	unify_x_variable(3)
	get_x_variable(2, 1)
	neck_cut
	put_x_value(3, 1)
	execute_predicate('$write_list_sep', 3)

$13:
	get_x_variable(2, 0)
	get_x_variable(0, 1)
	neck_cut
	put_x_value(2, 1)
	put_constant('write', 2)
	execute_predicate('$write_t', 3)
end('$write_term_term'/2):



'$write_list_sep'/3:

	switch_on_term(0, $3, 'fail', $3, 'fail', 'fail', 'fail')

$3:
	try(3, $1)
	trust($2)

$1:
	get_list(0)
	unify_x_variable(3)
	unify_constant('[]')
	get_x_variable(0, 2)
	neck_cut
	put_x_value(3, 1)
	put_constant('write', 2)
	execute_predicate('$write_t', 3)

$2:
	get_list(0)
	unify_x_variable(3)
	allocate(3)
	unify_y_variable(2)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	put_y_value(0, 0)
	put_x_value(3, 1)
	put_constant('write', 2)
	call_predicate('$write_t', 3, 3)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_constant('write', 2)
	call_predicate('$write_t', 3, 3)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$write_list_sep', 3)
end('$write_list_sep'/3):



'$write_t'/3:

	try(3, $1)
	trust($2)

$1:
	put_integer(1200, 3)
	put_integer(1, 4)
	allocate(0)
	call_predicate('$write_term', 5, 0)
	fail

$2:
	proceed
end('$write_t'/3):



'$stdout_atom'/1:


$1:
	get_x_variable(1, 0)
	put_constant('stdout', 0)
	execute_predicate('write_atom', 2)
end('$stdout_atom'/1):



'$stdout_int'/1:


$1:
	get_x_variable(1, 0)
	put_constant('stdout', 0)
	execute_predicate('write_integer', 2)
end('$stdout_int'/1):



'$stdout_nl'/0:


$1:
	put_constant('stdout', 0)
	put_integer(10, 1)
	pseudo_instr2(8, 0, 1)
	proceed
end('$stdout_nl'/0):



'write_atom'/1:


$1:
	pseudo_instr1(28, 1)
	pseudo_instr2(16, 1, 0)
	proceed
end('write_atom'/1):



'write_atom'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	pseudo_instr2(16, 0, 1)
	proceed

$2:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('write_atom')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('stream')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(2, 3)
	set_constant('write_atom')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	allocate(3)
	get_y_variable(0, 1)
	get_y_level(2)
	put_y_variable(1, 1)
	call_predicate('$streamnum', 2, 3)
	pseudo_instr2(101, 21, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('output')
	unify_void(5)
	cut(2)
	pseudo_instr2(16, 21, 20)
	deallocate
	proceed

$4:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('write_atom')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('stream')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(2, 3)
	set_constant('write_atom')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('write_atom'/2):



'writeq_atom'/1:


$1:
	pseudo_instr1(28, 1)
	pseudo_instr2(17, 1, 0)
	proceed
end('writeq_atom'/1):



'writeq_atom'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	pseudo_instr2(17, 0, 1)
	proceed

$2:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('writeq_atom')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('stream')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(2, 3)
	set_constant('writeq_atom')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	allocate(3)
	get_y_variable(0, 1)
	get_y_level(2)
	put_y_variable(1, 1)
	call_predicate('$streamnum', 2, 3)
	pseudo_instr2(101, 21, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('output')
	unify_void(5)
	cut(2)
	pseudo_instr2(17, 21, 20)
	deallocate
	proceed

$4:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('writeq_atom')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('stream')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(2, 3)
	set_constant('writeq_atom')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('writeq_atom'/2):



'write_integer'/2:

	try(2, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	pseudo_instr2(18, 0, 1)
	proceed

$2:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('write_integer')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('stream')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('write_integer')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$3:
	allocate(3)
	get_y_variable(0, 1)
	get_y_level(2)
	put_y_variable(1, 1)
	call_predicate('$streamnum', 2, 3)
	pseudo_instr2(101, 21, 0)
	get_structure('$prop', 7, 0)
	unify_void(1)
	unify_constant('output')
	unify_void(5)
	cut(2)
	pseudo_instr2(18, 21, 20)
	deallocate
	proceed

$4:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('write_integer')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('stream')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('write_integer')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('write_integer'/2):



