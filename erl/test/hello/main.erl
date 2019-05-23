-module(hello).
-compile(export_all).

hello() ->
	io:format("Hello, World!~n").
