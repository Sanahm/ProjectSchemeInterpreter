;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="char? simple"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(char? #t)
(char? #f)
(char? 5)
(char? 5.36)
(char? ())
(char? 'x)
(char? #\f)
(char? "string")
(char? (cons 4 5))
(char? '(+ 4 5 6 9))
