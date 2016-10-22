;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="simple and"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(and)
(and 1)
(and #f)
(and #f #t)
(and #f #f)
(and #t #f)
(and #f #f #f #f #f #t)
(and #f #f #f #f #f #f)
(and (and #f #f) #t)
(and (and #f #f) (and #t))
(and (and #t #t) (and #t))
(and (and #t #t 1) (and #t))
(and #\a)
(and 1.2 "hbd" #f)
(and 1.2 "hbd"  #\a #t)


