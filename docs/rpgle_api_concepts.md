## "Functional interface supplied by the operating system or a separately orderable licensed program”

On IBM i, that “interface” might be a

- *PGM (program object like QCMDEXC)
- *SRVPGM (service program procedure like CEEDOD).

Both are “supplied by the OS or licensed program.”

## "Allows an application program written in a high‑level language"

Your RPGLE program (or COBOL, C, CL, etc.) is the “application program.”

## "To use specific data or functions of the operating system or the licensed program"

 Instead of writing your own code to, say, display the library list, list jobs, or convert dates, you call the API. The API gives you direct access to those OS functions.

## Some APIs are delivered as programs (*PGM) you can call.
## Others are delivered as procedures in service programs (*SRVPGM) you bind to.
## Either way, they are “functional interfaces” that let your RPGLE code tap into the operating system’s capabilities.
