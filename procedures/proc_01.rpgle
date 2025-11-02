**free
CTL-OPT OPTION(*SRCSTMT) DFTACTGRP(*no);

DCL-PR SayHello;
   name CHAR(10) CONST;
END-PR;

SayHello('World');

*inlr = *on;
return;

DCL-PROC SayHello;
   DCL-PI SayHello;
      name CHAR(10) CONST;
   END-PI;

   DSPLY ('Hello ' + name);
END-PROC;

