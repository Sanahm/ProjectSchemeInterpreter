;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="lambda calcul ajout en fin de liste"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (longueur L)(if (pair? L)(+ 1 (longueur (cdr L)))0))
(longueur (list 1 2))
(longueur (list 1 2 3 4))
(longueur (list 1 2 3 '(4 6)))
(longueur (list))
