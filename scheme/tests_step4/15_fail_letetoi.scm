;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=FAIL
; TEST_COMMENT="fail let etoile"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(let* ((z 5)(x z)) (+ x z))
(let* ((z (+ x 5))(x 8) (+ z x))
(let* (()) (+ 5 5))

