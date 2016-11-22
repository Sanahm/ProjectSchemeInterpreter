;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="list? simple"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(list? #t)
(list? #f)
(list? 5)
(list? 5.36)
(list? ())
(list? 'x)
(list? #\f)
(list? "string")
(list? (cons 4 5))
(list? '(+ 4 5 6 9))
