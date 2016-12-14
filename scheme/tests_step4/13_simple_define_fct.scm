;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="define fonction"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (mul2 x) (* 2 x))
(mul2 4)
(define (recur debut fin) (define debut (* debut fin)) (if (< fin debut) debut (recur debut fin)))
(recur 0.1 9)
(define pwr2 (lambda (num) (* num num)))
(pwr2 3)
