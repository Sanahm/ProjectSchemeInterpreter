;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="simple string to number"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(string->number "1255")
(string->number "125.6595")
(string->number "125.6595" 2)
(string->number "125" 2)
(string->number "125" 8)
(string->number "125" 16)
(string->number "ae5" 16)
(string->number "100110" 2)
(string->number "2457" 8)
(string->number "f25" 16)
