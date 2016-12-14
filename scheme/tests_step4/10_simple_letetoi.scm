;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="let etoile"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(let ((x 2)(y 3)) (let* ((x 7)(z (+ x y))) (* z x)))
(let* ((x 5)(z x)) (+ x z))
(let* () (+ 5 5))


