;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="simple tanh"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(tanh pi)
(tanh (- pi))
(tanh 1.0)
(tanh -1.0)
(tanh 1)
(tanh -1)
(tanh (/ pi 2))
(tanh (/ pi (- 2)))
(tanh 123456)
(tanh 123456.654321)
