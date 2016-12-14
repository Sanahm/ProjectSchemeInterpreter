;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="factorial"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define factorial (lambda (n) (if (= n 0) 1 (* n (factorial (- n 1))))))
(factorial 0)
(factorial 1)
(factorial 2)
(factorial 3)
(factorial 7)
