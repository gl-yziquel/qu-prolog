'clause/2$0'/0:

	try(0, $1)
	trust($2)

$1:
	proceed

$2:
	fail
end('clause/2$0'/0):



'clause/2$1'/2:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 'true':$4])

$4:
	try(2, $1)
	trust($2)

$5:
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
end('clause/2$1'/2):



'clause'/2:

	try(2, $1)
	retry($2)
	trust($3)

$1:
	get_x_variable(2, 0)
	pseudo_instr1(1, 2)
	neck_cut
	put_structure(2, 0)
	set_constant('clause')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('+')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('?')
	set_constant('nonvar')
	put_structure(2, 3)
	set_constant('clause')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('instantiation_exception', 3)

$2:
	allocate(8)
	get_y_variable(7, 0)
	get_y_variable(2, 1)
	get_y_level(1)
	call_predicate('$legal_clause_head', 1, 8)
	cut(1)
	put_y_value(7, 0)
	put_y_variable(3, 1)
	call_predicate('$correct_name', 2, 7)
	pseudo_instr3(66, 23, 0, 1)
	get_y_variable(6, 0)
	get_y_variable(5, 1)
	call_predicate('clause/2$0', 0, 7)
	put_y_value(6, 0)
	put_y_variable(4, 1)
	put_y_value(5, 2)
	put_y_variable(0, 3)
	call_predicate('$get_clause_ref', 4, 5)
	pseudo_instr3(57, 24, 23, 0)
	put_y_value(2, 1)
	call_predicate('$post_trans_decompile', 2, 2)
	put_y_value(0, 0)
	put_y_value(1, 1)
	deallocate
	execute_predicate('clause/2$1', 2)

$3:
	get_x_variable(2, 0)
	put_structure(2, 0)
	set_constant('clause')
	set_x_value(2)
	set_x_value(1)
	put_structure(1, 1)
	set_constant('+')
	set_constant('nonvar')
	put_structure(1, 2)
	set_constant('?')
	set_constant('nonvar')
	put_structure(2, 3)
	set_constant('clause')
	set_x_value(1)
	set_x_value(2)
	put_list(2)
	set_x_value(3)
	set_constant('[]')
	put_integer(1, 1)
	execute_predicate('type_exception', 3)
end('clause'/2):



'$get_clause_ref'/4:

	try(4, $1)
	trust($2)

$1:
	get_x_value(0, 1)
	get_x_value(2, 3)
	proceed

$2:
	pseudo_instr3(13, 0, 2, 4)
	get_x_variable(0, 2)
	get_x_variable(2, 4)
	execute_predicate('$get_clause_ref', 4)
end('$get_clause_ref'/4):



'$post_trans_decompile'/2:

	switch_on_term(0, $3, 'fail', $2, 'fail', 'fail', $1)

$3:
	try(2, $1)
	trust($2)

$1:
	get_constant('[]', 0)
	get_constant('true', 1)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	unify_x_variable(3)
	get_x_variable(2, 1)
	put_x_value(3, 1)
	execute_predicate('$post_trans_decompile_aux', 3)
end('$post_trans_decompile'/2):



'$post_trans_decompile_aux/3$0'/2:

	try(2, $1)
	trust($2)

$1:
	pseudo_instr1(2, 0)
	neck_cut
	put_constant('!', 0)
	get_x_value(1, 0)
	proceed

$2:
	get_structure('$cut', 1, 1)
	unify_x_value(0)
	proceed
end('$post_trans_decompile_aux/3$0'/2):



'$post_trans_decompile_aux'/3:

	switch_on_term(0, $27, $12, $12, $13, $12, $25)

$13:
	switch_on_structure(0, 32, ['$default':$12, '$'/0:$14, '$get_level'/1:$15, '$cut'/1:$16, '$psi0_calls$'/1:$17, '$psi1_calls$'/2:$18, '$psi2_calls$'/3:$19, '$psi3_calls$'/4:$20, '$psi4_calls$'/5:$21, '$psi5_calls$'/6:$22, '$ite_call'/4:$23, '$or_call'/3:$24])

$14:
	try(3, $1)
	retry($2)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	retry($9)
	retry($10)
	retry($11)
	trust($12)

$15:
	try(3, $1)
	trust($12)

$16:
	try(3, $2)
	trust($12)

