;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="str2num et num2str"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(number->string (string->number "173"))
(number->string (string->number "121.227"))
(number->string (string->number "1010" 2))
(number->string (string->number "173" 8))
(number->string (string->number "abf" 16))
(string->number (number->string 19))
(string->number (number->string 19 8))
(string->number (number->string 19 16))
