'@<'/2:


$1:
	allocate(1)
	put_y_variable(0, 2)
	call_predicate('$compare0', 3, 1)
	put_integer(0, 0)
	pseudo_instr2(1, 20, 0)
	deallocate
	proceed
end('@<'/2):



'@='/2:


$1:
	allocate(1)
	put_y_variable(0, 2)
	call_predicate('$compare0', 3, 1)
	put_y_value(0, 0)
	get_integer(0, 0)
	deallocate
	proceed
end('@='/2):



'@>'/2:


$1:
	allocate(1)
	put_y_variable(0, 2)
	call_predicate('$compare0', 3, 1)
	put_integer(0, 0)
	pseudo_instr2(1, 0, 20)
	deallocate
	proceed
end('@>'/2):



'@=</2$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('@>', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('@=</2$0'/2):



'@=<'/2:


$1:
	execute_predicate('@=</2$0', 2)
end('@=<'/2):



'@>=/2$0'/2:

	try(2, $1)
	trust($2)

$1:
	allocate(1)
	get_y_level(0)
	call_predicate('@<', 2, 1)
	cut(0)
	fail

$2:
	proceed
end('@>=/2$0'/2):



'@>='/2:


$1:
	execute_predicate('@>=/2$0', 2)
end('@>='/2):



'compare'/3:

	switch_on_term(0, $5, 'fail', 'fail', 'fail', 'fail', $4)

$4:
	switch_on_constant(0, 8, ['$default':'fail', '=':$1, '<':$2, '>':$3])

$5:
	try(3, $1)
	retry($2)
	trust($3)

