;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="boolean? simple"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(boolean? #t)
(boolean? #f)
(boolean? 5)
(boolean? 5.36)
(boolean? ())
(boolean? 'x)
(boolean? #\f)
(boolean? "string")
(boolean? (cons 4 5))
(boolean? '(+ 4 5 6 9))
