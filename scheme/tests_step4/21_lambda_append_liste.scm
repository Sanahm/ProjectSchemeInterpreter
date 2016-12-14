;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="lambda calcul fonction append"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (append_p L1 L2) (if (pair? L1) (cons (car L1) (append_p (cdr L1) L2)) L2))
(append_p '(1 2) '())
(append_p '(1 2) '(3 4))
(append_p '(1 2) '(3 4 "g"))
(append_p '(1 2) '(3 4 x))
