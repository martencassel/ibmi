**free
CTL-OPT MAIN(sayHello) OPTION(*SRCSTMT);
DCL-PROC sayHello;
DCL-PI *N EXTPGM;
 name CHAR(10) CONST;
END-PI;
DSPLY ('Hello ' + name);
END-PROC;
