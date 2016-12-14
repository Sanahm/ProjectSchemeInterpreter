;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="lambda calcul procedure map, le vrai"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(map + '(1 2) '(3 4) '(5 6))
(map - '(1 2 3 4))
(map - '(1 2) '(1 2))
(define mul3 (lambda (x) (* 3 x)))
(map mul3 '(1 2 3))
(map string->number '("0" "01" "10" "11"))
(map string->number '("a" "101" "111" "110") '(16 2 8 10))
