;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="pair? simple"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(pair? #t)
(pair? #f)
(pair? 5)
(pair? 5.36)
(pair? ())
(pair? 'x)
(pair? #\f)
(pair? "string")
(pair? (cons 4 5))
(pair? '(+ 4 5 6 9))
