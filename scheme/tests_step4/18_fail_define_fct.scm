;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=FAIL
; TEST_COMMENT="fail define fonction"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (mul2 x ) (* x 2))
(mul2 2)
(define mul2 x (* x 2))
(define (mul 2 (* x 8)) (* x 2))

