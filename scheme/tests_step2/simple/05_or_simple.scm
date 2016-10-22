;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="simple or"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(or)
(or 1)
(or #f)
(or #f #t)
(or #f #f)
(or #t #f)
(or #f #f #f #f #f #t)
(or #f #f #f #f #f #f)
(or (or #f #f) #t)
(or (or #f #f) (or #t))
