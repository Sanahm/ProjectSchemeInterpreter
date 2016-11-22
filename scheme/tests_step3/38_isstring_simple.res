;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="string? simple"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(string? #t)
(string? #f)
(string? 5)
(string? 5.36)
(string? ())
(string? 'x)
(string? #\f)
(string? "string")
(string? (cons 4 5))
(string? '(+ 4 5 6 9))
