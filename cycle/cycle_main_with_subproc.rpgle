**free
// A cycle-main program that also calls a subprocedure.
// The cycle-main is implicit: code here is the main procedure.

ctl-opt dftactgrp(*no) actgrp(*new);

dsply 'Hello from cycle-main!';
AnotherProc();   // Call the subprocedure
*inlr = *on;     // End program

// Define a regular subprocedure
dcl-proc AnotherProc;
   dsply 'Hello from subprocedure!';
end-proc;
