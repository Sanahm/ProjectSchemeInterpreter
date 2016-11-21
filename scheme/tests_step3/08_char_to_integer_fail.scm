;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=FAIL
; TEST_COMMENT="simple char to integer fail"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


(char->integer )
(char->integer  1)
(char->integer  a)
(char->integer  1 2 3)
(char->integer (1 2))
