%
% router_monitor.ql
%
% A simple message monitor.
%
% Other processes can send messages to this process setting the reply-to
% address to the address of the real recipient.
% The monitor displays the message information and forwards the message on
% to the recipient.
%
main(_) :-
    router_monitor.

router_monitor :-
    repeat,
    ipc_recv(Msg, From, Reply),
    ( Msg == quit
      ->
        true
      ;
	From = FThread:FProcess@FMachine,
	Reply = RThread:RProcess@RMachine,
        write('Message: '), write(Msg),
        write_term_list([nl, wa('From: '), w(FThread), tab(3),
                         wa(FProcess), tab(3), wa(FMachine)]),
        write_term_list([nl, wa('To: '), w(RThread), tab(3),
                         wa(RProcess), tab(3), wa(RMachine)]),
        nl,
        ipc_send(Msg, Reply, From),
        fail
    ).

