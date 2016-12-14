;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="lambda calcul dupliquer une liste"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (duplicata L) (if (pair? L) (cons (car L) (duplicata (cdr L))) (list)) )
(duplicata '(1 2))
(duplicata '(1 2 3))
(duplicata '())
(duplicata '(1 (1 2)))
