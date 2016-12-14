;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="count"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define count ((lambda (total) (lambda (increment) (set! total (+ total increment)) total )) 0 ))
(count 3)
(count 5)
(count 2.6)
