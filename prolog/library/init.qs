'$initialise_system_backtrackable/0$0'/0:

	try(0, $1)
	trust($2)

$1:
	put_constant('$query', 1)
	put_integer(0, 2)
	pseudo_instr3(33, 1, 2, 0)
	put_integer(0, 1)
	get_x_value(0, 1)
	neck_cut
	proceed

$2:
	execute_predicate('$query', 0)
end('$initialise_system_backtrackable/0$0'/0):



'$initialise_system_backtrackable'/0:


$1:
	allocate(0)
	call_predicate('$initial_loading', 0, 0)
	call_predicate('$initialise_subsystems', 0, 0)
	deallocate
	execute_predicate('$initialise_system_backtrackable/0$0', 0)
end('$initialise_system_backtrackable'/0):



'$initialise_system_non_backtrackable'/0:


$1:
	execute_predicate('$init_retry', 0)
end('$initialise_system_non_backtrackable'/0):



'$initial_loading'/0:


$1:
	proceed
end('$initial_loading'/0):



'$initialise_subsystems'/0:


$1:
	allocate(0)
	call_predicate('$init_debug', 0, 0)
	call_predicate('$init_exception', 0, 0)
	call_predicate('$init_fcompile', 0, 0)
	call_predicate('$init_index', 0, 0)
	call_predicate('$init_interpreter', 0, 0)
	call_predicate('$init_op', 0, 0)
	call_predicate('$init_stream', 0, 0)
	call_predicate('$init_term_exp', 0, 0)
	deallocate
	execute_predicate('$init_objvar', 0)
end('$initialise_subsystems'/0):



