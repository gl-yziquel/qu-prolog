'atom_chars/2$0'/2:

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
	unify_x_variable(2)
	unify_x_variable(0)
	get_list(1)
	unify_x_variable(3)
	unify_x_variable(1)
	pseudo_instr2(35, 2, 4)
	get_x_value(3, 4)
	execute_predicate('atom_chars/2$0', 2)
end('atom_chars/2$0'/2):



'atom_chars/2$1'/2:

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
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(0)
	call_predicate('char_code', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('atom_chars/2$1', 2)
end('atom_chars/2$1'/2):



'atom_chars/2$2'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('atom_chars/2$2'/1):



'atom_chars'/2:

	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	allocate(2)
	get_y_variable(1, 1)
	pseudo_instr1(2, 0)
	neck_cut
	pseudo_instr2(32, 0, 1)
	get_x_variable(0, 1)
	put_y_variable(0, 1)
	call_predicate('atom_chars/2$0', 2, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	allocate(3)
	get_y_variable(0, 0)
	pseudo_instr1(46, 1)
	get_x_variable(0, 1)
	put_y_variable(1, 1)
	get_y_level(2)
	call_predicate('atom_chars/2$1', 2, 3)
	cut(2)
	pseudo_instr2(33, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$3:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('atom_chars')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('atom_chars')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('atom_chars')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('atom_chars')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('atom_chars')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('atom_chars')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$5:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('atom_chars/2$2', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('atom_chars')
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('-')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('atom_chars')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('atom_chars')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)
end('atom_chars'/2):



'atom_codes/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('atom_codes/2$0'/1):



'atom_codes'/2:

	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	pseudo_instr2(32, 0, 2)
	get_x_variable(0, 2)
	get_x_value(1, 0)
	proceed

$2:
	allocate(4)
	get_y_variable(0, 0)
	get_y_variable(1, 1)
	pseudo_instr1(46, 21)
	get_y_level(2)
	put_y_value(1, 0)
	put_y_variable(3, 2)
	put_integer(0, 1)
	call_predicate('$atom_codes_and_length', 3, 4)
	put_integer(257, 0)
	pseudo_instr2(1, 23, 0)
	cut(2)
	pseudo_instr2(33, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$3:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('atom_codes')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('atom_codes')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('atom_codes')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('atom_codes')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('atom_codes')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('atom_codes')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$5:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('atom_codes/2$0', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('atom_codes')
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('-')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('atom_codes')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('atom_codes')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)

$6:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('atom_codes')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('atom_codes')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('atom_codes')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_integer(2, 1)
	execute_predicate('type_exception', 4)
end('atom_codes'/2):



'$atom_codes_and_length'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(3)
	unify_y_variable(2)
	get_y_variable(1, 2)
	put_y_variable(0, 2)
	call_predicate('$atom_codes_length', 3, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$atom_codes_and_length', 3)
end('$atom_codes_and_length'/3):



'$atom_codes_length'/3:


$1:
	allocate(3)
	get_y_variable(1, 1)
	get_y_variable(0, 2)
	get_y_level(2)
	call_predicate('$character_code', 1, 3)
	cut(2)
	pseudo_instr2(69, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed
end('$atom_codes_length'/3):



'$character_code'/1:


$1:
	pseudo_instr1(3, 0)
	put_integer(0, 1)
	pseudo_instr2(1, 1, 0)
	put_integer(256, 1)
	pseudo_instr2(1, 0, 1)
	proceed
end('$character_code'/1):



'number_chars/2$0'/2:

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
	unify_x_variable(2)
	unify_x_variable(0)
	get_list(1)
	unify_x_variable(3)
	unify_x_variable(1)
	pseudo_instr2(35, 2, 4)
	get_x_value(3, 4)
	execute_predicate('number_chars/2$0', 2)
end('number_chars/2$0'/2):



'number_chars/2$1'/2:

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
	unify_x_variable(0)
	allocate(2)
	unify_y_variable(1)
	get_list(1)
	unify_x_variable(1)
	unify_y_variable(0)
	call_predicate('char_code', 2, 2)
	put_y_value(1, 0)
	put_y_value(0, 1)
	deallocate
	execute_predicate('number_chars/2$1', 2)
end('number_chars/2$1'/2):



'number_chars/2$2'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	fail

$2:
	proceed
end('number_chars/2$2'/1):



'number_chars'/2:

	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	trust($5)

$1:
	allocate(3)
	get_y_variable(1, 1)
	pseudo_instr1(3, 0)
	neck_cut
	put_y_variable(0, 19)
	put_y_variable(2, 1)
	call_predicate('$number_codes', 2, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('number_chars/2$0', 2, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	allocate(4)
	get_y_variable(1, 0)
	pseudo_instr1(46, 1)
	get_x_variable(0, 1)
	put_y_variable(2, 1)
	get_y_level(3)
	put_y_variable(0, 19)
	call_predicate('number_chars/2$1', 2, 4)
	cut(3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	call_predicate('$codes_number', 2, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$3:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('number_chars')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('number_chars')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('number_chars')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('number_chars')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('number_chars')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('number_chars')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$5:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('number_chars/2$2', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('number_chars')
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('-')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('number_chars')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('list')
	set_constant('atom')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('number_chars')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('integer', 3)
	deallocate
	execute_predicate('type_exception', 4)
end('number_chars'/2):



'number_codes/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(3, 0)
	neck_cut
	fail

$2:
	proceed
end('number_codes/2$0'/1):



'number_codes'/2:

	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	allocate(2)
	get_y_variable(1, 1)
	pseudo_instr1(3, 0)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$number_codes', 2, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	allocate(3)
	get_y_variable(1, 0)
	get_x_variable(0, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$codes_number', 2, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$3:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('number_codes')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('number_codes')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('number_codes')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('number_codes')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('number_codes')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('number_codes')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$5:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('number_codes/2$0', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('number_codes')
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('-')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('number_codes')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('number_codes')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('integer', 3)
	deallocate
	execute_predicate('type_exception', 4)

$6:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('number_codes')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('integer')
	put_structure(1, 2)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('number_codes')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('number_codes')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_integer(2, 1)
	execute_predicate('type_exception', 4)
end('number_codes'/2):



'$number_codes'/2:

	try(2, $1)
	trust($2)

$1:
	put_integer(0, 2)
	pseudo_instr2(1, 0, 2)
	neck_cut
	get_list(1)
	unify_integer(45)
	unify_x_variable(2)
	put_x_variable(3, 4)
	get_structure('-', 1, 4)
	unify_x_value(0)
	pseudo_instr2(0, 1, 3)
	get_x_variable(0, 1)
	put_constant('[]', 1)
	execute_predicate('$positive_codes', 3)

$2:
	get_x_variable(2, 1)
	put_constant('[]', 1)
	execute_predicate('$positive_codes', 3)
end('$number_codes'/2):



'$positive_codes'/3:

	try(3, $1)
	trust($2)

$1:
	get_list(2)
	unify_x_variable(2)
	unify_x_value(1)
	put_integer(10, 1)
	pseudo_instr2(1, 0, 1)
	neck_cut
	put_integer(48, 3)
	pseudo_instr3(2, 3, 0, 1)
	get_x_value(2, 1)
	proceed

$2:
	get_x_variable(3, 1)
	put_x_variable(4, 5)
	get_structure('mod', 2, 5)
	unify_x_value(0)
	unify_integer(10)
	pseudo_instr2(0, 1, 4)
	put_integer(48, 5)
	pseudo_instr3(2, 5, 1, 4)
	put_x_variable(5, 6)
	get_structure('//', 2, 6)
	unify_x_value(0)
	unify_integer(10)
	pseudo_instr2(0, 1, 5)
	get_x_variable(0, 1)
	put_list(1)
	set_x_value(4)
	set_x_value(3)
	execute_predicate('$positive_codes', 3)
end('$positive_codes'/3):



'$codes_number/2$0'/2:

	switch_on_term(0, $3, $2, $3, $2, $2, $2)

$3:
	try(2, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(0, 1)
	get_list(0)
	unify_integer(45)
	unify_x_variable(0)
	neck_cut
	put_y_variable(1, 1)
	call_predicate('$codes_positive_number_check', 2, 2)
	put_x_variable(1, 2)
	get_structure('-', 1, 2)
	unify_y_value(1)
	pseudo_instr2(0, 0, 1)
	get_y_value(0, 0)
	deallocate
	proceed

$2:
	execute_predicate('$codes_positive_number_check', 2)
end('$codes_number/2$0'/2):



'$codes_number'/2:


$1:
	pseudo_instr1(46, 0)
	execute_predicate('$codes_number/2$0', 2)
end('$codes_number'/2):



'$codes_positive_number_check'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, '[]':$4])

$4:
	try(2, $1)
	trust($2)

$5:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	neck_cut
	fail

$2:
	get_x_variable(2, 1)
	put_integer(0, 1)
	execute_predicate('$codes_positive_number', 3)
end('$codes_positive_number_check'/2):



'$codes_positive_number'/3:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(3, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_x_value(1, 2)
	proceed

$2:
	get_list(0)
	allocate(4)
	unify_y_variable(3)
	unify_y_variable(1)
	get_y_variable(2, 1)
	get_y_variable(0, 2)
	put_y_value(3, 0)
	call_predicate('$digit_code', 1, 4)
	put_integer(48, 1)
	pseudo_instr3(3, 23, 1, 0)
	put_x_variable(2, 3)
	get_structure('*', 2, 3)
	unify_y_value(2)
	unify_integer(10)
	pseudo_instr2(0, 1, 2)
	pseudo_instr3(2, 1, 0, 2)
	get_x_variable(1, 2)
	put_y_value(1, 0)
	put_y_value(0, 2)
	deallocate
	execute_predicate('$codes_positive_number', 3)
end('$codes_positive_number'/3):



'$digit_code'/1:


$1:
	pseudo_instr1(3, 0)
	put_integer(48, 1)
	pseudo_instr2(2, 1, 0)
	put_integer(57, 1)
	pseudo_instr2(2, 0, 1)
	proceed
end('$digit_code'/1):



'char_code/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr2(34, 0, 2)
	get_x_variable(0, 2)
	neck_cut
	get_x_value(1, 0)
	proceed

$2:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('char_code')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('char_code')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(2, 4)
	set_constant('char_code')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('character', 3)
	execute_predicate('type_exception', 4)
end('char_code/2$0'/2):



'char_code/2$1'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	fail

$2:
	proceed
end('char_code/2$1'/1):



'char_code'/2:

	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	execute_predicate('char_code/2$0', 2)

$2:
	allocate(3)
	get_y_variable(0, 0)
	get_y_variable(1, 1)
	get_y_level(2)
	put_y_value(1, 0)
	call_predicate('$character_code', 1, 3)
	cut(2)
	pseudo_instr2(35, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$3:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('char_code')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('char_code')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(2, 4)
	set_constant('char_code')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$4:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('char_code')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('char_code')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(2, 4)
	set_constant('char_code')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$5:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('char_code/2$1', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('char_code')
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('-')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('char_code')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(2, 4)
	set_constant('char_code')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('atom', 3)
	deallocate
	execute_predicate('type_exception', 4)

$6:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('char_code')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('atom')
	put_structure(1, 2)
	set_constant('@')
	set_constant('integer')
	put_structure(2, 3)
	set_constant('char_code')
	set_x_value(1)
	set_x_value(2)
	put_list(1)
	set_x_value(3)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atom')
	put_structure(1, 3)
	set_constant('?')
	set_constant('integer')
	put_structure(2, 4)
	set_constant('char_code')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(2, 1)
	put_constant('integer', 3)
	execute_predicate('type_exception', 4)
end('char_code'/2):



'name/2$0'/1:

	try(1, $1)
	trust($2)

$1:
	pseudo_instr1(43, 0)
	neck_cut
	fail

$2:
	proceed
end('name/2$0'/1):



'name'/2:

	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	trust($8)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	pseudo_instr2(32, 0, 2)
	get_x_variable(0, 2)
	get_x_value(1, 0)
	proceed

$2:
	allocate(2)
	get_y_variable(1, 1)
	pseudo_instr1(3, 0)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$number_codes', 2, 2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$3:
	allocate(3)
	get_y_variable(1, 0)
	get_x_variable(0, 1)
	get_y_level(2)
	put_y_variable(0, 1)
	call_predicate('$codes_number', 2, 3)
	cut(2)
	put_y_value(1, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$4:
	allocate(4)
	get_y_variable(0, 0)
	get_y_variable(1, 1)
	pseudo_instr1(46, 21)
	get_y_level(2)
	put_y_value(1, 0)
	put_y_variable(3, 2)
	put_integer(0, 1)
	call_predicate('$atom_codes_and_length', 3, 4)
	put_integer(257, 0)
	pseudo_instr2(1, 23, 0)
	cut(2)
	pseudo_instr2(33, 21, 0)
	get_y_value(0, 0)
	deallocate
	proceed

$5:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('name')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('atomic')
	put_structure(1, 2)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('name')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atomic')
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('name')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$6:
	get_x_variable(2, 0)
	pseudo_instr1(1, 1)
	neck_cut
	put_structure(2, 0)
	set_constant('name')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('atomic')
	put_structure(1, 2)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('name')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atomic')
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('name')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(2, 1)
	execute_predicate('instantiation_exception', 3)

$7:
	allocate(3)
	get_y_variable(1, 0)
	get_y_variable(0, 1)
	get_y_level(2)
	call_predicate('name/2$0', 1, 3)
	cut(2)
	put_structure(2, 0)
	set_constant('name')
	set_y_value(1)
	set_y_value(0)
	put_structure(1, 1)
	set_constant('-')
	set_constant('atomic')
	put_structure(1, 2)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('name')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atomic')
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('name')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('atomic', 3)
	deallocate
	execute_predicate('type_exception', 4)

$8:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('name')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('-')
	set_constant('atomic')
	put_structure(1, 2)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('@')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('name')
	set_x_value(1)
	set_x_value(3)
	put_list(1)
	set_x_value(2)
	set_constant('[]')
	put_structure(1, 2)
	set_constant('@')
	set_constant('atomic')
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 4)
	set_constant('?')
	set_x_value(3)
	put_structure(2, 3)
	set_constant('name')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_structure(1, 3)
	set_constant('list')
	set_constant('integer')
	put_integer(2, 1)
	execute_predicate('type_exception', 4)
end('name'/2):



