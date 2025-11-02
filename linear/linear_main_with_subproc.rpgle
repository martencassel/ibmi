**free
// Must specify DFTACTGRP(*NO) to allow subprocedures.
// Otherwise the compiler issues RNF1520: "The procedure cannot be defined with DFTACTGRP(*YES)".
ctl-opt main(MainProc) dftactgrp(*no) actgrp(*new);

dcl-proc MainProc;
   dsply 'Hello from linear-main!';
   AnotherProc();
   *inlr = *on;
end-proc;

dcl-proc AnotherProc;
   dsply 'Hello from AnotherProc!';
end-proc;
