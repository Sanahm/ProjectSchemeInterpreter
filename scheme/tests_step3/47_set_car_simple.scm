;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="set-car! simple"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define x (list 4 5 6 9))
(set-car! x "string")
x
(set-car! x (list "string" #t))
x
(set-car! x (cons 8 #f))
x
