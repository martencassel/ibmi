**free
ctl-opt dftactgrp(*no) actgrp(*new);

dcl-s num1    packed(7:2) inz(100.00);
dcl-s num2    int(10) inz(25);
dcl-s negVal   packed(7:2);
dcl-s posVal   int(10);
dcl-s flag    ind inz('1');
dcl-s result   ind;

// --- Unary minus: numeric → numeric
negVal = -num1;        // 100.00 → -100.00

// --- Unary plus: numeric -> numeric
posVal = +num2;        // 25 → 25 (no change, just enforces numeric)

// --- Logical NOT: indicator -> indicator
result = not flag;     // *ON -> *OFF


// Display results
dsply ('Unary Minus Result: ' + %char(negVal));
dsply ('Unary Plus Result: ' + %char(posVal));
dsply ('NOT flag: ' + %char(result));

result = *on;
dsply ('Final Result: ' + %char(result));

return;
