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
	get_x_variable(1, 0)
	pseudo_instr1(90, 0)
	execute_predicate('$same_handle', 2)
end('icm_thread_handle'/1):



