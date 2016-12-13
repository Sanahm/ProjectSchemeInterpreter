;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="lambda calcul"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define = (lambda (x y) (if (and (>= x y) (<= x y)) #t #f)))
(define zero? (lambda (x) (if (= x 0) #t #f)))
(zero? 0)
(zero? 7)
(define signe (lambda (x) (if (> x 0) 1 (if (zero? x) 0 -1))))
(signe -3)
(signe 9)
(signe 0)
(define naturel? (lambda (x) (and (integer? x) (>= x 0))))
(naturel? 35)
(naturel? -11)
