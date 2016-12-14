;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="lambda calcul primitive reverse"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (reverse_p L) (if (null? L) '() (append (reverse (cdr L)) (list (car L)))))
(reverse_p '())
(reverse_p '( 1 2 3))
(reverse_p '( 1 2 3 4 (5 6)))
