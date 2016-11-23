;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=FAIL
; TEST_COMMENT="fail set-cdr! set_car!"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define x (list 4 5 8))
(define y 5)
(set-car! x "string")
(set-cdr! x #t 7)
(set-car! x 9)
(set-cdr! y 8)
