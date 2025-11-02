**FREE
ctl-opt option(*srcstmt) dftactgrp(*no);

/* ---------------------------------------------------
   Prototype for QUSRJOBI (Retrieve Job Information)
   --------------------------------------------------- */
dcl-pr QUSRJOBI extpgm('QUSRJOBI');
   rcvVar     char(5000);                  // Receiver variable
   rcvVarLen  int(10)   const;             // Length of receiver variable
   formatName char(8)   const;             // Format name (e.g. 'JOBI0100')
   jobName    char(26)  const;             // Job name/user/number
   intJobId   char(16)  const options(*nopass); // Internal job ID (optional)
   errorCode  char(32);                    // Error code structure
end-pr;

/* ---------------------------------------------------
   Data structures for returned info and error code
   --------------------------------------------------- */
dcl-ds jobi0100 qualified;
   bytesReturned int(10);
   bytesAvail    int(10);
   jobName       char(10);
   userName      char(10);
   jobNumber     char(6);
   jobStatus     char(10);
   jobType       char(1);
   jobSubtype    char(1);
   reserved      char(2);
end-ds;

dcl-ds errorCode qualified;
   bytesProv int(10) inz(%size(errorCode));
   bytesAvail int(10) inz(0);
   exceptionId char(7);
   reserved    char(1);
end-ds;

/* ---------------------------------------------------
   Main procedure
   --------------------------------------------------- */
dcl-proc main;
   dcl-pi *n end-pi;

   // Call QUSRJOBI for the current job (*)
   QUSRJOBI(jobi0100: %size(jobi0100): 'JOBI0100': '*': : errorCode);

   // Display some returned fields
   dsply ('Job: ' + %trim(jobi0100.jobName) +
          ' User: ' + %trim(jobi0100.userName) +
          ' Number: ' + %trim(jobi0100.jobNumber));

end-proc;
