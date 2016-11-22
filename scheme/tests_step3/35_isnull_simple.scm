;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="null? simple"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(null? #t)
(null? #f)
(null? 5)
(null? 5.36)
(null? ())
(null? 'x)
(null? #\f)
(null? "string")
(null? (cons 4 5))
(null? '(+ 4 5 6 9))
