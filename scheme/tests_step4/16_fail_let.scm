;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=FAIL
; TEST_COMMENT="fail let"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(let ((x 5)) (+ x 5))
(let ((x 7)(z x) (+ 5 z x))
(let (()) (+ 5 5)
(let (+ 5 5))

