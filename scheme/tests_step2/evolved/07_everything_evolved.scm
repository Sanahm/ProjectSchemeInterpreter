;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="a lot of everything"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define variable (if #f (or #f #t) (and #t (begin 7 #t '"string")))) ; variable
variable ; "string"
