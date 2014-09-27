
main(_) ->
    {ok, Sock} = gen_udp:open(0, [binary]),
    {Command, A1, A2} = {1, 32768+200, 32768+200},
    gen_udp:send(
      Sock, {127, 0, 0, 1}, 6666, <<Command:16/big, A1:16/big, A2:16/big>>).
