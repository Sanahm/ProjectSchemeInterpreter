;;;; En tete pour script de test ;;;;;;;;;;
; TEST_RETURN_CODE=PASS
; TEST_COMMENT="simple number to string"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(number->string 16565.55484)
(number->string 154.5254 2)
(number->string 154.5254 8)
(number->string 154.5254 16)
(number->string 154 8)
(number->string 154 16)
(number->string (/ 1 5))
(number->string (+ 1 5 4 ( - 5 1)))
(number->string (* 5 7 (/ 5 7)))
(number->string 5876 16)
(number->string (char->integer #\())
