;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="lambda calcul ajout en fin de liste"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (ajout-en-fin L x) (if (pair? L) (cons (car L) (ajout-en-fin (cdr L) x)) (list x)))
(define L (list 1 2 3))
L
(ajout-en-fin L 5)
(ajout-en-fin L '(5 6))
(ajout-en-fin L (ajout-en-fin L 5))
