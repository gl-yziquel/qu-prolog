'stream_to_chars/2$0'/3:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, '$prop'/7:$5])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$6:
	try(3, $1)
	trust($2)

$1:
	get_structure('$prop', 7, 0)
	unify_constant('write')
	unify_void(6)
	neck_cut
	proceed

$2:
	put_structure(2, 3)
	set_constant('stream_to_chars')
	set_x_value(1)
	set_x_value(2)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_constant('default')
	execute_predicate('exception', 1)
end('stream_to_chars/2$0'/3):



'stream_to_chars'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('stream_to_chars')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('?')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('stream_to_chars')
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
	set_constant('stream_to_chars')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(2)
	get_y_variable(0, 0)
	get_y_variable(1, 1)
	pseudo_instr2(101, 20, 0)
	put_x_value(0, 1)
	get_structure('$prop', 7, 1)
	unify_void(2)
	unify_constant('string')
	unify_void(4)
	neck_cut
	put_y_value(0, 1)
	put_y_value(1, 2)
	call_predicate('stream_to_chars/2$0', 3, 2)
	pseudo_instr2(44, 20, 0)
	get_y_value(1, 0)
	put_y_value(0, 0)
	deallocate
	execute_predicate('close', 1)

$3:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('stream_to_chars')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('list')
	set_constant('integer')
	put_structure(1, 3)
	set_constant('?')
	set_x_value(2)
	put_structure(2, 2)
	set_constant('stream_to_chars')
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
	set_constant('stream_to_chars')
	set_x_value(2)
	set_x_value(4)
	put_list(2)
	set_x_value(3)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('stream', 3)
	execute_predicate('type_exception', 4)
end('stream_to_chars'/2):



'stream_to_atom/2$0'/3:

	switch_on_term(0, $6, $2, $2, $3, $2, $2)

$3:
	switch_on_structure(0, 4, ['$default':$2, '$'/0:$4, '$prop'/7:$5])

$4:
	try(3, $1)
	trust($2)

$5:
	try(3, $1)
	trust($2)

$6:
	try(3, $1)
	trust($2)

$1:
	get_structure('$prop', 7, 0)
	unify_constant('write')
	unify_void(6)
	neck_cut
	proceed

$2:
	put_structure(2, 3)
	set_constant('stream_to_atom')
	set_x_value(1)
	set_x_value(2)
	put_structure(3, 0)
	set_constant('permission_error')
	set_constant('unrecoverable')
	set_x_value(3)
	set_constant('default')
	execute_predicate('exception', 1)
end('stream_to_atom/2$0'/3):



'stream_to_atom'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('stream_to_atom')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atom')
	put_structure(2, 3)
	set_constant('stream_to_atom')
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
	set_constant('atom')
	put_structure(2, 4)
	set_constant('stream_to_atom')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(2)
	get_y_variable(0, 0)
	get_y_variable(1, 1)
	pseudo_instr2(101, 20, 0)
	put_x_value(0, 1)
	get_structure('$prop', 7, 1)
	unify_void(2)
	unify_constant('string')
	unify_void(4)
	neck_cut
	put_y_value(0, 1)
	put_y_value(1, 2)
	call_predicate('stream_to_atom/2$0', 3, 2)
	pseudo_instr2(45, 20, 0)
	get_y_value(1, 0)
	put_y_value(0, 0)
	deallocate
	execute_predicate('close', 1)

$3:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('stream_to_atom')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('?')
	set_constant('atom')
	put_structure(2, 3)
	set_constant('stream_to_atom')
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
	set_constant('atom')
	put_structure(2, 4)
	set_constant('stream_to_atom')
	set_x_value(2)
	set_x_value(3)
	put_list(2)
	set_x_value(4)
	set_x_value(1)
	put_integer(1, 1)
	put_constant('stream', 3)
	execute_predicate('type_exception', 4)
end('stream_to_atom'/2):



