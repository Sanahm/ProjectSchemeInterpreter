;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="lambda calcul primitive somme element liste"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (somme L) (if (null? L) 0 (+ (car L) (somme (cdr L)))))
(somme '())
(somme '(1 2 3))
(somme '(4 5))
