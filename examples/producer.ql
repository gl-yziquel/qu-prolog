% producer.ql
% A simple example of using Elvin communication. The file consumer.ql 
% contains code for receiving notifications from the producer.
%

% Start the producer - simply connect to the elvin server elvin://localhost
start :-
    elvin_connect(connect('elvin://localhost')).

%% Note that the Elvin server can also be set up as a default server or with a scope to be
%% used with discovery. To set up the Elvin server you will need to edit elvind.conf
%% (possibly in /etc/elvind) to add a scope or to set it as default. After doing so
%% the following can also be used to connect
%%    elvin_connect(discover(scopename)).
%%    elvin_connect(default).

% send a notification - Msg is an ElvinTermList, 
% and from=producer is added to this
send(Msg) :-
    elvin_add_notification([from="producer"|Msg]).

