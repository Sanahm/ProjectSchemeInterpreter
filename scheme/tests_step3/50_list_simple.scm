;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="list simple"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(list 4 5 6 9)
(list 4 5 6 (cons 7 8))
(list "string" 'x #\t)
(list ())
(list)
