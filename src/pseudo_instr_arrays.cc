// pseudo_instr_arrays.cc -  pseudo_instruction arrays - generated
// automatically from pseudoinstr.ql using sys_bin/MkPsi
//
// ##Copyright##
// 
// Copyright (C) 2000, 20001
// Software Verification Research Centre
// The University of Queensland
// Australia 4072
// 
// email: svrc@it.uq.edu.au
// 
// The Qu-Prolog 6.0 System and Documentation  
// 
// COPYRIGHT NOTICE, LICENCE AND DISCLAIMER.
// 
// Copyright 2000,2001 by The University of Queensland, 
// Queensland 4072 Australia
// 
// Permission to use, copy and distribute this software and associated
// documentation for any non-commercial purpose and without fee is hereby 
// granted, subject to the following conditions:
// 
// 1. 	that the above copyright notice and this permission notice and 
// 	warranty disclaimer appear in all copies and in supporting 
// 	documentation; 
// 
// 2.	that the name of the University of Queensland not be used in 
// 	advertising or publicity pertaining to distribution of the software 
// 	without specific, written prior permission; 
// 
// 3.	that users of this software should be responsible for determining the 
// 	fitness of the software for the purposes for which the software is 
// 	employed by them; 
// 
// 4. 	that no changes to the system or documentation are subsequently 
// 	made available to third parties or redistributed without prior 
// 	written consent from the SVRC; and
// 
// The University of Queensland disclaims all warranties with regard to this
// software, including all implied warranties of merchantability and fitness
// to the extent permitted by law. In no event shall the University of 
// Queensland be liable for any special, indirect or consequential damages or 
// any damages whatsoever resulting from loss of use, data or profits, whether 
// in an action of contract, negligence or other tortious action, arising out 
// of or in connection with the use or performance of this software.
// 
// THE UNIVERSITY OF QUEENSLAND MAKES NO REPRESENTATIONS ABOUT THE ACCURACY OR
// SUITABILITY OF THIS MATERIAL FOR ANY PURPOSE.  IT IS PROVIDED "AS IS",
// WITHOUT ANY EXPRESSED OR IMPLIED WARRANTIES.
// 
// 
// For information on commercial use of this software contact the SVRC.
// 
// ##Copyright##
//
// $Id: pseudo_instr_arrays.cc,v 1.41 2004/02/19 03:03:27 qp Exp $

#include "thread_qp.h"

#include "pseudo_instr_arrays.h"

