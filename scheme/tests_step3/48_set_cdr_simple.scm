;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="set-cdr! simple"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define x (list 4 5 6 9))
(set-cdr! x "string")
x
(set-cdr! x (list "string" #t))
x
(set-cdr! x (cons 8 #f))
x
