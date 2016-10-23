;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="simple if"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(if #t (or #f #f 1) 3)
(if #f (or #f #f 1) 3)
(if #t (and #f #f 1) 3)
(if #f (and #f #f 1) (or))
(if (if #t (or #f #f 1) 3) #t #f)
(if (if #t (or #f #f 1) 3) (if #f (and #f #f 1) (or)) )
(if (if (if #t (or #f #f 1) 3) (if #f (and #f #f 1) (or)) ) 3 #t)

