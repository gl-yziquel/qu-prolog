main(_) :-
    router_monitor.

router_monitor :-
    repeat,
    ipc_recv(Msg, From, Reply),
    ( Msg == quit
      ->
        true
      ;
        icm_handle_to_components(FThread, FProcess, FMachine,
                                 _, From),
        icm_handle_to_components(RThread, RProcess, RMachine,
                                 _, Reply),
        nl,
        write('Message: '), write(Msg),
        write_term_list([nl, wa('From: '), w(FThread), tab(3),
                         wa(FProcess), tab(3), wa(FMachine)]),
        write_term_list([nl, wa('To: '), w(RThread), tab(3),
                         wa(RProcess), tab(3), wa(RMachine)]),
        ipc_send(Msg, Reply, From),
        fail
    ).

