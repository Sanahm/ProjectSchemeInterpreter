;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=FAIL
; TEST_COMMENT="evolved redefine function"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(define quote 8) ; quote
quote ; 8
(define if "string") ; if
if ; "string"
(define and 8) ; and
and ;8
(define or #\i) ; or
or ; #\i
(define begin #t) ; begin
begin ; #t
(set! begin "salut"); begin
begin ; "salut"
(define set! 77); set!
set! ; 77
(define define 42) ; define
define ; 42
(set! quote 8) ; 

