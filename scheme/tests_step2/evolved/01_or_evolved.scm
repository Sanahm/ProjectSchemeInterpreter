;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="evolved or"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(or #t (something wrong)) ; #t
(or #f (define x 5)) ; x
x ; 5
(or #f 'salut) ;salut 
(or #f ''salut)  ; (quote salut)
(or #f #f #f #f #f #f (and (define x 6) #f)) ; #f
x ; 6
(or (or (or (or #f)))) ; #f
(or #f (if #t 5 6)) ; 5
