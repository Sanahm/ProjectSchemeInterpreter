;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="simple char to integer"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(char->integer  #\4)
(char->integer  #\a)
(char->integer  #\A)
(char->integer  #\z)
(char->integer  #\w)

