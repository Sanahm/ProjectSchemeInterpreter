;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="lambda calcul"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define pow2 (lambda (x) (* x x)))
(pow2 2)
(define norme3 (lambda (x y z) (sqrt (+ (pow2 x) (pow2 y) (pow2 z)))))
(norme3 3 6 6)
(define fabs (lambda (x) (if (< x 0) (- x) x)))
(fabs -5)
(fabs 7)
(define = (lambda (x y) (if (and (>= x y) (<= x y)) #t #f)))
(= 7 -7)
(= 7 7)
(= 0 0)
