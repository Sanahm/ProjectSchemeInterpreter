;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="evolved and"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(and #f (something wrong)) ; #f
(and #t (define x 5)) ; x
x ; 5
(and #t 'salut) ;salut 
(and #t ''salut)  ; (quote salut)
(and #t #t #t #t #t #t (or #f (define x 6))) ; x
x ; 6
(and (and (and (and #t)))) ; #t
(and #t (if #t 5 6)) ; 5
