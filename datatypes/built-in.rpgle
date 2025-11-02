**free
ctl-opt dftactgrp(*no) actgrp(*new);

dcl-s num1 packed(7:2) inz(-123.45);
dcl-s str  char(20)    inz('   RPGLE Demo   ');
dcl-s today date       inz(*sys);
dcl-s ts   timestamp   inz(*sys);
dcl-s resN packed(9:2);
dcl-s resC char(30);

 // Numeric
resN = %abs(num1);
dsply ('%ABS(-123.45): ' + %char(resN));

resN = %int(123.99);
dsply ('%INT(123.99): ' + %char(resN));

resN = %sqrt(25);
dsply ('%SQRT(25): ' + %char(resN));

 // Date/Time
dsply ('%DATE(*SYS): ' + %char(today));
dsply ('%TIMESTAMP(*SYS): ' + %char(ts));

resN = %diff(%date('2025-12-31'): today: *days);
dsply ('%DIFF(Dec31 - Today): ' + %char(resN) + ' days');

 // String
resC = %trim(str);
dsply resC;

resC = %upper('abc');
dsply %char(resC);

resC = %subst('HelloWorld':6:5);
dsply %char(resC);

 // Bitwise
resN = %bitand(15:7);
dsply %char(resN);

*inlr = *on;
return;
