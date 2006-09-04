--------------------------------------------------------------------------------
Porting cinit to other operating systems,
Nico Schottelius, 2005-06-02
--------------------------------------------------------------------------------

cinit is currently Linux-specific.

It currently does not compile / work on other Unices, because
we use O_ASYNC flag of open(2) which is _not_ a standard.

This way we can act very elegant on incoming connections by our
forks. If somebody finds a at least as elegant solution
to act on incoming data which is more portable, I would
be happy to recieve a diff -u.

Additionally we currently do mount a temporarily filesystem
on /etc/cinit/tmp, which allows us to create a socket, where
nothing is mounted r/w yet.

If a Unix has some kind of tmpfs, this can easily be changed
to the appropriate value in conf/*tmp*.

The O_ASYNC thing will perhaps become a compile option to cinit
(via conf/socket_function for instance), so that using standard
mechanism will be possible.
