**FREE
ctl-opt dftactgrp(*no) actgrp(*new);

 // --- Declarations ---
dcl-s num1       packed(7:2) inz(100.00);
dcl-s num2       int(10)     inz(25);
dcl-s negVal     packed(7:2);
dcl-s posVal     int(10);
dcl-s sum        packed(9:2);
dcl-s diff       packed(9:2);
dcl-s prod       packed(9:2);
dcl-s quot       packed(9:2);
dcl-s power      packed(9:2);
dcl-s today      date        inz(*sys);
dcl-s nextWeek   date;
dcl-s firstName  char(10)    inz('Marten');
dcl-s lastName   char(10)    inz('Lind');
dcl-s fullName   char(25);
dcl-s flag1      ind         inz(*on);
dcl-s flag2      ind         inz(*off);
dcl-s resultInd  ind;


return;
