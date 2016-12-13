;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="resolution d'equation du second ordre"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(define = (lambda (x y) (if (and (>= x y) (<= x y)) #t #f)))
(define zero? (lambda (x) (if (= x 0) #t #f)))
(define delta (lambda ( a b c ) (sqrt (- (* b b) (* 4 a c)))))
(define solve2 (lambda ( a b c ) (if (zero? a) (if (zero? b) #f (if (zero? c) 0 (- (/ c b)))) (cons (/ (- (- b) (delta a b c) ) (* 2 a)) (/ (+ (- b) (delta a b c) ) (* 2 a)) ) ) ) ) ;resolution d'equation polynomiale de second ordre.
(solve2 1 0 -1)
(solve2 1 -2 1)
(solve2 1 0 1)
