% consumer.ql
% A simple example of using Elvin communication. See producer.ql
% 

% Start the consumer - simply connect to the elvin server elvin://localhost
% and add a notification that looks for messages from the producer
start :-
    elvin_connect(connect('elvin://localhost')),   
    elvin_add_subscription('from == "producer"'),
    message_loop.

% Start a loop waiting for messages and display them on stdout - exit
% when a message with a quit field arrives

message_loop :-
    repeat,
    M <<- _,       % get the first message
    write(M), nl,
    member(quit = _, M).


