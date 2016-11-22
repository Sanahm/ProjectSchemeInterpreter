;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="symbol? simple"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(symbol? #t)
(symbol? #f)
(symbol? 5)
(symbol? 5.36)
(symbol? ())
(symbol? 'x)
(symbol? #\f)
(symbol? "string")
(symbol? (cons 4 5))
(symbol? '(+ 4 5 6 9))
