;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT=simple_set!
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define x1 5)
x1
(set! x1 6)
x1
(set! x1 "string")
x1
(set! x1 #\f)
x1
(set! x1 -462.52)
x1
(set! x1 #t)
x1