pseudo_instr0_data pseudo_instr0_array[] =
{
	{&Thread::psi_failpt_to_catch,	0,	"psi_failpt_to_catch"}, 
	{&Thread::psi_catch_to_failpt,	0,	"psi_catch_to_failpt"}, 
	{&Thread::psi_clear_all_signals,	0,	"psi_clear_all_signals"}, 
	{&Thread::psi_psidelay_resume,	0,	"psi_psidelay_resume"}, 
	{&Thread::psi_compress_var_delays,	0,	"psi_compress_var_delays"}, 
	{&Thread::psi_retry_ov_delays,	0,	"psi_retry_ov_delays"}, 
	{&Thread::psi_retry_ov_eq_delays,	0,	"psi_retry_ov_eq_delays"}, 
	{&Thread::psi_thread_yield,	0,	"psi_thread_yield"}, 
	{&Thread::psi_thread_exit,	0,	"psi_thread_exit"}, 
	{&Thread::psi_thread_is_initial_thread,	0,	"psi_thread_is_initial_thread"}, 
	{&Thread::psi_signal_thread_exit,	0,	"psi_signal_thread_exit"}, 
	{&Thread::psi_gc,	0,	"psi_gc"}, 
	{&Thread::psi_icm_deregister,	0,	"psi_icm_deregister"}, 
	{&Thread::psi_elvin_disconnect,	0,	"psi_elvin_disconnect"}
};
pseudo_instr1_data pseudo_instr1_array[] =
{
	{&Thread::psi_compound,	0,	"psi_compound"}, 
	{&Thread::psi_var,	0,	"psi_var"}, 
	{&Thread::psi_atom,	0,	"psi_atom"}, 
	{&Thread::psi_integer,	0,	"psi_integer"}, 
	{&Thread::psi_object_variable,	0,	"psi_object_variable"}, 
	{&Thread::psi_quant,	0,	"psi_quant"}, 
	{&Thread::psi_sub,	0,	"psi_sub"}, 
	{&Thread::psi_get_level,	1,	"psi_get_level"}, 
	{&Thread::psi_delayneckcut,	0,	"psi_delayneckcut"}, 
	{&Thread::psi_cut,	0,	"psi_cut"}, 
	{&Thread::psi_get_qplibpath,	1,	"psi_get_qplibpath"}, 
	{&Thread::psi_get_args,	1,	"psi_get_args"}, 
	{&Thread::psi_retract,	0,	"psi_retract"}, 
	{&Thread::psi_save,	0,	"psi_save"}, 
	{&Thread::psi_restore,	0,	"psi_restore"}, 
	{&Thread::psi_cputime,	1,	"psi_cputime"}, 
	{&Thread::psi_stat_memory,	1,	"psi_stat_memory"}, 
	{&Thread::psi_stat_program,	1,	"psi_stat_program"}, 
	{&Thread::psi_empty_sub,	1,	"psi_empty_sub"}, 
	{&Thread::psi_call_predicate0,	0,	"psi_call_predicate0"}, 
	{&Thread::psi_code_top,	1,	"psi_code_top"}, 
	{&Thread::psi_get_catch,	1,	"psi_get_catch"}, 
	{&Thread::psi_set_catch,	0,	"psi_set_catch"}, 
	{&Thread::psi_psi_resume,	0,	"psi_psi_resume"}, 
	{&Thread::psi_erase,	0,	"psi_erase"}, 
	{&Thread::psi_clear_signal,	0,	"psi_clear_signal"}, 
	{&Thread::psi_default_signal_handler,	0,	"psi_default_signal_handler"}, 
	{&Thread::psi_current_input,	1,	"psi_current_input"}, 
	{&Thread::psi_current_output,	1,	"psi_current_output"}, 
	{&Thread::psi_set_input,	0,	"psi_set_input"}, 
	{&Thread::psi_set_output,	0,	"psi_set_output"}, 
	{&Thread::psi_flush_output,	0,	"psi_flush_output"}, 
	{&Thread::psi_at_end_of_stream,	0,	"psi_at_end_of_stream"}, 
	{&Thread::psi_past_end_of_stream,	0,	"psi_past_end_of_stream"}, 
	{&Thread::psi_reset_stream,	0,	"psi_reset_stream"}, 
	{&Thread::psi_local_object_variable,	0,	"psi_local_object_variable"}, 
	{&Thread::psi_new_object_variable,	1,	"psi_new_object_variable"}, 
	{&Thread::psi_valid_object_variable_prefix,	0,	"psi_valid_object_variable_prefix"}, 
	{&Thread::psi_set_trace_level,	0,	"psi_set_trace_level"}, 
	{&Thread::psi_freeze_var,	0,	"psi_freeze_var"}, 
	{&Thread::psi_thaw_var,	0,	"psi_thaw_var"}, 
	{&Thread::psi_frozen_var,	0,	"psi_frozen_var"}, 
	{&Thread::psi_thawed_var,	0,	"psi_thawed_var"}, 
	{&Thread::psi_atomic,	0,	"psi_atomic"}, 
	{&Thread::psi_any_variable,	0,	"psi_any_variable"}, 
	{&Thread::psi_simple,	0,	"psi_simple"}, 
	{&Thread::psi_nonvar,	0,	"psi_nonvar"}, 
	{&Thread::psi_std_var,	0,	"psi_std_var"}, 
	{&Thread::psi_std_nonvar,	0,	"psi_std_nonvar"}, 
	{&Thread::psi_std_compound,	0,	"psi_std_compound"}, 
	{&Thread::psi_list,	0,	"psi_list"}, 
	{&Thread::psi_freeze_term,	0,	"psi_freeze_term"}, 
	{&Thread::psi_thaw_term,	0,	"psi_thaw_term"}, 
	{&Thread::psi_name_vars,	0,	"psi_name_vars"}, 
	{&Thread::psi_ip_array_clear,	0,	"psi_ip_array_clear"}, 
	{&Thread::psi_ipc_commit,	0,	"psi_ipc_commit"}, 
	{&Thread::psi_tcp_listen,	0,	"psi_tcp_listen"}, 
	{&Thread::psi_tcp_checkconn,	0,	"psi_tcp_checkconn"}, 
	{&Thread::psi_tcp_close,	0,	"psi_tcp_close"}, 
	{&Thread::psi_realtime,	1,	"psi_realtime"}, 
	{&Thread::psi_single_sub,	0,	"psi_single_sub"}, 
	{&Thread::psi_tcp_is_socket,	0,	"psi_tcp_is_socket"}, 
	{&Thread::psi_process_pid,	1,	"psi_process_pid"}, 
	{&Thread::psi_thread_set_symbol,	0,	"psi_thread_set_symbol"}, 
	{&Thread::psi_thread_goal,	1,	"psi_thread_goal"}, 
	{&Thread::psi_thread_is_thread,	0,	"psi_thread_is_thread"}, 
	{&Thread::psi_thread_is_runnable,	0,	"psi_thread_is_runnable"}, 
	{&Thread::psi_thread_is_suspended,	0,	"psi_thread_is_suspended"}, 
	{&Thread::psi_thread_tid,	1,	"psi_thread_tid"}, 
	{&Thread::psi_thread_suspend,	0,	"psi_thread_suspend"}, 
	{&Thread::psi_thread_resume,	0,	"psi_thread_resume"}, 
	{&Thread::psi_thread_wait,	0,	"psi_thread_wait"}, 
	{&Thread::psi_thread_defaults,	1,	"psi_thread_defaults"}, 
	{&Thread::psi_thread_set_defaults,	0,	"psi_thread_set_defaults"}, 
	{&Thread::psi_machine_ip_address,	1,	"psi_machine_ip_address"}, 
	{&Thread::psi_machine_name,	1,	"psi_machine_name"}, 
	{&Thread::psi_nsig,	1,	"psi_nsig"}, 
	{&Thread::psi_thread_errno,	1,	"psi_thread_errno"}, 
	{&Thread::psi_set_trace_flag,	0,	"psi_set_trace_flag"}, 
	{&Thread::psi_clear_trace_flag,	0,	"psi_clear_trace_flag"}, 
	{&Thread::psi_test_trace_flag,	0,	"psi_test_trace_flag"}, 
	{&Thread::psi_tcp_connect2,	0,	"psi_tcp_connect2"}, 
	{&Thread::psi_stdin,	1,	"psi_stdin"}, 
	{&Thread::psi_stdout,	1,	"psi_stdout"}, 
	{&Thread::psi_stderr,	1,	"psi_stderr"}, 
	{&Thread::psi_ipc_open,	1,	"psi_ipc_open"}, 
	{&Thread::psi_ipc_close,	0,	"psi_ipc_close"}, 
	{&Thread::psi_process_set_symbol,	0,	"psi_process_set_symbol"}, 
	{&Thread::psi_process_symbol,	1,	"psi_process_symbol"}, 
	{&Thread::psi_icm_process_handle,	1,	"psi_icm_process_handle"}, 
	{&Thread::psi_icm_thread_handle,	1,	"psi_icm_thread_handle"}, 
	{&Thread::psi_alloc_buffer,	1,	"psi_alloc_buffer"}, 
	{&Thread::psi_dealloc_buffer,	0,	"psi_dealloc_buffer"}, 
	{&Thread::psi_debug_write,	0,	"psi_debug_write"}, 
	{&Thread::psi_addExtraInfoToVars,	0,	"psi_addExtraInfoToVars"}, 
	{&Thread::psi_reset_std_stream,	0,	"psi_reset_std_stream"}, 
	{&Thread::psi_current_threads,	1,	"psi_current_threads"}, 
	{&Thread::psi_thread_exit,	0,	"psi_thread_exit"}, 
	{&Thread::psi_icm_address,	1,	"psi_icm_address"}, 
	{&Thread::psi_icm_port,	1,	"psi_icm_port"}, 
	{&Thread::psi_bound,	0,	"psi_bound"}, 
	{&Thread::psi_make_iterator,	1,	"psi_make_iterator"}, 
	{&Thread::psi_set_autoflush,	0,	"psi_set_autoflush"}, 
	{&Thread::psi_get_open_streams,	1,	"psi_get_open_streams"}, 
	{&Thread::psi_broadcast,	0,	"psi_broadcast"}, 
	{&Thread::psi_elvin_connect,	0,	"psi_elvin_connect"}, 
	{&Thread::psi_elvin_add_subscription,	0,	"psi_elvin_add_subscription"}, 
	{&Thread::psi_elvin_delete_subscription,	0,	"psi_elvin_delete_subscription"}, 
	{&Thread::psi_elvin_subscriptions,	1,	"psi_elvin_subscriptions"}, 
	{&Thread::psi_elvin_makeID,	1,	"psi_elvin_makeID"}, 
	{&Thread::psi_elvin_add_notification,	0,	"psi_elvin_add_notification"}, 
	{&Thread::psi_chdir,	0,	"psi_chdir"}
};
pseudo_instr2_data pseudo_instr2_array[] =
{
	{&Thread::psi_is,	2,	"psi_is"}, 
	{&Thread::psi_less,	0,	"psi_less"}, 
	{&Thread::psi_lesseq,	0,	"psi_lesseq"}, 
	{&Thread::psi_ip_set,	0,	"psi_ip_set"}, 
	{&Thread::psi_ip_lookup,	1,	"psi_ip_lookup"}, 
	{&Thread::psi_get_char,	1,	"psi_get_char"}, 
	{&Thread::psi_put_char,	0,	"psi_put_char"}, 
	{&Thread::psi_get_code,	1,	"psi_get_code"}, 
	{&Thread::psi_put_code,	0,	"psi_put_code"}, 
	{&Thread::psi_compare_pointers,	0,	"psi_compare_pointers"}, 
	{&Thread::psi_set_flag,	0,	"psi_set_flag"}, 
	{&Thread::psi_get_flag,	1,	"psi_get_flag"}, 
	{&Thread::psi_copy_term_from_buffer,	1,	"psi_copy_term_from_buffer"}, 
	{&Thread::psi_stat_atom,	3,	"psi_stat_atom"}, 
	{&Thread::psi_stat_predicate,	3,	"psi_stat_predicate"}, 
	{&Thread::psi_stat_name,	1,	"psi_stat_name"}, 
	{&Thread::psi_write_atom,	0,	"psi_write_atom"}, 
	{&Thread::psi_writeq_atom,	0,	"psi_writeq_atom"}, 
	{&Thread::psi_write_integer,	0,	"psi_write_integer"}, 
	{&Thread::psi_write_var,	0,	"psi_write_var"}, 
	{&Thread::psi_writeR_var,	0,	"psi_writeR_var"}, 
	{&Thread::psi_write_object_variable,	0,	"psi_write_object_variable"}, 
	{&Thread::psi_writeR_object_variable,	0,	"psi_writeR_object_variable"}, 
	{&Thread::psi_writeq_object_variable,	0,	"psi_writeq_object_variable"}, 
	{&Thread::psi_get_substitution,	1,	"psi_get_substitution"}, 
	{&Thread::psi_sub_term,	1,	"psi_sub_term"}, 
	{&Thread::psi_next_sub,	1,	"psi_next_sub"}, 
	{&Thread::psi_sub_table_size,	1,	"psi_sub_table_size"}, 
	{&Thread::psi_compress_sub_object_variable,	1,	"psi_compress_sub_object_variable"}, 
	{&Thread::psi_reset_entry,	0,	"psi_reset_entry"}, 
	{&Thread::psi_atom_length,	1,	"psi_atom_length"}, 
	{&Thread::psi_concat_atom,	1,	"psi_concat_atom"}, 
	{&Thread::psi_atom_codes,	1,	"psi_atom_codes"}, 
	{&Thread::psi_codes_atom,	1,	"psi_codes_atom"}, 
	{&Thread::psi_char_code,	1,	"psi_char_code"}, 
	{&Thread::psi_code_char,	1,	"psi_code_char"}, 
	{&Thread::psi_record_get_first_ref,	1,	"psi_record_get_first_ref"}, 
	{&Thread::psi_record_get_next_ref,	1,	"psi_record_get_next_ref"}, 
	{&Thread::psi_record_get_last_ref,	1,	"psi_record_get_last_ref"}, 
	{&Thread::psi_record_get_term,	1,	"psi_record_get_term"}, 
	{&Thread::psi_close,	0,	"psi_close"}, 
	{&Thread::psi_stream_position,	1,	"psi_stream_position"}, 
	{&Thread::psi_set_stream_position,	0,	"psi_set_stream_position"}, 
	{&Thread::psi_line_number,	1,	"psi_line_number"}, 
	{&Thread::psi_stream_to_chars,	1,	"psi_stream_to_chars"}, 
	{&Thread::psi_stream_to_atom,	1,	"psi_stream_to_atom"}, 
	{&Thread::psi_system,	1,	"psi_system"}, 
	{&Thread::psi_mktemp,	1,	"psi_mktemp"}, 
	{&Thread::psi_delay,	0,	"psi_delay"}, 
	{&Thread::psi_delayed_problems_for_var,	1,	"psi_delayed_problems_for_var"}, 
	{&Thread::psi_get_bound_structure,	1,	"psi_get_bound_structure"}, 
	{&Thread::psi_not_free_in,	0,	"psi_not_free_in"}, 
	{&Thread::psi_not_free_in_var_simplify,	0,	"psi_not_free_in_var_simplify"}, 
	{&Thread::psi_is_distinct,	0,	"psi_is_distinct"}, 
	{&Thread::psi_get_distinct,	1,	"psi_get_distinct"}, 
	{&Thread::psi_object_variable_name_to_prefix,	1,	"psi_object_variable_name_to_prefix"}, 
	{&Thread::psi_readR_var,	2,	"psi_readR_var"}, 
	{&Thread::psi_readR_object_variable,	2,	"psi_readR_object_variable"}, 
	{&Thread::psi_quantifier,	1,	"psi_quantifier"}, 
	{&Thread::psi_bound_var,	1,	"psi_bound_var"}, 
	{&Thread::psi_body,	1,	"psi_body"}, 
	{&Thread::psi_check_binder,	0,	"psi_check_binder"}, 
	{&Thread::psi_get_var_name,	1,	"psi_get_var_name"}, 
	{&Thread::psi_set_var_name,	0,	"psi_set_var_name"}, 
	{&Thread::psi_set_object_variable_name,	0,	"psi_set_object_variable_name"}, 
	{&Thread::psi_freeze_term,	1,	"psi_freeze_term"}, 
	{&Thread::psi_thaw_term,	1,	"psi_thaw_term"}, 
	{&Thread::psi_collect_vars,	1,	"psi_collect_vars"}, 
	{&Thread::psi_call_predicate1,	0,	"psi_call_predicate1"}, 
	{&Thread::psi_increment,	1,	"psi_increment"}, 
	{&Thread::psi_decrement,	1,	"psi_decrement"}, 
	{&Thread::psi_name_vars,	1,	"psi_name_vars"}, 
	{&Thread::psi_get_unnamed_vars,	1,	"psi_get_unnamed_vars"}, 
	{&Thread::psi_global_state_lookup,	1,	"psi_global_state_lookup"}, 
	{&Thread::psi_global_state_set,	0,	"psi_global_state_set"}, 
	{&Thread::psi_global_state_increment,	1,	"psi_global_state_increment"}, 
	{&Thread::psi_global_state_decrement,	1,	"psi_global_state_decrement"}, 
	{&Thread::psi_get_dynamic_chain,	1,	"psi_get_dynamic_chain"}, 
	{&Thread::psi_threadID_goal,	1,	"psi_threadID_goal"}, 
	{&Thread::psi_tcp_host_to_ip_address,	1,	"psi_tcp_host_to_ip_address"}, 
	{&Thread::psi_tcp_host_from_ip_address,	2,	"psi_tcp_host_from_ip_address"}, 
	{&Thread::psi_get_msgstream_handle,	1,	"psi_get_msgstream_handle"}, 
	{&Thread::psi_thread_symbol,	0,	"psi_thread_symbol"}, 
	{&Thread::psi_load,	1,	"psi_load"}, 
	{&Thread::psi_is_free_in,	0,	"psi_is_free_in"}, 
	{&Thread::psi_pipe,	3,	"psi_pipe"}, 
	{&Thread::psi_env_getenv,	1,	"psi_env_getenv"}, 
	{&Thread::psi_env_putenv,	0,	"psi_env_putenv"}, 
	{&Thread::psi_signal_to_atom,	1,	"psi_signal_to_atom"}, 
	{&Thread::psi_strerror,	1,	"psi_strerror"}, 
	{&Thread::psi_icm_handles_equal,	0,	"psi_icm_handles_equal"}, 
	{&Thread::psi_icm_handles_qp_equal,	0,	"psi_icm_handles_qp_equal"}, 
	{&Thread::psi_uncurry,	1,	"psi_uncurry"}, 
	{&Thread::psi_get_line,	1,	"psi_get_line"}, 
	{&Thread::psi_ip_array_init,	0,	"psi_ip_array_init"}, 
	{&Thread::psi_copy_term,	1,	"psi_copy_term"}, 
	{&Thread::psi_buffer_set_domains_apart,	0,	"psi_buffer_set_domains_apart"}, 
	{&Thread::psi_copy_substitution,	1,	"psi_copy_substitution"}, 
	{&Thread::psi_copy_obvar_to_buffer_tail,	0,	"psi_copy_obvar_to_buffer_tail"}, 
	{&Thread::psi_stat_ip_table,	1,	"psi_stat_ip_table"}, 
	{&Thread::psi_set_stream_properties,	0,	"psi_set_stream_properties"}, 
	{&Thread::psi_get_stream_properties,	1,	"psi_get_stream_properties"}, 
	{&Thread::psi_set_std_stream,	0,	"psi_set_std_stream"}, 
	{&Thread::psi_thread_push_goal,	0,	"psi_thread_push_goal"}, 
	{&Thread::structuralUnifyTerm,	0,	"structuralUnifyTerm"}, 
	{&Thread::psi_not_free_in_nfi_simp,	0,	"psi_not_free_in_nfi_simp"}, 
	{&Thread::psi_require_nfi_simp,	0,	"psi_require_nfi_simp"}, 
	{&Thread::psi_fast_simplify,	1,	"psi_fast_simplify"}, 
	{&Thread::psi_gmtime,	0,	"psi_gmtime"}, 
	{&Thread::psi_localtime,	0,	"psi_localtime"}, 
	{&Thread::psi_equal_equal,	0,	"psi_equal_equal"}, 
	{&Thread::psi_simplify_term,	1,	"psi_simplify_term"}, 
	{&Thread::psi_is_not_free_in,	0,	"psi_is_not_free_in"}, 
	{&Thread::psi_put_line,	0,	"psi_put_line"}, 
	{&Thread::psi_icm_symbolic_address_to_icm_handle,	1,	"psi_icm_symbolic_address_to_icm_handle"}
};
pseudo_instr3_data pseudo_instr3_array[] =
{
	{&Thread::psi_functor,	0,	"psi_functor"}, 
	{&Thread::psi_arg,	1,	"psi_arg"}, 
	{&Thread::psi_add,	1,	"psi_add"}, 
	{&Thread::psi_subtract,	1,	"psi_subtract"}, 
	{&Thread::psi_compare_var,	1,	"psi_compare_var"}, 
	{&Thread::psi_compare_atom,	1,	"psi_compare_atom"}, 
	{&Thread::psi_fast_equal,	1,	"psi_fast_equal"}, 
	{&Thread::psi_stat_choice,	3,	"psi_stat_choice"}, 
	{&Thread::psi_stat_global,	3,	"psi_stat_global"}, 
	{&Thread::psi_stat_local,	3,	"psi_stat_local"}, 
	{&Thread::psi_stat_binding_trail,	3,	"psi_stat_binding_trail"}, 
	{&Thread::psi_stat_code,	7,	"psi_stat_code"}, 
	{&Thread::psi_stat_string,	7,	"psi_stat_string"}, 
	{&Thread::psi_get_next_clause,	3,	"psi_get_next_clause"}, 
	{&Thread::psi_icm_register,	0,	"psi_icm_register"}, 
	{&Thread::psi_set_domain,	0,	"psi_set_domain"}, 
	{&Thread::psi_set_range,	0,	"psi_set_range"}, 
	{&Thread::psi_get_domain,	1,	"psi_get_domain"}, 
	{&Thread::psi_get_range,	1,	"psi_get_range"}, 
	{&Thread::psi_build_sub_term,	1,	"psi_build_sub_term"}, 
	{&Thread::psi_get_opcode,	4,	"psi_get_opcode"}, 
	{&Thread::psi_get_const,	4,	"psi_get_const"}, 
	{&Thread::psi_get_number,	4,	"psi_get_number"}, 
	{&Thread::psi_get_address,	4,	"psi_get_address"}, 
	{&Thread::psi_get_offset,	4,	"psi_get_offset"}, 
	{&Thread::psi_get_pred,	4,	"psi_get_pred"}, 
	{&Thread::psi_get_entry,	5,	"psi_get_entry"}, 
	{&Thread::psi_copy_to_buffer_tail,	0,	"psi_copy_to_buffer_tail"}, 
	{&Thread::psi_concat_atom3,	1,	"psi_concat_atom3"}, 
	{&Thread::psi_record_record_first,	1,	"psi_record_record_first"}, 
	{&Thread::psi_record_record_last,	1,	"psi_record_record_last"}, 
	{&Thread::psi_open,	1,	"psi_open"}, 
	{&Thread::psi_get_atom_from_atom_table,	1,	"psi_get_atom_from_atom_table"}, 
	{&Thread::psi_symtype,	1,	"psi_symtype"}, 
	{&Thread::psi_access,	1,	"psi_access"}, 
	{&Thread::psi_read_next_token,	3,	"psi_read_next_token"}, 
	{&Thread::psi_encoded_write,	0,	"psi_encoded_write"}, 
	{&Thread::psi_call_predicate2,	0,	"psi_call_predicate2"}, 
	{&Thread::psi_put_structure,	1,	"psi_put_structure"}, 
	{&Thread::psi_set_argument,	0,	"psi_set_argument"}, 
	{&Thread::psi_ip_setA,	0,	"psi_ip_setA"}, 
	{&Thread::psi_ip_lookupA,	1,	"psi_ip_lookupA"}, 
	{&Thread::psi_ipc_next,	2,	"psi_ipc_next"}, 
	{&Thread::psi_tcp_socket,	4,	"psi_tcp_socket"}, 
	{&Thread::psi_tcp_setsockopt,	0,	"psi_tcp_setsockopt"}, 
	{&Thread::psi_tcp_getsockopt,	1,	"psi_tcp_getsockopt"}, 
	{&Thread::psi_tcp_bind,	0,	"psi_tcp_bind"}, 
	{&Thread::psi_tcp_connect1,	0,	"psi_tcp_connect1"}, 
	{&Thread::psi_open_socket_stream,	1,	"psi_open_socket_stream"}, 
	{&Thread::psi_open_msgstream,	1,	"psi_open_msgstream"}, 
	{&Thread::psi_tcp_getsockname,	3,	"psi_tcp_getsockname"}, 
	{&Thread::psi_tcp_getpeername,	3,	"psi_tcp_getpeername"}, 
	{&Thread::psi_tcp_service_to_proto_port,	3,	"psi_tcp_service_to_proto_port"}, 
	{&Thread::psi_tcp_service_proto_to_port,	1,	"psi_tcp_service_proto_to_port"}, 
	{&Thread::psi_tcp_service_from_proto_port,	4,	"psi_tcp_service_from_proto_port"}, 
	{&Thread::psi_tcp_service_proto_from_port,	6,	"psi_tcp_service_proto_from_port"}, 
	{&Thread::psi_thread_fork,	0,	"psi_thread_fork"}, 
	{&Thread::psi_decompile,	1,	"psi_decompile"}, 
	{&Thread::psi_make_sub_from_buffer,	1,	"psi_make_sub_from_buffer"}, 
	{&Thread::psi_stat_object_trail,	3,	"psi_stat_object_trail"}, 
	{&Thread::psi_stat_ip_trail,	3,	"psi_stat_ip_trail"}, 
	{&Thread::psi_stat_tag_trail,	3,	"psi_stat_tag_trail"}, 
	{&Thread::psi_stat_scratchpad,	3,	"psi_stat_scratchpad"}, 
	{&Thread::psi_get_delays,	4,	"psi_get_delays"}, 
	{&Thread::psi_atom_concat2,	1,	"psi_atom_concat2"}, 
	{&Thread::psi_stat_ref_trail,	3,	"psi_stat_ref_trail"}, 
	{&Thread::psi_get_first_clause,	3,	"psi_get_first_clause"}, 
	{&Thread::psi_get_integer,	4,	"psi_get_integer"}, 
	{&Thread::psi_ipc_first,	1,	"psi_ipc_first"}, 
	{&Thread::psi_simplify_term3,	3,	"psi_simplify_term3"}
};
pseudo_instr4_data pseudo_instr4_array[] =
{
	{&Thread::psi_dynamic,	0,	"psi_dynamic"}, 
	{&Thread::psi_atom_search,	1,	"psi_atom_search"}, 
	{&Thread::psi_sub_atom,	1,	"psi_sub_atom"}, 
	{&Thread::psi_load_foreign,	0,	"psi_load_foreign"}, 
	{&Thread::psi_open_string,	1,	"psi_open_string"}, 
	{&Thread::psi_get_pred_from_pred_table,	7,	"psi_get_pred_from_pred_table"}, 
	{&Thread::psi_encoded_read,	6,	"psi_encoded_read"}, 
	{&Thread::psi_quantify,	0,	"psi_quantify"}, 
	{&Thread::psi_call_predicate3,	0,	"psi_call_predicate3"}, 
	{&Thread::psi_ipc_send,	0,	"psi_ipc_send"}, 
	{&Thread::psi_tcp_accept,	7,	"psi_tcp_accept"}, 
	{&Thread::psi_next_instr,	3,	"psi_next_instr"}, 
	{&Thread::psi_assert,	1,	"psi_assert"}, 
	{&Thread::psi_ccompile,	1,	"psi_ccompile"}, 
	{&Thread::psi_set_domains_apart,	0,	"psi_set_domains_apart"}, 
	{&Thread::psi_new_sub,	1,	"psi_new_sub"}
};
pseudo_instr5_data pseudo_instr5_array[] =
{
	{&Thread::psi_ipc_get_message,	22,	"psi_ipc_get_message"}, 
	{&Thread::psi_call_predicate4,	0,	"psi_call_predicate4"}, 
	{&Thread::psi_icm_handle_from_components,	1,	"psi_icm_handle_from_components"}, 
	{&Thread::psi_icm_handle_to_components,	30,	"psi_icm_handle_to_components"}
};
