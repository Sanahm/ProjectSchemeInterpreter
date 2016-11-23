;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="cons simple"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(cons 4 5)
(cons (list 4 7) 8)
(cons "string" (list #t #\d))
(cons (list 7.2 78) (list "salut" 2))
(cons 5 ())
(cons () ())
(cons () "string")
