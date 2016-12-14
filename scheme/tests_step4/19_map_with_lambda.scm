;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="map with lambda"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (mul2 x) (* 2 x))
(define (map proc items) (if (null? items) '() (cons (proc (car items)) (map proc (cdr items)))))
mul2
(map mul2 '(1 2 3 4))
(map sqrt '(1 2 9 (* 4 4)))
