**free
// A basic linear-main program.
// Demonstrates ctl-opt main(...) and one main procedure.

ctl-opt main(MainProc) dftactgrp(*no) actgrp(*new);

dcl-proc MainProc;
   dsply 'Hello from linear-main!';
   *inlr = *on;   // End the program
end-proc;
