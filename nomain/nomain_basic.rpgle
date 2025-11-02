**free

// CRTRPGMOD MODULE(USER/HELLO) SRCFILE(USER/QRPGLESRC) OPTION(*EVENTF) DBGVIEW(*SOURCE) TGTRLS(*CURRENT)

// A basic NOMAIN module.
// Contains only subprocedures, no main procedure.
// Must be bound into another program or service program.
ctl-opt nomain;


dcl-proc AddNumbers export;
   dcl-pi *n int(10);
      a int(10);
      b int(10);
   end-pi;
   return a + b;
end-proc;

dcl-proc SayHello export;
   dsply 'Hello from NOMAIN module!';
end-proc;
