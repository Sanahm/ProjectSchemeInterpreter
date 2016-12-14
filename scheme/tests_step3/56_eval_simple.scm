;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="simple eval"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(eval 4)
(define envt (interaction-environment))
(eval 4 envt)
(eval '(+ 4 5) envt)
