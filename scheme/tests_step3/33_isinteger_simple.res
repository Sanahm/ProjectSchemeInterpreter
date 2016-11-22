;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="integer? simple"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(integer? #t)
(integer? #f)
(integer? 5)
(integer? 5.36)
(integer? ())
(integer? 'x)
(integer? #\f)
(integer? "string")
(integer? (cons 4 5))
(integer? '(+ 4 5 6 9))
