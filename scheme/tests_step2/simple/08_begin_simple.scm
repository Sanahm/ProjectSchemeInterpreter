;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="simple begin"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(begin 1 2 3)
(begin 1 2 3 #t)
(begin 1 2 3 (and #t #f))
(begin 1 2 3 (or #t #f))
(begin 1 2 3 (and #t #f) (if #t (or #f #f 1) 3))
(begin )

