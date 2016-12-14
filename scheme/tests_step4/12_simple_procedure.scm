;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="procedure?"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(procedure? +)
(procedure? sqrt)
(define (mul2 x) (* 2 x))
(procedure? mul2)
(procedure? 5)