$1:
	get_constant('=', 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	allocate(1)
	get_y_level(0)
	call_predicate('@=', 2, 1)
	cut(0)
	deallocate
	proceed

$2:
	get_constant('<', 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	allocate(1)
	get_y_level(0)
	call_predicate('@<', 2, 1)
	cut(0)
	deallocate
	proceed

$3:
	get_constant('>', 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	execute_predicate('@>', 2)
end('compare'/3):



'$compare0/3$0'/5:

	try(5, $1)
	trust($2)

$1:
	execute_predicate('$compare_type', 3)

$2:
	get_x_variable(5, 2)
	get_x_variable(1, 3)
	get_x_variable(2, 4)
	put_x_value(5, 3)
	execute_predicate('$fine_compare', 4)
end('$compare0/3$0'/5):



'$compare0'/3:


$1:
	allocate(6)
	get_y_variable(5, 0)
	get_y_variable(4, 1)
	get_y_variable(3, 2)
	get_y_level(0)
	put_y_variable(2, 1)
	call_predicate('$term_type', 2, 6)
	put_y_value(4, 0)
	put_y_variable(1, 1)
	call_predicate('$term_type', 2, 6)
	put_y_value(2, 0)
	put_y_value(1, 1)
	put_y_value(3, 2)
	put_y_value(5, 3)
	put_y_value(4, 4)
	call_predicate('$compare0/3$0', 5, 1)
	cut(0)
	deallocate
	proceed
end('$compare0'/3):



'$term_type'/2:

	try(2, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	trust($6)

$1:
	get_integer(1, 1)
	pseudo_instr1(1, 0)
	neck_cut
	proceed

$2:
	get_integer(2, 1)
	pseudo_instr1(4, 0)
	neck_cut
	proceed

$3:
	get_integer(3, 1)
	allocate(1)
	get_y_level(0)
	call_predicate('number', 1, 1)
	cut(0)
	deallocate
	proceed

$4:
	get_integer(4, 1)
	pseudo_instr1(2, 0)
	neck_cut
	proceed

$5:
	get_integer(5, 1)
	pseudo_instr1(0, 0)
	neck_cut
	proceed

$6:
	get_integer(6, 1)
	pseudo_instr1(5, 0)
	neck_cut
	proceed
end('$term_type'/2):



'$compare_type'/3:

	try(3, $1)
	trust($2)

$1:
	get_integer(-1, 2)
	pseudo_instr2(1, 0, 1)
	neck_cut
	proceed

$2:
	get_integer(1, 2)
	pseudo_instr2(1, 1, 0)
	proceed
end('$compare_type'/3):



'$fine_compare/4$0'/7:

	try(7, $1)
	trust($2)

$1:
	get_x_variable(7, 0)
	get_x_variable(8, 1)
	get_x_variable(0, 2)
	get_x_variable(1, 3)
	get_x_variable(2, 4)
	pseudo_instr3(6, 7, 8, 3)
	put_constant('true', 4)
	get_x_value(3, 4)
	neck_cut
	execute_predicate('$compare0', 3)

$2:
	pseudo_instr3(4, 5, 6, 0)
	get_x_value(4, 0)
	proceed
end('$fine_compare/4$0'/7):



'$fine_compare/4$1'/7:

	try(7, $1)
	trust($2)

$1:
	get_x_variable(7, 0)
	get_x_variable(8, 1)
	get_x_variable(0, 2)
	get_x_variable(1, 3)
	get_x_variable(2, 4)
	pseudo_instr3(6, 7, 8, 3)
	put_constant('true', 4)
	get_x_value(3, 4)
	neck_cut
	execute_predicate('$compare0', 3)

$2:
	pseudo_instr3(4, 5, 6, 0)
	get_x_value(4, 0)
	proceed
end('$fine_compare/4$1'/7):



'$fine_compare/4$2/9$0/7$0'/4:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(4, $1)
	trust($2)

$5:
	try(4, $1)
	trust($2)

$1:
	get_x_variable(4, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	put_integer(0, 3)
	get_x_value(4, 3)
	neck_cut
	execute_predicate('$compare0', 3)

$2:
	get_x_value(3, 0)
	proceed
end('$fine_compare/4$2/9$0/7$0'/4):



'$fine_compare/4$2/9$0'/7:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(7, $1)
	trust($2)

$5:
	try(7, $1)
	trust($2)

$1:
	allocate(4)
	get_y_variable(3, 4)
	get_y_variable(2, 5)
	get_y_variable(1, 6)
	put_integer(0, 4)
	get_x_value(0, 4)
	neck_cut
	put_y_variable(0, 4)
	put_integer(0, 0)
	call_predicate('$compare_args', 5, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$fine_compare/4$2/9$0/7$0', 4)

$2:
	get_x_value(6, 0)
	proceed
end('$fine_compare/4$2/9$0'/7):



'$fine_compare/4$2'/9:

	try(9, $1)
	retry($2)
	trust($3)

$1:
	pseudo_instr2(1, 0, 1)
	neck_cut
	put_integer(-1, 0)
	get_x_value(2, 0)
	proceed

$2:
	pseudo_instr2(1, 1, 0)
	neck_cut
	put_integer(1, 0)
	get_x_value(2, 0)
	proceed

$3:
	allocate(7)
	get_y_variable(6, 0)
	get_y_variable(5, 2)
	get_x_variable(0, 3)
	get_x_variable(1, 4)
	get_y_variable(4, 5)
	get_y_variable(3, 6)
	get_y_variable(2, 7)
	get_y_variable(1, 8)
	put_y_variable(0, 2)
	call_predicate('$compare0', 3, 7)
	put_y_value(0, 0)
	put_y_value(6, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	put_y_value(2, 4)
	put_y_value(1, 5)
	put_y_value(5, 6)
	deallocate
	execute_predicate('$fine_compare/4$2/9$0', 7)
end('$fine_compare/4$2'/9):



'$fine_compare/4$3/8$0/6$0'/4:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(4, $1)
	trust($2)

$5:
	try(4, $1)
	trust($2)

$1:
	get_x_variable(4, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	put_integer(0, 3)
	get_x_value(4, 3)
	neck_cut
	execute_predicate('$compare0', 3)

$2:
	get_x_value(3, 0)
	proceed
end('$fine_compare/4$3/8$0/6$0'/4):



'$fine_compare/4$3/8$0'/6:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(6, $1)
	trust($2)

$5:
	try(6, $1)
	trust($2)

$1:
	get_x_variable(6, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	allocate(4)
	get_y_variable(3, 3)
	get_y_variable(2, 4)
	get_y_variable(1, 5)
	put_integer(0, 2)
	get_x_value(6, 2)
	neck_cut
	put_y_variable(0, 2)
	call_predicate('$compare0', 3, 4)
	put_y_value(0, 0)
	put_y_value(3, 1)
	put_y_value(2, 2)
	put_y_value(1, 3)
	deallocate
	execute_predicate('$fine_compare/4$3/8$0/6$0', 4)

$2:
	get_x_value(5, 0)
	proceed
end('$fine_compare/4$3/8$0'/6):



'$fine_compare/4$3'/8:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(8, $1)
	trust($2)

$5:
	try(8, $1)
	trust($2)

$1:
	get_x_variable(8, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	allocate(6)
	get_y_variable(5, 3)
	get_y_variable(4, 4)
	get_y_variable(3, 5)
	get_y_variable(2, 6)
	get_y_variable(1, 7)
	put_integer(0, 2)
	get_x_value(8, 2)
	neck_cut
	put_y_variable(0, 2)
	call_predicate('$compare0', 3, 6)
	put_y_value(0, 0)
	put_y_value(5, 1)
	put_y_value(4, 2)
	put_y_value(3, 3)
	put_y_value(2, 4)
	put_y_value(1, 5)
	deallocate
	execute_predicate('$fine_compare/4$3/8$0', 6)

$2:
	get_x_value(7, 0)
	proceed
end('$fine_compare/4$3'/8):



'$fine_compare'/4:

	switch_on_term(0, $13, 'fail', 'fail', 'fail', 'fail', $10)

$10:
	switch_on_constant(0, 16, ['$default':'fail', 1:$1, 2:$2, 3:$11, 4:$12, 5:$8, 6:$9])

$11:
	try(4, $3)
	retry($4)
	trust($5)

$12:
	try(4, $6)
	trust($7)

$13:
	try(4, $1)
	retry($2)
	retry($3)
	retry($4)
	retry($5)
	retry($6)
	retry($7)
	retry($8)
	trust($9)

$1:
	get_integer(1, 0)
	allocate(7)
	get_y_variable(6, 1)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	put_y_value(6, 0)
	put_y_variable(3, 1)
	put_y_variable(2, 2)
	call_predicate('$break_substitute', 3, 7)
	put_y_value(5, 0)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$break_substitute', 3, 7)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(3, 2)
	put_y_value(1, 3)
	put_y_value(4, 4)
	put_y_value(6, 5)
	put_y_value(5, 6)
	deallocate
	execute_predicate('$fine_compare/4$0', 7)

$2:
	get_integer(2, 0)
	allocate(7)
	get_y_variable(6, 1)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	put_y_value(6, 0)
	put_y_variable(3, 1)
	put_y_variable(2, 2)
	call_predicate('$break_substitute', 3, 7)
	put_y_value(5, 0)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$break_substitute', 3, 7)
	put_y_value(2, 0)
	put_y_value(0, 1)
	put_y_value(3, 2)
	put_y_value(1, 3)
	put_y_value(4, 4)
	put_y_value(6, 5)
	put_y_value(5, 6)
	deallocate
	execute_predicate('$fine_compare/4$1', 7)

$3:
	get_integer(3, 0)
	get_integer(0, 3)
	get_x_value(1, 2)
	neck_cut
	proceed

$4:
	get_integer(3, 0)
	pseudo_instr2(1, 1, 2)
	neck_cut
	put_integer(-1, 0)
	get_x_value(3, 0)
	proceed

$5:
	get_integer(3, 0)
	get_integer(1, 3)
	proceed

$6:
	get_integer(4, 0)
	get_integer(0, 3)
	get_x_value(1, 2)
	neck_cut
	proceed

$7:
	get_integer(4, 0)
	pseudo_instr3(5, 1, 2, 0)
	get_x_value(3, 0)
	proceed

$8:
	get_integer(5, 0)
	get_x_variable(0, 1)
	allocate(6)
	get_y_variable(5, 2)
	get_y_variable(4, 3)
	put_y_variable(3, 1)
	put_y_variable(2, 2)
	call_predicate('$break_substitute', 3, 6)
	put_y_value(5, 0)
	put_y_variable(1, 1)
	put_y_variable(0, 2)
	call_predicate('$break_substitute', 3, 5)
	put_x_variable(3, 3)
	put_x_variable(0, 0)
	pseudo_instr3(0, 22, 3, 0)
	put_x_variable(4, 4)
	put_x_variable(1, 1)
	pseudo_instr3(0, 20, 4, 1)
	put_y_value(4, 2)
	put_y_value(2, 5)
	put_y_value(0, 6)
	put_y_value(3, 7)
	put_y_value(1, 8)
	deallocate
	execute_predicate('$fine_compare/4$2', 9)

$9:
	get_integer(6, 0)
	get_x_variable(0, 1)
	allocate(11)
	get_y_variable(10, 2)
	get_y_variable(7, 3)
	put_y_variable(6, 1)
	put_y_variable(9, 2)
	call_predicate('$break_substitute', 3, 11)
	put_y_value(10, 0)
	put_y_variable(5, 1)
	put_y_variable(8, 2)
	call_predicate('$break_substitute', 3, 10)
	put_x_variable(0, 0)
	put_y_variable(4, 19)
	put_y_variable(3, 19)
	pseudo_instr4(7, 29, 0, 24, 23)
	put_x_variable(1, 1)
	put_y_variable(2, 19)
	put_y_variable(1, 19)
	pseudo_instr4(7, 28, 1, 22, 21)
	put_y_variable(0, 2)
	call_predicate('$compare0', 3, 8)
	put_y_value(0, 0)
	put_y_value(4, 1)
	put_y_value(2, 2)
	put_y_value(3, 3)
	put_y_value(1, 4)
	put_y_value(6, 5)
	put_y_value(5, 6)
	put_y_value(7, 7)
	deallocate
	execute_predicate('$fine_compare/4$3', 8)
end('$fine_compare'/4):



'$compare_args/5$0'/6:

	switch_on_term(0, $5, $2, $2, $2, $2, $3)

$3:
	switch_on_constant(0, 4, ['$default':$2, 0:$4])

$4:
	try(6, $1)
	trust($2)

$5:
	try(6, $1)
	trust($2)

$1:
	get_x_variable(6, 0)
	get_x_variable(0, 1)
	get_x_variable(1, 2)
	get_x_variable(2, 3)
	get_x_variable(3, 4)
	get_x_variable(4, 5)
	put_integer(0, 5)
	get_x_value(6, 5)
	neck_cut
	execute_predicate('$compare_args', 5)

$2:
	get_x_value(5, 0)
	proceed
end('$compare_args/5$0'/6):



'$compare_args'/5:

	try(5, $1)
	trust($2)

$1:
	get_integer(0, 4)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	allocate(6)
	get_y_variable(5, 1)
	get_y_variable(4, 2)
	get_y_variable(3, 3)
	get_y_variable(2, 4)
	pseudo_instr2(69, 0, 1)
	get_y_variable(1, 1)
	pseudo_instr3(1, 21, 24, 0)
	pseudo_instr3(1, 21, 23, 1)
	put_y_variable(0, 2)
	call_predicate('$compare0', 3, 6)
	put_y_value(0, 0)
	put_y_value(1, 1)
	put_y_value(5, 2)
	put_y_value(4, 3)
	put_y_value(3, 4)
	put_y_value(2, 5)
	deallocate
	execute_predicate('$compare_args/5$0', 6)
end('$compare_args'/5):



