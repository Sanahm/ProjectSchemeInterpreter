;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="evolved if"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(if (define x 5) #f #t) ; #f
x ; 5
(if (set! x 9) (or #f (or #f #t)) (and #t (and #t #f))) ; #t
x ; 9
(if #f (or #f (or #f #t)) (and #t (and #t #f))) ; #f
(if #f (set! x 8) 9) ; 9
x ;9
(if 'salut 'salut2 'salut3) ; salut2

