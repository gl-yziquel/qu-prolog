'icm_handle_from_components'/4:


$1:
	put_x_variable(5, 6)
	get_list(6)
	unify_x_value(2)
	unify_constant('[]')
	pseudo_instr5(2, 0, 1, 2, 5, 4)
	get_x_value(3, 4)
	proceed
end('icm_handle_from_components'/4):



'icm_thread_handle'/1:


$1:
	pseudo_instr1(90, 1)
	get_structure('$icm_handle', 4, 1)
	unify_x_variable(1)
	unify_x_variable(2)
	unify_x_variable(3)
	unify_x_variable(4)
	get_structure('/', 2, 0)
	unify_x_ref(0)
	unify_x_value(4)
	get_structure('@', 2, 0)
	unify_x_ref(0)
	unify_x_value(3)
	get_structure(':', 2, 0)
	unify_x_value(1)
	unify_x_value(2)
	proceed
end('icm_thread_handle'/1):



