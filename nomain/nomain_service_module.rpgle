**free
// NOMAIN service module example
// This source compiles into a *MODULE, then into a *SRVPGM.
// It provides reusable procedures for other programs.

ctl-opt nomain dftactgrp(*no);

// Add two integers
dcl-proc AddNumbers export;
   dcl-pi *n int(10);
      a int(10);
      b int(10);
   end-pi;
   return a + b;
end-proc;

// Convert a string to uppercase
dcl-proc ToUpper export;
   dcl-pi *n varchar(100);
      input varchar(100);
   end-pi;
   return %upper(input);
end-proc;

// Display a greeting
dcl-proc SayHello export;
   dsply 'Hello from the service module!';
end-proc;
