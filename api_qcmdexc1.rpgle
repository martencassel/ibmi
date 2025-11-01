**FREE
//---------------------------------------------------------------
//   Example program: API_QCMDEXC1
//   Purpose: Demonstrates calling the QCMDEXC API to run a CL command
//   Documentation:
//   https://www.ibm.com/docs/en/i/7.5.0?topic=apis-qcmdexc-program
//----------------------------------------------------------------*/
// Run in its own activation group, not the default one
ctl-opt dftactgrp(*no) actgrp(*new);

// Prototype for the QCMDEXC API (runs a CL command)
// cmdString = command text
// cmdLength = length of the command string
dcl-pr QCMDEXC extpgm('QCMDEXC');
   cmdString char(300);
   cmdLength packed(15:5);
end-pr;

// Working variables
dcl-s cmd char(300);          // Holds the command text
dcl-s cmdLen packed(15:5);    // Holds the length of the command text

// Build the command string
cmd = 'DSPLIBL';               // CL command: Display Library List
cmdLen = %len(%trimr(cmd));    // Calculate actual length of the string

// Call QCMDEXC to run the command
QCMDEXC(cmd: cmdLen);

// End the program cleanly
*inlr = *on;
return;