$17:
	try(3, $4)
	trust($12)

$18:
	try(3, $5)
	trust($12)

$19:
	try(3, $6)
	trust($12)

$20:
	try(3, $7)
	trust($12)

$21:
	try(3, $8)
	trust($12)

$22:
	try(3, $9)
	trust($12)

$23:
	try(3, $10)
	trust($12)

$24:
	try(3, $11)
	trust($12)

$25:
	switch_on_constant(0, 4, ['$default':$12, '$$neckcut':$26])

$26:
	try(3, $3)
	trust($12)

$27:
	try(3, $1)
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
	trust($12)

$1:
	get_structure('$get_level', 1, 0)
	unify_x_variable(0)
	neck_cut
	put_constant('level', 3)
	get_x_value(0, 3)
	put_x_value(1, 0)
	get_list(0)
	unify_x_variable(0)
	unify_x_variable(1)
	execute_predicate('$post_trans_decompile_aux', 3)

$2:
	get_structure('$cut', 1, 0)
	unify_x_variable(0)
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	neck_cut
	put_y_variable(0, 1)
	call_predicate('$post_trans_decompile_aux/3$0', 2, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$post_trans_decompile_rest', 3)

$3:
	get_constant('$$neckcut', 0)
	get_x_variable(0, 1)
	neck_cut
	put_constant('!', 1)
	execute_predicate('$post_trans_decompile_rest', 3)

$4:
	get_structure('$psi0_calls$', 1, 0)
	unify_x_variable(0)
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	neck_cut
	put_y_variable(0, 1)
	put_x_variable(2, 2)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	call_predicate('$psi0_decl', 5, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$post_trans_decompile_rest', 3)

$5:
	get_structure('$psi1_calls$', 2, 0)
	unify_x_variable(0)
	unify_x_variable(3)
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	neck_cut
	put_y_variable(0, 1)
	put_x_value(3, 2)
	put_x_variable(3, 3)
	put_x_variable(4, 4)
	put_x_variable(5, 5)
	call_predicate('$psi1_decl', 6, 3)
	put_y_value(0, 0)
	put_y_value(2, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$post_trans_decompile_aux', 3)

$6:
	get_structure('$psi2_calls$', 3, 0)
	unify_x_variable(0)
	unify_x_variable(4)
	unify_x_variable(3)
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	neck_cut
	put_y_variable(0, 1)
	put_x_value(4, 2)
	put_x_variable(4, 4)
	put_x_variable(5, 5)
	put_x_variable(6, 6)
	call_predicate('$psi2_decl', 7, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$post_trans_decompile_rest', 3)

$7:
	get_structure('$psi3_calls$', 4, 0)
	unify_x_variable(0)
	unify_x_variable(5)
	unify_x_variable(3)
	unify_x_variable(4)
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	neck_cut
	put_y_variable(0, 1)
	put_x_value(5, 2)
	put_x_variable(5, 5)
	put_x_variable(6, 6)
	put_x_variable(7, 7)
	call_predicate('$psi3_decl', 8, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$post_trans_decompile_rest', 3)

$8:
	get_structure('$psi4_calls$', 5, 0)
	unify_x_variable(0)
	unify_x_variable(6)
	unify_x_variable(3)
	unify_x_variable(4)
	unify_x_variable(5)
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	neck_cut
	put_y_variable(0, 1)
	put_x_value(6, 2)
	put_x_variable(6, 6)
	put_x_variable(7, 7)
	put_x_variable(8, 8)
	call_predicate('$psi4_decl', 9, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$post_trans_decompile_rest', 3)

$9:
	get_structure('$psi5_calls$', 6, 0)
	unify_x_variable(0)
	unify_x_variable(7)
	unify_x_variable(3)
	unify_x_variable(4)
	unify_x_variable(5)
	unify_x_variable(6)
	allocate(3)
	get_y_variable(2, 1)
	get_y_variable(1, 2)
	neck_cut
	put_y_variable(0, 1)
	put_x_value(7, 2)
	put_x_variable(7, 7)
	put_x_variable(8, 8)
	put_x_variable(9, 9)
	call_predicate('$psi5_decl', 10, 3)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(1, 2)
	deallocate
	execute_predicate('$post_trans_decompile_rest', 3)

$10:
	get_structure('$ite_call', 4, 0)
	unify_x_variable(3)
	unify_x_variable(4)
	unify_x_variable(5)
	unify_void(1)
	get_x_variable(0, 1)
	neck_cut
	put_structure(2, 6)
	set_constant('->')
	set_x_value(3)
	set_x_value(4)
	put_structure(2, 1)
	set_constant(';')
	set_x_value(6)
	set_x_value(5)
	execute_predicate('$post_trans_decompile_rest', 3)

$11:
	get_structure('$or_call', 3, 0)
	unify_x_variable(3)
	unify_x_variable(4)
	unify_void(1)
	get_x_variable(0, 1)
	neck_cut
	put_structure(2, 1)
	set_constant(';')
	set_x_value(3)
	set_x_value(4)
	execute_predicate('$post_trans_decompile_rest', 3)

$12:
	get_x_variable(3, 0)
	get_x_variable(0, 1)
	put_x_value(3, 1)
	execute_predicate('$post_trans_decompile_rest', 3)
end('$post_trans_decompile_aux'/3):



'$post_trans_decompile_rest'/3:

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
	unify_x_variable(3)
	get_structure(',', 2, 2)
	unify_x_value(1)
	unify_x_variable(2)
	put_x_value(3, 1)
	execute_predicate('$post_trans_decompile_aux', 3)
end('$post_trans_decompile_rest'/3):



'listing'/0:

	try(0, $1)
	trust($2)

$1:
	allocate(1)
	put_y_variable(0, 0)
	put_constant('dynamic', 1)
	call_predicate('predicate_property', 2, 1)
	put_y_value(0, 0)
	call_predicate('$listing_predicate', 1, 0)
	fail

$2:
	proceed
end('listing'/0):



'listing'/1:

	switch_on_term(0, $11, $4, $5, $6, $4, $9)

$5:
	try(1, $2)
	trust($4)

$6:
	switch_on_structure(0, 4, ['$default':$4, '$'/0:$7, '/'/2:$8])

$7:
	try(1, $3)
	trust($4)

$8:
	try(1, $3)
	trust($4)

$9:
	switch_on_constant(0, 4, ['$default':$4, '[]':$10])

$10:
	try(1, $1)
	trust($4)

$11:
	try(1, $1)
	retry($2)
	retry($3)
	trust($4)

$1:
	get_constant('[]', 0)
	neck_cut
	proceed

$2:
	get_list(0)
	unify_x_variable(0)
	allocate(1)
	unify_y_variable(0)
	call_predicate('listing', 1, 1)
	put_y_value(0, 0)
	deallocate
	execute_predicate('listing', 1)

$3:
	get_structure('/', 2, 0)
	unify_x_variable(1)
	unify_x_variable(2)
	pseudo_instr1(2, 1)
	pseudo_instr1(3, 2)
	neck_cut
	put_x_variable(0, 0)
	pseudo_instr3(0, 0, 1, 2)
	execute_predicate('$listing_predicate', 1)

$4:
	get_x_variable(1, 0)
	put_structure(1, 0)
	set_constant('listing')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('list')
	set_constant('gcomp')
	put_structure(1, 2)
	set_constant('@')
	set_x_value(1)
	put_structure(1, 1)
	set_constant('listing')
	set_x_value(2)
	put_list(3)
	set_x_value(1)
	set_constant('[]')
	put_structure(1, 1)
	set_constant('@')
	set_constant('gcomp')
	put_structure(1, 4)
	set_constant('listing')
	set_x_value(1)
	put_list(2)
	set_x_value(4)
	set_x_value(3)
	put_structure(2, 1)
	set_constant('/')
	set_constant('p')
	set_constant('n')
	put_structure(1, 3)
	set_constant('list')
	set_x_value(1)
	put_integer(1, 1)
	execute_predicate('type_exception', 4)
end('listing'/1):



'$listing_predicate'/1:

	try(1, $1)
	trust($2)

$1:
	allocate(2)
	get_y_variable(1, 0)
	put_y_variable(0, 1)
	call_predicate('clause', 2, 2)
	put_structure(2, 0)
	set_constant(':-')
	set_y_value(1)
	set_y_value(0)
	call_predicate('portray_clause', 1, 0)
	fail

$2:
	proceed
end('$listing_predicate'/1):



