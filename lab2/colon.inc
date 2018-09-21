%define lw 0

%macro colon 2
%%la: dq lw
db %1, 0
%2:
%define lw %%la
%endmacro

colon "colo", colo
dw 'colon rulez', 0

colon "reasons_to_live", reasons_to_live
db 0