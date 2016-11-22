;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="real? simple"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(real? #t)
(real? #f)
(real? 5)
(real? 5.36)
(real? ())
(real? 'x)
(real? #\f)
(real? "string")
(real? (cons 4 5))
(real? '(+ 4 5 6 9))
