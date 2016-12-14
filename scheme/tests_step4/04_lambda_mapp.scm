;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="lambda calcul procedure map"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define (mapp proc items) (if (null? items) '() (cons (proc (car items)) (mapp proc (cdr items)))))

(mapp sqrt '(1 4 9 16))
(define mul2 (lambda (x) (* 2 x)))
(map mul2 '(1 2 3 4))
(define tp (lambda ( x ) (sqrt ((lambda (y) (* y y)) x))))
(map tp '(1 4 9 16))
(map mul2 (list 1 2 3 4))
