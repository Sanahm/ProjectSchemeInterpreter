;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=FAIL
; TEST_COMMENT="fail eval"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(eval 4)
(define envt (interaction-environment))
(eval 4 87)
(eval 4 envt envt)

